
#ifndef MATRIZ_C_H	
#define MATRIZ_C_H

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
 using std::vector;

class matriz_c
{
    private:
        vector <vector <float>> m_copiar; // lo devuelvo en teoría
        vector <vector <float>> m_llenar; // lo devuelvo en teoría
    public:
       
        vector <vector <float>> reserva(int filas,int columnas);
        vector <vector <float>> llenar();
        vector <vector <float>> copiar(vector <vector <float>> mat);
        void imprimir_2(vector <vector <float>> a);
        void imprimir_1(vector <float> a);
};


#endif


