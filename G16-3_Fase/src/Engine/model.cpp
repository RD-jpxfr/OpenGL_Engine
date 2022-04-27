#include <iostream>
#include <vector>
#include <tuple>
#include "color.cpp"
using namespace std;

class Model{
    public:
        string filename; //nome do file associado.
        Color color;
        int vertexCount;
        vector< float > coordenadas;
    
    // Default Constructor
    Model(string f, Color c, vector< float > coord){
        filename = f;
        color = c;
        vertexCount = coord.size() / 3;
        coordenadas = coord;
    }   
};