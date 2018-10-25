#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "mtsp_files/clases/matriz_c.h"  // INDEPENDIENTE DE TODAS LAS DEMÁS CLASES
#include "mtsp_files/clases/funciones.h" //
#include "mtsp_files/clases/nodo_c.h"    //
#include "mtsp_files/clases/desglosa_hijo.h"    //
#include "mtsp_files/clases/des_nodo.h"
#include "mtsp_files/clases/cabecera_esultimo.h"

#include <fstream>
#include <sstream>

using namespace std;
 using std::vector;
/*
float es_ultimo_c(int &B, nodo_c n,const vector<vector<float> > &dots, vector<float> punto_final){

vector<float> c,r1;
float distancia;
r1.resize(B); c.resize(1); //numero de coordenadas
n.es_ultimo(&distancia,r1,c,punto_final,dots);

return distancia;
}*/




int main( int argc, char** argv ){

  ros::init(argc, argv, "tsp_script_start");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;

vector <vector<float>> puntos, puntos_recorrido;
 matriz_c m; nodo_c padre_argumento;
  des_nodo bb;
int contador,contador_def,B=6, // B = FILAS ; A=COLUMNAS=3
 A=3; float ind;



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
      puntos=m.reserva(B,3);
//      puntos=m.llenar();
      puntos=m.llena_auto();
      m.imprimir_2(puntos);


      punto_final.resize(A);
		punto_final[0]=13;
		punto_final[1]=4;
		punto_final[2]=6;
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














    while (ros::ok())
    {

      visualization_msgs::Marker points ,pf, po, line_strip, line_list;

      po.header.frame_id =pf.header.frame_id =points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "/my_frame";
      po.header.stamp =pf.header.stamp =points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
      po.ns =pf.ns =points.ns = line_strip.ns = line_list.ns = "tsp_script";
      po.action =pf.action =points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
      po.pose.orientation.w =pf.pose.orientation.w =points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;


      points.id = 0;
      line_strip.id = 1;
      line_list.id = 2;
      pf.id = 3; po.id = 4;



      points.type = visualization_msgs::Marker::POINTS;
      po.type = visualization_msgs::Marker::POINTS;
      pf.type = visualization_msgs::Marker::POINTS;
      line_strip.type = visualization_msgs::Marker::LINE_STRIP;
      line_list.type = visualization_msgs::Marker::LINE_LIST;



      // POINTS markers use x and y scale for width/height respectively
      points.scale.x = 0.2;
      points.scale.y = 0.2;

      po.scale.x = 0.2;
      po.scale.y = 0.2;

      pf.scale.x = 0.2;
      pf.scale.y = 0.2;

      // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
      line_strip.scale.x = 0.1;
      line_list.scale.x = 0.1;



      // Ciudades intermedias verdes
      points.color.g = 1.0f;
      points.color.a = 1.0;

      // Ciudad partida blanca
      po.color.r = 1.0f;
      po.color.g = 1.0f;
      po.color.b = 1.0f;
      po.color.a = 1.0;

      // Ciudad destino roja
      pf.color.r = 1.0f;
      pf.color.a = 1.0;



      // Line strip is blue
      line_strip.color.b = 1.0;
      line_strip.color.a = 1.0;

      // Line list is red
      line_list.color.r = 1.0;
      line_list.color.a = 1.0;




      // Create the vertices for the points and lines
      for (uint32_t i = 0; i < (B+1); ++i)
      {
        geometry_msgs::Point p;
        p.x = (float)puntos_recorrido[i][0] ;
        p.y = (float)puntos_recorrido[i][1] ;

   //     if(B==3){
       p.z = (float)puntos_recorrido[i][2];
   //	}

  	if(i==0){
        po.points.push_back(p);
        line_strip.points.push_back(p);
       }
       if(i==B){
        pf.points.push_back(p);
        line_strip.points.push_back(p);
       }
       if(i>0 && i<B){
        points.points.push_back(p);
        line_strip.points.push_back(p);
       }

      }


  	marker_pub.publish(po);
  	marker_pub.publish(pf);
      marker_pub.publish(points);
      marker_pub.publish(line_strip);

      r.sleep();

    }

    return 0;
   }


