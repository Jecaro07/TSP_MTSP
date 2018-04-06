#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
//#include <array>

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

#define A 5 // NUMERO DE PUNTOS DE LA TRAYECTORIA (de la matriz "puntos")
#define B 2 // NUMERO DE COORDENADAS

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



// vector<vector<float> > matriz
// float matriz[A][B]
// ACORDARME DE HACERLO POR REFERENCIA SI CAMBIA LA DIMENSION DE LA MATRIZ
std::vector<float> cut_matrix (const vector<vector<float> > &matriz,float fila,float columna){
	//int* resultado;
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
	
	p.camino=auxiliar; //asignacion vectores inmediata???
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


float es_ultimo(struct nodo n,const vector<vector<float> > &dots, vector<float> punto_final){
	
	vector<float> c,r1;
	float distancia;
	r1.resize(2); c.resize(1); //numero de coordenadas
	
	
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


struct s_dev_hijo devuelve_hijo (struct nodo padre,const vector<vector<float> > &dots,float dis,int counter){
	struct s_dev_hijo salida; 
    vector<vector<float> > aux;
    int flag; float dist,distancia;
   	vector<float> mul,c,r1,r2;
   	
   	//EMPIEZAN RESIZES
   	c.resize(2);
	r1.resize(2); r2.resize(2); //numero de coordenadas
	
	padre.camino.resize(padre.punto_sig.size());
	padre.camino_activo.resize(padre.punto_sig.size());
	padre.escoge.resize(padre.punto_sig.size());

   	//ACABAN RESIZES
   	
   	salida.p=padre;
   	
/*   	ROS_INFO("CONTADOR (DEV_HIJO): ");
            cout << counter << " "; 
  ROS_INFO("\n"); */	
	
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

// INTENTO 1
//	ROS_INFO("CAMINO DESORDENADO 1: ");
//	cout<<salida.p.camino[0]<<" "<<salida.p.camino[1]<<" "<<salida.p.camino[2]<<" "<<salida.p.camino[3]<<" "<<endl;
//    ROS_INFO("\n");
    
 // INTENTO 2
 /*
 ROS_INFO("CAMINO DESORDENADO 2: ");
 for (int i = 0; i < salida.p.camino.size(); i++) {
            cout << salida.p.camino[i] << " ";
        }   
  ROS_INFO("\n");
   */ 

		salida.p=ordena_nodo(salida.p);	

	}
	
	aux.resize(salida.p.camino_activo.size(), vector<float>(salida.p.camino_activo.size()));

	for(int i=0 ; i < salida.p.camino_activo.size() ; i++){ //indices bien nombrados??
	for(int j=0 ; j < salida.p.camino_activo.size() ; j++){
	 aux[i][j]=1;
	}}

	salida.p.escoge=cut_matrix(aux,0,-1); //repasar si devuelve un vector

//	cout<<salida.p.escoge[0]<<" "<<salida.p.escoge[1]<<" "<<salida.p.escoge[2]<<" "<<salida.p.escoge[3]<<" "<<endl;
//	ROS_INFO("TAMANO: %f",aux[1][3]);


	flag=0;

		for(int i=0 ; i < salida.p.camino_activo.size() ; i++){
		if(flag==0 && salida.p.camino_activo[i]==1){
			flag=1;
			salida.p.camino_activo[i]=0;
			salida.p.escoge[i]=0;
			dist=salida.p.camino[i];
			salida.h.distancia_recorrida=dist+dis; 
			salida.h.punto_act=salida.p.punto_sig[i]; //tiene sentido??
			
		}
		}
		
		if(devuelve_activo(salida.p.camino_activo)==0){
			salida.p.vivo=0;
		}
		
		salida.p.definido=1;
	
	//MULTIPLICO ELEMENTO A ELEMENTO--->BEGIN
	//se hace el resize
	   	mul.resize(salida.p.escoge.size());
	
	for(int i=0 ; i < salida.p.escoge.size() ; i++){ //tamaño correcto pa recorrer el vector??
		mul[i]=salida.p.punto_sig[i]*salida.p.escoge[i];
	}
	
	//MULTIPLICO ELEMENTO A ELEMENTO--->END

	salida.h.punto_sig=refresca_auxiliar_f(mul);	
	
	// REPASAR ESTAS DOS ÚLTIMAS LÍNEAS
	salida.h.recorrido=salida.p.recorrido;	
    salida.h.recorrido.push_back (salida.h.punto_act);	
    
    // DEVUELVO LA SALIDA
    salida.contador=counter;
    /*
*/
    
    return salida;
    
}


struct s_desg_nodo desglosa_nodo (struct nodo padre,const vector<vector<float> > &puntos2,float dis,int contador_dh){

struct s_dev_hijo salida2;
struct s_desg_nodo devuelto;
int salir,contador;

salir=0; contador=1;
// dis=padre.distancia_recorrida;


 while(salir==0){

	salida2=devuelve_hijo(padre,puntos2,dis,contador_dh);

contador=contador+1;
devuelto.a.push_back (salida2.h);

/*
ROS_INFO("DATOS DEL HIJO 2: ");
ROS_INFO("NIVEL: %d",salida2.h.nivel);

ROS_INFO("RECORRIDO: ");
for (int i = 0; i < salida2.h.recorrido.size(); i++) {
            cout << salida2.h.recorrido[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("PUNTO SIGUIENTE: ");
for (int i = 0; i < salida2.h.punto_sig.size(); i++) {
            cout << salida2.h.punto_sig[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("INDICADOR: %d",salida2.h.indicador);
ROS_INFO("DEFINIDO: %d",salida2.h.definido);
ROS_INFO("DISTANCIA RECORRIDA: %f",salida2.h.distancia_recorrida);
ROS_INFO("PUNTO ACTUAL: %f ",salida2.h.punto_act);
*/

if(salida2.p.vivo==0){
	salir=1;
}

	// cout << "SALIR: " << salir << " " << endl;

padre=salida2.p;

	//
	contador_dh=salida2.contador;
	//

/*
ROS_INFO("CAMINO ACTIVO FINAL: ");
for (int i = 0; i < padre.camino_activo.size(); i++) {
            cout << padre.camino_activo[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("DEVUELVE_ACTIVO: ");
            cout << devuelve_activo(padre.camino_activo) << " " << endl;  
  ROS_INFO("\n");
*/	 
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


void repeticion(int &salir,nodo &nodo_1,
vector<nodo> &nodo_desglosable,int &INDICE,float &distancia,
vector< vector<float> > &puntos2, vector <float> &punto_final,
s_desg_nodo &salida_dn, float &counter, vector<nodo> &v_n_maduros,
int &tope, vector<float> &nodo_pre, vector<float> &c, vector<float> &r1,
float &auxx, vector<float> &nodo_final, vector<float> &v,
int &flag){
	
// EMPIEZA REPETICION 
 
 
 // VARIABLES "INVENTADAS POR AHORA"
 salir=0;
 nodo_1=nodo_desglosable[INDICE];  // en matlab pone nodo_desglosable[INDICE];
 distancia=nodo_1.distancia_recorrida;
 
 
 if(es_ultimo(nodo_desglosable[INDICE],puntos2,punto_final)>0){
 // no desgloso el nodo si está en el último nivel que quiero
}

else{
	
	while(salir==0){ // COMIENZO DEL WHILE
	// desgloso los nodos del nivel inferior al que considero 
	// y lo defino completamente	
		salida_dn=desglosa_nodo(nodo_1,puntos2,distancia,counter);
		counter=salida_dn.contador;
		salida_desglosa_nodo(salida_dn);
		v_n_maduros.push_back(salida_dn.p);
		nodo_1=salida_dn.a[0];
		distancia=salida_dn.a[0].distancia_recorrida;
		
		for (int j=0;j<salida_dn.a.size();j++){
		nodo_desglosable.push_back(salida_dn.a[j]);}
		
	if (salida_dn.a[0].nivel>=(tope+1)){
	
	for(int ii=0;ii<salida_dn.a.size();ii++){
		nodo_pre.push_back(salida_dn.a[ii].distancia_recorrida);
		
		
		c[0]=salida_dn.a[ii].punto_act; 
		
		ROS_INFO("PUNTO ACTUAL: ");
            cout << c[0] << " ";
		ROS_INFO("\n");
		
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

	ROS_INFO("VECTOR V: ");
for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
        }   
  ROS_INFO("\n");
  
 ROS_INFO("INDICADORES DE LOS NODOS DESGLOSABLES: ");
for (int i = 0; i < nodo_desglosable.size(); i++) {
            cout << nodo_desglosable[i].indicador << " ";
        }   
  ROS_INFO("\n");
  
  ROS_INFO("COMPONENTE_REP ENTRE V Y EL INDICADOR : ");
for (int i = 0; i < nodo_desglosable.size(); i++) {
            cout << componente_rep(v,nodo_desglosable[i].indicador) << " ";
        }   
  ROS_INFO("\n");


	flag=0;
	for (int i=0; i<nodo_desglosable.size();i++){
	
		if((nodo_desglosable[i].indicador>0) & (componente_rep(v,nodo_desglosable[i].indicador)==0) & (flag==0) & (nodo_desglosable[i].punto_sig.size()>0)){
		
		INDICE=i;
		
		 ROS_INFO("INDICE: ");
            cout << nodo_desglosable[i].indicador << " "; 
		 ROS_INFO("\n");
		
		nodo_desglosable[i].indicador=0; flag=1;
		
		}// FIN DEL "IF"
		
	}// FIN DEL "FOR"
	
	
	// RECORRO LOS NODOS INMADUROS, "NODO_DESGLOSABLE"
	
	ROS_INFO("NODO PRE: ");
for (int i = 0; i < nodo_pre.size(); i++) {
            cout << nodo_pre[i] << " ";
        }   
  ROS_INFO("\n");
  
  ROS_INFO("NODO FINAL: ");
for (int i = 0; i < nodo_final.size(); i++) {
            cout << nodo_final[i] << " ";
        }   
  ROS_INFO("\n");
	
	
   ROS_INFO("INDICADORES DE LOS NODOS DESGLOSABLES (2): ");
for (int i = 0; i < nodo_desglosable.size(); i++) {
            cout << nodo_desglosable[i].indicador << " ";
        }   
  ROS_INFO("\n");
 
 
// FIN "REPETICION"

	
}



int main( int argc, char** argv )
{

// MATRIZ DE PUNTOS 

vector<vector<float>> puntos={
	{0,0}, // PUNTO INICIAL
	{3.7,1.5},
	{2.3,5},
	{4,5},
	{-5,0}	
};
vector <float> punto_final;
/*
float puntos[A][B]={
	{0,0}, // PUNTO INICIAL
	{3,6},
	{7,9},
	{-4,3},
	{6,1},
	{2,2},
	{0,14},
	{4,4},
	{20,-5},
	{-1,7},
	{9,0},
	{23,-9},
	{-1,-25},
	{-1,-3},
	{1,1}
};*/

vector< vector<float> > puntos2(A,vector<float>(B));
float puntos_recorrido[A+1][B];
s_dev_hijo salida,salida2;
s_desg_nodo salida_dn;
nodo padre, nodo_1;
vector<float> v,r1,r2,c;

// VARIABLES DEL SCRIPT "REPETICION"
int INDICE,flag,fin,tope,cont_repeticion;
float auxx,counter;
vector<float> nodo_pre, nodo_final;
//

// VARIABLES DEL SCRIPT "BUSCA_RECORRIDO"
int vital;
bool c11, c1,c2,c3;
float errorr;
vector<float> MINIMO;
vector<nodo> aux;
nodo aux_var;

//

vector<nodo> v_n_maduros, nodo_desglosable;


// AQUI EMPIEZA LO "SUCIO"
int salir,contador;
float distancia;
int contador_dh=1;
vector<nodo> a;

//float uno[1]={0};
//float dos[4]={1,2,3,4};

std::vector<float> uno_tal;
std::vector<float> dos_tal;


// IMPORTANTE HACER EL RESIZE
uno_tal.resize(1);
dos_tal.resize(puntos2.size()-1);

r1.resize(2); r2.resize(2); c.resize(1); punto_final.resize(2);

// VALORES DE "PUNTO_FINAL"

punto_final[0]=1;
punto_final[1]=1;

//

for (int j=0;j<puntos2.size();j++){
dos_tal[j]=j+1;
}

uno_tal[0]=0;


//AQUI ACABA LO SUCIO

for (int i=0;i<A;i++){
	for (int j=0;j<B;j++){
puntos2[i][j]=puntos[i][j];
	std::cout << puntos[i][j] << ", ";
}std::cout << std::endl;

}

//getchar();


float c_inic[]={3,2,5,8,3,7};



// EMPIEZA EL TEMPLATE

// float* temp;= new float(A)
vector<float> temp;
temp.resize(A);
temp=cut_matrix(puntos2,-1,0);


// ACABA EL TEMPLATE


prueba.definido=0;

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
 cont_repeticion=10; // numero de repeticiones
  distancia=nodo_1.distancia_recorrida;
  salir=0; 
 nodo_desglosable.push_back(padre);
 INDICE=0;
 tope=puntos2.size()-1;
 
 // EMPIEZA LA FUNCION DE DESGLOSA NODO
// salida_dn=desglosa_nodo(padre,puntos2,padre.distancia_recorrida,0); 
 // RESULTADOS DE DESGLOSA NODO
 //salida_desglosa_nodo(salida_dn);
 
 
 // EMPIEZA REPETICION
 
 for(int xz=0;xz<cont_repeticion;xz++){
 
 repeticion(salir,nodo_1,nodo_desglosable,INDICE,distancia,
puntos2, punto_final,salida_dn, counter, v_n_maduros,
tope, nodo_pre, c, r1,auxx, nodo_final, v,flag);

}



// EMPIEZA "BUSCA RECORRIDO"
// fin=puntos2.size()-1;

for (int i = 0; i < nodo_final.size(); i++) {
	if(minimo(nodo_final)==nodo_final[i]){
		vital=i;
	}// fin del if
}// fin del "for"

MINIMO.push_back(minimo(nodo_final));

errorr=pow(10,-4);

for(int i=0; i<nodo_desglosable.size(); i++){
	
	distancia=norma(resta(punto_final,cut_matrix(puntos2,nodo_desglosable[i].punto_act,-1)));
	
	c11= nodo_desglosable[i].punto_sig.size()==0; // CREO
	c1= nodo_desglosable[i].nivel==(tope+1); // no sé si he definido bien "tope"
	c2=distancia-(nodo_final[vital]-nodo_pre[vital])<errorr;
	c3=nodo_desglosable[i].distancia_recorrida==nodo_pre[vital];
	
	if (c1 && c2 && c3){
		
		aux.push_back(nodo_desglosable[i]);
		
		ROS_INFO("FINAL: ");
            cout << i << " "; 
		 ROS_INFO("\n");
		
	}// fin del if
	
}// fin del for


if(aux.size()>1){
	aux_var=aux[0];
	aux.clear();
	aux.push_back(aux_var);
}

// EN CUALQUIER CASO, AUX TENDRÁ DIMENSIÓN 1


  ROS_INFO("AUX.RECORRIDO: ");
for (int i = 0; i < aux.size(); i++) {
	cout << "CIUDAD " << i << ": " ;
	for (int j = 0; j < aux[i].recorrido.size(); j++) {
            cout << aux[i].recorrido[j] << " ";
		}
		ROS_INFO("\n");
        }   
  ROS_INFO("\n");
  
  
  // AHORA SOLO ME FALTA VOLCAR EN "PUNTOS_RECORRIDO" 
  // LOS PUNTOS EN EL ORDEN EN EL QUE SE UNIRÁN EN RVIZ (puntos2(ordenado) + punto_final)

for (int i = 0; i < (A); i++) {
	for (int j = 0; j < (B); j++) {
		puntos_recorrido[i][j]=puntos2[aux[0].recorrido[i]][j];
		}
        }   
        puntos_recorrido[A][0]=punto_final[0];
        puntos_recorrido[A][1]=punto_final[1];

/*
*/
/*
 //
 v_n_maduros.push_back (salida_dn.p);
 nodo_1= salida_dn.a[0];
 distancia=salida_dn.a[0].distancia_recorrida;
 
 for(int i=0; i< salida_dn.a.size(); i++){
 nodo_desglosable.push_back (salida_dn.a[i]);
}

	INDICE=salida_dn.contador;
 padre=nodo_desglosable[INDICE];
 salida_dn=desglosa_nodo(padre,puntos2,padre.distancia_recorrida,salida_dn.contador);
 salida_desglosa_nodo(salida_dn);
//
 */
 
 
/* ROS_INFO("NIVEL HIJOS: ");
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
  */
  
 
 /*
 salir=0; contador=1;
 
 while(salir==0){
	
	salida2=devuelve_hijo(padre,puntos2,padre.distancia_recorrida,contador_dh);
contador=contador+1;
a.push_back (salida2.h);

ROS_INFO("DATOS DEL HIJO 2: ");
ROS_INFO("NIVEL: %d",salida2.h.nivel);

ROS_INFO("RECORRIDO: ");
for (int i = 0; i < salida2.h.recorrido.size(); i++) {
            cout << salida2.h.recorrido[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("PUNTO SIGUIENTE: ");
for (int i = 0; i < salida2.h.punto_sig.size(); i++) {
            cout << salida2.h.punto_sig[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("INDICADOR: %d",salida2.h.indicador);
ROS_INFO("DEFINIDO: %d",salida2.h.definido);
ROS_INFO("DISTANCIA RECORRIDA: %f",salida2.h.distancia_recorrida);
ROS_INFO("PUNTO ACTUAL: %f ",salida2.h.punto_act);

if(salida2.p.vivo==0){
	salir=1;
}

	cout << "SALIR: " << salir << " " << endl;

padre=salida2.p;

	//
	contador_dh=salida2.contador;
	//

ROS_INFO("CAMINO ACTIVO FINAL: ");
for (int i = 0; i < padre.camino_activo.size(); i++) {
            cout << padre.camino_activo[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("DEVUELVE_ACTIVO: ");
            cout << devuelve_activo(padre.camino_activo) << " " << endl;  
  ROS_INFO("\n");
	 
 }
 */
 
 
 // ACABA LA FUNCION DE DESGLOSA NODO
 
 /*
 
salida2=devuelve_hijo(padre,puntos2,padre.distancia_recorrida,contador);
contador=contador+1;
a.push_back (salida2.h);

ROS_INFO("DATOS DEL HIJO 2: ");
ROS_INFO("NIVEL: %d",salida2.h.nivel);

ROS_INFO("RECORRIDO: ");
for (int i = 0; i < salida2.h.recorrido.size(); i++) {
            cout << salida2.h.recorrido[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("PUNTO SIGUIENTE: ");
for (int i = 0; i < salida2.h.punto_sig.size(); i++) {
            cout << salida2.h.punto_sig[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("INDICADOR: %d",salida2.h.indicador);
ROS_INFO("DEFINIDO: %d",salida2.h.definido);
ROS_INFO("DISTANCIA RECORRIDA: %f",salida2.h.distancia_recorrida);
ROS_INFO("PUNTO ACTUAL: %f ",salida2.h.punto_act);

if(salida2.p.vivo==0){
	salir=1;
}

	cout << "SALIR: " << salir << " " << endl;

padre=salida2.p;

ROS_INFO("CAMINO ACTIVO FINAL: ");
for (int i = 0; i < padre.camino_activo.size(); i++) {
            cout << padre.camino_activo[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("DEVUELVE_ACTIVO: ");
            cout << devuelve_activo(padre.camino_activo) << " " << endl;  
  ROS_INFO("\n");


//

salida2=devuelve_hijo(padre,puntos2,padre.distancia_recorrida,contador);
contador=contador+1;
a.push_back (salida2.h);

ROS_INFO("DATOS DEL HIJO 2: ");
ROS_INFO("NIVEL: %d",salida2.h.nivel);

ROS_INFO("RECORRIDO: ");
for (int i = 0; i < salida2.h.recorrido.size(); i++) {
            cout << salida2.h.recorrido[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("PUNTO SIGUIENTE: ");
for (int i = 0; i < salida2.h.punto_sig.size(); i++) {
            cout << salida2.h.punto_sig[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("INDICADOR: %d",salida2.h.indicador);
ROS_INFO("DEFINIDO: %d",salida2.h.definido);
ROS_INFO("DISTANCIA RECORRIDA: %f",salida2.h.distancia_recorrida);
ROS_INFO("PUNTO ACTUAL: %f ",salida2.h.punto_act);

if(salida2.p.vivo==0){
	salir=1;
}

	cout << "SALIR: " << salir << " " << endl;

padre=salida2.p;

ROS_INFO("CAMINO ACTIVO FINAL: ");
for (int i = 0; i < padre.camino_activo.size(); i++) {
            cout << padre.camino_activo[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("DEVUELVE_ACTIVO: ");
            cout << devuelve_activo(padre.camino_activo) << " " << endl;  
  ROS_INFO("\n");

//

salida2=devuelve_hijo(padre,puntos2,padre.distancia_recorrida,contador);
contador=contador+1;
a.push_back (salida2.h);

ROS_INFO("DATOS DEL HIJO 2: ");
ROS_INFO("NIVEL: %d",salida2.h.nivel);

ROS_INFO("RECORRIDO: ");
for (int i = 0; i < salida2.h.recorrido.size(); i++) {
            cout << salida2.h.recorrido[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("PUNTO SIGUIENTE: ");
for (int i = 0; i < salida2.h.punto_sig.size(); i++) {
            cout << salida2.h.punto_sig[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("INDICADOR: %d",salida2.h.indicador);
ROS_INFO("DEFINIDO: %d",salida2.h.definido);
ROS_INFO("DISTANCIA RECORRIDA: %f",salida2.h.distancia_recorrida);
ROS_INFO("PUNTO ACTUAL: %f ",salida2.h.punto_act);

if(salida2.p.vivo==0){
	salir=1;
}

	cout << "SALIR: " << salir << " " << endl;

padre=salida2.p;

ROS_INFO("CAMINO ACTIVO FINAL: ");
for (int i = 0; i < padre.camino_activo.size(); i++) {
            cout << padre.camino_activo[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("DEVUELVE_ACTIVO: ");
            cout << devuelve_activo(padre.camino_activo) << " " << endl;  
  ROS_INFO("\n");

//

salida2=devuelve_hijo(padre,puntos2,padre.distancia_recorrida,contador);
contador=contador+1;
a.push_back (salida2.h);

ROS_INFO("DATOS DEL HIJO 2: ");
ROS_INFO("NIVEL: %d",salida2.h.nivel);

ROS_INFO("RECORRIDO: ");
for (int i = 0; i < salida2.h.recorrido.size(); i++) {
            cout << salida2.h.recorrido[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("PUNTO SIGUIENTE: ");
for (int i = 0; i < salida2.h.punto_sig.size(); i++) {
            cout << salida2.h.punto_sig[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("INDICADOR: %d",salida2.h.indicador);
ROS_INFO("DEFINIDO: %d",salida2.h.definido);
ROS_INFO("DISTANCIA RECORRIDA: %f",salida2.h.distancia_recorrida);
ROS_INFO("PUNTO ACTUAL: %f ",salida2.h.punto_act);

if(salida2.p.vivo==0){
	salir=1;
}

	cout << "SALIR: " << salir << " " << endl;

padre=salida2.p;

ROS_INFO("CAMINO ACTIVO FINAL: ");
for (int i = 0; i < padre.camino_activo.size(); i++) {
            cout << padre.camino_activo[i] << " ";
        }   
  ROS_INFO("\n");

ROS_INFO("DEVUELVE_ACTIVO: ");
            cout << devuelve_activo(padre.camino_activo) << " " << endl;  
  ROS_INFO("\n");

*/





//FIN PRUEBAS

//std::vector<float> c_inic={ 34,23 };

  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;

//funcion(c_inic);
/*
prueba[0].nivel=1;
prueba[0].punto_act=recorta(matriz[5][2],0,-1);*/


  while (ros::ok())
  {

    visualization_msgs::Marker points, line_strip, line_list;
    points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "/my_frame";
    points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
    points.ns = line_strip.ns = line_list.ns = "points_and_lines";
    points.action = line_strip.action = line_list.action = visualization_msgs::Marker::ADD;
    points.pose.orientation.w = line_strip.pose.orientation.w = line_list.pose.orientation.w = 1.0;



    points.id = 0;
    line_strip.id = 1;
    line_list.id = 2;



    points.type = visualization_msgs::Marker::POINTS;
    line_strip.type = visualization_msgs::Marker::LINE_STRIP;
    line_list.type = visualization_msgs::Marker::LINE_LIST;



    // POINTS markers use x and y scale for width/height respectively
    points.scale.x = 0.2;
    points.scale.y = 0.2;

    // LINE_STRIP/LINE_LIST markers use only the x component of scale, for the line width
    line_strip.scale.x = 0.1;
    line_list.scale.x = 0.1;



    // Points are green
    points.color.g = 1.0f;
    points.color.a = 1.0;

    // Line strip is blue
    line_strip.color.b = 1.0;
    line_strip.color.a = 1.0;

    // Line list is red
    line_list.color.r = 1.0;
    line_list.color.a = 1.0;



    // Create the vertices for the points and lines
    for (uint32_t i = 0; i < (A+1); ++i)
    {
   //   float y = 5 * sin(f + i / 100.0f * 2 * M_PI);
   //   float z = 5 * cos(f + i / 100.0f * 2 * M_PI);

      geometry_msgs::Point p;
      p.x = (float)puntos_recorrido[i][0] ;
      p.y = (float)puntos_recorrido[i][1] ;
     // p.z = z;

      points.points.push_back(p);
      line_strip.points.push_back(p);

      // The line list needs two points for each line
   //   line_list.points.push_back(p);
   //   p.z += 1.0;
   //   line_list.points.push_back(p);
    }


    marker_pub.publish(points);
    marker_pub.publish(line_strip);
  //  marker_pub.publish(line_list);

    r.sleep();

  //  f += 0.01;
  }
 } 
