#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "../../lib/tinyxml2.h"
#include "parse.cpp"
#include "curves.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLEW/glew.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <IL/il.h>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace tinyxml2;

// Vector de grupos
vector<Group> groups;
vector<Light> lights;

//camera focus
float lx = 0.0f;
float ly = 0.0f;
float lz = 0.0f;

//camera
float camX = 00, camY = 247, camZ = 247;
int startX, startY, tracking = 0;
int alpha = 0, beta = 45, r = 350;

// array para anular emissao de luz dos modelos
float black[4] = { 0, 0, 0, 1 };
float red[4] = { 1, 0, 0, 1 };

bool pause = false; //movement state
float t = 0; //time elapsed whilst not paused
float tp = 0; //time elapsed paused

bool trajectory = false; // render trajectory
float segments = 100.f; //number of segments per curve

// GLEW variables | vertex | normal | texCoord
GLuint *figures_buffers, *normals_buffers, *texture_buffers;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio 
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 100000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderCatmullRomCurve(TranslateT tt) {

    // draw the curve using line segments - GL_LINE_LOOP
    //To get the points for the full curve call 'getGlobalCatmullRomPoint with gt in[0, 1[.
    glPushMatrix();
    float white[4] = { 0.5,0.5,0.5,1 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
    glBegin(GL_LINE_LOOP);
    float pos[3];
    float deriv[3];
    for (int i = 0; i < segments; ++i) {
        getGlobalCatmullRomPoint(i / segments, pos, deriv, tt);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
    glPopMatrix();
}

void translateCatmullRom(TranslateT tt) {

    // draw the trajectory
    if (trajectory)
        renderCatmullRomCurve(tt);


    float pos[3]; // vector para translacao
    float deriv[3]; // vector para rotacao
    getGlobalCatmullRomPoint(t / tt.time / 1000, pos, deriv, tt);
    
    float zi[3];
    cross(deriv, tt.y, zi);
    float yi[3];
    cross(zi, deriv, yi);
    float m[4 * 4];
    normalize(deriv);
    normalize(yi);
    normalize(zi);
    buildRotMatrix(deriv, yi, zi, m);
    

    glTranslatef(pos[0], pos[1], pos[2]);
    glMultMatrixf(m);

    tt.y[0] = yi[0];
    tt.y[1] = yi[1];
    tt.y[2] = yi[2];
}

// draw Models
int drawFigures(vector<Model> modelos, int n) {
    
    // desenhar as várias fíguras
    for (vector<Model>::const_iterator i = modelos.begin(); i != modelos.end(); i++) {
        // desenhar fígura
        glMaterialfv(GL_FRONT, GL_EMISSION, (*i).emis);
        glMaterialfv(GL_FRONT, GL_AMBIENT, (*i).amb);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, (*i).dif);

        glBindBuffer(GL_ARRAY_BUFFER, figures_buffers[n]);
        glVertexPointer(3, GL_FLOAT, 0, 0);

        glBindBuffer(GL_ARRAY_BUFFER, normals_buffers[n]);
        glNormalPointer(GL_FLOAT, 0, 0);

        glBindTexture(GL_TEXTURE_2D, (*i).texID);
        glBindBuffer(GL_ARRAY_BUFFER, texture_buffers[n]);
        glTexCoordPointer(2, GL_FLOAT, 0, 0);

        glDrawArrays(GL_TRIANGLES, 0, (*i).vertexCount);


        glMaterialfv(GL_FRONT, GL_EMISSION, black);
        glBindTexture(GL_TEXTURE_2D, 0);
        n++;
    }

    return n;
}

// draw group
int drawGroup(Group group, int n) {
    glPushMatrix();
    // Geometric Transformations
    for (vector<string>::const_iterator i = group.order.begin(); i != group.order.end(); i++) {
        // Translate
        if (*i == "T") {
            glTranslatef(group.trans.x, group.trans.y, group.trans.z);
        }
        // Rotate
        else if (*i == "R"){
            glRotated(group.rot.angle, group.rot.axisX, group.rot.axisY, group.rot.axisZ);
        }
        // Scale
        else if (*i == "S") {
            glScaled(group.scale.x, group.scale.y, group.scale.z);
        }
        // RotateT
        else if (*i == "RT") {
            glRotated(t/group.rotT.time*360.0f/1000, group.rotT.axisX, group.rotT.axisY, group.rotT.axisZ);
        }
        // TranslateT
        else if (*i == "TT") {
            translateCatmullRom(group.transT);
        }
    }
    // desenhar os modelos
    n = drawFigures(group.models, n);
    // desenhar sub-grupos se existirem
    for (vector<Group>::const_iterator i = group.subGroups.begin(); i != group.subGroups.end(); i++) {
        n = drawGroup(*i, n);
    }
    glPopMatrix();

    return n;
}

// choose light
GLenum gl_light(int number) {
    GLenum l[8] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };
    return l[number];
}

