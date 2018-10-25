
#ifndef NODO_C_H_
#define NODO_C_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "structure_bal.h"
#include "funciones.h"


class nodo_c
{
    private:
		std::vector<float>  escoge; //
		int nivel;
		int vivo;
		float indicador; // FLOAT en un principio
		int definido;
		float distancia_recorrida;
		float punto_act;
		std::vector<float> punto_sig; //
		std::vector<float> camino; //
		std::vector<float> camino_activo; //
		std::vector<float> recorrido; //


    public:
      void imprime();

      void ini_padre(std::vector <std::vector <float>> puntos);

      void ini_hijo(int &contador_def,int &valor);

      void vuelca_distancia(float &distancia);

      float f_nodo_pre(std::vector <float> &nodo_pre);

      void f_nodo_final(std::vector <float> &nodo_final,float &auxx);

      void devuelve_nivel(int &valor);

	  void condicion_nodo_desglosable(std::vector <float> &v,float &ind,
	       int &INDICE,int i, int &flag);

	  void condicion_v_n_maduros(std::vector <float> &v,float &ind);

	  void devuelve_indicador(float &ind);

    void devuelve_punto_sig(std::vector<float> &ps);

    void devuelve_recorrido(std::vector<float> &rec);

    void devuelve_punto_act(float &pa);

      void iguala(nodo_c padre_argumento);

      bal actu_padre(float distancia,std::vector <std::vector <float>> puntos);

      float actu_padre_2(int i);

      void funcion(int &salir);

      std::vector<float> actu_padre_3();

      void actu_hijo(float dist,float dis,std::vector <float> p_s,int i);

      void es_ultimo(float *distancia,std::vector<float> r1,std::vector<float> c,
         std::vector <float> punto_final,std::vector <std::vector <float>> dots);

      void actu_hijo_2(std::vector<float> mul,std::vector<float> rec);

      void madura() ;

};




#endif
