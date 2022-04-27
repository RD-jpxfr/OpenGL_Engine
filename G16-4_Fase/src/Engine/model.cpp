#include <iostream>
#include <vector>
#include "color.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLEW/glew.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
using namespace std;

class Model{
    public:
        string filename; //nome do file de pontos associado.
        string texture; //nome do file de texturas associado.
        float amb[4];
        float dif[4];
        float emis[4];
        int vertexCount;
        vector< float > coordenadas;
        vector <float> normais;
        vector <float> texCoords;
        GLuint texID;

        // Default Constructor
        Model::Model(string f, string text, Color c, bool e, vector<float> coord, vector<float> normies, vector<float> texs, GLuint id) {
            filename = f;
            texture = text;
            amb[0] = c.r * 0.15;
            amb[1] = c.g * 0.15;
            amb[2] = c.b * 0.15;
            amb[3] = c.a;
            dif[0] = c.r * 0.85;
            dif[1] = c.g * 0.85;
            dif[2] = c.b * 0.85;
            dif[3] = c.a;
            if (e) {
                emis[0] = c.r;
                emis[1] = c.g;
                emis[2] = c.b;
            }
            else {
                emis[0] = 0;
                emis[1] = 0;
                emis[2] = 0;
            }
            emis[3] = c.a;
            vertexCount = coord.size() / 3;
            coordenadas = coord;
            normais = normies;
            texCoords = texs;
            texID = id;
        }

        void Model::setImage(GLuint id) {
            texID = id;
        }

};