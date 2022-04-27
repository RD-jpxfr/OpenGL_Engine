#include "point.cpp"
class TranslateT {
  public:         
    float time; //Time
    vector<Point> points;  
    Point* pointmatrix;
    float y[3];

    // Default constructor
    TranslateT(){
        time = 0;
        y[0] = 0;
        y[1] = 1;
        y[2] = 0;
    }

    void createMatrix() {
        pointmatrix = (Point*)malloc(points.size() * sizeof(Point));
        int j = 0;
        for (vector<Point>::const_iterator i = points.begin(); i != points.end(); i++)
        {
            pointmatrix[j] = *i;
            j++;
        }
    }
};  