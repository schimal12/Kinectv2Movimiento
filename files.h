//Arturo Rodríguez García

void archivo(int n)
{
	FILE *archivo;
	archivo = fopen("ejemplo.txt", "w");
	fprintf(archivo,"%i", n);
	fclose(archivo);
}


void write_a_frame_resume_in_file(struct FRAME_RESUME Frame)
{
	FILE *archivo;
	archivo = fopen("C:/Users/IIMAS/Desktop/PeopleRecognition/Files/frame_resume.txt", "w");
	
	for(int i = 0; i < BODY_COUNT; i++)
	{
		
		//Printing the tracking status of the person
		//fprintf(archivo, "Tracked: %i,", Frame.person[i].isTracked);
		
		//Printing a specific joint
		//fprintf(archivo, "Tracked: %i,", Frame.person[i].body.joint[6].isTracked);
		//fprintf(archivo, "X: %.2f,", Frame.person[i].body.joint[4].coordinate3D.X);
		//fprintf(archivo, "Y: %.2f,", Frame.person[i].body.joint[4].coordinate3D.Y);
		//fprintf(archivo, "Z: %.2f,", Frame.person[i].body.joint[4].coordinate3D.Z);
		//fprintf(archivo, "X: %.2f,", Frame.person[i].body.joint[5].coordinate3D.X);
		//fprintf(archivo, "Y: %.2f,", Frame.person[i].body.joint[5].coordinate3D.Y);
		//fprintf(archivo, "Z: %.2f,", Frame.person[i].body.joint[5].coordinate3D.Z);
		//fprintf(archivo, "X: %.2f,", Frame.person[i].body.joint[7].coordinate2D.X);
		//fprintf(archivo, "Y: %.2f,", Frame.person[i].body.joint[7].coordinate2D.Y);

		//Printing the gesture values
		//fprintf(archivo, "BodyGesture: %i,", Frame.person[i].bodyGesture.type);
		//fprintf(archivo, "BodyGesture: %i,", Frame.person[i].bodyGesture.parameter1);
		fprintf(archivo, "BodyPose: %i,", Frame.person[i].bodyPose.type); 
		//fprintf(archivo, "LeftHandGesture: %i,", Frame.person[i].leftHandGesture.type);
		//fprintf(archivo, "LeftHandGesture: %i,", Frame.person[i].leftHandGesture.parameter1);
		//fprintf(archivo, "RightHandGesture: %i,", Frame.person[i].rightHandGesture.type);
		//fprintf(archivo, "RightHandGesture: %i,", Frame.person[i].rightHandGesture.parameter1);
	}
	
	fclose(archivo);
}