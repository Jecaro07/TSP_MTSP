
#include "matriz_c.h"

using namespace std;
 using std::vector;

 vector <vector <float>> matriz_c::reserva(int filas,int columnas) // USAR DESPUES DE COPIAR
       {
		   m_llenar.resize(filas);
		   for(int i=0;i<m_llenar.size();i++){
		  m_llenar[i].resize(columnas);
		  }
		  return m_llenar;
        }


        vector <vector <float>> matriz_c::llenar() // USAR DESPUES DE COPIAR
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


        vector <vector <float>> matriz_c::llena_auto() // USAR DESPUES DE COPIAR
       {
		   m_llenar[0][0]=1; m_llenar[0][1]=2; m_llenar[0][2]=3;
       m_llenar[1][0]=4; m_llenar[1][1]=5; m_llenar[1][2]=6;
       m_llenar[2][0]=7; m_llenar[2][1]=8; m_llenar[2][2]=9;
       m_llenar[3][0]=3; m_llenar[3][1]=3; m_llenar[3][2]=3;
       m_llenar[4][0]=1; m_llenar[4][1]=-4; m_llenar[4][2]=1;
       m_llenar[5][0]=-1; m_llenar[5][1]=-1; m_llenar[5][2]=-1;
		  return m_llenar;
        }


       vector <vector <float>> matriz_c::copiar(vector <vector <float>> mat) // Mat es lo que yo pongo a la entrada
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


       void matriz_c::imprimir_2(vector <vector <float>> a) // USAR DESPUES DE COPIAR
       {
           for(int i=0;i<a.size();i++){
          for(int j=0;j<a[i].size();j++){
			  cout<< a[i][j] <<" ";
		  }
		  cout<<endl;
		  }cout<<endl;
        }

        void matriz_c::imprimir_1(vector <float> a) // USAR DESPUES DE COPIAR
       {
           for(int i=0;i<a.size();i++){
			  cout<< a[i] <<" ";
		  }cout<<endl;cout<<endl;
        }
