//Arturo Rodríguez García

//Definition of structures used in the code

struct COORDINATE2D
{
	float X;
	float Y;
};

struct COORDINATE3D
{
	float X;
	float Y;
	float Z;
};

struct JOINT
{
	int isTracked;  //Flag which is 0 if the joint is not tracked, 1 if is tracked and 2 if is inferred
	struct COORDINATE2D coordinate2D;
	struct COORDINATE3D coordinate3D;
};

//The 25 joints are:
//0 Spine Base
//1 Spine Mid
//2 Neck
//3 Head
//4 Shoulder Left
//5 Elbow Left
//6 Wrist Left
//7 Hand Left
//8 Shoulder Right
//9 Elbow Right
//10 Wrist Right
//11 Hand Right
//12 Hip Left
//13 Knee Left
//14 Ankle Left
//15 Foot Left
//16 Hip Right
//17 Knee Right
//18 Ankle Right
//19 Foot Right
//20 Spine Shoulder
//21 Hand Tip Left
//22 Thumb Left
//23 Hand Tip Right
//24 Thumb Right
struct BODY
{
	struct JOINT joint[25];
};

struct GESTURE
{
	int type;
	int parameter1;
};
struct POSE
{
	int type;
};

//For bodyGesture, the types are:
//0 No specific gesture
//1 Hand up (only one)    parameter1 is -1 if is doing with the left hand, 1 with right hand
//2 Waving (with both hands)   parameter1 is always 0
//3 Point  and parameter is angle 

//For handLeftGesture and rightHandGesture the types ares:
//0 Unknown
//1 NotTracked
//2 Open
//3 Closed
//4 Lasso
struct PERSON
{
	int isTracked;  //Boolean flag which is 1 if the body is tracked and 0 if not
	struct POSE bodyPose;
	struct BODY body;
	struct GESTURE bodyGesture;  
	struct GESTURE leftHandGesture;
	struct GESTURE rightHandGesture;

};

struct FRAME_RESUME
{
	struct PERSON person[BODY_COUNT];
};

