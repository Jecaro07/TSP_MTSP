#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include "matriz_c.h"

#include <fstream>
#include <sstream>

using namespace std;
 using std::vector;
using namespace std;

 
 struct bal {
vector<float> punto_sig;
vector<float> camino_activo;
vector<float> recorrido;
} ;
  
struct nodo {
vector<float>  escoge;
int nivel;
int vivo;
float indicador;
int definido;
float distancia_recorrida;
float punto_act;
vector<float> punto_sig;
vector<float> camino;
vector<float> camino_activo;
vector<float> recorrido;
} ;

struct s_dev_hijo {
struct nodo p;
struct nodo h;
int contador;
} ;

struct s_desg_nodo {
vector<nodo> a;
struct nodo p;
int contador;
} ;


std::string input_file = "";

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}


 void pedir_pantalla_f(int &cont_repeticion,int &A, int &B, vector<vector<float>> &puntos,
 vector<float> &punto_final){
 
 int coordenadas,n_puntos;
  float pto;
  
  string line; 
    vector <string> words;
    vector <float> p_inicial;
    vector <vector<float>> p;
  ifstream myfile;
  myfile.open(input_file);
  if (myfile.is_open()){
	  
	// COORDENADAS  
   getline (myfile,line) ;
		words = split(line,' ');
		coordenadas=stoi(words[1]);
      //cout << coordenadas<< '\n';  
      words.clear();
    //cout<<endl;
    
    // PUNTOS_INTERMEDIOS 
    getline (myfile,line) ;
		words = split(line,' ');
		n_puntos=stoi(words[1]);
      //cout << n_puntos<< '\n';  
      n_puntos=n_puntos+1;
      words.clear();
    //cout<<endl;
    
    puntos.resize(n_puntos);
    
    
    // PUNTO_INICIAL 
    getline (myfile,line) ;
		words = split(line,' ');
	puntos[0].resize(coordenadas);
	for (int j=0;j<puntos[0].size();j++){
	puntos[0][j]=stof(words[j+1]);
	//cout << puntos[0][j]<< '\n'; 
	} 
      words.clear();
    //cout<<endl;
    
    // PUNTO_FINAL 
    getline (myfile,line) ;
		words = split(line,' ');
	punto_final.resize(coordenadas);
	for (int j=0;j<punto_final.size();j++){
	punto_final[j]=stof(words[j+1]);
	//cout << punto_final[j]<< '\n'; 
	} 
      words.clear(); 
    //cout<<endl;
  
  // PUNTOS TRAYECTORIA
  getline (myfile,line);
  
  for(int i=0;i<(n_puntos-1);i++){	  
  getline (myfile,line) ;
		words = split(line,' ');
	puntos[i+1].resize(coordenadas);
	for (int j=0;j<puntos[i+1].size();j++){
	puntos[i+1][j]=stof(words[j]);
	//cout << puntos[i+1][j]<< '\n'; 
	} 
      words.clear();
    //cout<<endl;
  }
  
  
  // NUMERO DE REPETICIONES  
   getline (myfile,line) ;
		words = split(line,' ');
		cont_repeticion=stoi(words[1]);
       //cout << cont_repeticion<< '\n';  
      words.clear();
    //cout<<endl;
    
    myfile.close();
  }

  else{ cout << "Unable to open file"; 
}
  
  
   
   B=coordenadas; A=n_puntos; 
 
 }

std::vector<float> cut_matrix (const vector<vector<float> > &matriz,float fila,float columna){
	
	if (columna==-1){
		vector<float> resultado;
		resultado.resize(matriz[0].size());
		for (int i = 0; i < matriz[0].size(); i++) {	
		resultado[i] = matriz[fila][i];
		}
			return resultado;

	}

	if(fila==-1){
		vector<float> resultado;
		resultado.resize(matriz.size());
		for (int z = 0; z < matriz.size(); z++) {
		resultado[z] = matriz[z][columna];
		}
			return resultado;

	}
}

float minimo(std::vector<float> temp){
	float y; 
	float v[temp.size()]; float *p;
	
	for(int i=0;i<temp.size();i++){
		
		v[i]=temp[i];
	}
	
	p=std::min_element(v,v+temp.size()) ;
	y=*p;

	return y;
 
}