// start a "Point" Light
void pointLight(int id, Light l) {
    GLenum light = gl_light(id);
    glEnable(light);

    glLightfv(light, GL_POSITION, l.posicao);
    glLightfv(light, GL_AMBIENT, l.ambience);
    glLightfv(light, GL_DIFFUSE, l.defuse);
    //glLightf(light, GL_QUADRATIC_ATTENUATION, 0.25F);
    
}

// start a "Directional" Light
void directionalLight(int id, Light l) {
    GLenum light = gl_light(id);
    glEnable(light);

    //normalize(l.direcao);
    glLightfv(light, GL_POSITION, l.direcao);
    glLightfv(light, GL_AMBIENT, l.ambience);
    glLightfv(light, GL_DIFFUSE, l.defuse);
}

// start a "Spot" Light
void spotLight(int id, Light l) {
    GLenum light = gl_light(id);
    glEnable(light);

    glLightfv(light, GL_POSITION, l.posicao);
    glLightfv(light, GL_DIFFUSE, l.defuse);
    glLightfv(light, GL_SPOT_DIRECTION, l.direcao);
    glLightf(light, GL_SPOT_CUTOFF, 45.0);
    glLightf(light, GL_SPOT_EXPONENT, 0.0);
}

void renderScene(void) {

    if (pause)
        tp += glutGet(GLUT_ELAPSED_TIME) - t - tp;
    else
        t += glutGet(GLUT_ELAPSED_TIME) - t - tp;

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(camX, camY, camZ,
        lx, ly, lz,
        0.0f, 1.0f, 0.0f);

    glPushMatrix();
    glTranslatef(lx,ly,lz);
    glMaterialfv(GL_FRONT, GL_EMISSION, red);
    glutSolidSphere(0.0015 * r, 10, 10);;
    glMaterialfv(GL_FRONT, GL_EMISSION, black);
    glPopMatrix();
    
    
    int nl = 0;
    for (vector<Light>::const_iterator i = lights.begin(); i != lights.end(); i++) {
        if (!(*i).type.compare("POINT")) {
            pointLight(nl, *i);
        }
        else if (!(*i).type.compare("DIRECTIONAL")) {
            directionalLight(nl, *i);
        }
        else if (!(*i).type.compare("SPOT")) {
            spotLight(nl, *i);
        }
    }

    // represents order of figures
    int ng = 0;
    for (vector<Group>::const_iterator i = groups.begin(); i != groups.end(); i++) {
        ng = drawGroup(*i, ng);
    }

    // End of frame
    glutSwapBuffers();
}

// put figure in a VBO and return the number of figures already in VBOs
int prepareFigures(vector<Model> modelos, int n) {
    for (vector<Model>::const_iterator i = modelos.begin(); i != modelos.end(); i++) {

        glBindBuffer(GL_ARRAY_BUFFER, figures_buffers[n]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*i).coordenadas.size(), (*i).coordenadas.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, normals_buffers[n]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*i).normais.size(), (*i).normais.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, texture_buffers[n]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*i).texCoords.size(), (*i).texCoords.data(), GL_STATIC_DRAW);

        n++;
    }
    return n;
}

