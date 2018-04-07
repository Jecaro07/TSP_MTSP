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


int main( int argc, char** argv )
{
	// VARIABLES DE ENTRADA
	vector <vector<vector<float>>> pp;
	int cont_repeticion;
	vector <int> A;
	int B;
    vector <vector<float>> punto_final;
	
	//VARIABLES DE FUNCIÓN
	 int coordenadas,n_puntos,salir_b1=0,CAM=0;
     float pto;
	
	string line; 
    vector <string> words;
	ifstream myfile;
	myfile.open("mtsp_datos.txt");
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
	cout<<pto<<endl; cout<<endl;
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
   cout << punto_final[CAM][j]<< ' ';
	 }// fin del for 
   cout<<endl; 	
   words.clear();
   
	 }
	
	if(salir_b1==0){
		
		// CIUDADES INTERMEDIAS
   getline (myfile,line) ;
	words = split(line,' ');	
   n_puntos=stoi(words[1]);	
     cout<< n_puntos <<endl; cout<<endl;
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
		cout << pp[CAM][i][j]<< ' ';
		}
		words.clear();
		cout<<endl;} // fin de ambos for
   cout<<endl;
   
   CAM=CAM+1;
   pp.resize(CAM+1); 
   punto_final.resize(CAM+1);
	}
		
	
	
}

	// NUMERO DE REPETICIONES  
   getline (myfile,line) ;
		words = split(line,' ');
		cont_repeticion=stoi(words[1]);
       cout << cont_repeticion<< '\n';  
      words.clear();
    cout<<endl;
    
    myfile.close();	
	
	}
	else{ cout << "Unable to open file"; 
	}
  
  
   
   B=coordenadas; // A=n_puntos;
	
	return 0;
}