float norma(std::vector<float> u){
	float accum = 0,norm;
    for (int i = 0; i < u.size(); i++) {
        accum += u[i] * u[i];
    }
    return norm = sqrt(accum);
}

vector<float> resta(vector<float> r1,vector<float> r2){
	vector<float> res;
	res.resize(r1.size());
	
	for(int i=0; i<r1.size();i++){
		res[i]=r1[i]-r2[i];
	}
	return res;
}

vector<float> ordena_vector(vector<float> v){
	vector<float> v_,v_aux;
	int lon=v.size(),flag,contt,cont_;
	v_.resize(v.size());
	v_aux.resize(v.size());
	contt=0; ; cont_=0;
	
	for(int j=0;j<lon;j++){
		flag=0;

		for(int i=0;i<v.size();i++){

			if(minimo(v)==v[i] && flag==0){
				v_[cont_]=v[i];
				flag=1; v[i]=0; cont_=cont_+1;
				
			}
			
		}
		
		for(int i=0;i<v.size();i++){
		
		if(v[i]==0){}
		else{
			v_aux.resize(v.size()-1);
			v_aux[contt]=v[i];
		  contt=1+contt;

		}
		}
		v.clear();
		v.resize(v_aux.size());
		v=v_aux;
		contt=0;
	}
			return v_;

	
}


vector<float> reordena_vector2(vector<float> v_original, vector<float> v_ordenado, vector<float> v_a_cambiar){
	vector<float> v_cambiado;int flag=0;
	v_cambiado.resize(v_original.size());

	for(int i=0; i<v_original.size(); i++){
	for(int j=0; j<v_ordenado.size(); j++){
		
		if(v_original[j]==v_ordenado[i] && flag==0){
			
			v_cambiado[i]=v_a_cambiar[j];
			v_original[j]=-1; flag=1;			
		}
			
	}	
	flag=0;	
	}
	return v_cambiado;
	
	}




nodo ordena_nodo(nodo p){
	vector<float> auxiliar;
	auxiliar.resize(p.camino.size());
	
	auxiliar=ordena_vector(p.camino);	
	p.punto_sig=reordena_vector2(p.camino,auxiliar,p.punto_sig);
	p.camino_activo=reordena_vector2(p.camino,auxiliar,p.camino_activo);
	
	p.camino=auxiliar; 
	return p;
}

vector<float> refresca_auxiliar_f( vector<float> entrada){
	vector<float> indices_aux, indices=entrada,salida;
	for(int x=0;x<indices.size();x++){
			if(indices[x]==0){}
		else{
			indices_aux.push_back (indices[x]);
		}
	}
	salida=indices_aux;
	return salida;
}





int devuelve_activo(std::vector<float> v){
	
	int res, flag=0;
	for(int i=0;i<v.size();i++){
		if(flag==0 && v[i]==1){
			flag=1; res=1;
		}
		if((v.size()-1)==i && flag==0){
			res=0;
		}
	}
	return res;
	}


int componente_rep(vector<float> v,int numero){
	int res=0;
	for(int i=0;i<v.size();i++){
		if(numero==v[i]){
			res=1;}		
	}// fin del "for"
	return res;
} // fin de "componente_rep"


float es_ultimo(int &B, struct nodo n,const vector<vector<float> > &dots, vector<float> punto_final){
	
	vector<float> c,r1;
	float distancia;
	r1.resize(B); c.resize(1); //numero de coordenadas
	
	
	if(n.punto_sig.size()==0){
		c[0]=n.punto_act; 
		r1=cut_matrix(dots,c[0],-1);
		distancia=norma(resta(r1,punto_final));
	}
	else{
		distancia=0;
	}
	return distancia;
}



