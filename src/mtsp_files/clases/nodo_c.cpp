
#include "matriz_c.h"
#include "nodo_c.h"
#include "structure_bal.h"

using namespace std;
 using std::vector;

       void nodo_c::imprime()
       {
		matriz_c m;
		cout<<"NIVEL: "<<nivel<<endl;
		cout<<"VIVO: "<<vivo<<endl;
		cout<<"INDICADOR: "<<indicador<<endl;
		cout<<"DEFINIDO: "<<definido<<endl;
		cout<<"DISTANCIA_RECORRIDA: "<<distancia_recorrida<<endl;
		cout<<"PUNTO_ACT: "<<punto_act<<endl;
		cout<<"camino: "<<endl;
		m.imprimir_1(camino);
		cout<<"camino_activo: "<<endl;
		m.imprimir_1(camino_activo);
		cout<<"recorrido: "<<endl;
		m.imprimir_1(recorrido);
		cout<<"punto_sig: "<<endl;
		m.imprimir_1(punto_sig);
		cout<<"escoge: "<<endl;
		m.imprimir_1(escoge);
        }

       void nodo_c::ini_padre(vector <vector <float>> puntos)
       {
		vector<float> dos_tal,uno_tal;

		uno_tal.resize(1);cout<<"ME HE EQUIVOCAO"<<endl; dos_tal.resize(puntos.size()-1);
		recorrido.resize(1); punto_sig.resize(puntos.size()-1);
		for (int j=0;j<dos_tal.size();j++){
		dos_tal[j]=j+1; }
		uno_tal[0]=0;

		nivel=1;
		definido=0;
		distancia_recorrida=0;
		punto_act=0;
		indicador=0;
		recorrido=uno_tal;
		punto_sig=dos_tal;

        }

        void nodo_c::ini_hijo(int &contador_def,int &valor)
       {

		indicador=contador_def; contador_def=contador_def+1;
		cout<<"INDICADOR: "<<indicador<<endl;
		nivel=1+valor;
		definido=0;

        }

        void nodo_c::vuelca_distancia(float &distancia)
       {
		distancia=distancia_recorrida;

		//return (*distancia);
        }

      //  a[ii].f_nodo_pre(&c[0],&nodo_pre);

        float nodo_c::f_nodo_pre(vector <float> &nodo_pre){
		nodo_pre.push_back(distancia_recorrida);
		return punto_act; // NO SE SI ESTA ES LA NOMENCLATURA
		}

       void nodo_c::f_nodo_final(vector <float> &nodo_final,float &auxx){

		nodo_final.push_back((distancia_recorrida)+auxx);
		}


        void nodo_c::devuelve_nivel(int &valor){
        valor=nivel;
	 }


	 /*
	 	v_n_maduros[i].condicion_v_n_maduros_2(v,ind,INDICE,i);


		if((nodo_desglosable[i].indicador>0)
		& (componente_rep(v,nodo_desglosable[i].indicador)==0)
		& (flag==0) & (nodo_desglosable[i].punto_sig.size()>0)){

		INDICE=i;
		nodo_desglosable[i].indicador=0; flag=1;}
		*/

	 void nodo_c::condicion_nodo_desglosable(vector <float> &v,float &ind,
	       int &INDICE,int i, int &flag){

        if((indicador>0)
		& (componente_rep(v,indicador)==0)
		& (flag==0) & (punto_sig.size()>0)){

		INDICE=i;
		indicador=0; flag=1;}
	 }


	 void nodo_c::condicion_v_n_maduros(vector <float> &v,float &ind){
        if((indicador==0)
        || ((indicador)-(ind)<0)
         || (componente_rep(v,indicador))){}

		else{v.push_back(indicador);}

	 }

	 void nodo_c::devuelve_indicador(float &ind){
        ind=indicador;
	 }

   void nodo_c::devuelve_punto_sig(vector<float> &ps){
        ps=punto_sig;
	 }

   void nodo_c::devuelve_recorrido(vector<float> &rec){
        rec=recorrido;
	 }

   void nodo_c::devuelve_punto_act(float &pa){
        pa=punto_act;
	 }

        void nodo_c::iguala(nodo_c padre_argumento){

			nivel=padre_argumento.nivel;

			/*cout<<"NIVEL: "<<nivel<<endl;
		cout<<"VIVO: "<<vivo<<endl;
		cout<<"INDICADOR: "<<indicador<<endl;
		cout<<"DEFINIDO: "<<definido<<endl;
		cout<<"DISTANCIA_RECORRIDA: "<<distancia_recorrida<<endl;
		cout<<"PUNTO_ACT: "<<punto_act<<endl;
		cout<<"camino: "<<endl;
		m.imprimir_1(camino);
		cout<<"camino_activo: "<<endl;
		m.imprimir_1(camino_activo);
		cout<<"recorrido: "<<endl;
		m.imprimir_1(recorrido);
		cout<<"punto_sig: "<<endl;
		m.imprimir_1(punto_sig);
		cout<<"escoge: "<<endl;
		m.imprimir_1(escoge);*/
		}

        bal nodo_c::actu_padre(float distancia,vector <vector <float>> puntos)
       {
		   int flag; bal b;
		   float var1,var2;
		   matriz_c m;
		   vector<float> r1,r2,auxiliar;
		   vector <vector<float>> aux;

		   if(definido==1){}
		else{
		for(int i=0 ; i < punto_sig.size() ; i++){
			var1=punto_act;
			 var2=punto_sig[i];
			r1=cut_matrix(puntos,var1,-1);
	        r2=cut_matrix(puntos,var2,-1);
			 distancia=norma(resta(r1,r2));
			camino[i]=distancia;
			camino_activo[i]=1;}
			vivo=1;

			// ORDENA NODO
			auxiliar.resize(camino.size());
			auxiliar=ordena_vector(camino);
			punto_sig=reordena_vector2(camino,auxiliar,punto_sig);
			camino_activo=reordena_vector2(camino,auxiliar,camino_activo);
			camino=auxiliar;
			}



			//
			aux=m.reserva(camino_activo.size(),camino_activo.size());
			for(int i=0 ; i < camino_activo.size() ; i++){
			for(int j=0 ; j < camino_activo.size() ; j++){
				aux[i][j]=1;}}
			escoge=cut_matrix(aux,0,-1);

			b.camino_activo=camino_activo;
			b.punto_sig=punto_sig;
			b.recorrido=recorrido;
			return b;

        }

        float nodo_c::actu_padre_2(int i)
       {
		   float dist;
		   camino_activo[i]=0;
		   escoge[i]=0;
		   dist=camino[i];

		   return dist;

        }

         void nodo_c::funcion(int &salir)
       {
		   if(vivo==0){
			salir=1;
			}
        }


        vector<float> nodo_c::actu_padre_3()
       {
		vector<float> mul;

        if(devuelve_activo(camino_activo)==0){
			vivo=0;}
		definido=1;
	   	mul.resize(escoge.size());
		for(int i=0 ; i < escoge.size() ; i++){
			mul[i]=punto_sig[i]*escoge[i];}

        return mul;
        }



         void nodo_c::actu_hijo(float dist,float dis,vector <float> p_s,int i)
       {
		   cout<<"DIST: "<<dist<<endl;
		   cout<<"DIS: "<<dis<<endl;
		   distancia_recorrida=dist+dis;
		   punto_act=p_s[i];

        }

         void nodo_c::es_ultimo(float *distancia,vector<float> r1,vector<float> c,
         vector <float> punto_final,vector <vector <float>> dots){

		   if(punto_sig.size()==0){
		     c[0]=punto_act;
		     r1=cut_matrix(dots,c[0],-1);
		     (*distancia)=norma(resta(r1,punto_final));}
			else{ (*distancia)=0;}

        }




       void nodo_c::actu_hijo_2(vector<float> mul,vector<float> rec){

        punto_sig=refresca_auxiliar_f(mul);
	    recorrido=rec;
        recorrido.push_back (punto_act);
    }


        void nodo_c::madura()
       {
		camino.resize(punto_sig.size());
	    camino_activo.resize(punto_sig.size());
	    escoge.resize(punto_sig.size());
        }
