
#include "mtsp_files/funcion_mtsp_file.h"

using namespace std;
 using std::vector;



int main( int argc, char** argv ){

  ros::init(argc, argv, "tsp_start_limpio");
  ros::NodeHandle n;
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);
  float f = 0.0;

 vector <vector<float>>  salida, entrada,puntos_recorrido;


 entrada.resize(7);
 		   for(int i=0;i<entrada.size();i++){
 		  entrada[i].resize(3); // COORDENADAS 3D
 		  }

//LLENAR (ENTRADA)
       entrada[0][0]=1; entrada[0][1]=2; entrada[0][2]=3;
       entrada[1][0]=4; entrada[1][1]=5; entrada[1][2]=6;
       entrada[2][0]=7; entrada[2][1]=8; entrada[2][2]=9;
       entrada[3][0]=3; entrada[3][1]=3; entrada[3][2]=3;
       entrada[4][0]=1; entrada[4][1]=-4; entrada[4][2]=1;
       entrada[5][0]=-1; entrada[5][1]=-1; entrada[5][2]=-1;

       entrada[6][0]=13;   entrada[6][1]=4;    entrada[6][2]=6;


// FUNCIÓN DEL MTSP
  salida=funcion_mtsp(entrada);

//IMPRIMIR (SALIDA)
  for(int i=0;i<salida.size();i++){
  for(int j=0;j<salida[i].size();j++){
  cout<< salida[i][j] <<" ";}}


puntos_recorrido=salida;



// REPRESENTAR EN "RVIZ EL RESULTADO
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
      for (uint32_t i = 0; i < (entrada.size()); ++i)
      {
        geometry_msgs::Point p;
        p.x = (float)puntos_recorrido[i][0] ;
        p.y = (float)puntos_recorrido[i][1] ;

   //     if(B==3){
       p.z = (float)puntos_recorrido[i][2];
   //	}

  	if(i==0){
        po.points.push_back(p);
        line_strip.points.push_back(p);
       }
       if(i==entrada.size()-1){
        pf.points.push_back(p);
        line_strip.points.push_back(p);
       }
       if(i>0 && i<entrada.size()-1){
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
