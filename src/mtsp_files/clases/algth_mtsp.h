
#ifndef DES_NODO_H_
#define DES_NODO_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

class des_nodo
{
    private:
        std::vector <nodo_c> a;
		    nodo_c p;
		    int contador; // antes; "contardor_"
		    desglosa_hijo aa; // CREO QUE TENDRÍA QUE PONERLO.

    public:

        void des_nodo_c(nodo_c &padre_argumento, std::vector <std::vector<float>> &puntos,
             float dis,int &contador_def);

        void inicializo(std::vector <std::vector<float>> puntos);

	      void llena_nodo_des(std::vector <nodo_c> &nodo_desglosable
  	        ,nodo_c &padre_argumento);

   	    void vuelca_resultados_1(std::vector <std::vector<float>> puntos,int &contador,
	          std::vector<nodo_c> &v_n_maduros,nodo_c &padre_argumento,float &distancia,
	          std::vector<nodo_c> &nodo_desglosable,int tope,std::vector<float> &nodo_pre,
	          std::vector<float> &c,std::vector<float> &r1,
	          float &auxx,std::vector<float> &nodo_final,int &salir,
	          std::vector <float> &punto_final);

};

#endif
