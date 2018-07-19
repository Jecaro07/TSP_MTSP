
#include "matriz_c.h"
#include "nodo_c.h"
#include "desglosa_hijo.h"
#include "des_nodo.h"

using namespace std;
 using std::vector;



 void des_nodo::des_nodo_c(nodo_c &padre_argumento, vector <vector<float>> &puntos,
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

     void des_nodo::inicializo(vector <vector<float>> puntos){
		aa.inicializo(puntos);

		}

	 void des_nodo::llena_nodo_des(vector <nodo_c> &nodo_desglosable
	 ,nodo_c &padre_argumento){
	    aa.llena_nodo_des(nodo_desglosable,padre_argumento);
		}


	void des_nodo::vuelca_resultados_1(vector <vector<float>> puntos,int &contador,
	 vector<nodo_c> &v_n_maduros,nodo_c &padre_argumento,float &distancia,
	vector<nodo_c> &nodo_desglosable,int tope,vector<float> &nodo_pre,
	vector<float> &c,vector<float> &r1,
	float &auxx,vector<float> &nodo_final,int &salir,
	vector <float> &punto_final){

		int valor; float vv;

		//(*contador)=contador_;
		v_n_maduros.push_back(p);
		padre_argumento=a[0];


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