/*
cout<< "TAMAÑO NODO DESGLOSABLE: "<<nodo_desglosable.size()<<endl;cout<<endl;

cout<< "nodo_desglosable[0].punto_sig: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[0].punto_sig);

cout<< "nodo_desglosable[1].punto_sig: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[1].punto_sig);

cout<< "nodo_desglosable[2].punto_sig: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[2].punto_sig);

cout<< "nodo_desglosable[3].punto_sig: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[3].punto_sig);

cout<< "nodo_desglosable[0].recorrido: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[0].recorrido);

cout<< "nodo_desglosable[1].recorrido: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[1].recorrido);

cout<< "nodo_desglosable[2].recorrido: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[2].recorrido);

cout<< "nodo_desglosable[3].recorrido: "<<endl;cout<<endl;
mmm.imprimir_1(nodo_desglosable[3].recorrido);

*/




// REPETICION ITERACIÓN 1 (ACABA)


/*

// EMPIEZA "REPETICION"
void repeticion(int &B, int &salir,nodo &nodo_1,
vector<nodo> &nodo_desglosable,int &INDICE,float &distancia,
vector< vector<float> > &puntos2, vector <float> &punto_final,
s_desg_nodo &salida_dn, float &counter, vector<nodo> &v_n_maduros,
int &tope, vector<float> &nodo_pre, vector<float> &c, vector<float> &r1,
float &auxx, vector<float> &nodo_final, vector<float> &v,
int &flag){

// EMPIEZA REPETICION

 // VARIABLES
 salir=0;
 nodo_1=nodo_desglosable[INDICE];  // en matlab pone nodo_desglosable[INDICE];
 distancia=nodo_1.distancia_recorrida;


 if(es_ultimo(B,nodo_desglosable[INDICE],puntos2,punto_final)>0){
 // no desgloso el nodo si está en el último nivel que quiero
}

else{

	while(salir==0){ // COMIENZO DEL WHILE
	// desgloso los nodos del nivel inferior al que considero
	// y lo defino completamente
		salida_dn=desglosa_nodo(B,nodo_1,puntos2,distancia,counter);
		counter=salida_dn.contador;
		v_n_maduros.push_back(salida_dn.p);
		nodo_1=salida_dn.a[0];
		distancia=salida_dn.a[0].distancia_recorrida;

		for (int j=0;j<salida_dn.a.size();j++){
		nodo_desglosable.push_back(salida_dn.a[j]);}

	if (salida_dn.a[0].nivel>=(tope+1)){

	for(int ii=0;ii<salida_dn.a.size();ii++){
		nodo_pre.push_back(salida_dn.a[ii].distancia_recorrida);


		c[0]=salida_dn.a[ii].punto_act;

		r1=cut_matrix(puntos2,c[0],-1);
		auxx=norma(resta(r1,punto_final));

		nodo_final.push_back((salida_dn.a[ii].distancia_recorrida)+auxx);
	} // FIN DEL FOR
		salir=1;
	} // FIN DEL IF

	} // FIN DEL WHILE



} // FIN DEL ELSE

// SECCION DE "REPETICION" ENCARGADA DE REFRESCAR ÍNDICE ENTRE ITERACIONES
	// Recorremos los nodos desarrollados, "v_n_maduros"


	for (int i=0; i<v_n_maduros.size();i++){

		if((v_n_maduros[i].indicador==0) || ((v_n_maduros[i].indicador)-(v_n_maduros[i-1].indicador)<0) || (componente_rep(v,v_n_maduros[i].indicador))){
		}
		else{
			v.push_back(v_n_maduros[i].indicador);
		}// fin del "IF"
	} // fin del "for"

	flag=0;
	for (int i=0; i<nodo_desglosable.size();i++){

		if((nodo_desglosable[i].indicador>0) & (componente_rep(v,nodo_desglosable[i].indicador)==0) & (flag==0) & (nodo_desglosable[i].punto_sig.size()>0)){

		INDICE=i;
		nodo_desglosable[i].indicador=0; flag=1;

		}// FIN DEL "IF"

	}// FIN DEL "FOR"


// FIN "REPETICION"

}

// FIN DE "REPETICION"
*/


// LO HE AÑADIDO YO PARA VER SI VA BIEN LA COSA
 /* padree.imprime();
    cout<<"TAMAÑO DE A: "<< a.size()<<endl;
    a[a.size()-1].imprime(); */


//  return 0;
// }
