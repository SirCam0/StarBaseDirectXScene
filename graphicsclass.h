////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "d3dclass.h"
#include "timerclass.h"
#include "shadermanagerclass.h"
#include "positionclass.h"
#include "cameraclass.h"
#include "skydomeclass.h"
#include "skydomeshaderclass.h"
#include "skyplaneclass.h"
#include "skyplaneshaderclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"
#include "rendertextureclass.h"
#include "reflectionshaderclass.h"
#include "waterclass.h"
#include "terrainclass.h"
#include "terrainshaderclass.h"
#include "watershaderclass.h"
#include "particleshaderclass.h"
#include "particlesystemclass.h"
#include "firemodelclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame(float);

	bool launch = false;

private:
	//bool Render(float);
	//Xu
	bool HandleMovementInput(float);
	void RenderRefractionToTexture();
	void RenderReflectionToTexture();
	bool Render(float rocketAltitude);

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	TimerClass* m_Timer;
	ShaderManagerClass* m_ShaderManager;
	PositionClass* m_Position;
	CameraClass* m_Camera;
	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;
	SkyPlaneClass* m_SkyPlane;
	SkyPlaneShaderClass* m_SkyPlaneShader;
	LightClass* m_Light;
	ModelClass* m_Starship1;
	ModelClass* m_Starship2;
	ModelClass* m_LaunchPad;
	ModelClass* m_TestStand1;
	ModelClass* m_TestStand2;
	ModelClass* m_HorizontalTank1;
	ModelClass* m_HorizontalTank2;
	ModelClass* m_HorizontalTank3;
	ModelClass* m_HorizontalTank4;
	ModelClass* m_VerticalTank1;
	ModelClass* m_VerticalTank2;
	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	RenderTextureClass* m_RefractionTexture, * m_ReflectionTexture;
	ReflectionShaderClass* m_ReflectionShader;
	WaterClass* m_Water;
	WaterShaderClass* m_WaterShader;
	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
	FireModelClass* m_RocketPlume1;
	FireModelClass* m_RocketPlume2;
	FireModelClass* m_RocketPlume3;
};

#endif