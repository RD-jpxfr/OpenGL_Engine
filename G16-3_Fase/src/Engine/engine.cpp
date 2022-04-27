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

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace tinyxml2;

// Vector de grupos
vector<Group> groups;

//variable for color
float colorRatio = 0.0045;

//camera focus
float lx = 0.0f;
float ly = 0.0f;
float lz = 0.0f;

//camera
float camX = 00, camY = 247, camZ = 247;
int startX, startY, tracking = 0;
int alpha = 0, beta = 45, r = 350;



bool pause = false; //movement state
float t = 0; //time elapsed whilst not paused
float tp = 0; //time elapsed paused

bool trajectory = false; // render trajectory
float segments = 100.f; //number of segments per curve

// GLEW variables
GLuint *figures_buffers;

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
    glBegin(GL_LINE_LOOP);
    float pos[3];
    float deriv[3];
    for (int i = 0; i < segments; ++i) {
        getGlobalCatmullRomPoint(i / segments, pos, deriv, tt);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();

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
        glColor3f((*i).color.r * colorRatio, (*i).color.g * colorRatio, (*i).color.b * colorRatio);
        glBindBuffer(GL_ARRAY_BUFFER, figures_buffers[n]);
        glVertexPointer(3, GL_FLOAT, 0, 0);
        glDrawArrays(GL_TRIANGLES, 0, (*i).vertexCount);
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

    // represents order of figures
    int n = 0;
    for (vector<Group>::const_iterator i = groups.begin(); i != groups.end(); i++) {
        n = drawGroup(*i, n);
    }

    // End of frame
    glutSwapBuffers();
}

// put figure in a VBO and return the number of figures already in VBOs
int prepareFigures(vector<Model> modelos, int n) {
    for (vector<Model>::const_iterator i = modelos.begin(); i != modelos.end(); i++) {

        glBindBuffer(GL_ARRAY_BUFFER, figures_buffers[n]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (*i).coordenadas.size(), (*i).coordenadas.data(), GL_STATIC_DRAW);
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

    int n = 0;
    for (vector<Group>::const_iterator i = groups.begin(); i != groups.end(); i++) {
        n = prepareGroup((*i), n);
    }

    glPolygonMode(GL_FRONT, GL_LINE);

    glEnableClientState(GL_VERTEX_ARRAY);
}

void processKeys(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        lz -= 1;
        break;
    case '-':
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
    case ' ':
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
    case GLUT_KEY_UP:
        ly += 1.0f;
        break;
    case GLUT_KEY_DOWN:
        ly -= 1.0f;
        break;
    case GLUT_KEY_RIGHT:
        lx += 1.0f;
        break;
    case GLUT_KEY_LEFT:
        lx -= 1.0f;
        break;
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
    // Parsing do ficheiro XML
    parseXML(argv[1], groups);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Prepare data
    glewInit();
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