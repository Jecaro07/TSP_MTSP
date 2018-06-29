#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "nodo_c.h"
#include "structure_bal.h"

void split(const std::string &s, char delim, std::vector<std::string> &elems);


std::vector<std::string> split(const std::string &s, char delim);


/* void pedir_pantalla_f(int &cont_repeticion,int &A, int &B, std::vector<std::vector<float>> &puntos,
 std::vector<float> &punto_final);*/

std::vector<float> cut_matrix (const std::vector<std::vector<float> > &matriz,
float fila,float columna);

float minimo(std::vector<float> temp);

float norma(std::vector<float> u);

std::vector<float> resta(std::vector<float> r1,std::vector<float> r2);

std::vector<float> ordena_vector(std::vector<float> v);


std::vector<float> reordena_vector2(std::vector<float> v_original,
std::vector<float> v_ordenado, std::vector<float> v_a_cambiar);

nodo ordena_nodo(nodo p);

std::vector<float> refresca_auxiliar_f( std::vector<float> entrada);

int devuelve_activo(std::vector<float> v);


int componente_rep(std::vector<float> v,int numero);


float es_ultimo(int &B, struct nodo n,
const std::vector<std::vector<float> > &dots, std::vector<float> punto_final);



struct s_dev_hijo devuelve_hijo (int &B, struct nodo padre,
const std::vector<std::vector<float> > &dots,float dis,int counter);


struct s_desg_nodo desglosa_nodo (int &B,struct nodo padre,
const std::vector<std::vector<float> > &puntos2,float dis,int contador_dh);


void salida_desglosa_nodo(s_desg_nodo salida_dn);


void repeticion(int &B, int &salir,nodo &nodo_1,
std::vector<nodo> &nodo_desglosable,int &INDICE,float &distancia,
std::vector< std::vector<float> > &puntos2, std::vector <float> &punto_final,
s_desg_nodo &salida_dn, float &counter, std::vector<nodo> &v_n_maduros,
int &tope, std::vector<float> &nodo_pre, std::vector<float> &c, std::vector<float> &r1,
float &auxx, std::vector<float> &nodo_final, std::vector<float> &v,
int &flag);

void imprimir_resultados(int cont_repeticion,int A, int B,
  std::vector<std::vector<float>> puntos_recorrido,
  std::vector<std::vector<float>> puntos,
std::vector<float> MINIMO,
  std::vector<nodo> aux, int vital);



#endif