struct s_dev_hijo devuelve_hijo (int &B, struct nodo padre,
const vector<vector<float> > &dots,float dis,int counter){
	struct s_dev_hijo salida; 
    vector<vector<float> > aux;
    int flag; float dist,distancia;
   	vector<float> mul,c,r1,r2;
   	
   	//EMPIEZAN RESIZES
   	c.resize(2);
	//r1.resize(B); r2.resize(B); //numero de coordenadas
	
	padre.camino.resize(padre.punto_sig.size());
	padre.camino_activo.resize(padre.punto_sig.size());
	padre.escoge.resize(padre.punto_sig.size());

   	//ACABAN RESIZES
   	
   	salida.p=padre;
	
	salida.h.indicador=counter; counter=counter+1;
	salida.h.nivel=1+salida.p.nivel;
	salida.h.definido=0;
		 

	
	if(salida.p.definido==1){}
	else{
		for(int i=0 ; i < salida.p.punto_sig.size() ; i++){
			c[0]=salida.p.punto_act;
			 c[1]=salida.p.punto_sig[i];
			r1=cut_matrix(dots,c[0],-1);
	        r2=cut_matrix(dots,c[1],-1);
			 distancia=norma(resta(r1,r2));
			salida.p.camino[i]=distancia;
			salida.p.camino_activo[i]=1;

		}//FIN DEL FOR 
		salida.p.vivo=1;	
		salida.p=ordena_nodo(salida.p);	

	}
	
	aux.resize(salida.p.camino_activo.size(), vector<float>(salida.p.camino_activo.size()));

	for(int i=0 ; i < salida.p.camino_activo.size() ; i++){ 
	for(int j=0 ; j < salida.p.camino_activo.size() ; j++){
	 aux[i][j]=1;
	}}

	salida.p.escoge=cut_matrix(aux,0,-1); 

	flag=0;

		for(int i=0 ; i < salida.p.camino_activo.size() ; i++){
		if(flag==0 && salida.p.camino_activo[i]==1){
			flag=1;
			salida.p.camino_activo[i]=0;
			salida.p.escoge[i]=0;
			dist=salida.p.camino[i];
			salida.h.distancia_recorrida=dist+dis; 
			salida.h.punto_act=salida.p.punto_sig[i]; 
			
		}
		}
		
		if(devuelve_activo(salida.p.camino_activo)==0){
			salida.p.vivo=0;
		}
		
		salida.p.definido=1;
	
	//MULTIPLICO ELEMENTO A ELEMENTO--->BEGIN
	//se hace el resize
	   	mul.resize(salida.p.escoge.size());
	
	for(int i=0 ; i < salida.p.escoge.size() ; i++){ 
		mul[i]=salida.p.punto_sig[i]*salida.p.escoge[i];
	}
	

	salida.h.punto_sig=refresca_auxiliar_f(mul);	
	
	// REPASAR ESTAS DOS ÚLTIMAS LÍNEAS
	salida.h.recorrido=salida.p.recorrido;	
    salida.h.recorrido.push_back (salida.h.punto_act);	
    
    // DEVUELVO LA SALIDA
    salida.contador=counter;
   
    return salida;
    
}


struct s_desg_nodo desglosa_nodo (int &B,struct nodo padre,
const vector<vector<float> > &puntos2,float dis,int contador_dh){

struct s_dev_hijo salida2;
struct s_desg_nodo devuelto;
int salir,contador;

salir=0; contador=1;



 while(salir==0){

	salida2=devuelve_hijo(B,padre,puntos2,dis,contador_dh);

contador=contador+1;
devuelto.a.push_back (salida2.h);


if(salida2.p.vivo==0){
	salir=1;
}

padre=salida2.p;
contador_dh=salida2.contador;

 }

devuelto.p=padre;
devuelto.contador=salida2.contador;

return devuelto;

}


