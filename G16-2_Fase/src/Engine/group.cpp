#include <string>
#include <vector>
#include "model.cpp"
#include "translate.cpp"
#include "rotate.cpp"
#include "scale.cpp"
using namespace std;

class Group{
    public:
        // Componente de Transla��o do grupo
        Translate trans;
        // Componente de Rota��o do grupo
        Rotate rot;
        // Componente de Escala do grupo
        Scale scale;
        // Vector de modelos dentro do grupo
        vector<Model> models;
        // SubGrupos dentro do grupo
        vector<Group> subGroups;
        // Order Vector - pode conter T | R | S
        vector<char> order;

        // Construtor
        Group(Translate t, Rotate r, Scale s, vector<Model> ms, vector<Group> sgs, vector<char> odr) {
            trans = t;
            rot = r;
            scale = s;
            models = ms;
            subGroups = sgs;
            order = odr;
        }
};