#include <iostream>
#include <fstream>
#include <string>
#include "patches.cpp"
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


void coordenadasPlano(float x, float z, ofstream& file){

    //nº de vertices no modelo
    file << 6 + 6 << endl;

// Plano vista de cima 
//1st triangle
    //1st vertex
    file << x/2 << " " << 0 << " " << z/2 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 1 << " " << 1 << endl;
    //2nd vertex
    file << x/2 << " " << 0 << " " << -z/2 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 1 << " " << 0 << endl;
    //3rd vertex
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 0 << " " << 1 << endl;

//2nd triangle
    //1st vertex
    file << -x/2 << " " << 0 << " " << -z/2 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 0 << " " << 0 << endl;
    //2nd vertex
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 0 << " " << 1 << endl;
    //3rd vertex
    file << x/2 << " " << 0 << " " << -z/2 << endl;
    file << 0 << " " << 1 << " " << 0 << endl;
    file << 1 << " " << 0 << endl;

// Plano vista de Baixo
//1st triangle
    //1st vertex
    file << x/2 << " " << 0 << " " << z/2 << endl;
    file << 0 << " " << -1 << " " << 0 << endl;
    file << 1 << " " << 1 << endl;
    //2nd vertex
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    file << 0 << " " << -1 << " " << 0 << endl;
    file << 0 << " " << 1 << endl;
    //3rd vertex
    file << x/2 << " " << 0 << " " << -z/2 << endl;
    file << 0 << " " << -1 << " " << 0 << endl;
    file << 1 << " " << 0 << endl;

//2nd vertex
    //1st vertex
    file << -x/2 << " " << 0 << " " << -z/2 << endl;
    file << 0 << " " << -1 << " " << 0 << endl;
    file << 0 << " " << 0 << endl;
    //2nd vertex
    file << x/2 << " " << 0 << " " << -z/2 << endl;
    file << 0 << " " << -1 << " " << 0 << endl;
    file << 1 << " " << 0 << endl;
    //3rd vertex
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    file << 0 << " " << -1 << " " << 0 << endl;
    file << 0 << " " << 1 << endl;

}

