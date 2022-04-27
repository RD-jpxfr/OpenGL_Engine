#pragma once

class Point {
  public:         
      float p[3]; //Coordenadas dos pontos 

    // Default constructor
    Point(){
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
    }

    Point(float xx, float yy, float zz){
        p[0] = xx;
        p[1] = yy;
        p[2] = zz;
    }
}; 