// put all the figures of a group in VBOs and return the number of figures already in VBOs
int prepareGroup(Group group, int n) {
 
    n = prepareFigures(group.models, n);

    // prepare all subgroups
    for (vector<Group>::const_iterator i = group.subGroups.begin(); i != group.subGroups.end(); i++) {
        n = prepareGroup(*i, n);
    }

    return n;
}

// number of Models/figures
int countModels(Group group) {
    int m;

    m = group.models.size();
    // count models in each subgroup
    for (vector<Group>::const_iterator i = group.subGroups.begin(); i != group.subGroups.end(); i++) {
        m += countModels(*i);
    }

    return m;
}

// put all the figures of the scene in VBOs
void prepareScene(void) {
    int m = 0;
    for (vector<Group>::const_iterator i = groups.begin(); i != groups.end(); i++) {
        m += countModels(*i);
    }

    figures_buffers = (GLuint*)malloc(sizeof(GLuint) * m);
    glGenBuffers(m, figures_buffers);

    normals_buffers = (GLuint*)malloc(sizeof(GLuint) * m);
    glGenBuffers(m, normals_buffers);
    
    texture_buffers = (GLuint*)malloc(sizeof(GLuint) * m);
    glGenBuffers(m, texture_buffers);

    int n = 0;
    for (vector<Group>::const_iterator i = groups.begin(); i != groups.end(); i++) {
        n = prepareGroup((*i), n);
    }


}

void initGL() {

    // alguns settings para OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glClearColor(0, 0, 0, 0);

    glEnable(GL_LIGHTING);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void processKeys(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        ly += 1.0f;
        break;
    case 's':
        ly -= 1.0f;
        break;
    case 'd':
        lx += 1.0f;
        break;
    case 'a':
        lx -= 1.0f;
        break;
    case 'e':
        lz -= 1;
        break;
    case 'q':
        lz += 1;
        break;
    case 'r':
        lx = 0;
        ly = 0;
        lz = 0;
        break;
    case '1':
        glPolygonMode(GL_FRONT, GL_LINE);
        break;
    case '2':
        glPolygonMode(GL_FRONT, GL_FILL);
        break;
    case '3':
        glPolygonMode(GL_FRONT, GL_POINT);
        break;
    case '4':
        if (trajectory)
            trajectory = false;
        else
            trajectory = true;
        break;
    case 'p':
        if (pause)
            pause = false;
        else
            pause = true;
        break;
    }
    glutPostRedisplay();
}

void processSpecialKeys(int keycode, int x, int y) {
    switch (keycode) {
    }
    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) {

    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else
            tracking = 0;
    }
    else if (state == GLUT_UP) {
        if (tracking == 1) {
            alpha += (xx - startX);
            beta += (yy - startY);
        }
        else if (tracking == 2) {

            r -= yy - startY;
            if (r < 3)
                r = 3.0;
        }
        tracking = 0;
    }
}

void processMouseMotion(int xx, int yy) {

    int deltaX, deltaY;
    int alphaAux, betaAux;
    int rAux;

    if (!tracking)
        return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {


        alphaAux = alpha + deltaX;
        betaAux = beta + deltaY;

        if (betaAux > 85.0)
            betaAux = 85.0;
        else if (betaAux < -85.0)
            betaAux = -85.0;

        rAux = r;
    }
    else if (tracking == 2) {

        alphaAux = alpha;
        betaAux = beta;
        rAux = r - deltaY;
        if (rAux < 3)
            rAux = 3;
    }
    camX = lx + rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camZ = lz + rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
    camY = ly + rAux * sin(betaAux * 3.14 / 180.0);
}

int main(int argc, char* argv[]){

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@Engine");

    // Prepare data
    glewInit();
    initGL();
    
    // Parsing do ficheiro XML
    parseXML(argv[1], groups, lights);
    prepareScene();

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();


    return 0;
}