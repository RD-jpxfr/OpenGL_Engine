#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include "group.cpp"
#include "../../lib/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

// Parsing da secção de Translação
Translate parseTrans(XMLElement* node) {

    // Temp string holder
    const char* output;

    // Temp Translate
    Translate t = Translate();

    // Se exisitr
    if (node) {
        output = node->Attribute("X");
        if (output) {
            t.x = stof(output);
        }

        output = node->Attribute("Y");
        if (output) {
            t.y = stof(output);
        }

        output = node->Attribute("Z");
        if (output) {
            t.z = stof(output);
        }
    }
    return t;
}

TranslateT parseTransT(XMLElement* node) {
    // Temp string holder
    const char* output;

    // Vector de pontos
    vector<Point> points;

    // Point temporario
    Point p;

    // Temp Translate
    TranslateT tt = TranslateT();

    // Se exisitr
    if (node) {
        // Time
        output = node->Attribute("time");
        if (output) {
            tt.time = stof(output);
        }

        // Points
        // Primeiro model
        XMLElement* tempPoint = node->FirstChildElement("point");

        while (tempPoint) {
            output = tempPoint->Attribute("X");
            if (output) {
                p.p[0] = stof(output);
            }

            output = tempPoint->Attribute("Y");
            if (output) {
                p.p[1] = stof(output);
            }

            output = tempPoint->Attribute("Z");
            if (output) {
                p.p[2] = stof(output);
            }

            // Criar um model e associar coordenadas e filename
            points.push_back(p);

            // Avança para o model seguinte
            tempPoint = tempPoint->NextSiblingElement();
        }

        tt.points = points;
    }

    tt.createMatrix();

    return tt;
}

// Parsing da secção de Rotação
Rotate parseRot(XMLElement* node) {

    // Temp string holder
    const char* output;

    // Temp Rotate
    Rotate r = Rotate();

    //Se existir
    if (node) {
        output = node->Attribute("angle");
        if (output) {
            r.angle = stof(output);
        }

        output = node->Attribute("axisX");
        if (output) {
            r.axisX = stof(output);
        }

        output = node->Attribute("axisY");
        if (output) {
            r.axisY = stof(output);
        }

        output = node->Attribute("axisZ");
        if (output) {
            r.axisZ = stof(output);
        }
    }
    return r;
}

RotateT parseRott(XMLElement* node) {
    // Temp string holder
    const char* output;

    // Temp Rotate
    RotateT rt = RotateT();

    //Se existir
    if (node) {
        output = node->Attribute("time");
        if (output) {
            rt.time = stof(output);
        }

        output = node->Attribute("axisX");
        if (output) {
            rt.axisX = stof(output);
        }

        output = node->Attribute("axisY");
        if (output) {
            rt.axisY = stof(output);
        }

        output = node->Attribute("axisZ");
        if (output) {
            rt.axisZ = stof(output);
        }
    }
    return rt;
}

Scale parseScale(XMLElement* node) {
    // Temp string holder
    const char* output;

    // Temp Scale
    Scale s = Scale();

    if (node) {
        output = node->Attribute("X");
        if (output) {
            s.x = stof(output);
        }

        output = node->Attribute("Y");
        if (output) {
            s.y = stof(output);
        }

        output = node->Attribute("Z");
        if (output) {
            s.z = stof(output);
        }
    }
    return s;
}

// Parsing da secção de Escala
vector< float > readfile(string filename) {
    ifstream infile(filename);

    float x, y, z;

    vector< float > cord;

    while (infile >> x >> y >> z) {
        cord.push_back(x);
        cord.push_back(y);
        cord.push_back(z);
    }

    return cord;
}

Color parseColor(XMLElement* node) {
    // Temp string holder
    const char* output;

    // Temp Translate
    Color c = Color();

    // Se exisitr
    if (node) {
        output = node->Attribute("R");
        if (output) {
            c.r = stof(output);
        }

        output = node->Attribute("G");
        if (output) {
            c.g = stof(output);
        }

        output = node->Attribute("B");
        if (output) {
            c.b = stof(output);
        }
    }
    return c;
}

