#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

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

 void pedir_pantalla_f(int &cont_repeticion,int &A, int &B, vector<vector<float>> &puntos,
 vector<float> &punto_final){
 
 int coordenadas,n_puntos;
  float pto;

	// COORDENADAS
	do{		
	cout << "Numero de coordenadas que manejamos (2/3): " << endl; 
   cin >> coordenadas;		
	}while(coordenadas!=3 && coordenadas!=2);
   cout << "Coordenadas: " << coordenadas << endl;
   
   // NUMERO DE PUNTOS
   cout << "Numero de puntos que manejamos (entero): " << endl; 
   cin >> n_puntos;	
   
   n_puntos=n_puntos+1;
   
   puntos.resize(n_puntos); // IMPORTANTE EL RESIZE
   punto_final.resize(coordenadas);
   
   // PUNTO INICIAL
   puntos[0].resize(coordenadas); // IMPORTANTE EL RESIZE
   for(int j=0; j<coordenadas;j++){ 
   cout << "Punto inicial; coordenada " << j+1 << " : " << endl; 
	cin >> pto; 
	puntos[0][j]=pto; }// fin del for 
	
	// PUNTO FINAL
	for(int j=0; j<coordenadas;j++){ 
   cout << "Punto final; coordenada " << j+1 << " : " << endl; 
	cin >> pto; 
	punto_final[j]=pto; }// fin del for 
   
   // PUNTOS DE LA TRAYECTORIA
   for(int i=1; i<n_puntos;i++){
	   puntos[i].resize(coordenadas); // IMPORTANTE EL RESIZE
	   for(int j=0; j<coordenadas;j++){   
   	cout << "Punto de la trayectoria numero "<< i << " ; coordenada " << j+1 << " : " << endl; 
	cin >> pto; 
	puntos[i][j]=pto;  
   }} // fin de ambos for
   
   // NUMERO DE REPETICIONES DEL ALGORITMO
   cout << "¿Cuántas repeticiones quieres hacer?: " << endl; 
   cin >> cont_repeticion;		
   
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


struct s_dev_hijo devuelve_hijo (int &B, struct nodo padre,const vector<vector<float> > &dots,float dis,int counter){
	struct s_dev_hijo salida; 
    vector<vector<float> > aux;
    int flag; float dist,distancia;
   	vector<float> mul,c,r1,r2;
   	
   	//EMPIEZAN RESIZES
   	c.resize(2);
	r1.resize(B); r2.resize(B); //numero de coordenadas
	
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


struct s_desg_nodo desglosa_nodo (int &B,struct nodo padre,const vector<vector<float> > &puntos2,float dis,int contador_dh){

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
		//salida_desglosa_nodo(salida_dn);
		v_n_maduros.push_back(salida_dn.p);
		nodo_1=salida_dn.a[0];
		distancia=salida_dn.a[0].distancia_recorrida;
		
		for (int j=0;j<salida_dn.a.size();j++){
		nodo_desglosable.push_back(salida_dn.a[j]);}
		
	if (salida_dn.a[0].nivel>=(tope+1)){
	
	for(int ii=0;ii<salida_dn.a.size();ii++){
		nodo_pre.push_back(salida_dn.a[ii].distancia_recorrida);
		
		
		c[0]=salida_dn.a[ii].punto_act; 
		
		/*
		ROS_INFO("PUNTO ACTUAL: ");
            cout << c[0] << " ";
		ROS_INFO("\n");
		*/
		
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

/*
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
*/

	flag=0;
	for (int i=0; i<nodo_desglosable.size();i++){
	
		if((nodo_desglosable[i].indicador>0) & (componente_rep(v,nodo_desglosable[i].indicador)==0) & (flag==0) & (nodo_desglosable[i].punto_sig.size()>0)){
		
		INDICE=i;
		/*
		 ROS_INFO("INDICE: ");
            cout << nodo_desglosable[i].indicador << " "; 
		 ROS_INFO("\n");
		*/
		nodo_desglosable[i].indicador=0; flag=1;
		
		}// FIN DEL "IF"
		
	}// FIN DEL "FOR"
	
	
	// RECORRO LOS NODOS INMADUROS, "NODO_DESGLOSABLE"
	/*
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
 */
 
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


int main( int argc, char** argv )
{

int A,B,cont_repeticion;
   vector<vector<float>> puntos;
   vector<float> punto_final;
  
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
int vital;
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

std::vector<float> uno_tal;
std::vector<float> dos_tal;


  pedir_pantalla_f(cont_repeticion,A, B,puntos,punto_final);


// IMPORTANTE HACER EL RESIZE
uno_tal.resize(1);
dos_tal.resize(puntos.size()-1);

//r1.resize(B);
 r2.resize(B); c.resize(1); 

// VALORES DE "PUNTO_FINAL"

//punto_final[0]=1;
//punto_final[1]=1;

//

for (int j=0;j<puntos.size();j++){
dos_tal[j]=j+1;
}

uno_tal[0]=0;

/*
for (int i=0;i<A;i++){
	for (int j=0;j<B;j++){
puntos2[i][j]=puntos[i][j];
	std::cout << puntos[i][j] << ", ";
}std::cout << std::endl;

}*/


//float c_inic[]={3,2,5,8,3,7};



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
 //cont_repeticion=10; // numero de repeticiones
  distancia=nodo_1.distancia_recorrida;
  salir=0; 
 nodo_desglosable.push_back(padre);
 INDICE=0;
 tope=puntos.size()-1;
 
 
 // EMPIEZA REPETICION
 
 for(int xz=0;xz<cont_repeticion;xz++){
 
 repeticion(B,salir,nodo_1,nodo_desglosable,INDICE,distancia,
puntos, punto_final,salida_dn, counter, v_n_maduros,
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
	
	distancia=norma(resta(punto_final,cut_matrix(puntos,nodo_desglosable[i].punto_act,-1)));
	
	c11= nodo_desglosable[i].punto_sig.size()==0;
	c1= nodo_desglosable[i].nivel==(tope+1); 
	c2=distancia-(nodo_final[vital]-nodo_pre[vital])<errorr;
	c3=nodo_desglosable[i].distancia_recorrida==nodo_pre[vital];
	
	if (c1 && c2 && c3){
		
		aux.push_back(nodo_desglosable[i]);
	
	    /*	
		ROS_INFO("FINAL: ");
            cout << i << " "; 
		 ROS_INFO("\n");
		*/
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

puntos_recorrido.resize(A+1);


for (int i = 0; i < (A); i++) {
	puntos_recorrido[i].resize(B);
	for (int j = 0; j < (B); j++) {
		puntos_recorrido[i][j]=puntos[aux[0].recorrido[i]][j];
		}
        }
                
        puntos_recorrido[A].resize(B); 
        for (int j = 0; j < (B); j++) {
		puntos_recorrido[A][j]=punto_final[j];
		}  
   
// IMPRIMO RESULTADOS POR PANTALLA   
       
 imprimir_resultados(cont_repeticion,A,B,puntos_recorrido,puntos,MINIMO,
   aux,vital);
       
//FIN PRUEBAS

  ros::init(argc, argv, "points_and_lines");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;



  while (ros::ok())
  {

    visualization_msgs::Marker points ,pf, po, line_strip, line_list;
    
    po.header.frame_id =pf.header.frame_id =points.header.frame_id = line_strip.header.frame_id = line_list.header.frame_id = "/my_frame";
    po.header.stamp =pf.header.stamp =points.header.stamp = line_strip.header.stamp = line_list.header.stamp = ros::Time::now();
    po.ns =pf.ns =points.ns = line_strip.ns = line_list.ns = "points_and_lines";
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
    for (uint32_t i = 0; i < (A+1); ++i)
    {
      geometry_msgs::Point p;
      p.x = (float)puntos_recorrido[i][0] ;
      p.y = (float)puntos_recorrido[i][1] ;
      
      if(B==3){
     p.z = (float)puntos_recorrido[i][2];
	}
	
	if(i==0){
      po.points.push_back(p);
      line_strip.points.push_back(p);
     }
     if(i==A){
      pf.points.push_back(p);
      line_strip.points.push_back(p);
     }
     if(i>0 && i<A){
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
 } 