void coordenadasBox(float x, float y, float z, int divisions, ofstream& file) {

    float xratio = x / divisions;
    float yratio = y / divisions;
    float zratio = z / divisions;

    //nº de vertices no modelo
    file << 6 * (int)pow(divisions, 2) * 6 << endl;

    //horizontal cima
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        //1st triangle
            //1st vertex
            file << -x / 2 + (i + 1) * xratio << " " << y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 0 << " " << 1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)1 - (1.0f / 3.0f) * (j + 1) / divisions << endl;
            //2nd vertex
            file << -x / 2 + (i + 1) * xratio << " " << y / 2 << " " << -z / 2 + j * zratio << endl;
            file << 0 << " " << 1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)1 - (1.0f / 3.0f) * j / divisions << endl;
            //3rd vertex
            file << -x / 2 + i * xratio << " " << y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 0 << " " << 1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)1 - (1.0f / 3.0f) * (j + 1) / divisions << endl;

        //2nd triangle
            //1st vertex
            file << -x / 2 + i * xratio << " " << y / 2 << " " << -z / 2 + j * zratio << endl;
            file << 0 << " " << 1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)1 - (1.0f / 3.0f) * j / divisions << endl;
            //2nd vertex
            file << -x / 2 + i * xratio << " " << y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 0 << " " << 1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)1 - (1.0f / 3.0f) * (j + 1) / divisions << endl;
            //3rd vertex
            file << -x / 2 + (i + 1) * xratio << " " << y / 2 << " " << -z / 2 + j * zratio << endl;
            file << 0 << " " << 1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)1 - (1.0f / 3.0f) * j / divisions << endl;
        }
    }

    //horizontal baixo
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        //1st triangle
            //1st vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 0 << " " << -1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) * (j + 1) / divisions << endl;
            //2nd vertex
            file << -x / 2 + i * xratio << " " << -y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 0 << " " << -1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) * (j + 1) / divisions << endl;
            //3rd vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 << " " << -z / 2 + j * zratio << endl;
            file << 0 << " " << -1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) * j / divisions << endl;

        //2nd triangle
            //1st vertex
            file << -x / 2 + i * xratio << " " << -y / 2 << " " << -z / 2 + j * zratio << endl;
            file << 0 << " " << -1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) * j / divisions << endl;
            //2nd vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 << " " << -z / 2 + j * zratio << endl;
            file << 0 << " " << -1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) * j / divisions << endl;
            //3rd vertex
            file << -x / 2 + i * xratio << " " << -y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 0 << " " << -1 << " " << 0 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) * (j + 1) / divisions << endl;
        }
    }

    //verticais frente
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        //1st triangle
            //1st vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << z / 2 << endl;
            file << 0 << " " << 0 << " " << 1 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * j / divisions << endl;
            //2nd vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + (j + 1) * yratio << " " << z / 2 << endl;
            file << 0 << " " << 0 << " " << 1 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (j + 1) / divisions << endl;
            //3rd vertex
            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << z / 2 << endl;
            file << 0 << " " << 0 << " " << 1 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (j + 1) / divisions << endl;

        //2nd triangle
            //1st vertex
            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << z / 2 << endl;
            file << 0 << " " << 0 << " " << 1 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (j + 1) / divisions << endl;
            //2nd vertex
            file << -x / 2 + i * xratio << " " << -y / 2 + j * yratio << " " << z / 2 << endl;
            file << 0 << " " << 0 << " " << 1 << endl;
            file << (float)0.25 + 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * j / divisions << endl;
            //3rd vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << z / 2 << endl;
            file << 0 << " " << 0 << " " << 1 << endl;
            file << (float)0.25 + 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * j / divisions << endl;
        }
    }

    //verticais trás
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        //1st triangle
            //1st vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << -z / 2 << endl;
            file << 0 << " " << 0 << " " << -1 << endl;
            file << (float)1 - 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * j / divisions << endl;
            //2nd vertex
            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << -z / 2 << endl;
            file << 0 << " " << 0 << " " << -1 << endl;
            file << (float)1 - 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (j + 1) / divisions << endl;
            //3rd vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + (j + 1) * yratio << " " << -z / 2 << endl;
            file << 0 << " " << 0 << " " << -1 << endl;
            file << (float)1 - 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (j + 1) / divisions << endl;

        //2nd triangle
            //1st vertex
            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << -z / 2 << endl;
            file << 0 << " " << 0 << " " << -1 << endl;
            file << (float)1 - 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (j + 1) / divisions << endl;
            //2nd vertex
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << -z / 2 << endl;
            file << 0 << " " << 0 << " " << -1 << endl;
            file << (float)1 - 0.25 * (i + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * j / divisions << endl;
            //3rd vertex
            file << -x / 2 + i * xratio << " " << -y / 2 + j * yratio << " " << -z / 2 << endl;
            file << 0 << " " << 0 << " " << -1 << endl;
            file << (float)1 - 0.25 * i / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * j / divisions << endl;
        }
    }

    //perfil direita
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        //1st triangle
            //1st vertex
            file << x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 1 << " " << 0 << " " << 0 << endl;
            file << (float)0.75 - 0.25 * (j + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * i / divisions << endl;
            //2nd vertex
            file << x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + j * zratio << endl;
            file << 1 << " " << 0 << " " << 0 << endl;
            file << (float)0.75 - 0.25 * j / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * i / divisions << endl;
            //3rd vertex
            file << x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
            file << 1 << " " << 0 << " " << 0 << endl;
            file << (float)0.75 - 0.25 * j / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (i + 1) / divisions << endl;

        //2nd triangle
            //1st vertex
            file << x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 1 << " " << 0 << " " << 0 << endl;
            file << (float)0.75 - 0.25 * (j + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (i + 1) / divisions << endl;
            //2nd vertex
            file << x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << 1 << " " << 0 << " " << 0 << endl;
            file << (float)0.75 - 0.25 * (j + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * i / divisions << endl;
            //3rd vertex
            file << x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
            file << 1 << " " << 0 << " " << 0 << endl;
            file << (float)0.75 - 0.25 * j / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (i + 1) / divisions << endl;
        }
    }

    //perfil esquerda
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
        //1st triangle
            //1st vertex
            file << -x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -1 << " " << 0 << " " << 0 << endl;
            file << (float)0.25 * (j + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * i / divisions << endl;
            //2nd vertex
            file << -x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
            file << -1 << " " << 0 << " " << 0 << endl;
            file << (float)0.25 * j / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (i + 1) / divisions << endl;
            //3rd vertex
            file << -x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + j * zratio << endl;
            file << -1 << " " << 0 << " " << 0 << endl;
            file << (float)0.25 * j / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * i / divisions << endl;

            //2nd triangle
                //1st vertex
            file << -x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -1 << " " << 0 << " " << 0 << endl;
            file << (float)0.25 * (j + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (i + 1) / divisions << endl;
            //2nd vertex
            file << -x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
            file << -1 << " " << 0 << " " << 0 << endl;
            file << (float)0.25 * j / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * (i + 1) / divisions << endl;
            //3rd vertex
            file << -x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -1 << " " << 0 << " " << 0 << endl;
            file << (float)0.25 * (j + 1) / divisions << " " << (float)(1.0f / 3.0f) + (1.0f / 3.0f) * i / divisions << endl;
        }
    }

}