vector<Model> parseModels(XMLElement* fnode) {
    // Nodo temporario
    XMLElement* temp = fnode->FirstChildElement("models");

    // Vector de models temp
    vector<Model> models;

    // Se existir models
    if (temp) {
        // Temp string holder
        const char* output;

        // Primeiro model
        XMLElement* tempModel = temp->FirstChildElement("model");

        // Vector temporario de coordenadas
        vector< float > cords;

        // Loop que passa por tds os modelos
        while (tempModel) {
            // Pega nas componentes RGB
            Color c = parseColor(tempModel);

            // Pega na componente file e guarda na temp string holder
            output = tempModel->Attribute("file");

            // Leitura do ficheiro para obter coordenadas
            cords = readfile(output);

            // Criar um model e associar coordenadas e filename
            models.push_back(Model(output, c, cords));

            // Avança para o model seguinte
            tempModel = tempModel->NextSiblingElement();
        }
    }
    return models;
}

void parseGroup(XMLElement* fnode, vector<Group>& groups) {
    // Dentro de cada grupo
    while (fnode) {
        // Default Construtors para as TGs
        Translate t = Translate();
        TranslateT tt = TranslateT();
        Rotate r = Rotate();
        RotateT rt = RotateT();
        Scale s = Scale();

        // Vetor de ordem das TGs
        vector<string> order;

        // Uma das TGs
        XMLElement* fchild = fnode->FirstChildElement();

        // Nome de nodo filho
        char const* nodename;

        // Flag que verifica se encontrou um model ou um grupo
        int flag = 1;

        // Ciclo que percorre os child elements ate chegar aos models
        while (fchild && flag != 0) {
            // Passagem do nome do node para string para comparação
            nodename = fchild->Name();
            string stemp = nodename;

            // verifica se não e um model ou um grupo
            if (stemp != "models" && stemp != "grupo") {
                // Se for um translate
                if (stemp == "translate") {
                    if (fchild->Attribute("time") == NULL) {
                        // Executa o parsing do translate
                        t = parseTrans(fchild);

                        // Coloca Translate no vector de ordem
                        order.push_back("T");
                    }

                    else {
                        // Executa o parsing do translateT
                        tt = parseTransT(fchild);

                        // Coloca TranslateT no vector de ordem
                        order.push_back("TT");
                    }

                }

                // Se for um rotate
                else if (stemp == "rotate") {
                    if (fchild->Attribute("time") == NULL) {
                        // Executa o parsing do rotate
                        r = parseRot(fchild);

                        // Coloca Rotate no vector de ordem
                        order.push_back("R");
                    }

                    else {
                        // Executa o parsing do rotateT
                        rt = parseRott(fchild);

                        // Coloca RotateT no vector de ordem
                        order.push_back("RT");
                    }
                }

                // Se for um scale
                else if (stemp == "scale") {
                    // Executa o parsing da scale
                    s = parseScale(fchild);

                    // Coloca Scale no vector de ordem
                    order.push_back("S");
                }
            }

            else {
                // Foi encontrado um models | group
                flag = 0;
            }

            // Seguir para o proximo sibling
            fchild = fchild->NextSiblingElement();
        }

        // Secção dos models
        vector<Model> models = parseModels(fnode);

        // Vector de subgroups
        vector<Group> subGroups;

        // Temp é o grupo dentro do grupo se existir
        XMLElement* temp = fnode->FirstChildElement("group");

        // Verifica se existe um grupo dentro do grupo
        if (temp) {
            // Chama a parsing do grupo para os filhos do main group recursivamente
            parseGroup(temp, subGroups);
        }

        // Criação do grupo temporário e respetiva adição ao vetor final
        groups.push_back(Group(t, tt, r, rt, s, models, subGroups, order));

        // Avança para o grupo seguinte
        fnode = fnode->NextSiblingElement();
    }
}

void parseXML(char* fnome, vector<Group>& grupos) {
    // Load do file passado como argumento
    XMLDocument doc;
    doc.LoadFile(fnome);

    // ROOT <=> Scene
    XMLElement* root = doc.RootElement();

    // Primeiro Group
    XMLElement* fnode = root->FirstChildElement("group");

    // Parsing dos grupos
    parseGroup(fnode, grupos);
}