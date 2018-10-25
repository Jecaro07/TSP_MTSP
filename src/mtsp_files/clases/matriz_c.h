
#ifndef MATRIZ_C_H_
#define MATRIZ_C_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

class matriz_c
{
    public:
        std::vector <std::vector <float>> reserva(int filas,int columnas);
        std::vector <std::vector <float>> llenar();
        std::vector <std::vector <float>> llena_auto();
        std::vector <std::vector <float>> copiar(std::vector <std::vector <float>> mat);
		    void imprimir_2(std::vector <std::vector <float>> a);
		    void imprimir_1(std::vector <float> a);

    private:
	     	std::vector <std::vector <float>> m_copiar; // lo devuelvo en teoría
	     	std::vector <std::vector <float>> m_llenar; // lo devuelvo en teoría
};


#endif