void coordenadasSphere(float radius, int slices, int stacks, ofstream& file) {
    //angle gap for stacks
    float stackGap = M_PI / stacks;
    //angle gap for slices
    float sliceGap = 2 * M_PI / slices;

    //nº de vertices no modelo
    file << 6 * slices * (stacks - 2) + 3 * slices * 2 << endl;

    int i;
    //for every stack except the top and bottom
    for (i = 1; i < stacks - 1; i++) {


        for (int j = 0; j < slices; j++)
        {
        //1st triangle
            //1st vertex
            file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * j) << endl;
            file << cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * j) << " " << sin(-(M_PI / 2) + stackGap * i) << " " <<  cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * j) << endl;
            file << (float)j / slices << " " << (float)i / stacks << endl;
            //2nd vertex
            file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
            file << cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << sin(-(M_PI / 2) + stackGap * i) << " " << cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
            file << (float)(j + 1) / slices << " " << (float)i / stacks << endl;
            //3nd vertex
            file << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * j) << endl;
            file << cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * j) << " " << sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * j) << endl;
            file << (float)j / slices << " " << (float)(i + 1) / stacks << endl;

        //2nd triangle
            //1st vertex
            file << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * (j + 1)) << endl;
            file << cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * (j + 1)) << " " << sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * (j + 1)) << endl;
            file << (float)(j + 1) / slices << " " << (float)(i + 1) / stacks << endl;
            //2nd vertex
            file << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * j) << endl;
            file << cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * j) << " " << sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * j) << endl;
            file << (float)j / slices << " " << (float)(i + 1) / stacks << endl;
            //3rd vertex
            file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
            file << cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << sin(-(M_PI / 2) + stackGap * i) << " " << cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
            file << (float)(j + 1) / slices << " " << (float)i / stacks << endl;
        }

    }

    //for the top and bottom stack
    for (int j = 0; j < slices && stacks > 1; j++)
    {
    //top stack
        //1st vertex
        file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * j) << endl;
        file << cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * j) << " " << sin(-(M_PI / 2) + stackGap * i) << " " << cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * j) << endl;
        file << (float)j / slices << " " << (float)i / stacks << endl;
        //2nd vertex
        file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
        file << cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << sin(-(M_PI / 2) + stackGap * i) << " " << cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
        file << (float)(j + 1) / slices << " " << (float)i / stacks << endl;
        //3rd vertex
        file << 0 << " " << radius << " " << 0 << endl;
        file << 0 << " " << 1 << " " << 0 << endl;
        file << (float)(j + 0.5f) / slices << " " << (float)i / stacks << endl;

    //bottom stack
        //1st vertex
        file << radius * cos(-(M_PI / 2) + stackGap) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap) << " " << radius * cos(-(M_PI / 2) + stackGap) * cos(sliceGap * (j + 1)) << endl;
        file << cos(-(M_PI / 2) + stackGap) * sin(sliceGap * (j + 1)) << " " << sin(-(M_PI / 2) + stackGap) << " " << cos(-(M_PI / 2) + stackGap) * cos(sliceGap * (j + 1)) << endl;
        file << (float)(j + 1) / slices << " " << (float)1.0f / stacks << endl;
        //2nd vertex
        file << radius * cos(-(M_PI / 2) + stackGap) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap) << " " << radius * cos(-(M_PI / 2) + stackGap) * cos(sliceGap * j) << endl;
        file << cos(-(M_PI / 2) + stackGap) * sin(sliceGap * j) << " " << sin(-(M_PI / 2) + stackGap) << " " << cos(-(M_PI / 2) + stackGap) * cos(sliceGap * j) << endl;
        file << (float)j / slices << " " << (float)1.0f / stacks << endl;
        //3rd vertex
        file << 0 << " " << -radius << " " << 0 << endl;
        file << 0 << " " << -1 << " " << 0 << endl;
        file << (float)(j + 0.5f) / slices << " " << (float)1.0f / stacks << endl;
    }

}

