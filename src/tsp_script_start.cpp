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


//#include "clases/d_h.h"


#include <fstream>
#include <sstream>

using namespace std;
 using std::vector;
using namespace std;

float es_ultimo_c(int &B, nodo_c n,const vector<vector<float> > &dots, vector<float> punto_final){

vector<float> c,r1;
float distancia;
r1.resize(B); c.resize(1); //numero de coordenadas
n.es_ultimo(&distancia,r1,c,punto_final,dots);

return distancia;
}

 class d_h
{
    private:
        nodo_c padre;
        nodo_c hijo;
        int contador;

    public:

 void dev_hijo_c(nodo_c &padre_argumento,vector <vector<float>> &puntos,
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

  void imprime_hijo()
       {
		hijo.imprime();
        }

  void imprime_padre()
       {
		padre.imprime();
        }


  void inicializo(vector <vector<float>> puntos){
		padre.ini_padre(puntos);
		}

  void vuelca_contador(int *contador_){
		(*contador_)=contador;
		}



  void funcion(vector <nodo_c> &a,int &salir,nodo_c &padre_argumento){
		a.push_back(hijo);

		//cout<<"PRIMERA VEZ A[0]: "<<endl;
		//a[0]->imprime();

		padre.funcion(salir);  // esta bien??
		padre_argumento=padre;    // SALIDA "DEV_HIJO"

		}


	void funcion2(int *contador_){
		(*contador_)=contador;
		}

	void llena_nodo_des(vector <nodo_c> &nodo_desglosable
	,nodo_c &padre_argumento){
		nodo_desglosable.push_back(padre_argumento);
		}

};


class d_n
{
    private:
        vector <nodo_c> a;
		nodo_c p;
		int contador; // antes; "contardor_"

		d_h aa; // CREO QUE TENDRÍA QUE PONERLO.

    public:

 void des_nodo_c(nodo_c &padre_argumento, vector <vector<float>> &puntos,
                 float dis,int &contador_def){

		int salir,contador; //d_h aa;
		salir=0; contador=1;
		 a.clear();

    while(salir==0){
    aa.dev_hijo_c(padre_argumento,puntos,dis,contador_def);

    cout<<endl;cout<<"PADRE: "<<endl;
    aa.imprime_padre();

    cout<<endl;cout<<"HIJO: "<<endl;
    aa.imprime_hijo();


	contador=contador+1;
	aa.funcion(a,salir,padre_argumento); // se supone que aquí modifico "a" por primera vez

   // aa.vuelca_contador(&contador_);
   // contador_def=contador_;
    }

	p=padre_argumento;
	//aa.funcion2(&contador_);


	//POR SI QUIERO COMPARAR SALIDA CON "SCRIPT_SUCIO"

	//padree.imprime();
    //cout<<"TAMAÑO DE A: "<< a.size()<<endl;
    //a[a.size()-1].imprime();

    //POR SI QUIERO COMPARAR SALIDA CON "SCRIPT_SUCIO"
     }

     void inicializo(vector <vector<float>> puntos){
		aa.inicializo(puntos);

		}

	 void llena_nodo_des(vector <nodo_c> &nodo_desglosable
	 ,nodo_c &padre_argumento){
	    aa.llena_nodo_des(nodo_desglosable,padre_argumento);
		}


