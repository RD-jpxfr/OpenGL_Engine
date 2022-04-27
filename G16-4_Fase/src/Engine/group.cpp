#include <string>
#include <vector>
#include "model.cpp"
#include "translate.cpp"
#include "rotate.cpp"
#include "scale.cpp"
#include "translateT.cpp"
#include "rotateT.cpp"
using namespace std;

class Group{
    public:
        // Componente de Transla��o do grupo
        Translate trans;
        // Componente de Transla��o tempo do grupo
        TranslateT transT;
        // Componente de Rota��o do grupo
        Rotate rot;
        // Componente de rota��o tempo do grupo
        RotateT rotT;
        // Componente de Escala do grupo
        Scale scale;
        // Vector de modelos dentro do grupo
        vector<Model> models;
        // SubGrupos dentro do grupo
        vector<Group> subGroups;
        // Order Vector - pode conter T | R | S
        vector<string> order;

        // Construtor
        Group(Translate t, TranslateT tt, Rotate r, RotateT rt, Scale s, vector<Model> ms, vector<Group> sgs, vector<string> odr) {
            trans = t;
            transT = tt;
            rot = r;
            rotT = rt;
            scale = s;
            models = ms;
            subGroups = sgs;
            order = odr;
        }
};