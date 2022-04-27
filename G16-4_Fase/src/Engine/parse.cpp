#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include "Light.cpp"
#include "group.cpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <GLEW/glew.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <IL/il.h>
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

// Parsing da secção de Translação com tempo
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

// Parsing da secção de Rotação com tempo
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

// Parsing da secção de Escala
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

// Parsing de um model
void readfile(string filename, vector<float>& cord, vector<float>& normies, vector<float>& texs) {
    ifstream infile(filename);

    float x, y, z;
    int n = 0, items;
    string temp, temp2;

    // Numero de items
    getline(infile, temp);
    items = stoi(temp);

    while (n < items) {
    // Vertice
        // Linha
        getline(infile, temp);

        // Aux para dividir string
        istringstream iss(temp);

        // Coord x
        getline(iss, temp2, ' ');
        x = stof(temp2);
        cord.push_back(x);

        // Coord y
        getline(iss, temp2, ' ');
        y = stof(temp2);
        cord.push_back(y);

        // Coord z
        getline(iss, temp2, ' ');
        z = stof(temp2);
        cord.push_back(z);

    // Normal
        // Linha
        getline(infile, temp);

        // Aux para dividir string
        istringstream iss2(temp);

        // Coord x    
        getline(iss2, temp2, ' ');
        x = stof(temp2);
        normies.push_back(x);

        // Coord y
        getline(iss2, temp2, ' ');
        y = stof(temp2);
        normies.push_back(y);

        // Coord z
        getline(iss2, temp2, ' ');
        z = stof(temp2);
        normies.push_back(z);

    // Textura
        // Linha
        getline(infile, temp);

        // Aux para dividir string
        istringstream iss3(temp);

        // Coord x    
        getline(iss3, temp2, ' ');
        x = stof(temp2);
        texs.push_back(x);

        // Coord y
        getline(iss3, temp2, ' ');
        y = stof(temp2);
        texs.push_back(y);

        n++;
    }
}

// Parsing da secção da Cor
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
        output = node->Attribute("A");
        if (output) {
            c.a = stof(output);
        }
    }
    return c;
}

// load a texture
GLuint loadTexture(std::string s) {

    unsigned int t, tw, th;
    unsigned char* texData;
    unsigned int texID;

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)s.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texID;

}

// Funçao que trata da parse de todos os modelos
vector<Model> parseModels(XMLElement* fnode) {
    // Nodo temporario
    XMLElement* temp = fnode->FirstChildElement("models");

    // Vector de models temp
    vector<Model> models;

    // Se existir models
    if (temp) {
        // Temp string holder
        const char* output;
        const char* texture;

        bool emis = false;

        // Primeiro model
        XMLElement* tempModel = temp->FirstChildElement("model");

        // Vector temporario de coordenadas
        vector< float > cords;
        vector< float > normies;
        vector< float > texs;
        GLuint id = 0;


        // Loop que passa por tds os modelos
        while (tempModel) {
            // Pega nas componentes RGB
            Color c = parseColor(tempModel);

            // Pega na componente file e guarda na temp string holder
            output = tempModel->Attribute("file");

            // Pega na componente Texture e guarda na string texture
            texture = tempModel->Attribute("texture");

            // Leitura do ficheiro para obter coordenadas
            readfile(output, cords, normies, texs);

            // Pega na component emissao
            output = tempModel->Attribute("emis");
            if (strcmp(output, "True") == 0) {
                emis = true;
            }

            if (texture) {
                id = loadTexture(texture);
            }
            else {
                texture = "";
            }

            // Criar um model e associar coordenadas, normais, cor e texturas a um filename
            models.push_back(Model::Model(output, texture, c, emis, cords, normies, texs, id));

            // Avança para o model seguinte
            tempModel = tempModel->NextSiblingElement();
        }

    }
    return models;
}

