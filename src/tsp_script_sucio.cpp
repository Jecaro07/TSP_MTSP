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


class matriz_c
{
    private:
        vector <vector <float>> m_copiar; // lo devuelvo en teoría
        vector <vector <float>> m_llenar; // lo devuelvo en teoría
    public:

       vector <vector <float>> reserva(int filas,int columnas) // USAR DESPUES DE COPIAR
       {
		   m_llenar.resize(filas);
		   for(int i=0;i<m_llenar.size();i++){
		  m_llenar[i].resize(columnas);
		  }
		  return m_llenar;
        }



        vector <vector <float>> llenar() // USAR DESPUES DE COPIAR
       {
		   float valor;
		   for(int i=0;i<m_llenar.size();i++){
          for(int j=0;j<m_llenar[i].size();j++){
			  cout<<"Valor introducido: ";
			  cin >> valor;cout<<endl;
			  m_llenar[i][j]=valor;
		  }
		  }
		  return m_llenar;
        }

        vector <vector <float>> llena_auto() // USAR DESPUES DE COPIAR
       {
           m_llenar[0][0]=1; m_llenar[0][1]=2; m_llenar[0][2]=3;
       m_llenar[1][0]=4; m_llenar[1][1]=5; m_llenar[1][2]=6;
       m_llenar[2][0]=7; m_llenar[2][1]=8; m_llenar[2][2]=9;
       m_llenar[3][0]=7; m_llenar[3][1]=3; m_llenar[3][2]=3;
       m_llenar[4][0]=1; m_llenar[4][1]=-4; m_llenar[4][2]=1;
          return m_llenar;
        }


       vector <vector <float>> copiar(vector <vector <float>> mat) // Mat es lo que yo pongo a la entrada
       {
		   // RESERVA MEMORIA 2X2
		   m_copiar.resize(mat.size());
          for(int i=0;i<m_copiar.size();i++){
			  m_copiar[i].resize(mat[i].size());
		  }

		  for(int i=0;i<m_copiar.size();i++){
          for(int j=0;j<m_copiar[i].size();j++){
			  m_copiar[i][j]=mat[i][j];
		  }
		  }
		  return m_copiar;
        }


       void imprimir_2(vector <vector <float>> a) // USAR DESPUES DE COPIAR
       {
           for(int i=0;i<a.size();i++){
          for(int j=0;j<a[i].size();j++){
			  cout<< a[i][j] <<" ";
		  }
		  cout<<endl;
		  }cout<<endl;
        }

