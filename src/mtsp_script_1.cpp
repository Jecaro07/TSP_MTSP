#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#include <fstream>
#include <sstream>

using namespace std;
 using std::vector;
using namespace std;

  
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
} prueba;

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

void pedir_pantalla_f(vector <vector<vector<float>>> &pp, int &cont_repeticion,vector <int> &A, int &B,
 vector <vector<float>> &punto_final){
 
 int coordenadas,n_puntos,salir_b1=0,CAM=0;
  float pto;
	
string line; 
    vector <string> words;
	ifstream myfile;
	myfile.open("mtsp_datos_2.txt");
	if (myfile.is_open()){
	  
	// COORDENADAS  
   getline (myfile,line) ;
		words = split(line,' ');
		coordenadas=stoi(words[1]);
     // cout << coordenadas<< '\n';  
      words.clear();
    //cout<<endl;
    
    pp.resize(1); 
   punto_final.resize(1);
   
   // PUNTO INICIAL
   pp[0].resize(1); 
   pp[0][0].resize(coordenadas); 
   
   getline (myfile,line) ;
	words = split(line,' ');
   for(int j=0; j<pp[0][0].size();j++){ 
   pp[0][0][j]=stof(words[j+1]);
   //cout << pp[0][0][j]<< ' ';
	 }// fin del for 
   //cout<<endl; 	
   words.clear();
   
   
   while(salir_b1==0){  
      
	
	// PUNTO FINAL
	getline (myfile,line) ;
	words = split(line,' ');
	pto=stof(words[1]);
	//cout<<pto<<endl; cout<<endl;
	words.clear();
	 if(pto==0){
		salir_b1=1;
	}
	else{
		
	if(CAM>0){ 
    pp[CAM].resize(1); 
    pp[CAM][0].resize(coordenadas); 
	pp[CAM][0]=pp[0][0];  
    }
		
	punto_final[CAM].resize(coordenadas);
	
	getline (myfile,line) ;
	words = split(line,' ');
   for(int j=0; j<punto_final[CAM].size();j++){ 
   punto_final[CAM][j]=stof(words[j+1]);
   //cout << punto_final[CAM][j]<< ' ';
	 }// fin del for 
   //cout<<endl; 	
   words.clear();
   
	 }
	
	if(salir_b1==0){
		
		// CIUDADES INTERMEDIAS
   getline (myfile,line) ;
	words = split(line,' ');	
   n_puntos=stoi(words[1]);	
     //cout<< n_puntos <<endl; cout<<endl;
   words.clear();
   getline (myfile,line) ;
   
   n_puntos=n_puntos+1;
   A.resize(CAM+1); A[CAM]=n_puntos;
   pp[CAM].resize(n_puntos); // IMPORTANTE EL RESIZE
   
   
    // PUNTOS DE LA TRAYECTORIA

   for(int i=1; i<n_puntos;i++){
	  getline (myfile,line) ;
	  words = split(line,' ');
	   pp[CAM][i].resize(coordenadas); // IMPORTANTE EL RESIZE
	   for(int j=0; j<coordenadas;j++){    
		pp[CAM][i][j]=stof(words[j]); 
		//cout << pp[CAM][i][j]<< ' ';
		}
		words.clear();
		//cout<<endl;
		} // fin de ambos for
   //cout<<endl;
   
   CAM=CAM+1;
   pp.resize(CAM+1); 
   punto_final.resize(CAM+1);
	}
		
	
	
}

	// NUMERO DE REPETICIONES  
   getline (myfile,line) ;
		words = split(line,' ');
		cont_repeticion=stoi(words[1]);
     //  cout << cont_repeticion<< '\n';  
      words.clear();
    //cout<<endl;
    
    myfile.close();	
	
	}
	else{ cout << "Unable to open file"; 
	} 
   B=coordenadas; // A=n_puntos;
 
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


struct s_dev_hijo devuelve_hijo (int &CIU,int &ccc,int &B, struct nodo padre,const vector<vector<float> > &dots,float dis,int counter){
	struct s_dev_hijo salida; 
    vector<vector<float> > aux;
    int flag; float dist,distancia;
   	vector<float> mul,c,r1,r2;
   	
   	//EMPIEZAN RESIZES
   	c.resize(2);
	r1.resize(B); r2.resize(B); //numero de coordenadas
	
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //5  VECES
	
	padre.camino.resize(padre.punto_sig.size());
	// cout<< "tamaño de punto_sig "<< ccc <<": "<<padre.punto_sig.size()<<endl; ccc=ccc+1;
	//EMPIEZA SIENDO 2 Y DEBERIA EMPEZAR SIENDO 3 (CIU=1)
	
	padre.camino_activo.resize(padre.punto_sig.size());
	padre.escoge.resize(padre.punto_sig.size());

   	//ACABAN RESIZES
   	
   	salida.p=padre;
	
	salida.h.indicador=counter; counter=counter+1;
	salida.h.nivel=1+salida.p.nivel;
	salida.h.definido=0;
		 

	
	if(salida.p.definido==1){}
	else{
	// cout<< "tamaño de punto_sig "<< ccc <<": "<<salida.p.punto_sig.size()<<endl; ccc=ccc+1;
	//EMPIEZA SIENDO 2 Y DEBERIA EMPEZAR SIENDO 3 (CIU=1)

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
	
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //4  VECES
	aux.clear();
	aux.resize(salida.p.camino_activo.size());
    //cout<< "tamaño de camino_activo "<< ccc <<": "<<salida.p.camino_activo.size()<<endl; ccc=ccc+1;


	for(int i=0 ; i < salida.p.camino_activo.size() ; i++){ 
		aux[i].resize(salida.p.camino_activo.size());
	for(int j=0 ; j < salida.p.camino_activo.size() ; j++){
	 aux[i][j]=1;
	}}

	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //4  VECES
 
	
	//cout<< "tamaño de escoge "<< ccc <<": "<<salida.p.escoge.size()<<endl; ccc=ccc+1;
	// 2 2 1 0

	salida.p.escoge=cut_matrix(aux,0,-1); 

	//cout<< "tamaño de escoge "<< ccc <<": "<<salida.p.escoge.size()<<endl; ccc=ccc+1;
	// 2 2 1

	flag=0;
	
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //3  VECES

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
		
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //4  VECES	
		
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
   
   
   //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //4  VECES
   
    return salida;
    
}


struct s_desg_nodo desglosa_nodo (int &CIU,int &ccc,int &B,struct nodo padre,const vector<vector<float> > &puntos2,float dis,int contador_dh){

struct s_dev_hijo salida2;
struct s_desg_nodo devuelto;
int salir,contador;

salir=0; contador=1;

// cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; // 4 VECES

 while(salir==0){
	 
    //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //5  VECES
	salida2=devuelve_hijo(CIU,ccc,B,padre,puntos2,dis,contador_dh);
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //4  VECES

contador=contador+1;
devuelto.a.push_back (salida2.h);


if(salida2.p.vivo==0){
	salir=1;
}

padre=salida2.p;
contador_dh=salida2.contador;
 
 //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //4  VECES
 
 }

devuelto.p=padre;
devuelto.contador=salida2.contador;

// cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //3  VECES

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


void repeticion(int &ccc,int &CIU, int &B, int &salir,nodo &nodo_1,
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
 
  //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; // 1 VEZ
 
 if(es_ultimo(B,nodo_desglosable[INDICE],puntos2,punto_final)>0){
 // no desgloso el nodo si está en el último nivel que quiero
}

else{
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //1  vez
	
	while(salir==0){ // COMIENZO DEL WHILE
	// desgloso los nodos del nivel inferior al que considero 
	// y lo defino completamente	
	
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; // 3 veces
	
		salida_dn=desglosa_nodo(CIU,ccc,B,nodo_1,puntos2,distancia,counter);
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //2  veces	
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
				
	//cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; // 2 veces
				
	} // FIN DEL WHILE
	
  //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //0  veces

	
} // FIN DEL ELSE

 //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; // 0 veces

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
	
	 
 //cout << "CIU: "<< CIU  << "; NUMERO "<< ccc <<endl; ccc=ccc+1; //  0 veces
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

void principal(int &ccc,vector<vector<vector<float>>> &puntos_recorrido_def,vector <float> &uno_tal,vector <float> &dos_tal, 
 vector< vector <vector<float>>> &pp, vector <float> &r2,
 vector <float> &c, vector <float> &r1, vector <float> &MINIMO,
 vector <float> &nodo_final, vector <float> &v, vector <int> &A, int &B,
  int &cont_repeticion, int &tope, int &INDICE, int &salir,
  int &vital, int &flag, int &CIU, float &errorr, bool &c11,bool &c1,
  bool &c2,bool &c3, vector <nodo> &aux,nodo &aux_var,vector <vector<float>> &puntos_recorrido,
 vector <nodo> &nodo_desglosable,vector <nodo> &v_n_maduros,nodo &padre,
 float &distancia,nodo &nodo_1, vector<vector<float>> &punto_final,
 s_desg_nodo &salida_dn, float &counter, float &auxx, vector <float> &nodo_pre){  // definido en un buen lugar? (POSIBLES ERRORES)
	
	  // IMPORTANTE HACER EL RESIZE
	int ffllaagg;
	  
	  dos_tal.reserve(2345);
	  
// IMPORTANTE: USAR UN RESERVE GORDO.
// Por defecto, la capacidad del vector que creo es el tamaño del primer resize
// que le hago al vector. RESERVE me dice el número de elementos que puede contener
// "dos_tal". Con 2345, puedo manejar el numero de ciudades intermedias que
//  me de la gana sin riesgo de quedarme sin memoria.
	  
//uno_tal.clear(); // NO USAR SWAP
//dos_tal.clear(); // NO USAR SWAP
// ME AHORRO HACER "CLEAR": CON EL RESIZE AJUSTO EL TAMAÑO SIN PROBLEMAS.
// AUNQUE EL VECTOR QUEDE LLENO, MÁS ADELANTE SE MODIFICAN SUS
// VALORES EN EL TAMAÑO QUE HE RESERVADO CON "RESIZE".

uno_tal.resize(1);
dos_tal.resize(pp[CIU].size()-1); // (pp[CIU].size()-1)=5
	
 
 r2.resize(B); c.resize(1); 
 puntos_recorrido_def.resize(CIU+1);



for (int j=0;j<pp[CIU].size();j++){
dos_tal[j]=j+1;
}

uno_tal[0]=0;

// DESGLOSA NODO

padre.camino.clear();padre.camino_activo.clear();
padre.escoge.clear();
// ESTO NO HACE NADA

padre.nivel=1;
padre.definido=0;
padre.distancia_recorrida=0;
padre.punto_act=0;
padre.indicador=0;
 padre.recorrido=uno_tal;
 padre.punto_sig.clear();padre.punto_sig=dos_tal; 
 // ESTO TAMPOCO HACE NADA

// DATOS PREVIOS A "REPETICION" 
 counter=0;
  distancia=nodo_1.distancia_recorrida;
  salir=0; 
 nodo_desglosable.clear();nodo_desglosable.push_back(padre);
 
 
 //CLAVE: ESTABA AMONTONANDO SOBRE LOS NODOS DESGLOSABLES DEL OTRO
 // CAMINO (CIU=0). 
 // LOS QUITO CON "CLEAR" Y EMPIEZO CON EL PADRE QUE ESTOY DEFINIENDO
 // EN (CIU=1), donde padre.punto_sig.size()=3 (más puntos quer al principio).
 // Antes me quedaba sin memoria porque manejaba los datos de dimension 2 (2 CIUDADES
 // INTERMEDIAS) de CIU=0.
  
   nodo_pre.clear(); nodo_final.clear(); aux.clear();
 
 // TAMBIÉN TENÍA QUE HACER "CLEAR" CON ESTOS 3 VECTORES.
 // USO "PUSH_BACK" CON ELLOS, Y TENGO QUE RESETEARLOS PARA QUE 
 // QUE EMPIECEN A ACUMULAR DESDE EL PRINCIPIO DE CADA
 // SCRIPT "PRINCIPAL" (Al principio de cada "CIU")
  
	MINIMO.clear();
	
 // PASABA LO MISMO CON MINIMO: ME QUEDABA CON LA DISTANCIA MINIMA DE 
 // LA PRIMERA INTERVENCIÓN DE "PRINCIPAL" (CIU=0)
 
 INDICE=0;
 tope=pp[CIU].size()-1;
 
 //cout <<"creo que el problema esta en inicializar las variables en repeticion" <<endl;

 // EMPIEZA REPETICION
 
 

 
 for(int xz=0;xz<cont_repeticion;xz++){
 repeticion(ccc,CIU,B,salir,nodo_1,nodo_desglosable,INDICE,distancia,
pp[CIU], punto_final[CIU],salida_dn, counter, v_n_maduros,
tope, nodo_pre, c, r1,auxx, nodo_final, v,flag);

}


// EMPIEZA "BUSCA RECORRIDO"

ffllaagg=0;

for (int i = 0; i < nodo_final.size(); i++) {
	if(minimo(nodo_final)==nodo_final[i] && ffllaagg==0){
		vital=i; ffllaagg=1;
	}// fin del if
}// fin del "for"

MINIMO.push_back(minimo(nodo_final));

errorr=pow(10,-4);

for(int i=0; i<nodo_desglosable.size(); i++){
	
	distancia=norma(resta(punto_final[CIU],cut_matrix(pp[CIU],nodo_desglosable[i].punto_act,-1)));
	
	c11= nodo_desglosable[i].punto_sig.size()==0;
	c1= nodo_desglosable[i].nivel==(tope+1); 
	c2=distancia-(nodo_final[vital]-nodo_pre[vital])<errorr;
	c3=nodo_desglosable[i].distancia_recorrida==nodo_pre[vital];
	
	if (c1 && c2 && c3){		
		aux.push_back(nodo_desglosable[i]);	  
	}// fin del if
	
}// fin del for


if(aux.size()>1){
	aux_var=aux[0];
	aux.clear();
	aux.push_back(aux_var);
}

// EN CUALQUIER CASO, AUX TENDRÁ DIMENSIÓN 1

  cout << endl;	
  cout << "RECORRIDO CIUDADES INTERMEDIAS: " << endl;
	for (int j = 1; j < aux[0].recorrido.size(); j++) {
            cout << aux[0].recorrido[j] << " ";
        }   
  cout << endl;cout << endl;
  
  
  // AHORA SOLO ME FALTA VOLCAR EN "PUNTOS_RECORRIDO" 
  // LOS PUNTOS EN EL ORDEN EN EL QUE SE UNIRÁN EN RVIZ (puntos2(ordenado) + punto_final)

puntos_recorrido.resize(A[CIU]+1);


for (int i = 0; i < (A[CIU]); i++) {
	puntos_recorrido[i].resize(B);
	for (int j = 0; j < (B); j++) {
		puntos_recorrido[i][j]=pp[CIU][aux[0].recorrido[i]][j];
		}
        }
                
        puntos_recorrido[A[CIU]].resize(B); 
        for (int j = 0; j < (B); j++) {
		puntos_recorrido[A[CIU]][j]=punto_final[CIU][j];
		}
		
// VUELCO EN "puntos_recorrido_def" el resultado

puntos_recorrido_def[CIU].resize(puntos_recorrido.size());
for (int i=0;i<puntos_recorrido.size();i++){
	puntos_recorrido_def[CIU][i].resize(puntos_recorrido[i].size());
	for (int j=0; j<puntos_recorrido[i].size();j++){
		
	puntos_recorrido_def[CIU][i][j]=puntos_recorrido[i][j];	
		
	}}
  
   
// IMPRIMO RESULTADOS POR PANTALLA   
       
 imprimir_resultados(cont_repeticion,A[CIU],B,puntos_recorrido,pp[CIU],MINIMO,
   aux,vital);
	
}



int main( int argc, char** argv )
{

  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;

int B,cont_repeticion,ccc;
vector <int> A;
   vector<vector<float>> puntos,puntos3;
   vector <vector<vector<float>>> pp, puntos_recorrido_def;
   vector <vector<float>> punto_final;
  
vector<vector<float>> puntos_recorrido;
s_dev_hijo salida,salida2;
s_desg_nodo salida_dn;
nodo padre, nodo_1;
vector<float> v,r1,r2,c;

// VARIABLES DE "REPETICION"
int INDICE,flag,fin,tope;
float auxx,counter;
vector<float> nodo_pre, nodo_final;
//

// VARIABLES DE "BUSCA_RECORRIDO"
int vital, CIU;
bool c11, c1,c2,c3;
float errorr;
vector<float> MINIMO;
vector<nodo> aux;
nodo aux_var;
vector<nodo> v_n_maduros, nodo_desglosable;

int salir,contador;
float distancia;
int contador_dh=1;
vector<nodo> a;

vector<float> uno_tal;
vector<float> dos_tal;



  pedir_pantalla_f(pp, cont_repeticion,A, B, punto_final);
  

 for (int lp=0;lp<(pp.size()-1);lp++){	
  CIU=lp;  ccc=1;
  principal(ccc,puntos_recorrido_def,uno_tal,dos_tal,pp,r2,c,r1,MINIMO,nodo_final,v,A, B,
  cont_repeticion,tope, INDICE,salir,vital,flag, CIU, errorr, c11,c1,c2,c3,
  aux,aux_var,puntos_recorrido,nodo_desglosable,v_n_maduros,padre,
 distancia,nodo_1,punto_final,salida_dn, counter, auxx, nodo_pre);
   CIU=CIU+1; 
 }
 
 //  YA HE PUESTO "principal" EN BUCLE
 // OFICIALMENTE, HE ACABADO EL CASO CON LAS CIUDADES RESTRINGIDAS
 
 // SOLO FALTARIA LIMPIAR TODOS LOS COMENTARIOS QUE ESTOY AÑADIENDO
 // Y HACER MÁS PRUEBAS CON OTROS .txt
 
 
 /*
 principal(ccc,puntos_recorrido_def,uno_tal,dos_tal,pp,r2,c,r1,MINIMO,nodo_final,v,A, B,
  cont_repeticion,tope, INDICE,salir,vital,flag, CIU, errorr, c11,c1,c2,c3,
  aux,aux_var,puntos_recorrido,nodo_desglosable,v_n_maduros,padre,
 distancia,nodo_1,punto_final,salida_dn, counter, auxx, nodo_pre);
 
 CIU=CIU+1; ccc=1;
 
 principal(ccc,puntos_recorrido_def,uno_tal,dos_tal,pp,r2,c,r1,MINIMO,nodo_final,v,A, B,
  cont_repeticion,tope, INDICE,salir,vital,flag, CIU, errorr, c11,c1,c2,c3,
  aux,aux_var,puntos_recorrido,nodo_desglosable,v_n_maduros,padre,
 distancia,nodo_1,punto_final,salida_dn, counter, auxx, nodo_pre);
 
 CIU=CIU+1; ccc=1;
 
 principal(ccc,puntos_recorrido_def,uno_tal,dos_tal,pp,r2,c,r1,MINIMO,nodo_final,v,A, B,
  cont_repeticion,tope, INDICE,salir,vital,flag, CIU, errorr, c11,c1,c2,c3,
  aux,aux_var,puntos_recorrido,nodo_desglosable,v_n_maduros,padre,
 distancia,nodo_1,punto_final,salida_dn, counter, auxx, nodo_pre); */


  // AHORA ESTOY PROBANDO CON "mtsp_datos_2.txt" y me da fallo con más de 
  // 2 ciudades intermedias
  // TENGO QUE VER DONDE ESTA EL ERROR Y PONER PRINCIPAL EN BUCLE
  
  // Con 2 ciudades intermedias no da fallo; ponga en el orden que ponga
  // la ruta más larga y la más corta 
  
 /* principal(ccc,puntos_recorrido_def,uno_tal,dos_tal,pp,r2,c,r1,MINIMO,nodo_final,v,A, B,
  cont_repeticion,tope, INDICE,salir,vital,flag, CIU, errorr, c11,c1,c2,c3,
  aux,aux_var,puntos_recorrido,nodo_desglosable,v_n_maduros,padre,
 distancia,nodo_1,punto_final,salida_dn, counter, auxx, nodo_pre);
 
 cout<< "TAMAÑO DE A: " << A.size() << endl;*/
  
 /* 
  // IMPORTANTE HACER EL RESIZE
uno_tal.resize(1);
dos_tal.resize(pp[0].size()-1);
 r2.resize(B); c.resize(1); 
for (int j=0;j<pp[0].size();j++){
dos_tal[j]=j+1;
}
uno_tal[0]=0;
// DESGLOSA NODO
padre.nivel=1;
padre.definido=0;
padre.distancia_recorrida=0;
padre.punto_act=0;
padre.indicador=0;
 padre.recorrido=uno_tal;
 padre.punto_sig=dos_tal; 
// DATOS PREVIOS A "REPETICION" 
 counter=0;
  distancia=nodo_1.distancia_recorrida;
  salir=0; 
 nodo_desglosable.push_back(padre);
 INDICE=0;
 tope=pp[0].size()-1;
 
 // EMPIEZA REPETICION
 
 for(int xz=0;xz<cont_repeticion;xz++){
 
 repeticion(B,salir,nodo_1,nodo_desglosable,INDICE,distancia,
pp[0], punto_final[0],salida_dn, counter, v_n_maduros,
tope, nodo_pre, c, r1,auxx, nodo_final, v,flag);
}
// EMPIEZA "BUSCA RECORRIDO"
for (int i = 0; i < nodo_final.size(); i++) {
	if(minimo(nodo_final)==nodo_final[i]){
		vital=i;
	}// fin del if
}// fin del "for"
MINIMO.push_back(minimo(nodo_final));
errorr=pow(10,-4);
for(int i=0; i<nodo_desglosable.size(); i++){
	
	distancia=norma(resta(punto_final[0],cut_matrix(pp[0],nodo_desglosable[i].punto_act,-1)));
	
	c11= nodo_desglosable[i].punto_sig.size()==0;
	c1= nodo_desglosable[i].nivel==(tope+1); 
	c2=distancia-(nodo_final[vital]-nodo_pre[vital])<errorr;
	c3=nodo_desglosable[i].distancia_recorrida==nodo_pre[vital];
	
	if (c1 && c2 && c3){		
		aux.push_back(nodo_desglosable[i]);	  
	}// fin del if
	
}// fin del for
if(aux.size()>1){
	aux_var=aux[0];
	aux.clear();
	aux.push_back(aux_var);
}
// EN CUALQUIER CASO, AUX TENDRÁ DIMENSIÓN 1
  cout << endl;	
  cout << "RECORRIDO CIUDADES INTERMEDIAS: " << endl;
	for (int j = 1; j < aux[0].recorrido.size(); j++) {
            cout << aux[0].recorrido[j] << " ";
        }   
  cout << endl;cout << endl;
  
  
  // AHORA SOLO ME FALTA VOLCAR EN "PUNTOS_RECORRIDO" 
  // LOS PUNTOS EN EL ORDEN EN EL QUE SE UNIRÁN EN RVIZ (puntos2(ordenado) + punto_final)
puntos_recorrido.resize(A[0]+1);
for (int i = 0; i < (A[0]); i++) {
	puntos_recorrido[i].resize(B);
	for (int j = 0; j < (B); j++) {
		puntos_recorrido[i][j]=pp[0][aux[0].recorrido[i]][j];
		}
        }
                
        puntos_recorrido[A[0]].resize(B); 
        for (int j = 0; j < (B); j++) {
		puntos_recorrido[A[0]][j]=punto_final[0][j];
		}  
   
// IMPRIMO RESULTADOS POR PANTALLA   
       
 imprimir_resultados(cont_repeticion,A[0],B,puntos_recorrido,pp[0],MINIMO,
   aux,vital);
       
//FIN PRUEBAS
*/





  while (ros::ok())
  {

    visualization_msgs::Marker points ,pf, po, line_list;
    
    vector<visualization_msgs::Marker> line_strip;
    line_strip.reserve(100);
    line_strip.resize(puntos_recorrido_def.size());
    
    
    po.header.frame_id =pf.header.frame_id =points.header.frame_id = line_list.header.frame_id = "/my_frame";
    po.header.stamp =pf.header.stamp =points.header.stamp =  line_list.header.stamp = ros::Time::now();
    po.ns =pf.ns =points.ns = line_list.ns = "points_and_lines";
    po.action =pf.action =points.action =  line_list.action = visualization_msgs::Marker::ADD;
    po.pose.orientation.w =pf.pose.orientation.w =points.pose.orientation.w =  line_list.pose.orientation.w = 1.0;


 for(uint32_t i=0; i<puntos_recorrido_def.size(); i++){
	line_strip[i].header.frame_id = "/my_frame";
    line_strip[i].header.stamp = ros::Time::now();
    line_strip[i].ns = "points_and_lines";
    line_strip[i].action = visualization_msgs::Marker::ADD;
    line_strip[i].pose.orientation.w = 1.0;
    }


    points.id = 0;
    line_list.id = 1;
    pf.id = 2; po.id = 3;
    
    for(uint32_t i=0; i<puntos_recorrido_def.size(); i++){ 
    line_strip[i].id = i+4;
      }


    points.type = visualization_msgs::Marker::POINTS; 
    po.type = visualization_msgs::Marker::POINTS;
    pf.type = visualization_msgs::Marker::POINTS;
    line_list.type = visualization_msgs::Marker::LINE_LIST;

	for(uint32_t i=0; i<puntos_recorrido_def.size(); i++){ 
		line_strip[i].type = visualization_msgs::Marker::LINE_STRIP;
      }


    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 0.2;
    points.scale.y = 0.2;
    
    po.scale.x = 0.2;
    po.scale.y = 0.2;
    
    pf.scale.x = 0.2;
    pf.scale.y = 0.2;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    
	
	for(uint32_t i=0; i<puntos_recorrido_def.size(); i++){ 
		line_strip[i].scale.x = 0.1;
      }


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
    for(uint32_t i=0; i<puntos_recorrido_def.size(); i++){ 
		
		if(i==0){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 0;
		line_strip[i].color.b = 0;
		} 

		if(i==1){
		line_strip[i].color.r = 0;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 0;
		}

		if(i==2){
		line_strip[i].color.r = 0;
		line_strip[i].color.g = 0;
		line_strip[i].color.b = 1.0;
		}
		if(i==3){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 0;
		}
		if(i==4){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 0;
		line_strip[i].color.b = 1.0;
		}
		if(i==5){
		line_strip[i].color.r = 0;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 1.0;
		}
		if(i==6){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 1.0;
		}
		
		if(i==7){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 0.5;
		line_strip[i].color.b = 0.5;
		}
		if(i==8){
		line_strip[i].color.r = 0.5;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 0.5;
		}
		if(i==9){
		line_strip[i].color.r = 0.5;
		line_strip[i].color.g = 0.5;
		line_strip[i].color.b = 1.0;
		}
		if(i==10){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 0.5;
		}
		if(i==11){
		line_strip[i].color.r = 1.0;
		line_strip[i].color.g = 0.5;
		line_strip[i].color.b = 1.0;
		}
		if(i>11){  // COLOR CIAN
		line_strip[i].color.r = 0;
		line_strip[i].color.g = 1.0;
		line_strip[i].color.b = 1.0;
		}
		
	// FALTA PROBAR MUCHAS RUTAS SIMULTANEAS PARA VER COMO VARIAN LOS COLORES
	// SE PODRIA MEJORAR PAR MAS DE 11 RUTAS (PARA AYUDAR A DISTINGUIR LOS
	// CAMINOS, NADA MÁS)
		
		line_strip[i].color.a = 1.0;
      }

	// HAY QUE HACER UN "ROSLAUNCH" PARA QUE SE ABRA "RVIZ" CADA VEZ QUE
	// RESUELVO MTSP; SI NO, LAS LINEAS DE DISTINTOS COLORES SE MEZCLAN

    // Line list is red
    line_list.color.r = 1.0;
    line_list.color.a = 1.0;



    // Create the vertices for the points and lines
    for (uint32_t ii = 0; ii < puntos_recorrido_def.size(); ++ii){
   
   // IDA 
    for (uint32_t i = 0; i < puntos_recorrido_def[ii].size(); ++i)
    {
      geometry_msgs::Point p;
      p.x = (float)puntos_recorrido_def[ii][i][0] ;
      p.y = (float)puntos_recorrido_def[ii][i][1] ;
      
      if(B==3){
     p.z = (float)puntos_recorrido_def[ii][i][2];
	}
	
	if(i==0){
      po.points.push_back(p);
      line_strip[ii].points.push_back(p);
     }
     if(i==(puntos_recorrido_def[ii].size()-1)){
      pf.points.push_back(p);
      line_strip[ii].points.push_back(p);
     }
     if(i>0 && i<(puntos_recorrido_def[ii].size()-1)){
      points.points.push_back(p);
      line_strip[ii].points.push_back(p);
     }
    }
    
    // VUELTA
    // Hay que poner este otro bucle para que vuelva desde el DESTINO 
    // hasta el ORIGEN y a partir de ahi, recorra la siguiente ruta
    // AHORA SE REPRESENTAN BIEN LAS RUTAS EN RVIZ
    
    for (uint32_t i = (puntos_recorrido_def[ii].size()); i > 0; --i)
    {
      geometry_msgs::Point p;
      p.x = (float)puntos_recorrido_def[ii][i-1][0] ;
      p.y = (float)puntos_recorrido_def[ii][i-1][1] ;
      
      if(B==3){
     p.z = (float)puntos_recorrido_def[ii][i-1][2];
	}
	
	if((i-1)==0){
      po.points.push_back(p);
      line_strip[ii].points.push_back(p);
     }
     if((i-1)==(puntos_recorrido_def[ii].size()-1)){
      pf.points.push_back(p);
      line_strip[ii].points.push_back(p);
     }
     if((i-1)>0 && (i-1)<(puntos_recorrido_def[ii].size()-1)){
      points.points.push_back(p);
      line_strip[ii].points.push_back(p);
     }
    }
    
  }// FIN DEFINITIVO FOR
  
  
/*
for (uint32_t i = 0; i < puntos_recorrido_def[1].size(); ++i)
    {
      geometry_msgs::Point p;
      p.x = (float)puntos_recorrido_def[1][i][0] ;
      p.y = (float)puntos_recorrido_def[1][i][1] ;
      
      if(B==3){
     p.z = (float)puntos_recorrido_def[1][i][2];
	}
	
	if(i==0){
      po.points.push_back(p);
      line_strip.points.push_back(p);
     }
     
     if(i==(puntos_recorrido_def[1].size()-1)){
      pf.points.push_back(p);
      line_strip.points.push_back(p);
     }
     if(i>0 && i<(puntos_recorrido_def[1].size()-1)){
      points.points.push_back(p);
      line_strip.points.push_back(p);
     }
    }*/



	marker_pub.publish(po);
	marker_pub.publish(pf);
    marker_pub.publish(points);
    
    for(uint32_t i=0; i<puntos_recorrido_def.size(); i++){ 
		marker_pub.publish(line_strip[i]);
      }

    r.sleep();

  }
} 
