#ifndef STRUCTURE_BAL_H_
#define STRUCTURE_BAL_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

struct nodo {
std::vector<float>  escoge;
int nivel;
int vivo;
float indicador;
int definido;
float distancia_recorrida;
float punto_act;
std::vector<float> punto_sig;
std::vector<float> camino;
std::vector<float> camino_activo;
std::vector<float> recorrido;
} ;

struct s_dev_hijo {
struct nodo p;
struct nodo h;
int contador;
} ;

struct s_desg_nodo {
std::vector<nodo> a;
struct nodo p;
int contador;
} ;


struct bal {
		std::vector<float> punto_sig;
		std::vector<float> camino_activo;
		std::vector<float> recorrido;
		} ;	

#endif