void salida_desglosa_nodo(s_desg_nodo salida_dn){
	
	ROS_INFO("DESGLOSE, Y'ALL: ");
  ROS_INFO("\n");
	
ROS_INFO("CONTADOR: ");
            cout << salida_dn.contador << " "; 
  ROS_INFO("\n");	
	
	
	 ROS_INFO("NIVEL HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
            cout << salida_dn.a[i].nivel << " ";
        }   
  ROS_INFO("\n");
 
  ROS_INFO("DEFINIDO HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
            cout << salida_dn.a[i].definido << " ";
        }   
  ROS_INFO("\n");
  
  ROS_INFO("DIS_RECORR. HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
            cout << salida_dn.a[i].distancia_recorrida << " ";
        }   
  ROS_INFO("\n");
 
   ROS_INFO("PUNTO ACT. HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
            cout << salida_dn.a[i].punto_act << " ";
        }   
  ROS_INFO("\n");
  
     ROS_INFO("INDICADOR HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
            cout << salida_dn.a[i].indicador << " ";
        }   
  ROS_INFO("\n");
  
     ROS_INFO("RECORRIDO HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
	cout << "HIJO " << i << ": " ;
	for (int j = 0; j < salida_dn.a[i].recorrido.size(); j++) {
            cout << salida_dn.a[i].recorrido[j] << " ";
		}
		ROS_INFO("\n");
        }   
  ROS_INFO("\n");
  
     ROS_INFO("PUNTO SIG. HIJOS: ");
for (int i = 0; i < salida_dn.a.size(); i++) {
	cout << "HIJO " << i << ": " ;
	for (int j = 0; j < salida_dn.a[i].punto_sig.size(); j++) {
            cout << salida_dn.a[i].punto_sig[j] << " ";
		}
		ROS_INFO("\n");
        }   
  ROS_INFO("\n");

  ROS_INFO("¿CUANTOS PUNTOS SIGUIENTES HAY?: ");
  cout << salida_dn.a[0].punto_sig.size() << " ";
    ROS_INFO("\n");


}


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

void imprimir_resultados(int cont_repeticion,int A, int B,
  vector<vector<float>> puntos_recorrido,
  vector<vector<float>> puntos, vector<float> MINIMO,
  vector<nodo> aux, int vital){
	
	cout << "DATOS DE ENTRADA " << endl;
  cout << "Espacio " << B << "D " << endl;
  cout << "Número de repeticiones: " << cont_repeticion << endl;

  
  cout << "Ciudad inicio= [ " ;
	for (int i = 0; i < B; i++) {
		if(i==(B-1)){
			cout << puntos_recorrido[0][i] << " ] ";
		}
		else{
            cout << puntos_recorrido[0][i] << ", ";
        }   
	}
  cout << endl;
  
    cout << "Ciudad destino= [ " ;
	for (int i = 0; i < B; i++) {
		if(i==(B-1)){
			cout << puntos_recorrido[A][i] << " ] ";
		}
		else{
            cout << puntos_recorrido[A][i] << ", ";
        }   
	}
  cout << endl;
  
  cout << "Ciudades intermedias ( " << (A-1) << " )"<< endl;
	for (int i = 1; i < A; i++) {
		for (int j=0; j<B;j++){
			
		if(j==0){
			cout << "  " << i << ": [ " << puntos[i][j] << ", ";
		}
		else {
			if(j==(B-1)){
            cout << puntos[i][j] << " ] " << endl;
			}
			else{
			cout << puntos[i][j] << ", ";
			}   
		}}
	}
  
  
  cout << endl;
  
  cout << "DATOS DE SALIDA " << endl;
  cout << "Distancia recorrida: " << MINIMO[0] << " uds" << endl;     
  cout << "Recorrido " << endl;     
       for (int i = 0; i < (A+1); i++) {
		for (int j=0; j<B;j++){
			
		if(j==0){
			if((i==0) || (i==A)){
			cout <<"      [ " << puntos_recorrido[i][j] << ", ";
		    }
		    else{
			cout <<"  " << aux[0].recorrido[i] << ":  [ " << puntos_recorrido[i][j] << ", ";				
			}
		}
		
		else {
			if(j==(B-1)){
				
			if (i==0){
            cout << puntos_recorrido[i][j] << " ]   INICIO  (PUNTO BLANCO)" << endl;
		    }
		    if (i==A){
            cout << puntos_recorrido[i][j] << " ]   FINAL  (PUNTO ROJO)" << endl;
		    }
		    if (i>0 && i<A){
            cout << puntos_recorrido[i][j] << " ]   (PUNTO VERDE)" << endl;
		    }
            
            if(i<A){
				if(B==3){
            cout <<"           | " << endl;
            cout <<"           |   ( " << norma(resta(puntos_recorrido[i],puntos_recorrido[i+1])) << " ) uds" << endl;
            cout <<"           | " << endl;
            cout <<"           V " << endl;}
                if(B==2){
            cout <<"         | " << endl;
            cout <<"         |   ( " << norma(resta(puntos_recorrido[i],puntos_recorrido[i+1])) << " ) uds" << endl;
            cout <<"         | " << endl;
            cout <<"         V " << endl;}
		    }
			
			}
			else{
			cout << puntos_recorrido[i][j] << ", ";
			}   
		}}
	}
   cout << "Óptimo alcanzado en iteración: " << (vital+1) << endl; 
   cout << endl;
	
}



