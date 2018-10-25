#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>


#include "funcion_mtsp_file.h"

#include <fstream>
#include <sstream>

using namespace std;
 using std::vector;


// INICIO DE "FUNCION_MTSP"
vector <vector<float>> funcion_mtsp(vector <vector<float>> entrada) {

vector <vector<float>> puntos, puntos_recorrido;
 matriz_c m; nodo_c padre_argumento;
  des_nodo bb;
int contador,contador_def,B=entrada.size()-1, // B = FILAS ; A=COLUMNAS=3
 A=entrada[0].size(); float ind;



//VARIABLES ENTRADA (BEGIN)
  int salir,vital;
  nodo_c nodo_1; // DE MOMENTO LO VOY A DEJAR (se supone que está vacío)
 vector<nodo_c> nodo_desglosable;
 int INDICE;
 float distancia;
 vector <float> punto_final;
  vector<nodo_c> v_n_maduros;
int tope; // CREO QUE NO HAY QUE QUITARLA
 vector<float> nodo_pre;
  vector<float> c;
   vector<float> r1;
float auxx;
 vector<float> nodo_final, MINIMO;
  vector<float> v;
int flag;
//VARIABLES ENTRADA (END)

// VARIABLES DE "BUSCA_RECORRIDO"
bool c11, c1,c2,c3;
float errorr;
vector<nodo_c> aux;
int valor; vector<float> ps,rec; float pa;
nodo_c aux_var;


	  contador_def=0;

    puntos=m.reserva(B,A);
for(int i=0;i<(B);i++){
  for(int j=0;j<(A);j++){
  puntos[i][j]=entrada[i][j];
}}

      m.imprimir_2(puntos);


      punto_final.resize(A);
  for(int i=0;i<A;i++){
    punto_final[i]=entrada[B][i];
  }
      m.imprimir_1(punto_final);


padre_argumento.ini_padre(puntos);
//bb.inicializo(puntos); //daba error porque no tenía definido "puntos" antes

// INICIALIZO LO QUE SEA (COPY-PASTE DEL ORIGINAL)
  contador=0; // cuidado: es "counter" en el original
  nodo_1.vuelca_distancia(distancia); //distancia=nodo_1.distancia_recorrida; // debería dar error, no? (SE SUPONE QUE ES 0)
  salir=0;
  nodo_desglosable.push_back(padre_argumento); // nodo_desglosable.push_back(padre);
   INDICE=0;
 tope=puntos.size()-1;
// INICIALIZO LO QUE SEA (COPY-PASTE DEL ORIGINAL)


// REPETICION ITERACIÓN 1 (EMPIEZA)
		salir=0; // NO PASA NADA POR REPETIRLO DENTRO DE "REPETICIÓN"
		nodo_1=nodo_desglosable[INDICE];  // en matlab pone nodo_desglosable[INDICE];

		nodo_1.vuelca_distancia(distancia); // NO PASA NADA POR REPETIRLO DENTRO DE "REPETICIÓN"

		//cout<<"NODO 1: "<<endl;
		//nodo_1.imprime();



	if(es_ultimo_c(B,nodo_desglosable[INDICE],puntos,punto_final)>0){
		// no desgloso el nodo si está en el último nivel que quiero
	}

else{

	while(salir==0){ // COMIENZO DEL WHILE
	// desgloso los nodos del nivel inferior al que considero
	// y lo defino completamente
		bb.des_nodo_c(padre_argumento,puntos,distancia,contador_def); //salida_dn=desglosa_nodo(B,nodo_1,puntos2,distancia,counter);

		bb.vuelca_resultados_1(puntos,contador,v_n_maduros,padre_argumento,distancia,
	    nodo_desglosable,tope,nodo_pre,c,r1,auxx,nodo_final,salir,punto_final);


	} // FIN DEL WHILE



} // FIN DEL ELSE



cout<<endl;
cout<<endl; cout<< "NODO_FINAL: "<<endl;
m.imprimir_1(nodo_final);
cout<< "NODO_PRE: "<<endl;
m.imprimir_1(nodo_pre);


// HASTA AQUÍ, BIEN.

// SECCION DE "REPETICION" ENCARGADA DE REFRESCAR ÍNDICE ENTRE ITERACIONES
	// Recorremos los nodos desarrollados, "v_n_maduros"

for (int i=0; i<v_n_maduros.size();i++){
	v_n_maduros[i-1].devuelve_indicador(ind);
	v_n_maduros[i].condicion_v_n_maduros(v,ind);
}

m.imprimir_1(v);

// HATA AQUÍ, BIEN.

	flag=0;
	for (int i=0; i<nodo_desglosable.size();i++){

	nodo_desglosable[i].condicion_nodo_desglosable(v,ind,
	INDICE, i, flag);

	}// FIN DEL "FOR"


 cout<<"INDICE: "<<INDICE<<endl;


 // ----------------------------------------------------------------------------
 // ----------------------------------------------------------------------------
 // ----------------------------------------------------------------------------
 // ----------------------------------------------------------------------------
 // EMPIEZA "BUSCA RECORRIDO"

 for (int i = 0; i < nodo_final.size(); i++) {
 	if(minimo(nodo_final)==nodo_final[i]){
 		vital=i;
 	}// fin del if
 }// fin del "for"

 std::cout<< "VITAL:"<< vital << std::endl << std::endl;



 MINIMO.push_back(minimo(nodo_final));

std::cout << "VALOR DE MÍNIMO: "  << std::endl;
 m.imprimir_1(MINIMO);
 std::cout << std::endl;


// EMPIEZA COMENTARIO DE BUSCA RECORRIDO

errorr=pow(10,-4);

// INICIO DEPURAR


for(int i=0; i<nodo_desglosable.size(); i++){
  nodo_desglosable[i].devuelve_punto_sig(ps);
 for (int j=0; j<ps.size();j++){
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_pto_sig: "<< ps[j]  << endl;
}}
std::cout<<std::endl;

for(int i=0; i<nodo_desglosable.size(); i++){
  nodo_desglosable[i].vuelca_distancia(distancia);
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_dist_rec: "<< distancia << endl;
}
cout<<endl;


for(int i=0; i<nodo_final.size(); i++){
	cout<< "Componente "<< i <<" de NODO FINAL: "<< nodo_final[i]  << endl;
}
cout<<endl;

for(int i=0; i<nodo_pre.size(); i++){
	cout<< "Componente "<< i <<" de NODO PRE: "<< nodo_pre[i]  << endl;
}
cout<<endl;

// FIN DEPURAR (HASTA AQUÍ BIEN)

for(int i=0; i<nodo_desglosable.size(); i++){ //

  nodo_desglosable[i].devuelve_punto_sig(ps);
  nodo_desglosable[i].devuelve_punto_act( pa );
  nodo_desglosable[i].devuelve_nivel(valor);

	distancia=norma(resta(punto_final,cut_matrix(puntos,pa,-1)));

	c11= ps.size()==0;
	c1= valor==(tope+1);
	c2=distancia-(nodo_final[vital]-nodo_pre[vital])<errorr;
  nodo_desglosable[i].vuelca_distancia(distancia); // PONERLO
  // AQUÍ PARA NO RESETEAR EL PRIMER VALOR DE "DISTANCIA" (LÍNEA DE ANTES)
  c3=distancia==nodo_pre[vital];

	if (c1 && c2 && c3){
		aux.push_back(nodo_desglosable[i]);
	}// fin del if

}// fin del for

// DEPURAR
for(int i=0; i<aux.size(); i++){
  aux[i].devuelve_punto_sig(ps);
 for (int j=0; j<ps.size();j++){
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_pto_sig: "<< ps[j]  << endl;
}}
cout<<endl;

for(int i=0; i<aux.size(); i++){
  aux[i].vuelca_distancia(distancia);
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_dist_rec: "<< distancia << endl;
}
cout<<endl;

cout<< "TOPE: "<< tope <<endl;
cout<< "VITAL: "<< vital <<endl;



if(aux.size()>1){
	aux_var=aux[0];
	aux.clear();
	aux.push_back(aux_var);
}

// EN CUALQUIER CASO, AUX TENDRÁ DIMENSIÓN 1 (HASTA AQUÍ BIEN)

cout << endl;
cout << "RECORRIDO CIUDADES INTERMEDIAS: " << endl;
aux[0].devuelve_recorrido(rec);
for (int j = 1; j < rec.size(); j++) {
          cout << rec[j] << " ";
      }
cout << endl;cout << endl;

// AHORA SOLO ME FALTA VOLCAR EN "PUNTOS_RECORRIDO"
// LOS PUNTOS EN EL ORDEN EN EL QUE SE UNIRÁN EN RVIZ (puntos2(ordenado) + punto_final)
// (hasta aqui bien)



aux[0].devuelve_recorrido(rec);
puntos_recorrido.resize(B+1);

for (int i = 0; i < (B); i++) {
    puntos_recorrido[i].resize(A);
    for (int j = 0; j < (A); j++) {
        puntos_recorrido[i][j]=puntos[rec[i]][j];
        }
        }

puntos_recorrido[B].resize(A);
for (int j = 0; j < (A); j++) {
puntos_recorrido[B][j]=punto_final[j];
}

return puntos_recorrido;
} // FIN DE "FUNCION_MTSP"


/*
float es_ultimo_c(int &B, nodo_c n,const vector<vector<float> > &dots, vector<float> punto_final){

vector<float> c,r1;
float distancia;
r1.resize(B); c.resize(1); //numero de coordenadas
n.es_ultimo(&distancia,r1,c,punto_final,dots);

return distancia;
}*/