	void vuelca_resultados_1(vector <vector<float>> puntos,int &contador,
	 vector<nodo_c> &v_n_maduros,nodo_c &padre_argumento,float &distancia,
	vector<nodo_c> &nodo_desglosable,int tope,vector<float> &nodo_pre,
	vector<float> &c,vector<float> &r1,
	float &auxx,vector<float> &nodo_final,int &salir,
	vector <float> &punto_final){

		int valor; float vv;

		//(*contador)=contador_;
		v_n_maduros.push_back(p);
		padre_argumento=a[0];

		/*
		cout<<endl;cout<<"AAAAA_SIZE: "<<a.size()<<endl;

		cout<<endl;cout<<"AAAAA_0: "<<endl;
		a[0].imprime();

		cout<<endl;cout<<"AAAAA_1: "<<endl;
		a[1].imprime();*/

		a[0].vuelca_distancia(distancia);

		for (int j=0;j<a.size();j++){
		nodo_desglosable.push_back(a[j]);}

		a[0].devuelve_nivel(valor);

		cout<<endl;
		cout<<"VALOR_COMPARA: "<<valor<<endl;
		cout<<"(TOPE+1): "<<(tope+1)<<endl;cout<<endl;


		// valor_compara


	if (valor>=(tope+1)){

	for(int ii=0;ii<a.size();ii++){

		// ANOTHER METHOD (BEGIN)
		vv=a[ii].f_nodo_pre(nodo_pre); // vv será c[0] por simplicidad
		//c[0]=vv;
		// ANOTHER METHOD (END)

		r1=cut_matrix(puntos,vv,-1);
		auxx=norma(resta(r1,punto_final));

		// ANOTHER METHOD (BEGIN)
		a[ii].f_nodo_final(nodo_final,auxx);
		// ANOTHER METHOD (END)

	} // FIN DEL FOR
		salir=1;
	} // FIN DEL IF


		}


/*	void vuelca_resultados_2(vector <vector<float>> puntos,int *contador, vector<nodo_c> *v_n_maduros,nodo_c *nodo_1,float *distancia,
	vector<nodo_c> *nodo_desglosable,int tope,vector<float> *nodo_pre,vector<float> *c,vector<float> *r1,
	float *auxx,vector<float> *nodo_final,int *salir,vector <float> *punto_final){

		int valor_compara; float vv;
		/*
		(*contador)=contador_;
		v_n_maduros->push_back(p);
		(*nodo_1)=a[0];

		// IMPRIMO CAMPOS DEL NODO a[0] (BEGIN)

		cout<<"NODO A[0]: "<<endl; cout<<endl;
		a[0].imprime();

		// IMPRIMO CAMPOS DEL NODO a[0] (END)


		// ANOTHER METHOD (DONE)
		(*distancia)=a[0].vuelca_distancia(distancia);
		// ANOTHER METHOD (DONE)

		for (int j=0;j<a.size();j++){
		nodo_desglosable->push_back(a[j]);}


cout<< "VALOR COMPARA_1: "<< valor_compara <<endl; // VALOR BASURA: 1345534635

		//MÉTODO PARA DEVOLVER UN VALOR CON EL QUE COMPARAR (BEGIN)
		a[0].devuelve_nivel(&valor_compara);
		//MÉTODO PARA DEVOLVER UN VALOR CON EL QUE COMPARAR (END)

	cout<< "TOPE: "<< tope <<endl;
	cout<< "VALOR COMPARA_2: "<< valor_compara <<endl; // VALOR "0"


		// valor_compara
	if (valor_compara>=(tope+1)){

	for(int ii=0;ii<a.size();ii++){

		// ANOTHER METHOD (BEGIN)
		vv=a[ii].f_nodo_pre(nodo_pre); // vv será c[0] por simplicidad
		//c[0]=vv;
		// ANOTHER METHOD (END)

		(*r1)=cut_matrix(puntos,vv,-1);
		(*auxx)=norma(resta(*r1,*punto_final));

		// ANOTHER METHOD (BEGIN)
	//	a[ii].f_nodo_final(&nodo_final,auxx);
		// ANOTHER METHOD (END)

	} // FIN DEL FOR
		(*salir)=1;
	} // FIN DEL IF
		}

	*/

};



int main( int argc, char** argv ){

  ros::init(argc, argv, "tsp_script_start");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;

vector <vector<float>> puntos;
d_n bb; matriz_c m;nodo_c padre_argumento;
int contador,contador_def,B=3; float ind;

//VARIABLES ENTRADA (BEGIN)
  int salir;
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
 vector<float> nodo_final;
  vector<float> v;
int flag;
//VARIABLES ENTRADA (END)

	  contador_def=0;
      puntos=m.reserva(B,3);
      puntos=m.llenar();
      m.imprimir_2(puntos);


      punto_final.resize(3);
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


// HATA AQUÍ, BIEN.

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


 cout<<"INDICE: "<<flag<<endl;









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


  return 0;
 }