        void imprimir_1(vector <float> a) // USAR DESPUES DE COPIAR
       {
           for(int i=0;i<a.size();i++){
			  cout<< a[i] <<" ";
		  }cout<<endl;cout<<endl;
        }
};


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
	matriz_c m;
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
	cout<<"INIDICADOR: "<<salida.h.indicador<<endl;
	salida.h.nivel=1+salida.p.nivel;
	salida.h.definido=0;



	if(salida.p.definido==1){}
	else{
		for(int i=0 ; i < salida.p.punto_sig.size() ; i++){
			c[0]=salida.p.punto_act;
			 c[1]=salida.p.punto_sig[i];
			r1=cut_matrix(dots,c[0],-1);
	        r2=cut_matrix(dots,c[1],-1);

	        cout<<"RESTA: "<<endl;
			m.imprimir_1(resta(r1,r2));
	        cout<<"NORMA_RESTA: "<< norma(resta(r1,r2)) <<endl;

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

			cout<<"DIST: "<<dist<<endl;
		   cout<<"DIS: "<<dis<<endl;

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

struct s_dev_hijo salida2; matriz_c mmm;
struct s_desg_nodo devuelto;
int salir,contador;

salir=0; contador=1;



 while(salir==0){

salida2=devuelve_hijo(B,padre,puntos2,dis,contador_dh);

cout<<endl; cout<< "SALIDA2.P: "<<endl;
		cout<<"NIVEL: "<<salida2.p.nivel<<endl;
		cout<<"VIVO: "<<salida2.p.vivo<<endl;
		cout<<"INDICADOR: "<<salida2.p.indicador<<endl;
		cout<<"DEFINIDO: "<<salida2.p.definido<<endl;
		cout<<"DISTANCIA_RECORRIDA: "<<salida2.p.distancia_recorrida<<endl;
		cout<<"PUNTO_ACT: "<<salida2.p.punto_act<<endl;
		cout<<"camino: "<<endl;
		mmm.imprimir_1(salida2.p.camino);
		cout<<"camino_activo: "<<endl;
		mmm.imprimir_1(salida2.p.camino_activo);
		cout<<"recorrido: "<<endl;
		mmm.imprimir_1(salida2.p.recorrido);
		cout<<"punto_sig: "<<endl;
		mmm.imprimir_1(salida2.p.punto_sig);
		cout<<"escoge: "<<endl;
		mmm.imprimir_1(salida2.p.escoge);


cout<<endl; cout<< "SALIDA2.H: "<<endl;
		cout<<"NIVEL: "<<salida2.h.nivel<<endl;
		cout<<"VIVO: "<<salida2.h.vivo<<endl;
		cout<<"INDICADOR: "<<salida2.h.indicador<<endl;
		cout<<"DEFINIDO: "<<salida2.h.definido<<endl;
		cout<<"DISTANCIA_RECORRIDA: "<<salida2.h.distancia_recorrida<<endl;
		cout<<"PUNTO_ACT: "<<salida2.h.punto_act<<endl;
		cout<<"camino: "<<endl;
		mmm.imprimir_1(salida2.h.camino);
		cout<<"camino_activo: "<<endl;
		mmm.imprimir_1(salida2.h.camino_activo);
		cout<<"recorrido: "<<endl;
		mmm.imprimir_1(salida2.h.recorrido);
		cout<<"punto_sig: "<<endl;
		mmm.imprimir_1(salida2.h.punto_sig);
		cout<<"escoge: "<<endl;
		mmm.imprimir_1(salida2.h.escoge);

contador=contador+1;
devuelto.a.push_back (salida2.h); // devuelto se resetea en cada
								  // llamada de "DESGLOSA_NODO"
if(salida2.p.vivo==0){
	salir=1;}
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

	matriz_c mmm;

// EMPIEZA REPETICION

 // VARIABLES
 salir=0;
 nodo_1=nodo_desglosable[INDICE];  // en matlab pone nodo_desglosable[INDICE];
 distancia=nodo_1.distancia_recorrida;

 /*
cout<<endl; cout<< "NODO_1: "<<endl;

		cout<<"NIVEL: "<<nodo_1.nivel<<endl;
		cout<<"VIVO: "<<nodo_1.vivo<<endl;
		cout<<"INDICADOR: "<<nodo_1.indicador<<endl;
		cout<<"DEFINIDO: "<<nodo_1.definido<<endl;
		cout<<"DISTANCIA_RECORRIDA: "<<nodo_1.distancia_recorrida<<endl;
		cout<<"PUNTO_ACT: "<<nodo_1.punto_act<<endl;
		cout<<"camino: "<<endl;
		mmm.imprimir_1(nodo_1.camino);
		cout<<"camino_activo: "<<endl;
		mmm.imprimir_1(nodo_1.camino_activo);
		cout<<"recorrido: "<<endl;
		mmm.imprimir_1(nodo_1.recorrido);
		cout<<"punto_sig: "<<endl;
		mmm.imprimir_1(nodo_1.punto_sig);
		cout<<"escoge: "<<endl;
		mmm.imprimir_1(nodo_1.escoge);
 */


 if(es_ultimo(B,nodo_desglosable[INDICE],puntos2,punto_final)>0){
 // no desgloso el nodo si está en el último nivel que quiero
}

else{


	//while(salir==0){ // COMIENZO DEL WHILE
	// desgloso los nodos del nivel inferior al que considero
	// y lo defino completamente
		salida_dn=desglosa_nodo(B,nodo_1,puntos2,distancia,counter);

		counter=salida_dn.contador;
		v_n_maduros.push_back(salida_dn.p);
		nodo_1=salida_dn.a[0];
		distancia=salida_dn.a[0].distancia_recorrida;

		cout<<endl;cout<<"AAAAA_0: "<<salida_dn.a.size()<<endl;


		for (int j=0;j<salida_dn.a.size();j++){
		nodo_desglosable.push_back(salida_dn.a[j]);}

		cout<<endl;
		cout<<"VALOR_COMPARA: "<<salida_dn.a[0].nivel<<endl;
		cout<<"(TOPE+1): "<<(tope+1)<<endl;cout<<endl;

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

	//} // FIN DEL WHILE

	//while(salir==0){ // COMIENZO DEL WHILE
	// desgloso los nodos del nivel inferior al que considero
	// y lo defino completamente

	cout<<"SALIR: "<<salir<<endl;

	cout<<"STARTTTTTT"<<endl;

	cout<<"nodo_1: "<<endl; cout<<endl;

	cout<<"NIVEL: "<<nodo_1.nivel<<endl;
		cout<<"VIVO: "<<nodo_1.vivo<<endl;
		cout<<"INDICADOR: "<<nodo_1.indicador<<endl;
		cout<<"DEFINIDO: "<<nodo_1.definido<<endl;
		cout<<"DISTANCIA_RECORRIDA: "<<nodo_1.distancia_recorrida<<endl;
		cout<<"PUNTO_ACT: "<<nodo_1.punto_act<<endl;
		cout<<"camino: "<<endl;
		mmm.imprimir_1(nodo_1.camino);
		cout<<"camino_activo: "<<endl;
		mmm.imprimir_1(nodo_1.camino_activo);
		cout<<"recorrido: "<<endl;
		mmm.imprimir_1(nodo_1.recorrido);
		cout<<"punto_sig: "<<endl;
		mmm.imprimir_1(nodo_1.punto_sig);
		cout<<"escoge: "<<endl;
		mmm.imprimir_1(nodo_1.escoge);


	cout<<"distancia: "<<distancia<<endl;
	cout<<"counter: "<<counter<<endl;

		salida_dn=desglosa_nodo(B,nodo_1,puntos2,distancia,counter);

		counter=salida_dn.contador;
		v_n_maduros.push_back(salida_dn.p);
		nodo_1=salida_dn.a[0];
		distancia=salida_dn.a[0].distancia_recorrida;

		cout<<endl;cout<<"AAAAA_0: "<<salida_dn.a.size()<<endl;


		for (int j=0;j<salida_dn.a.size();j++){
		nodo_desglosable.push_back(salida_dn.a[j]);}

		cout<<endl;
		cout<<"VALOR_COMPARA: "<<salida_dn.a[0].nivel<<endl;
		cout<<"(TOPE+1): "<<(tope+1)<<endl;cout<<endl;


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

	//} // FIN DEL WHILE

	cout<<"SALIR: "<<salir<<endl;



} // FIN DEL ELSE

cout<<endl;
cout<<endl; cout<< "NODO_FINAL: "<<endl;
mmm.imprimir_1(nodo_final);
cout<< "NODO_PRE: "<<endl;
mmm.imprimir_1(nodo_pre);



// SECCION DE "REPETICION" ENCARGADA DE REFRESCAR ÍNDICE ENTRE ITERACIONES
	// Recorremos los nodos desarrollados, "v_n_maduros"

	cout<< "v_n_maduros.size() "<< v_n_maduros.size()<<endl;


	for (int i=0; i<v_n_maduros.size();i++){

		if((v_n_maduros[i].indicador==0) ||
	 ((v_n_maduros[i].indicador)-(v_n_maduros[i-1].indicador)<0)
	 || (componente_rep(v,v_n_maduros[i].indicador))){
		}
		else{
			v.push_back(v_n_maduros[i].indicador);
		}// fin del "IF"
	} // fin del "for"

	mmm.imprimir_1(v);

// HASTA AQUÍ BIEN

	flag=0;
	for (int i=0; i<nodo_desglosable.size();i++){

		if((nodo_desglosable[i].indicador>0) &
    (componente_rep(v,nodo_desglosable[i].indicador)==0) &
    (flag==0) & (nodo_desglosable[i].punto_sig.size()>0)){

		INDICE=i;
		nodo_desglosable[i].indicador=0; flag=1;

		}// FIN DEL "IF"

	}// FIN DEL "FOR"

 cout<<"INDICE: "<<INDICE<<endl;

// FIN "REPETICION"
/* comento
	comento */
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
	/*
  if(argc < 2){
		std::cout << "Not enough input arguments" << std::endl;
		return -1;
	}
	input_file = argv[1];*/

  // DATOS NECESARIOS PARA LA REPRESENTACIÓN DE VALORES
  ros::init(argc, argv, "tsp_script");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;

   int A,B,cont_repeticion;
   vector<vector<float>> puntos,fff;
   vector<float> punto_final;

vector<vector<float>> puntos_recorrido;
s_dev_hijo salida,salida2,sss;
s_desg_nodo salida_dn,ss;
nodo padre, nodo_1,nn;
vector<float> v,r1,r2,c,ff;

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
vector<nodo> aux,nnn;
nodo aux_var;
vector<nodo> v_n_maduros, nodo_desglosable;

int salir,contador;
float distancia;
int contador_dh=1;
vector<nodo> a;

std::vector<float> uno_tal;
std::vector<float> dos_tal;


//pedir_pantalla_f(cont_repeticion,A, B,puntos,punto_final);


// DEFINO MATRIZ EN LA QUE VOLCARÉ TODAS LAS CIUDADES
matriz_c mmm;
B=5;A=3; // B = FILAS ; A=COLUMNAS=3
puntos=mmm.reserva(B,A);
//      puntos=mmm.llenar();
        puntos=mmm.llena_auto();
mmm.imprimir_2(puntos);

// INICIALIZAR Y LLENAR "PUNTO_FINAL"
punto_final.resize(B);
punto_final[0]=13;
punto_final[1]=4;
punto_final[2]=6;

// IMPORTANTE HACER EL RESIZE
uno_tal.resize(1);
dos_tal.resize(puntos.size()-1);
r2.resize(B); c.resize(1);


for (int j=0;j<puntos.size()-1;j++){
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
 tope=puntos.size()-1;


//salida_dn=desglosa_nodo(B,padre,puntos,0,0);

repeticion(B,salir,nodo_1,nodo_desglosable,INDICE,distancia,
puntos, punto_final,salida_dn, counter, v_n_maduros,
tope, nodo_pre, c, r1,auxx, nodo_final, v,flag);

//cout<<endl;cout<< "TOPE: "<< tope <<endl;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
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

std::cout<< "VITAL:"<< vital <<std::endl<< std::endl;


MINIMO.push_back(minimo(nodo_final));


std::cout << "VALOR DE MÍNIMO: "  << std::endl;
 mmm.imprimir_1(MINIMO);
 std::cout << std::endl;

// -----------------------------------------------------------------------------
// ------------EMPIEZA COMENTARIO DE BUSCA RECORRIDO----------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

errorr=pow(10,-4);

// INICIO DEPURAR

for(int i=0; i<nodo_desglosable.size(); i++){
 for (int j=0; j<nodo_desglosable[i].punto_sig.size();j++){
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_pto_sig: "<< nodo_desglosable[i].punto_sig[j]  << endl;
}}
std::cout<<std::endl;




for(int i=0; i<nodo_desglosable.size(); i++){
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_dist_rec: "<< nodo_desglosable[i].distancia_recorrida << endl;
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

for(int i=0; i<nodo_desglosable.size(); i++){

	distancia=norma(resta(punto_final,cut_matrix(puntos,nodo_desglosable[i].punto_act,-1)));

	c11= nodo_desglosable[i].punto_sig.size()==0;
	c1= nodo_desglosable[i].nivel==(tope+1);
	c2=distancia-(nodo_final[vital]-nodo_pre[vital])<errorr;
	c3=nodo_desglosable[i].distancia_recorrida==nodo_pre[vital];

	if (c1 && c2 && c3){
		aux.push_back(nodo_desglosable[i]);
	}// fin del if

}// fin del for




// DEPURAR
for(int i=0; i<aux.size(); i++){
 for (int j=0; j<aux[i].punto_sig.size();j++){
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_pto_sig: "<< aux[i].punto_sig[j]  << endl;
}}
cout<<endl;



for(int i=0; i<aux.size(); i++){
	cout<< "Componente "<< i <<" de NODO DESGLOSABLE_dist_rec: "<< aux[i].distancia_recorrida << endl;
}
cout<<endl;

cout<< "TOPE: "<< tope <<endl;
cout<< "VITAL: "<< vital <<endl;
//



if(aux.size()>1){
	aux_var=aux[0];
	aux.clear();
	aux.push_back(aux_var);
}

// EN CUALQUIER CASO, AUX TENDRÁ DIMENSIÓN 1 (HASTA AQUÍ BIEN)

cout << endl;
cout << "RECORRIDO CIUDADES INTERMEDIAS: " << endl;
for (int j = 1; j < aux[0].recorrido.size(); j++) {
          cout << aux[0].recorrido[j] << " ";
      }
cout << endl;cout << endl;



  // AHORA SOLO ME FALTA VOLCAR EN "PUNTOS_RECORRIDO"
  // LOS PUNTOS EN EL ORDEN EN EL QUE SE UNIRÁN EN RVIZ (puntos2(ordenado) + punto_final)
  // (hasta aquí bien)


puntos_recorrido.resize(B+1);

for (int i = 0; i < (B); i++) {
    puntos_recorrido[i].resize(A);
    for (int j = 0; j < (A); j++) {
        puntos_recorrido[i][j]=puntos[aux[0].recorrido[i]][j];
        }
        }

puntos_recorrido[B].resize(A);
for (int j = 0; j < (A); j++) {
puntos_recorrido[B][j]=punto_final[j];
}

/*
aux[0].devuelve_recorrido(rec);
puntos_recorrido.resize(A+1);

for (int i = 0; i < (A); i++) {
    puntos_recorrido[i].resize(B);
    for (int j = 0; j < (B); j++) {
        puntos_recorrido[i][j]=puntos[rec[i]][j];
        }
        }

        puntos_recorrido[A].resize(B);
        for (int j = 0; j < (B); j++) {
        puntos_recorrido[A][j]=punto_final[j];
        }
*/

// IMPRIMO RESULTADOS POR PANTALLA

 imprimir_resultados(cont_repeticion,A,B,puntos_recorrido,puntos,MINIMO,
   aux,vital);



// ---------------------------------------------------------------------
// ---------------------FINAL DE BUSCO RECORRIDO------------------------
// ---------------------------------------------------------------------
// ---------------------------------------------------------------------



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

   //   if(B==3){
   //  p.z = (float)puntos_recorrido[i][2];
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
