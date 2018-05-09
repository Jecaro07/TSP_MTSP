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


class Test
{
    private:
        int data1;
        float data2;

    public:
       
       void insertIntegerData(int d)
       {
          data1 = d;
          cout << "Number: " << data1;
        }

       float insertFloatData()
       {
           cout << "\nEnter data: ";
           cin >> data2;
           return data2;
        }
};

class matriz_2
{
    private:
        vector <vector <float>> m_copiar; // lo devuelvo en teoría
        vector <vector <float>> m_llenar; // lo devuelvo en teoría
    public:
       
       void reserva(int filas,int columnas) // USAR DESPUES DE COPIAR
       {
		   m_llenar.resize(filas);
		   for(int i=0;i<m_llenar.size();i++){
		  m_llenar[i].resize(columnas);				  
		  }
        }
        
        
        void llenar() // USAR DESPUES DE COPIAR
       {
		   float valor;
		   for(int i=0;i<m_llenar.size();i++){
          for(int j=0;j<m_llenar[i].size();j++){
			  cout<<"Valor introducido: ";
			  cin >> valor;cout<<endl;
			  m_llenar[i][j]=valor;				  
		  }
		  }
        }
       
       /*
       void copiar(vector <float> mat) // Mat es lo que yo pongo a la entrada
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
	
        }
        
		*/
       void imprimir() // USAR DESPUES DE COPIAR
       {
		   cout<<"VALOR DE M: "<<endl;
           for(int i=0;i<m_llenar.size();i++){
          for(int j=0;j<m_llenar[i].size();j++){
			  cout<< m_llenar[i][j] <<" ";				  
		  }
		  cout<<endl;
		  }cout<<endl;
        } 
};

 int main()
 {
	 vector <vector <float>> m_llear;
      matriz_2 m;
      m.reserva(2,3);
     m.llenar();
      m.imprimir();
      m.m_llenar.clear();
      return 0;
 }
