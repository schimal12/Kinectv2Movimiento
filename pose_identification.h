//Arturo Rodríguez García
//Sebastián Chimal
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h> 

void BodyPoseIdentification(struct PERSON person, int *type){
	JOINT Cuerpo[4][2];
	//Cadera Derecha
	Cuerpo[0][0] = person.body.joint[16];
	//Cadera Izquierda 
	Cuerpo[0][1] = person.body.joint[12];
	//Rodilla Derecha 
	Cuerpo[1][0] = person.body.joint[17];
	//Rodilla Izquierda
	Cuerpo[1][1] = person.body.joint[13];
	//Pie Derecho
	Cuerpo[2][0] = person.body.joint[19];
	//Pie Izquierdo
	Cuerpo[2][1] = person.body.joint[15];
	//Tobillo Derecho
	Cuerpo[3][0] = person.body.joint[18];
	//Tobillo Izquierdo
	Cuerpo[3][1] = person.body.joint[13];

	//Vectores 
	//Cadera Derecha a Rodilla Derecha 
	float vectorU[2][3];
	vectorU[0][0] = Cuerpo[1][0].coordinate3D.X - Cuerpo[0][0].coordinate3D.X;
	vectorU[0][1] = Cuerpo[1][0].coordinate3D.Y - Cuerpo[0][0].coordinate3D.Y;
	vectorU[0][2] = Cuerpo[1][0].coordinate3D.Z - Cuerpo[0][0].coordinate3D.Z;
	//Cadera Izquierda a Rodilla Derecha 
	vectorU[1][0] = Cuerpo[1][1].coordinate3D.X - Cuerpo[0][1].coordinate3D.X;
	vectorU[1][1] = Cuerpo[1][1].coordinate3D.Y - Cuerpo[0][1].coordinate2D.Y;
	vectorU[1][2] = Cuerpo[1][1].coordinate3D.Z - Cuerpo[0][1].coordinate3D.Z;
	//Vector normal en el plano X
	float vectorP[3]; 
	vectorP[0] = 0;
	vectorP[1] = 0;
	vectorP[2] = 1;

	float anguloCaderaRodillaDer, anguloCaderaRodillaIzq, anguloCaderaRodillaDer1, anguloCaderaRodillaIzq1;

	//Calculo del angulo entre el plano XY que contiene a Joint15/Joint12 (cadera derecha,izquierda) y la recta entre joint16-17 / joint12-joint13
	//ax+by+cz+d=0 => 0x+0y+1z+d = 0 => 0(Cuerpo[0][0].coordinate.X)+0(Cuerpo[0][0].coordinate.Y)+1(Cuerpo[0][0].coordinate.Z) + d = 0
	//z  - (Cuerpo[0][0].coordinate3D.X) = 0
	// ax + by + cz = 0 ==> n (0,0,1) ==> A = 0 ; B = 0 ; C = 1 // U1 = VectorU[0][0] ; U2 = VectorU[0][1] ; U3 = VectorU[0][2]
	//Calculo del angulo (Cadera-Rodilla) 
	anguloCaderaRodillaDer = asin(((vectorP[0] * vectorU[0][0]) + (vectorP[1] * vectorU[0][1]) + (vectorP[2] * vectorU[0][2])) / (sqrt((vectorP[0] * vectorP[0]) + (vectorP[1] * vectorP[1]) + (vectorP[2] * vectorP[2]))*(sqrt((vectorU[0][0] * vectorU[0][0]) + (vectorU[0][1] * vectorU[0][1]) + (vectorU[0][2] * vectorU[0][2])))));
	anguloCaderaRodillaIzq = asin(((vectorP[0] * vectorU[1][0]) + (vectorP[1] * vectorU[1][1]) + (vectorP[2] * vectorU[1][2])) / (sqrt((vectorP[0] * vectorP[0]) + (vectorP[1] * vectorP[1]) + (vectorP[2] * vectorP[2]))*(sqrt((vectorU[1][0] * vectorU[1][0]) + (vectorU[1][1] * vectorU[1][1]) + (vectorU[1][2] * vectorU[1][2])))));

	anguloCaderaRodillaDer1 = (180 * anguloCaderaRodillaDer) / M_PI;
	anguloCaderaRodillaIzq1 = (180 * anguloCaderaRodillaIzq) / M_PI;

	//Calculo de Rodilla-Tobillo 
	float vectorU1[2][3];
	//Rodilla Derecha - Tobillo Derecho 
	vectorU1[0][0] = Cuerpo[3][0].coordinate3D.X - Cuerpo[1][0].coordinate3D.X;
	vectorU1[0][1] = Cuerpo[3][0].coordinate3D.Y - Cuerpo[1][0].coordinate3D.Y;
	vectorU1[0][2] = Cuerpo[3][0].coordinate3D.Z - Cuerpo[1][0].coordinate3D.Z;
	 //Rodilla Izquierda - Tobillo Izquierdo 
	vectorU1[1][0] = Cuerpo[3][1].coordinate3D.X - Cuerpo[1][1].coordinate3D.X;
	vectorU1[1][1] = Cuerpo[3][1].coordinate3D.Y - Cuerpo[1][1].coordinate3D.Y;
	vectorU1[1][2] = Cuerpo[3][1].coordinate3D.Z - Cuerpo[1][1].coordinate3D.Z;
	//Se usa el mismo vector normal 
	float anguloRodillaTobilloDer, anguloRodillaTobilloIzq, anguloRodillaTobilloDer1, anguloRodillaTobilloIzq1;
	
	// Calculo de los angulos 
	anguloRodillaTobilloDer = asin(((vectorP[0] * vectorU1[0][0]) + (vectorP[1] * vectorU1[0][1]) + (vectorP[2] * vectorU1[0][2])) / (sqrt((vectorP[0] * vectorP[0]) + (vectorP[1] * vectorP[1]) + (vectorP[2] * vectorP[2]))*(sqrt((vectorU1[0][0] * vectorU1[0][0]) + (vectorU1[0][1] * vectorU1[0][1]) + (vectorU1[0][2] * vectorU1[0][2])))));
	anguloRodillaTobilloIzq = asin(((vectorP[0] * vectorU1[1][0]) + (vectorP[1] * vectorU1[1][1]) + (vectorP[2] * vectorU1[1][2])) / (sqrt((vectorP[0] * vectorP[0]) + (vectorP[1] * vectorP[1]) + (vectorP[2] * vectorP[2]))*(sqrt((vectorU1[1][0] * vectorU1[1][0]) + (vectorU1[1][1] * vectorU1[1][1]) + (vectorU1[1][2] * vectorU1[1][2])))));

	anguloRodillaTobilloDer1 = (180 * anguloRodillaTobilloDer) / M_PI;
	anguloRodillaTobilloIzq1 = (180 * anguloRodillaTobilloIzq) / M_PI;
	//Pruebas para medir angulos 
	//*type = anguloCaderaRodillaDer1;
	//*type = anguloCaderaRodillaIzq1;
	//*type = anguloRodillaTobilloDer1;
	//*type = anguloRodillaTobilloIzq1;
	//Identificar si esta parado 
	/*
	if (anguloCaderaRodillaDer1 > -19 && anguloCaderaRodillaIzq1 > -19){
		*type = 1;
	}
	else{
		*type = 0;
	}*/
	//Identificar si esta sentado 

	//Identificar si esta a nivel de suelo 
}