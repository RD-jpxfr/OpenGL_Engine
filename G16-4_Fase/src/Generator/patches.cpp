#include <iostream>
#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include "point.cpp"
#include "patch.cpp"
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

// calcular normal de dois vectores
void cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}

// Normalizar um vector
void normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

// calcular normal num ponto
void computeNormal(float* p1, float* p2, float* p3, float* n) {
    float u[3], v[3];

    u[0] = p2[0] - p1[0];
    u[1] = p2[1] - p1[1];
    u[2] = p2[2] - p1[2];

    v[0] = p3[0] - p1[0];
    v[1] = p3[1] - p1[1];
    v[2] = p3[2] - p1[2];

    normalize(u); normalize(v);

    cross(v, u, n);
    normalize(n);
}

// parse do file .patch
vector<Patch> parsePatch(string filename){
    ifstream infile(filename);

    int n = 0, nPatches; // Número de patches no file
    int nPoints;         // Número de pontos
    int index;           // Index
    float x, y, z;       // Coordenadas x, y, z dos pontos
    string temp, temp2;   //temp string
    
    // Vector de pontos temporario
    vector<Point> pontos;

    // Vector de patches a devolver
    vector<Patch> patches;

    // Ponto temporario
    Point p;

    // Numero de patches
    getline(infile, temp);
    nPatches = stoi(temp);

    // Indices para cada patch
    while (n < nPatches && getline(infile, temp)){
        // Patch p temporária
        Patch patch;

        //Separar tokens por , e adicionar ao vector de indices
        istringstream iss(temp);

        while(getline(iss, temp2, ',')){
            index = stoi(temp2);
            patch.indices.push_back(index);
        }

        //Adicionar patch ao vetor de patches
        patches.push_back(patch);
        
        //Incrementar variavel de ciclo
        n++;
    }

    //Reset da variável
    n = 0;
    
    // Numero de points
    getline(infile, temp);
    nPoints = stoi(temp); 

    while (n < nPoints && getline(infile, temp)){
        istringstream iss(temp);

        getline(iss, temp2, ',');
        x = stof(temp2);

        getline(iss, temp2, ',');
        y = stof(temp2);

        getline(iss, temp2, ',');
        z = stof(temp2);

        p = Point(x,y,z);
        pontos.push_back(p);

        n++;
    }

    // Iterar sobre as patches e ir buscar os pontos correspondentes
    for(auto& patch : patches){
        for(auto& index : patch.indices){
            patch.points.push_back(pontos[index]);
        }
    }

    return patches;
}

// Multiplicacao de uma matriz com uma matriz
void multMatrixMatrix(float* m1, float* m2, float* res) {

    for (int j = 0; j < 4; ++j) {
        for (int k = 0; k < 4; ++k) {
            res[j * 4 + k] = 0;
            for (int i = 0; i < 4; i++) {
                res[j * 4 + k] += m1[4 * j + i] * m2[i * 4 + k];
            }
        }
    }

}

// Multiplicacao de uma matriz com um vector
void multMatrixVector(float* m, float* v, float* res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

// Multiplicacao de um vector com um vector
void multVectorVector(float* m, float* v, float* res) {

    res[0] = 0;
    for (int k = 0; k < 4; ++k) {
        res[0] += v[k] * m[k];
    }

}

// Calcular o ponto da patch de Bezier dado um u e v
void getBezierPoint(float u, float v, vector<Point> points, float* pos) {

    // bezier matrix
    float m[4][4] = { {-1.0f,  3.0f, -3.0f,  1.0f},
                        { 3.0f, -6.f,  3.0f, 0.0f},
                        {-3.0f,  3.0f,  0.0f,  0.0f},
                        { 1.0f,  0.0f,  0.0f,  0.0f} };

    for (int i = 0; i < 3; i++)
    {
        float p[4][4] = { {points.at(0).p[i],  points.at(1).p[i], points.at(2).p[i],  points.at(3).p[i]},
                            { points.at(4).p[i], points.at(5).p[i],  points.at(6).p[i], points.at(7).p[i]},
                            {points.at(8).p[i],  points.at(9).p[i],  points.at(10).p[i], points.at(11).p[i]},
                            { points.at(12).p[i],  points.at(13).p[i],  points.at(14).p[i],  points.at(15).p[i]} };
        
        //cout << points.at(15).p[i] << endl;
        // Compute A = M * P
        float a[4][4];
        multMatrixMatrix(reinterpret_cast<float(&)[16]>(m), reinterpret_cast<float(&)[16]>(p), reinterpret_cast<float(&)[16]>(a));
        // Compute  B = A * Mt(igual a M)
        float b[4][4];
        multMatrixMatrix(reinterpret_cast<float(&)[16]>(a), reinterpret_cast<float(&)[16]>(m), reinterpret_cast<float(&)[16]>(b));


        float c[4];
        // Compute C = B * V
        float V[4] = { pow(v,3), pow(v,2), v, 1 };
        multMatrixVector(reinterpret_cast<float(&)[16]>(b), V, c);

        // Compute pos = U * C
        float U[4] = { pow(u,3), pow(u,2), u, 1 };
        multVectorVector(U, c, pos + i);
    }
}
