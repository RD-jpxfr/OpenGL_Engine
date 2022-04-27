#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include "../../lib/tinyxml2.h"
#include "model.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace tinyxml2;

// Vector de modelos
vector<Model> modelos;

//variable for color
float colorRatio = 0.0045;

//camera movement
float cx = 5.0f;
float cy = 5.0f;
float cz = 5.0f;

//camera view sphere
float radius = 15;
float phi = M_PI / 6;
float theta = M_PI_4;

void readfile(string filename, vector<tuple<float, float, float>>& cord){
    ifstream infile(filename);
    
    float x, y, z;

    while (infile >> x >> y >> z){
        cord.push_back(make_tuple(x, y, z));
    }
}

void parseXML(char* fnome, vector<string>& filenames){
    // Load do file passado como argumento
    XMLDocument doc;
    doc.LoadFile(fnome);

    // ROOT <=> Scene
    XMLElement* root = doc.RootElement();

    // Primeiro model
    XMLElement* fnode = root->FirstChildElement("model");

    while(fnode){

        // Temp string holder
        const char* output;

        // Pega na componente file e guarda na temp string holder
        output = fnode->Attribute("file");

        // Envia o valor da temp sring holder para o vector de strings
        filenames.push_back(output);

        // Avança para o seguinte
        fnode = fnode->NextSiblingElement();
    }
}

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
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawFigure(void) {
    glBegin(GL_TRIANGLES);
    glColor3f(188.0f * colorRatio, 102.0f * colorRatio, 17.0f * colorRatio); //color -> dark orange
    
    for (vector<Model>::const_iterator i = modelos.begin(); i != modelos.end(); i++) {
        for (vector< tuple<float, float, float> >::const_iterator j = i->coordenadas.begin(); j != i->coordenadas.end(); j++) {
            glVertex3f(get<0>(*j), get<1>(*j), get<2>(*j));
        }
    }
    glEnd();
}

void sphericCoordinates() {
    cx = radius * cos(phi) * sin(theta);
    cy = radius * sin(phi);
    cz = radius * cos(phi) * cos(theta);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    sphericCoordinates();

    // set the camera
    glLoadIdentity();
    gluLookAt(cx, cy, cz,
        0.0, 0.0, 0.0,
        0.0f, 1.0f, 0.0f);

    // put the geometric transformations here
    glPolygonMode(GL_FRONT, GL_LINE);

    drawFigure();

    // End of frame
    glutSwapBuffers();
}

void reactKey(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        if (radius > 1)
            radius -= 0.1;
        break;
    case '-':
        radius += 0.1;
        break;
    }
    glutPostRedisplay();
}

void moveCamera(int keycode, int x, int y) {
    switch (keycode) {
    case GLUT_KEY_UP:
        if (phi < M_PI_2 - 0.05f)
            phi += 0.05f;
        break;
    case GLUT_KEY_DOWN:
        if (phi > -M_PI_2 + 0.05f)
            phi -= 0.05f;
        break;
    case GLUT_KEY_RIGHT:
        theta += 0.05f;
        break;
    case GLUT_KEY_LEFT:
        theta -= 0.05f;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    // Nomes dos files .3d
    vector<string> filenames;

    // Parsing do ficheiro XML
    parseXML(argv[1], filenames);

    for(vector<string>::const_iterator i = filenames.begin(); i != filenames.end(); i++){
        // Vector de coordenadas do modelo
        vector<tuple<float, float, float>> cord;

        // Le o file e atualiza o vector de coordenadas
        readfile(*i, cord);

        // Adiciona modelo ao vetor
        modelos.push_back(Model(*i, cord));
    }

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM");

    // Required callback registry 
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // put here the registration of the keyboard callbacks
    glutKeyboardFunc(reactKey);
    glutSpecialFunc(moveCamera);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();


    return 0;
}