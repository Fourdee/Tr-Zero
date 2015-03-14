#pragma once
//-----------------------------------------------------------------
#define MAX_CAMERA_QUADS 2
//-----------------------------------------------------------------
class Mesh_Camera
{
	//-------------------------------------------------------------
	public:
		//---------------------------------------------------------
		//data
		//MD5MESH*					Camera_Speed;
		MD5MESH*					Camera_Quad[MAX_CAMERA_QUADS];
		//---------------------------------------------------------
		//constructors
		Mesh_Camera(void);
		~Mesh_Camera(void);
		//---------------------------------------------------------
		//functions
		void Create(void);
		void Update(void);
		void Destroy(void);
		//---------------------------------------------------------
	private:
		//---------------------------------------------------------
		//functions
		void Player_Update(D3DXVECTOR3 v1,D3DXQUATERNION q1);
		void ShaderUpdate(void);
	//-------------------------------------------------------------
};
