#include <iostream>
#include <fstream>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
using namespace std;


void coordenadasPlano(float x, float z, ofstream& file){

    // Plano vista de cima
    file << x/2 << " " << 0 << " " << z/2 << endl;
    file << x/2 << " " << 0 << " " << -z/2 << endl;
    file << -x/2 << " " << 0 << " " << z/2 << endl;

    file << -x/2 << " " << 0 << " " << -z/2 << endl;
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    file << x/2 << " " << 0 << " " << -z/2 << endl;

    // Plano vista de Baixo
    file << x/2 << " " << 0 << " " << z/2 << endl;
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    file << x/2 << " " << 0 << " " << -z/2 << endl;

    file << -x/2 << " " << 0 << " " << -z/2 << endl;
    file << x/2 << " " << 0 << " " << -z/2 << endl;
    file << -x/2 << " " << 0 << " " << z/2 << endl;
    
}

void coordenadasBox(float x, float y, float z, int divisions, ofstream& file) {

    float xratio = x / divisions;
    float yratio = y / divisions;
    float zratio = z / divisions;

    //horizontal cima
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            file << -x / 2 + (i + 1) * xratio << " " << y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -x / 2 + (i + 1) * xratio << " " << y / 2 << " " << -z / 2 + j * zratio << endl;
            file << -x / 2 + i * xratio << " " << y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;

            file << -x / 2 + i * xratio << " " << y / 2 << " " << -z / 2 + j * zratio << endl;
            file << -x / 2 + i * xratio << " " << y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -x / 2 + (i + 1) * xratio << " " << y / 2 << " " << -z / 2 + j * zratio << endl;
        }
    }

    //horizontal baixo
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -x / 2 + i * xratio << " " << -y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 << " " << -z / 2 + j * zratio << endl;

            file << -x / 2 + i * xratio << " " << -y / 2 << " " << -z / 2 + j * zratio << endl;
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 << " " << -z / 2 + j * zratio << endl;
            file << -x / 2 + i * xratio << " " << -y / 2 << " " << -z / 2 + (j + 1) * zratio << endl;
        }
    }

    //verticais frente
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << z / 2 << endl;
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + (j + 1) * yratio << " " << z / 2 << endl;
            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << z / 2 << endl;

            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << z / 2 << endl;
            file << -x / 2 + i * xratio << " " << -y / 2 + j * yratio << " " << z / 2 << endl;
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << z / 2 << endl;
        }
    }

    //verticais trás
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << -z / 2 << endl;
            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << -z / 2 << endl;
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + (j + 1) * yratio << " " << -z / 2 << endl;

            file << -x / 2 + i * xratio << " " << -y / 2 + (j + 1) * yratio << " " << -z / 2 << endl;
            file << -x / 2 + (i + 1) * xratio << " " << -y / 2 + j * yratio << " " << -z / 2 << endl;
            file << -x / 2 + i * xratio << " " << -y / 2 + j * yratio << " " << -z / 2 << endl;
        }
    }

    //perfil direita
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            file << x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + j * zratio << endl;
            file << x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;

            file << x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
        }
    }

    //perfil esquerda
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            file << -x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
            file << -x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + j * zratio << endl;

            file << -x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
            file << -x / 2 << " " << -y / 2 + (i + 1) * yratio << " " << -z / 2 + j * zratio << endl;
            file << -x / 2 << " " << -y / 2 + i * yratio << " " << -z / 2 + (j + 1) * zratio << endl;
        }
    }

}

void coordenadasSphere(float radius, int slices, int stacks, ofstream& file) {
    //angle gap for stacks
    float stackGap = M_PI / stacks;
    //angle gap for slices
    float sliceGap = 2 * M_PI / slices;

    int i;
    //for every stack except the top and bottom
    for (i = 1; i < stacks - 1; i++) {


        for (int j = 0; j < slices; j++)
        {
            file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * j) << endl;
            file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
            file << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * j) << endl;

            file << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * (j + 1)) << endl;
            file << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * (i + 1)) << " " << radius * cos(-(M_PI / 2) + stackGap * (i + 1)) * cos(sliceGap * j) << endl;
            file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;

        }

    }

    //for the top and bottom stack
    for (int j = 0; j < slices && stacks > 1; j++)
    {
        file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * j) << endl;
        file << radius * cos(-(M_PI / 2) + stackGap * i) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap * i) << " " << radius * cos(-(M_PI / 2) + stackGap * i) * cos(sliceGap * (j + 1)) << endl;
        file << 0 << " " << radius << " " << 0 << endl;

        file << radius * cos(-(M_PI / 2) + stackGap) * sin(sliceGap * (j + 1)) << " " << radius * sin(-(M_PI / 2) + stackGap) << " " << radius * cos(-(M_PI / 2) + stackGap) * cos(sliceGap * (j + 1)) << endl;
        file << radius * cos(-(M_PI / 2) + stackGap) * sin(sliceGap * j) << " " << radius * sin(-(M_PI / 2) + stackGap) << " " << radius * cos(-(M_PI / 2) + stackGap) * cos(sliceGap * j) << endl;
        file << 0 << " " << -radius << " " << 0 << endl;

    }

}

void coordenadasCone(float radius, float height, int slices, int stacks, ofstream& file) {
    
    //ratio between radius and height
    float ratio = height / radius;

    //height difference
    float jump = height / stacks;
    //angle gap
    float gap = 2 * M_PI / slices;


    float bottom_height;
    float bottom_radius;
    float top_height;
    float top_radius;

    //for every stack except the tip
    for (int i = 1; i <= stacks; i++) {
        bottom_height = (i - 1) * jump;
        bottom_radius = (height - bottom_height) / ratio;
        top_height = i * jump;
        top_radius = (height - top_height) / ratio;

        //for every slice
        for (int j = 0; j < slices; j++)
        {
           file << bottom_radius * sin(gap * j) << " " << bottom_height << " " << bottom_radius * cos(gap * j) << endl;
           file << bottom_radius * sin(gap * (j + 1)) << " " << bottom_height << " " << bottom_radius * cos(gap * (j + 1)) << endl;
           file << top_radius * sin(gap * j) << " " << top_height << " " << top_radius * cos(gap * j) << endl;

           file << top_radius * sin(gap * (j + 1)) << " " << top_height << " " << top_radius * cos(gap * (j + 1)) << endl;
           file << top_radius * sin(gap * j) << " " << top_height << " " << top_radius * cos(gap * j) << endl;
           file << bottom_radius * sin(gap * (j + 1)) << " " << bottom_height << " " << bottom_radius * cos(gap * (j + 1)) << endl;

        }

    }

    //for the base and tip
    for (int j = 0; j < slices && stacks > 0; j++)
    {
        //base
       file << 0 << " " << 0 << " " << 0 << endl;
       file << radius * sin(gap * (j + 1)) << " " << 0 << " " << radius * cos(gap * (j + 1)) << endl;
       file << radius * sin(gap * j) << " " << 0 << " " << radius * cos(gap * j) << endl;

        //tip
       file << top_radius * sin(gap * (j + 1)) << " " << top_height << " " << top_radius * cos(gap * (j + 1)) << endl;
       file << top_radius * sin(gap * j) << " " << top_height << " " << top_radius * cos(gap * j) << endl;
       file << 0 << " " << height << " " << 0 << endl;

    }
}

int main(int argc, char* argv[]){

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
    }

    //Flush do file
    file.flush();

    //Close File
    file.close();
}