void coordenadasTorus(float innerRadius, float outerRadius, int sides, int rings, ofstream& file) {
    //angle gap for stacks
    float ringGap = 2 * M_PI / rings;
    //angle gap for slices
    float sideGap = 2 * M_PI / sides;

    float torusRadius = innerRadius / 2;

    float radius = outerRadius - torusRadius;

    //nº de vertices no modelo
    file << 6 * sides * rings << endl;

    //for every ring
    for (int i = 0; i < 2 * rings; i++) {

        for (int j = 0; j < sides; j++)
        {
        //1st triangle
            //1st vertex
            file << radius * sin(ringGap * i) + torusRadius * sin(ringGap * i) * cos(M_PI - sideGap * j) << " " << torusRadius * sin(M_PI - sideGap * j) << " " << radius * cos(ringGap * i) + torusRadius * cos(ringGap * i) * cos(M_PI - sideGap * j) << endl;
            file << sin(ringGap * i) * cos(M_PI - sideGap * j) << " " << sin(M_PI - sideGap * j) << " " << cos(ringGap * i) * cos(M_PI - sideGap * j) << endl;
            file << (float)2 * j / sides << " " << (float)i / rings << endl;
            //2nd vertex
            file << radius * sin(ringGap * i) + torusRadius * sin(ringGap * i) * cos(M_PI - sideGap * (j + 1)) << " " << torusRadius * sin(M_PI - sideGap * (j + 1)) << " " << radius * cos(ringGap * i) + torusRadius * cos(ringGap * i) * cos(M_PI - sideGap * (j + 1)) << endl;
            file << sin(ringGap * i) * cos(M_PI - sideGap * (j + 1)) << " " << sin(M_PI - sideGap * (j + 1)) << " " << cos(ringGap * i) * cos(M_PI - sideGap * (j + 1)) << endl;
            file << (float)2 * (j + 1) / sides << " " << (float)i / rings << endl;
            //3nd vertex
            file << radius * sin(ringGap * (i + 1)) + torusRadius * sin(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << " " << torusRadius * sin(M_PI - sideGap * (j + 1)) << " " << radius * cos(ringGap * (i + 1)) + torusRadius * cos(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << endl;
            file << sin(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << " " << sin(M_PI - sideGap * (j + 1)) << " " << cos(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << endl;
            file << (float)2 * (j + 1) / sides << " " << (float)(i + 1) / rings << endl;

        //2nd triangle
            //1st vertex
            file << radius * sin(ringGap * i) + torusRadius * sin(ringGap * i) * cos(M_PI - sideGap * j) << " " << torusRadius * sin(M_PI - sideGap * j) << " " << radius * cos(ringGap * i) + torusRadius * cos(ringGap * i) * cos(M_PI - sideGap * j) << endl;
            file << sin(ringGap * i) * cos(M_PI - sideGap * j) << " " << sin(M_PI - sideGap * j) << " " << cos(ringGap * i) * cos(M_PI - sideGap * j) << endl;
            file << (float)2 * j / sides << " " << (float)i / rings << endl;
            //2nd vertex
            file << radius * sin(ringGap * (i + 1)) + torusRadius * sin(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << " " << torusRadius * sin(M_PI - sideGap * (j + 1)) << " " << radius * cos(ringGap * (i + 1)) + torusRadius * cos(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << endl;
            file << sin(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << " " << sin(M_PI - sideGap * (j + 1)) << " " << cos(ringGap * (i + 1)) * cos(M_PI - sideGap * (j + 1)) << endl;
            file << (float)2 * (j + 1) / sides << " " << (float)(i + 1) / rings << endl;
            //3rd vertex
            file << radius * sin(ringGap * (i + 1)) + torusRadius * sin(ringGap * (i + 1)) * cos(M_PI - sideGap * j) << " " << torusRadius * sin(M_PI - sideGap * j) << " " << radius * cos(ringGap * (i + 1)) + torusRadius * cos(ringGap * (i + 1)) * cos(M_PI - sideGap * j) << endl;
            file << sin(ringGap * (i + 1)) * cos(M_PI - sideGap * j) << " " << sin(M_PI - sideGap * j) << " " << cos(ringGap * (i + 1)) * cos(M_PI - sideGap * j) << endl;
            file << (float)2 * j / sides << " " << (float)(i + 1) / rings << endl;
        }

    }
}

void coordenadasCone(float radius, float height, int slices, int stacks, ofstream& file) {
    
    //ratio between radius and height
    float ratio = height / radius;

    //height difference
    float jump = height / stacks;
    //angle gap
    float gap = 2 * M_PI / slices;

    //nº de vertices no modelo
    file << 6 * slices * (stacks - 1) + 3 * slices * 2 << endl;

    float bottom_height;
    float bottom_radius;
    float top_height;
    float top_radius;

    float pos1[3], pos2[3], pos3[3];
    float n[3];

    //for every stack except the tip
    for (int i = 1; i < stacks; i++) {
        bottom_height = (i - 1) * jump;
        bottom_radius = (height - bottom_height) / ratio;
        top_height = i * jump;
        top_radius = (height - top_height) / ratio;

        //for every slice
        for (int j = 0; j < slices; j++)
        {
        // 1st triangle
            pos1[0] = bottom_radius * sin(gap * j);
            pos1[1] = bottom_height;
            pos1[2] = bottom_radius * cos(gap * j);

            pos2[0] = bottom_radius * sin(gap * (j + 1));
            pos2[1] = bottom_height;
            pos2[2] = bottom_radius * cos(gap * (j + 1));

            pos3[0] = top_radius * sin(gap * j);
            pos3[1] = top_height;
            pos3[2] = top_radius * cos(gap * j);

            //1st vertex
            computeNormal(pos1, pos3, pos2, n);
            file << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl;
            file << n[0] << " " << n[1] << " " << n[2] << endl;
            file << (float)0.25 + (0.25 * bottom_radius / radius) * sin(gap * j) << " " << (float)0.5 + (0.5 * bottom_radius / radius) * cos(gap * j) << endl;

            //2nd vertex
            computeNormal(pos2, pos1, pos3, n);
            file << pos2[0] << " " << pos2[1] << " " << pos2[2] << endl;
            file << n[0] << " " << n[1] << " " << n[2] << endl;
            file << (float)0.25 + (0.25 * bottom_radius / radius) * sin(gap * (j + 1)) << " " << (float)0.5 + (0.5 * bottom_radius / radius) * cos(gap * (j + 1)) << endl;

            //3rd vertex
            computeNormal(pos3, pos2, pos1, n);
            file << pos3[0] << " " << pos3[1] << " " << pos3[2] << endl;
            file << n[0] << " " << n[1] << " " << n[2] << endl;
            file << (float)0.25 + (0.25 * top_radius / radius) * sin(gap * j) << " " << (float)0.5 + (0.5 * top_radius / radius) * cos(gap * j) << endl;


        // 2nd triangle
            pos1[0] = top_radius * sin(gap * (j + 1));
            pos1[1] = top_height;
            pos1[2] = top_radius * cos(gap * (j + 1));

            pos2[0] = top_radius * sin(gap * j);
            pos2[1] = top_height;
            pos2[2] = top_radius * cos(gap * j);

            pos3[0] = bottom_radius * sin(gap * (j + 1));
            pos3[1] = bottom_height;
            pos3[2] = bottom_radius * cos(gap * (j + 1));

            //1st vertex 
            computeNormal(pos1, pos3, pos2, n);
            file << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl;
            file << n[0] << " " << n[1] << " " << n[2] << endl;
            file << (float)0.25 + (0.25 * top_radius / radius) * sin(gap * (j + 1)) << " " << (float)0.5 + (0.5 * top_radius / radius) * cos(gap * (j + 1)) << endl;

            //2nd vertex
            computeNormal(pos2, pos1, pos3, n);
            file << pos2[0] << " " << pos2[1] << " " << pos2[2] << endl;
            file << n[0] << " " << n[1] << " " << n[2] << endl;
            file << (float)0.25 + (0.25 * top_radius / radius) * sin(gap * j) << " " << (float)0.5 + (0.5 * top_radius / radius) * cos(gap * j) << endl;

            //3rd vertex
            computeNormal(pos3, pos2, pos1, n);
            file << pos3[0] << " " << pos3[1] << " " << pos3[2] << endl;
            file << n[0] << " " << n[1] << " " << n[2] << endl;
            file << (float)0.25 + (0.25 * bottom_radius / radius) * sin(gap * (j + 1)) << " " << (float)0.5 + (0.5 * bottom_radius / radius) * cos(gap * (j + 1)) << endl;

        }

    }

    //for the base and tip
    for (int j = 0; j < slices && stacks > 0; j++)
    {
    //base
        //1st vertex
        file << 0 << " " << 0 << " " << 0 << endl;
        file << 0 << " " << -1 << " " << 0 << endl;
        file << 0.75 << " " << 0.5 << endl;
        //2nd vertex
        file << radius * sin(gap * (j + 1)) << " " << 0 << " " << radius * cos(gap * (j + 1)) << endl;
        file << 0 << " " << -1 << " " << 0 << endl;
        file << 0.75 + 0.25 * sin(gap * (j + 1)) << " " << 0.5 + 0.5 * cos(gap * (j + 1)) << endl;
        //3rd vertex
        file << radius * sin(gap * j) << " " << 0 << " " << radius * cos(gap * j) << endl;
        file << 0 << " " << -1 << " " << 0 << endl;
        file << 0.75 + 0.25 * sin(gap * j) << " " << 0.5 + 0.5 * cos(gap * j) << endl;

    //tip
        pos1[0] = top_radius * sin(gap * j);
        pos1[1] = top_height;
        pos1[2] = top_radius * cos(gap * j);

        pos2[0] = top_radius * sin(gap * (j + 1));
        pos2[1] = top_height;
        pos2[2] = top_radius * cos(gap * (j + 1));

        pos3[0] = 0;
        pos3[1] = height;
        pos3[2] = 0;

        //1st vertex
        computeNormal(pos1, pos3, pos2, n);
        file << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl;
        file << n[0] << " " << n[1] << " " << n[2] << endl;
        file << (float)0.25 + (0.25 * top_radius / radius) * sin(gap * (j + 1)) << " " << (float)0.5 + (0.5 * top_radius / radius) * cos(gap * (j + 1)) << endl;
        //2nd vertex
        computeNormal(pos2, pos1, pos3, n);
        file << pos2[0] << " " << pos2[1] << " " << pos2[2] << endl;
        file << n[0] << " " << n[1] << " " << n[2] << endl;
        file << (float)0.25 + (0.25 * top_radius / radius) * sin(gap * j) << " " << (float)0.5 + (0.5 * top_radius / radius) * cos(gap * j) << endl;
        //3rd vertex
        computeNormal(pos3, pos2, pos1, n);
        file << pos3[0] << " " << pos3[1] << " " << pos3[2] << endl;
        file << n[0] << " " << n[1] << " " << n[2] << endl;
        file << (float)0.25 << " " << (float)0.5 << endl;

    }
}

void coordenadasPatch(int tess, vector<Patch> patches, ofstream& file) {
    float pos1[3], pos2[3], pos3[3];
    float n[3];
    //nº de vertices no modelo
    file << 6 * (int)pow(tess, 2) * patches.size() << endl;

    // por patch
    for (vector<Patch>::const_iterator i = patches.begin(); i != patches.end(); i++) {
        for (int vaux = 0; vaux < tess; vaux++) {
            float v0 = 1.0f * vaux / tess;
            float v1 = 1.0f * (vaux + 1) / tess;
            
            for (int uaux = 0; uaux < tess; uaux++) {
                float u0 = 1.0f * uaux / tess;
                float u1 = 1.0f * (uaux + 1) / tess;

            // 1st triangle
                getBezierPoint(u0, v0, (*i).points, pos1);
                getBezierPoint(u0, v1, (*i).points, pos2);
                getBezierPoint(u1, v0, (*i).points, pos3);

                // 1st vertex
                computeNormal(pos1, pos3, pos2, n);
                file << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl; // 1st point
                file << n[0] << " " << n[1] << " " << n[2] << endl; // 1st normal
                file << u0 << " " << v0 << endl;
                // 2nd vertex
                computeNormal(pos2, pos1, pos3, n);
                file << pos2[0] << " " << pos2[1] << " " << pos2[2] << endl; // 2nd point
                file << n[0] << " " << n[1] << " " << n[2] << endl; // 2nd normal
                file << u0 << " " << v1 << endl;
                // 3rd vertex
                computeNormal(pos3, pos2, pos1, n);
                file << pos3[0] << " " << pos3[1] << " " << pos3[2] << endl; // 3rd point
                file << n[0] << " " << n[1] << " " << n[2] << endl; // 3rd normal
                file << u1 << " " << v0 << endl;

            // 2nd triangle
                getBezierPoint(u1, v0, (*i).points, pos1);
                getBezierPoint(u0, v1, (*i).points, pos2);
                getBezierPoint(u1, v1, (*i).points, pos3);
                
                // 1st vertex
                computeNormal(pos1, pos3, pos2, n);
                file << pos1[0] << " " << pos1[1] << " " << pos1[2] << endl; // 1st point
                file << n[0] << " " << n[1] << " " << n[2] << endl; // 1st normal
                file << u1 << " " << v0 << endl;
                // 2nd vertex
                computeNormal(pos2, pos1, pos3, n);
                file << pos2[0] << " " << pos2[1] << " " << pos2[2] << endl; // 2nd point
                file << n[0] << " " << n[1] << " " << n[2] << endl; // 2nd normal
                file << u0 << " " << v1 << endl;
                // 3rd vertex
                computeNormal(pos3, pos2, pos1, n);
                file << pos3[0] << " " << pos3[1] << " " << pos3[2] << endl; // 3rd point
                file << n[0] << " " << n[1] << " " << n[2] << endl; // 3rd normal
                file << u1 << " " << v1 << endl;
            }
        }
    }
}

int main(int argc, char* argv[]){

    // FORMAT: 
    // numero de vertices de cada tipo (nºvertice triangulo = nºvertice normal = nºvertice textura)
    // vertice triangulo 
    // vertice normal 
    // vertice textura
    // vertice triangulo
    // ...

    // Conversão do arg[0] para String
    std::string tp(argv[1]);

    // Abertura do file
    std::ofstream file(argv[argc - 1]);
	    
    if (!file.is_open()) cout << "Error opening file" << endl;

    else{

        if(!tp.compare("plane")){
            // Coordenada x
            float x = atof(argv[2]);
    
            // Coordenada z
            float z = atof(argv[3]);
    
           coordenadasPlano(x, z, file);
        }
    
        else if(!tp.compare("box")){
        
            // Coordenada x
            float x = atof(argv[2]);
    
            // Coordenada y
            float y = atof(argv[3]);
    
            // Coordenada z
            float z = atof(argv[4]);

            // Divisoes
            int div = atoi(argv[5]);
    
            // Desenhar Box
            coordenadasBox(x, y, z, div, file);
        }
    
        else if(!tp.compare("sphere")){
            // Radius
            float radius = atof(argv[2]);
    
            // Slices
            int slices = atoi(argv[3]);
    
            // Stacks
            int stacks = atoi(argv[4]);

            // Desenhar esfera
            coordenadasSphere(radius, slices, stacks, file);
            
        }
    
        else if(!tp.compare("cone")){
            // Bottom radius
            float brad = atof(argv[2]);
    
            // Height
            float height = atof(argv[3]);
    
            // Slices
            int slices = atoi(argv[4]);
            
            // Stacks
            int stacks = atoi(argv[5]);

            // Desenhar cone
            coordenadasCone(brad, height, slices, stacks, file);
        }

        else if (!tp.compare("torus")) {
            // inner radius
            float inrad = atof(argv[2]);

            // outer radius
            float outrad = atof(argv[3]);

            // Sides
            int sides = atoi(argv[4]);

            // Rings
            int rings = atoi(argv[5]);

            // Desenhar cone
            coordenadasTorus(inrad, outrad, sides, rings, file);
        }

        else if (!tp.compare("patch")) {
            // number of tessellations
            int tess = atoi(argv[2]);

            // patches file
            string fpatches = argv[3];

            // vector de patches
            vector<Patch> patches = parsePatch(fpatches);

            // Desenhar superficie atraves das patches
            coordenadasPatch(tess, patches, file);

        }
    }

    //Flush do file
    file.flush();

    //Close File
    file.close();
}