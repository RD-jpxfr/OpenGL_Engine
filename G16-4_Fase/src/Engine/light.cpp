#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

class Light {
public:
    // POINT | DIRECTIONAL | SPOT -> Spotlight
    string type;

    // Color Ambience
    float ambience[4];

    // Color Defuse
    float defuse[4];

    // POINT -> Coord X, Coord Y, Coord Z, Point <-> W = 0
    float posicao[4];

    // DIRECIONAL -> Coord X, Coord Y, Coord Z, Vector <-> W = 1
    float direcao[4];

    // SPOT -> Utiliza posicao e direcao.
};
