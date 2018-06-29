#ifndef D_H_H_
#define D_H_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "nodo_c.h"    //

class d_h
{
   private:
       nodo_c padre;
       nodo_c hijo;
       int contador;

   public:

       void dev_hijo_c(nodo_c &padre_argumento,std::vector <std::vector<float>> &puntos,
            float dis,int &contador_def);
       void imprime_hijo();
       void imprime_padre();
       void inicializo(std::vector <std::vector<float>> puntos);
       void vuelca_contador(int *contador_);
       void funcion(std::vector <nodo_c> &a,int &salir,nodo_c &padre_argumento);
       void funcion2(int *contador_);
       void llena_nodo_des(std::vector <nodo_c> &nodo_desglosable
            ,nodo_c &padre_argumento);

};


#endif
