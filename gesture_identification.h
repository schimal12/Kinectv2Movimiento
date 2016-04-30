//Arturo Rodríguez García
//Sebastián Chimal
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
float DistanciaEntrePuntos(JOINT x, JOINT y){
	return sqrt(((x.coordinate3D.X - y.coordinate3D.X)*(x.coordinate3D.X - y.coordinate3D.X)) + ((x.coordinate3D.Y - y.coordinate3D.Y)*(x.coordinate3D.Y - y.coordinate3D.Y)) + ((x.coordinate3D.Z - y.coordinate3D.Z)*(x.coordinate3D.Z - y.coordinate3D.Z)));
}
void BodyGestureIdentification(struct PERSON person, int *type, int *parameter1)
{
	//Identificar gesto mano derecha arriba
	//Formula de la recta de joint[4]  - joint[5]
	float vectorU[2][3];
	//Brazo Derecho 
	vectorU[0][0] = person.body.joint[5].coordinate3D.X - person.body.joint[4].coordinate3D.X;
	vectorU[0][1] = person.body.joint[5].coordinate3D.Y - person.body.joint[4].coordinate3D.Y;
	vectorU[0][2] = person.body.joint[5].coordinate3D.Z - person.body.joint[4].coordinate3D.Z;
	//Brazo Izquierdo
	vectorU[1][0] = person.body.joint[9].coordinate3D.X - person.body.joint[8].coordinate3D.X;
	vectorU[1][1] = person.body.joint[9].coordinate3D.Y - person.body.joint[8].coordinate3D.Y;
	vectorU[1][2] = person.body.joint[9].coordinate3D.Z - person.body.joint[8].coordinate3D.Z;
	//Vector normal del plano que pasa por el punto (x,y,z) de joint[4]
	float vectorP[3];
	float ang, ang1, angA, ang1A;
	vectorP[0] = 0;
	vectorP[1] = 1;
	vectorP[2] = 0;
	//Angulo entre la recta formada por (joint[4] y joint[5]) y el plano en XY formado a partir del punto joint[5]
	ang = asin(((vectorP[0] * vectorU[0][0]) + (vectorP[1] * vectorU[0][1]) + (vectorP[2] * vectorU[0][2])) / (sqrt((vectorP[0] * vectorP[0]) + (vectorP[1] * vectorP[1]) + (vectorP[2] * vectorP[2]))*(sqrt((vectorU[0][0] * vectorU[0][0]) + (vectorU[0][1] * vectorU[0][1]) + (vectorU[0][2] * vectorU[0][2])))));
	ang1 = asin(((vectorP[0] * vectorU[1][0]) + (vectorP[1] * vectorU[1][1]) + (vectorP[2] * vectorU[1][2])) / (sqrt((vectorP[0] * vectorP[0]) + (vectorP[1] * vectorP[1]) + (vectorP[2] * vectorP[2]))*(sqrt((vectorU[1][0] * vectorU[1][0]) + (vectorU[1][1] * vectorU[1][1]) + (vectorU[1][2] * vectorU[1][2])))));
	angA = (180 * ang) / M_PI;
	ang1A = (180 * ang1) / M_PI;
	//Obtener angulo 
	vectorP[0] = 0;
	vectorP[1] = 0;
	vectorP[2] = 1;
	//Gesto de Apuntar
	float d10,d11, d20,d21, d30,d31; 
	JOINT Cuerpo[4][2];
	//Mano Izquierda
	Cuerpo[0][0] = person.body.joint[7];
	//Mano Derecha 
	Cuerpo[0][1] = person.body.joint[11];
	//Hombro Izquierdo
	Cuerpo[1][0] = person.body.joint[4];
	//Hombro Derecho 
	Cuerpo[1][1] = person.body.joint[8];
	//Codo Derecho 
	Cuerpo[2][0] = person.body.joint[9];
	// Codo Izquierdo
	Cuerpo[2][1] = person.body.joint[5];
	//Cuello
	Cuerpo[3][0] = person.body.joint[2];
	//Calcular Distancia entre puntos 
	//0 => Izquierda
	//1 => Derecha 
	//D10 => Distancia de la mano izquierda al codo izquierdo
	d10 = DistanciaEntrePuntos(Cuerpo[0][0], Cuerpo[2][1]);
	//D11 => Distancia mano derecha al codo derecho
	d11 = DistanciaEntrePuntos(Cuerpo[0][1], Cuerpo[2][0]);
	//D20=> Distancia del codo izquierdo al hombro izquierdo 
	d20 = DistanciaEntrePuntos(Cuerpo[2][1], Cuerpo[1][0]);
	//D21 => Distancia del codo derecho al hombro derecho
	d21 = DistanciaEntrePuntos(Cuerpo[2][0], Cuerpo[1][1]);
	//D30 => Distancia de la mano izquierda al hombro izquierdo
	d30 = DistanciaEntrePuntos(Cuerpo[0][0], Cuerpo[1][0]);
	//D31 => Distancia de la mano derecha al hombro derecho 
	d31 = DistanciaEntrePuntos(Cuerpo[0][1], Cuerpo[1][1]);
	
	boolean apuntar = false;
	float angulo;
	
	if ((abs(Cuerpo[0][0].coordinate3D.Y - Cuerpo[1][0].coordinate3D.Y)) < 100 && (d30 > ((d10 + d20) * 7 / 8)) && (angA>-10&&angA<10)){
		apuntar = true;
		float cateto_opuesto;
		float cateto_adyacente;

		cateto_opuesto = Cuerpo[3][0].coordinate3D.X - Cuerpo[0][0].coordinate3D.X;
		cateto_adyacente = Cuerpo[3][0].coordinate3D.Z - Cuerpo[0][0].coordinate3D.Z;
		if (cateto_adyacente == 0){
			cateto_adyacente = 0.01;
		}
		angulo = atan(cateto_opuesto / cateto_adyacente);
		angulo = angulo * 180 / M_PI;
		//Cuadrante
		   
	     //Cuadrante I (+,+)
	     if( cateto_opuesto < 0  && cateto_adyacente > 0 )
	     {
                angulo = angulo * -1;
	     }     

	     //Cuadrante II (-,+)
             if( cateto_opuesto > 0  && cateto_adyacente > 0 )
	     {
                angulo = angulo * -1;
	     }     

	     //Cuadrante III (-,-)
	     if( cateto_opuesto > 0  && cateto_adyacente < 0 )
	     {
                angulo = -90 - (90+angulo);
	     } 

	     //Cuadrante IV(+,-)
             if( cateto_opuesto < 0  && cateto_adyacente < 0 )
	     {
                angulo = 90 + (90-angulo);
	     }  
	}
	if ((abs(Cuerpo[0][1].coordinate3D.Y - Cuerpo[1][1].coordinate3D.Y)) < 100 && (d31 > ((d11 + d21) * 7 / 8)) && (ang1A>-10 && ang1A<10)){
		apuntar = true;
		float cateto_opuesto;
		float cateto_adyacente;

		cateto_opuesto = Cuerpo[3][0].coordinate3D.X - Cuerpo[0][1].coordinate3D.X;
		cateto_adyacente = Cuerpo[3][0].coordinate3D.Z - Cuerpo[0][1].coordinate3D.Z;
		if (cateto_adyacente == 0){
			cateto_adyacente = 0.01;
		}
		angulo = atan(cateto_opuesto / cateto_adyacente);
		angulo = angulo * 180 / M_PI;
		//Cuadrante

		//Cuadrante I (+,+)
		if (cateto_opuesto < 0 && cateto_adyacente > 0)
		{
			angulo = angulo * -1;
		}

		//Cuadrante II (-,+)
		if (cateto_opuesto > 0 && cateto_adyacente > 0)
		{
			angulo = angulo * -1;
		}

		//Cuadrante III (-,-)
		if (cateto_opuesto > 0 && cateto_adyacente < 0)
		{
			angulo = -90 - (90 + angulo);
		}

		//Cuadrante IV(+,-)
		if (cateto_opuesto < 0 && cateto_adyacente < 0)
		{
			angulo = 90 + (90 - angulo);
		}
	}
	//Condicionales para que lo detectable sea por arriba de los 10
	if (apuntar ){
		*type = 3;
		*parameter1= angulo;
	}
	else 
	{
		if (angA > 10 && ang1A < 0){
			*type = 1;
			*parameter1 = -1;
		}
		else{
			if (angA < 0 && ang1A > 10){
				*type = 1;
				*parameter1 = 1;
			}
			else{
				if (angA > 10 && ang1A > 10){
					*type = 2;
					*parameter1 = 0;
				}
				else{
					*type = 0;
					*parameter1 = 0;
				}
			}
		}
	}
}