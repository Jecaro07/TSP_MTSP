
#include "cabecera_esultimo.h"

using namespace std;
 using std::vector;



 float es_ultimo_c(int &B, nodo_c n,const vector<vector<float> > &dots, vector<float> punto_final){

 vector<float> c,r1;
 float distancia;
 r1.resize(B); c.resize(1); //numero de coordenadas
 n.es_ultimo(&distancia,r1,c,punto_final,dots);

 return distancia;
 }