// Função que trata da parse das cores difusas e ambientes
void parseLightCor(XMLElement* node, float* cor) {
    float r = 0, g = 0, b = 0;

    char const* output;

    //posX
    output = node->Attribute("R");
    if (output)
        r = stof(output);

    //posY
    output = node->Attribute("G");
    if (output)
        g = stof(output);

    //posZ
    output = node->Attribute("B");
    if (output)
        b = stof(output);

    // Colocar no array da light as componentes
    cor[0] = r;
    cor[1] = g;
    cor[2] = b;
    cor[3] = 1;
}

// Funçao que trata da parse das Posições para a componente Light
void parsePos(XMLElement* node, float* pos) {
    float posX = 0, posY = 0, posZ = 0;

    char const* output;

    //posX
    output = node->Attribute("posX");
    if (output)
        posX = stof(output);

    //posY
    output = node->Attribute("posY");
    if (output)
        posY = stof(output);

    //posZ
    output = node->Attribute("posZ");
    if (output)
        posZ = stof(output);

    // Colocar no array da light as componentes
    pos[0] = posX;
    pos[1] = posY;
    pos[2] = posZ;
    pos[3] = 1;
}

// Função que trata da parse das Direçoes para a componente Light
void parseDir(XMLElement* node, float* dir) {
    float dX = 0, dY = 0, dZ = 0;

    char const* output;

    // DirX
    output = node->Attribute("dX");
    if (output)
        dX = stof(output);

    // DirY
    output = node->Attribute("dY");
    if (output)
        dY = stof(output);

    // DirZ
    output = node->Attribute("dZ");
    if (output)
        dZ = stof(output);

    // Colocar no array da light as componentes
    dir[0] = dX;
    dir[1] = dY;
    dir[2] = dZ;
    dir[3] = 0;
}

// Função que da parse a luz
vector<Light> parseLight(XMLElement* fnode) {

    // light node
    XMLElement* child = fnode->FirstChildElement();

    // Holder para push back
    vector<Light> l;

    while (child) {
        // Vars Auxiliares
        Light light;

        char const* output;

        float cAngle = 0, bAngle = 0;

        // Type
        XMLElement* atrib = child->FirstChildElement();
        output = atrib->Attribute("type");
        light.type = output;

        // Ligh Difusa
        atrib = atrib->NextSiblingElement();
        parseLightCor(atrib, light.defuse);

        // Light Ambiente
        atrib = atrib->NextSiblingElement();
        parseLightCor(atrib, light.ambience);


        // POINT
        if (strcmp(output, "POINT") == 0) {
            // Nodo Type
            atrib = atrib->NextSiblingElement();
            parsePos(atrib, light.posicao);
        }

        // DIRECTIONAL
        else if (strcmp(output, "DIRECTIONAL") == 0) {
            // Nodo Type
            atrib = atrib->NextSiblingElement();
            parseDir(atrib, light.direcao);
        }

        // SPOT
        else if (strcmp(output, "SPOT") == 0) {

            // Nodo atribs
            atrib = atrib->NextSiblingElement();

            // Parse Posicao
            parsePos(atrib, light.posicao);

            // Parse Direcao
            parseDir(atrib, light.direcao);
        }

        l.push_back(light);

        child = child->NextSiblingElement();
    }
    return l;
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

void parseXML(char* fnome, vector<Group>& grupos, vector<Light>& light) {
    // Load do file passado como argumento
    XMLDocument doc;
    doc.LoadFile(fnome);

    // ROOT <=> Scene
    XMLElement* root = doc.RootElement();

    // Luz
    XMLElement* fnode = root->FirstChildElement("lights");
    
    if (fnode) {
        light = parseLight(fnode);
    }

    if (light.size() > 8) {
        std::cout << "Warning: Too many light sources, only first 8th will be used" << endl;
    }

    // Primeiro Group
    fnode = root->FirstChildElement("group");

    // Parsing dos grupos
    parseGroup(fnode, grupos);
}