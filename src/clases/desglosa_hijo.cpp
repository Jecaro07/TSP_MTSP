
//
#include "matriz_c.h"
#include "nodo_c.h"
#include "desglosa_hijo.h"

using namespace std;
 using std::vector;



void desglosa_hijo::dev_hijo_c(nodo_c &padre_argumento,vector <vector<float>> &puntos,
   float dis,int &contador_def){

   float dist;
   int flag,valor;//,counter;
   bal ret;vector<float> mul;

 //
     //padre.ini_padre(puntos);	// SOLO LO PONGO LA PRIMERA VEZ QUE LLAMO "DEVUELVE_HIJO"

     padre_argumento.devuelve_nivel(valor);

     hijo.ini_hijo(contador_def,valor);

     padre=padre_argumento;
     padre.madura();


     ret=padre.actu_padre(dis,puntos);
   flag=0;
   for(int i=0 ; i < ret.camino_activo.size() ; i++){
   if(flag==0 && ret.camino_activo[i]==1){
     flag=1;
     dist=padre.actu_padre_2(i);
     hijo.actu_hijo(dist,dis,ret.punto_sig,i);}}

   mul=padre.actu_padre_3();
   hijo.actu_hijo_2(mul,ret.recorrido);
   //  contador=contador_def;
 //  padre.imprime();	 hijo.imprime();

   }

 void desglosa_hijo::imprime_hijo()
      {
   hijo.imprime();
       }

 void desglosa_hijo::imprime_padre()
      {
   padre.imprime();
       }


 void desglosa_hijo::inicializo(vector <vector<float>> puntos){
   padre.ini_padre(puntos);
   }

 void desglosa_hijo::vuelca_contador(int *contador_){
   (*contador_)=contador;
   }



 void desglosa_hijo::funcion(vector <nodo_c> &a,int &salir,nodo_c &padre_argumento){
   a.push_back(hijo);

   //cout<<"PRIMERA VEZ A[0]: "<<endl;
   //a[0]->imprime();

   padre.funcion(salir);  // esta bien??
   padre_argumento=padre;    // SALIDA "DEV_HIJO"

   }


 void desglosa_hijo::funcion2(int *contador_){
   (*contador_)=contador;
   }

 void desglosa_hijo::llena_nodo_des(vector <nodo_c> &nodo_desglosable
 ,nodo_c &padre_argumento){
   nodo_desglosable.push_back(padre_argumento);
   }
