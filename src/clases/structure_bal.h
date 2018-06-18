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

struct bal {
		std::vector<float> punto_sig;
		std::vector<float> camino_activo;
		std::vector<float> recorrido;
		} ;	

#endif

