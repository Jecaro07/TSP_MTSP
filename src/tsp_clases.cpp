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
		
		
       void imprimir(vector <vector <float>> a) // USAR DESPUES DE COPIAR
       {
		   cout<<"VALOR DE m: "<<endl;
           for(int i=0;i<a.size();i++){
          for(int j=0;j<a[i].size();j++){
			  cout<< a[i][j] <<" ";				  
		  }
		  cout<<endl;
		  }cout<<endl;
        } 
};

 int main()
 {
      matriz_2 m;
      vector <vector <float>> a,c;
      m.reserva(2,3);
     a=m.llenar();
     c=m.copiar(a);
     
      m.imprimir(a);
      m.imprimir(c);
      
      return 0;
      
      
 }
