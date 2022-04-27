#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

class Model{
    public:
        string filename; //nome do file associado.
        vector< tuple<float, float, float> > coordenadas;

    Model(string f, vector< tuple<float, float, float> > coord){
        filename = f;
        coordenadas = coord;
    }
    
};