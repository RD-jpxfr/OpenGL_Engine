#include <vector>
#include "point.cpp"
using namespace std;

class Patch {
public:
    vector<Point> points;    //Pontos da patch
    vector<int> indices;    //Indices dos respetivos pontos

    Patch() {

    }
};