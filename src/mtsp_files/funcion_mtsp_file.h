#ifndef FUNCION_MTSP_FILE_H_
#define FUNCION_MTSP_FILE_H_

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "clases/matriz_c.h"  // INDEPENDIENTE DE TODAS LAS DEMÁS CLASES
#include "clases/funciones.h" //
#include "clases/nodo_c.h"    //
#include "clases/desglosa_hijo.h"    //
#include "clases/des_nodo.h"
#include "clases/cabecera_esultimo.h"

#include <fstream>
#include <sstream>

std::vector <std::vector<float>> funcion_mtsp(std::vector <std::vector<float>> entrada);



#endif
