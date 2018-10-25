#ifndef CABECERA_ESULTIMO_H_
#define CABECERA_ESULTIMO_H_

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

 float es_ultimo_c(int &B, nodo_c n,const std::vector<std::vector<float> > &dots, std::vector<float> punto_final);


#endif
