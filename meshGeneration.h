#ifndef MESHGENERATION_H_INCLUDED
#define MESHGENERATION_H_INCLUDED
#include<vector>
#include<utility>

//template<typename T>
class meshGeneration{
public:
    meshGeneration(void);   //constructor
    ~meshGeneration(){delete deltH;}   //de-constructor


    void boundarySeeds();
    //generate the grid node on the boundary
//    void calculateDisFoo();
//calculate the reduced distance function on the boundary
    void bi_LogicalInterpolation();
    //using bi-logical interpolation generating mesh
//    void bi_DistanceInterpolation();
//    //using bi_distance interpolation generating mesh
//    void fineMesh();
//

private:
    std::vector<std::pair<double,double>> _north,_south,_west,_east,_inner;
   // std::vector<std::pair<std::pair<int,int>,std::pair<double,double>>>  inNodes;

    //std::vector<std::vector<std::pair<double,double>>> _inner;
    int NI,NJ;
    double _lenX,_lenY,ytmp1,ytmp2,xtmp,ytmp,distFoo;
    double *deltH;
    double xa,xb,xc,ya,yb,yc;
};


#endif // MESHGENERATION_H_INCLUDED
