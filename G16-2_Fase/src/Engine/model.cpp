#include <iostream>
#include <vector>
#include <tuple>
#include "color.cpp"
using namespace std;

class Model{
    public:
        string filename; //nome do file associado.
        Color color;
        vector< tuple<float, float, float> > coordenadas;
    
    // Default Constructor
    Model(string f, Color c, vector< tuple<float, float, float> > coord){
        filename = f;
        color = c;
        coordenadas = coord;
    }   
};