class nodo_c
{
    private:
        vector<float>  escoge; //
		int nivel;
		int vivo;
		float indicador; // FLOAT en un principio
		int definido;
		float distancia_recorrida;
		float punto_act;
		vector<float> punto_sig; //
		vector<float> camino; //
		vector<float> camino_activo; //
		vector<float> recorrido; //
    public:
       
       
       void imprime() 
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
       
       void ini_padre(vector <vector <float>> puntos) 
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
        
        void ini_hijo(int &contador_def,int &valor) 
       {
		
		indicador=contador_def; contador_def=contador_def+1;
		cout<<"INDICADOR: "<<indicador<<endl;
		nivel=1+valor;
		definido=0;

        }
        
        void vuelca_distancia(float &distancia) 
       {
		distancia=distancia_recorrida;
		
		//return (*distancia);
        }
        
      //  a[ii].f_nodo_pre(&c[0],&nodo_pre);
        
        float f_nodo_pre(vector <float> &nodo_pre){    
		nodo_pre.push_back(distancia_recorrida);
		return punto_act; // NO SE SI ESTA ES LA NOMENCLATURA 
		}
        
       void f_nodo_final(vector <float> &nodo_final,float &auxx){ 
       
		nodo_final.push_back((distancia_recorrida)+auxx);
		}
		
		
        void devuelve_nivel(int &valor){
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
		
	 void condicion_nodo_desglosable(vector <float> &v,float &ind,
	       int &INDICE,int i, int &flag){
			   
        if((indicador>0) 
		& (componente_rep(v,indicador)==0) 
		& (flag==0) & (punto_sig.size()>0)){
		
		INDICE=i;
		indicador=0; flag=1;}
	 }	
	 
	 
	 void condicion_v_n_maduros(vector <float> &v,float &ind){
        if((indicador==0) 
        || ((indicador)-(ind)<0)
         || (componente_rep(v,indicador))){} 
		
		else{v.push_back(indicador);}
		
	 }
	 
	 void devuelve_indicador(float &ind){
        ind=indicador;
	 }
        
        void iguala(nodo_c padre_argumento){
			
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
        
        bal actu_padre(float distancia,vector <vector <float>> puntos) 
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
        
        float actu_padre_2(int i) 
       {
		   float dist;
		   camino_activo[i]=0;
		   escoge[i]=0;
		   dist=camino[i];
		   
		   return dist;
		   
        }
        
         void funcion(int &salir) 
       {
		   if(vivo==0){  
			salir=1;
			}
        }
        
        
        vector<float> actu_padre_3() 
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
        
        
        
         void actu_hijo(float dist,float dis,vector <float> p_s,int i) 
       {
		   cout<<"DIST: "<<dist<<endl;
		   cout<<"DIS: "<<dis<<endl;
		   distancia_recorrida=dist+dis; 
		   punto_act=p_s[i]; 
		   
        }
        
         void es_ultimo(float *distancia,vector<float> r1,vector<float> c,
         vector <float> punto_final,vector <vector <float>> dots){			 
			 
		   if(punto_sig.size()==0){
		     c[0]=punto_act; 
		     r1=cut_matrix(dots,c[0],-1);
		     (*distancia)=norma(resta(r1,punto_final));}
			else{ (*distancia)=0;}
			
        }
        
        
        
        
       void actu_hijo_2(vector<float> mul,vector<float> rec){  
		   
        punto_sig=refresca_auxiliar_f(mul);	
	    recorrido=rec;	
        recorrido.push_back (punto_act);
    }	
        
        
        void madura() 
       {
		camino.resize(punto_sig.size());
	    camino_activo.resize(punto_sig.size());
	    escoge.resize(punto_sig.size());
        }
        
     
        
};
 
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

float es_ultimo_c(int &B, nodo_c n,const vector<vector<float> > &dots, vector<float> punto_final){
	
	vector<float> c,r1;
	float distancia;
	r1.resize(B); c.resize(1); //numero de coordenadas
	
	n.es_ultimo(&distancia,r1,c,punto_final,dots);
	
	return distancia;
}


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
