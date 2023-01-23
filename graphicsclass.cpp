////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Terrain = 0;
	m_TerrainShader = 0;
	m_Position = 0;
	m_SkyDome = 0;
	m_SkyDomeShader = 0;
	m_SkyPlane = 0;
	m_SkyPlaneShader = 0;
	m_Camera = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_ReflectionShader = 0;
	m_Water = 0;
	m_WaterShader = 0;
	m_Starship1 = 0;
	m_Starship2 = 0;
	m_LaunchPad = 0;
	m_TestStand1 = 0;
	m_TestStand2 = 0;
	m_HorizontalTank1 = 0;
	m_HorizontalTank2 = 0;
	m_HorizontalTank3 = 0;
	m_HorizontalTank4 = 0;
	m_VerticalTank1 = 0;
	m_VerticalTank2 = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(50.0f, 24.f, 50.0f);
	m_Position->SetRotation(0.0f, 45.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(250.0f, 20.0f, 200.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.5f, -0.75f, 0.25f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	// Create the sky dome object.
	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the sky dome object.
	result = m_SkyDome->Initialize(m_D3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky dome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the sky dome shader object.
	result = m_SkyDomeShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky dome shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane object.
	m_SkyPlane = new SkyPlaneClass;
	if (!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_D3D->GetDevice(), L"../Engine/data/cloud001.dds", L"../Engine/data/perturb001.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane shader object.
	m_SkyPlaneShader = new SkyPlaneShaderClass;
	if (!m_SkyPlaneShader)
	{
		return false;
	}

	// Initialize the sky plane shader object.
	result = m_SkyPlaneShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the terrain object.
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Engine/data/hm.bmp", "../Engine/data/cm.bmp", 20.0f, L"../Engine/data/dirt.dds",
		L"../Engine/data/terrainnormal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection shader object.
	m_ReflectionShader = new ReflectionShaderClass;
	if (!m_ReflectionShader)
	{
		return false;
	}

	// Initialize the reflection shader object.
	result = m_ReflectionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the water object.
	m_Water = new WaterClass;
	if (!m_Water)
	{
		return false;
	}

	// Initialize the water object.
	result = m_Water->Initialize(m_D3D->GetDevice(), L"../Engine/data/waternormal.dds", 5.0f, 250.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water object.", L"Error", MB_OK);
		return false;
	}


	// Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/star.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle texture.", L"Error", MB_OK);
		return false;
	}

	// Create the Starship1 model object.
	m_Starship1 = new ModelClass;
	if(!m_Starship1)
	{
		return false;
	}

	// Initialize the Starship1 model object.
	result = m_Starship1->Initialize(m_D3D->GetDevice(), "../Engine/data/Starship.txt", L"../Engine/data/StarshipTexture2.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Starship2 model object.
	m_Starship2 = new ModelClass;
	if (!m_Starship2)
	{
		return false;
	}

	// Initialize the Starship2 model object.
	result = m_Starship2->Initialize(m_D3D->GetDevice(), "../Engine/data/Starship.txt", L"../Engine/data/StarshipTexture2.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}


	// Create the launch pad model object.
	m_LaunchPad = new ModelClass;
	if (!m_LaunchPad)
	{
		return false;
	}

	// Initialize the launch pad model object.
	result = m_LaunchPad->Initialize(m_D3D->GetDevice(), "../Engine/data/LaunchPad.txt", L"../Engine/data/concrete.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 5th model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Test Stand model object.
	m_TestStand1 = new ModelClass;
	if (!m_TestStand1)
	{
		return false;
	}

	// Initialize the Test Stand model object.
	result = m_TestStand1->Initialize(m_D3D->GetDevice(), "../Engine/data/TestStand.txt", L"../Engine/data/BrushedMetal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the TestStand model object.", L"Error", MB_OK);
		return false;
	}

	// Create the Test Stand 2 model object.
	m_TestStand2 = new ModelClass;
	if (!m_TestStand2)
	{
		return false;
	}

	// Initialize the Test Stand 2 model object.
	result = m_TestStand2->Initialize(m_D3D->GetDevice(), "../Engine/data/TestStand.txt", L"../Engine/data/BrushedMetal.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the TestStand model object.", L"Error", MB_OK);
		return false;
	}

	// Create the HorizontalTank1 model object.
	m_HorizontalTank1 = new ModelClass;
	if (!m_HorizontalTank1)
	{
		return false;
	}

	// Initialize the HorizontalTank1 model object.
	result = m_HorizontalTank1->Initialize(m_D3D->GetDevice(), "../Engine/data/FuelTankHorizontal.txt", L"../Engine/data/FuelTank1.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the HorizontalTank1 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the HorizontalTank2 model object.
	m_HorizontalTank2 = new ModelClass;
	if (!m_HorizontalTank2)
	{
		return false;
	}

	// Initialize the HorizontalTank2 model object.
	result = m_HorizontalTank2->Initialize(m_D3D->GetDevice(), "../Engine/data/FuelTankHorizontal.txt", L"../Engine/data/FuelTank2.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the HorizontalTank2 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the HorizontalTank3 model object.
	m_HorizontalTank3 = new ModelClass;
	if (!m_HorizontalTank3)
	{
		return false;
	}

	// Initialize the HorizontalTank3 model object.
	result = m_HorizontalTank3->Initialize(m_D3D->GetDevice(), "../Engine/data/FuelTankHorizontal.txt", L"../Engine/data/FuelTank1.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the HorizontalTank3 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the HorizontalTank4 model object.
	m_HorizontalTank4 = new ModelClass;
	if (!m_HorizontalTank4)
	{
		return false;
	}

	// Initialize the HorizontalTank4 model object.
	result = m_HorizontalTank4->Initialize(m_D3D->GetDevice(), "../Engine/data/FuelTankHorizontal.txt", L"../Engine/data/FuelTank2.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the HorizontalTank4 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the VerticalTank1 model object.
	m_VerticalTank1 = new ModelClass;
	if (!m_VerticalTank1)
	{
		return false;
	}

	// Initialize the VerticalTank1 model object.
	result = m_VerticalTank1->Initialize(m_D3D->GetDevice(), "../Engine/data/FuelTankVertical.txt", L"../Engine/data/FuelTank1.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the VerticalTank1 model object.", L"Error", MB_OK);
		return false;
	}
	
	// Create the VerticalTank2 model object.
	m_VerticalTank2 = new ModelClass;
	if (!m_VerticalTank2)
	{
		return false;
	}

	// Initialize the VerticalTank2 model object.
	result = m_VerticalTank2->Initialize(m_D3D->GetDevice(), "../Engine/data/FuelTankVertical.txt", L"../Engine/data/FuelTank1.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the VerticalTank2 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the rocketPlume1 model object.
	m_RocketPlume1 = new FireModelClass;
	if (!m_RocketPlume1)
	{
		return false;
	}

	result = m_RocketPlume1->Initialize(m_D3D->GetDevice(), "../Engine/data/RocketPlume.txt", L"../Engine/data/fire01.dds",
		L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the rocketPlume1 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the rocketPlume2 model object.
	m_RocketPlume2 = new FireModelClass;
	if (!m_RocketPlume2)
	{
		return false;
	}

	result = m_RocketPlume2->Initialize(m_D3D->GetDevice(), "../Engine/data/RocketPlume.txt", L"../Engine/data/fire01.dds",
		L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the rocketPlume2 model object.", L"Error", MB_OK);
		return false;
	}

	// Create the rocketPlume3 model object.
	m_RocketPlume3 = new FireModelClass;
	if (!m_RocketPlume3)
	{
		return false;
	}

	result = m_RocketPlume3->Initialize(m_D3D->GetDevice(), "../Engine/data/RocketPlume.txt", L"../Engine/data/fire01.dds",
		L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the rocketPlume3 model object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{

	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the water object.
	if (m_Water)
	{
		m_Water->Shutdown();
		delete m_Water;
		m_Water = 0;
	}

	// Release the reflection shader object.
	if (m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	// Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	// Release the model objects.
	if(m_Starship1)
	{
		m_Starship1->Shutdown();
		delete m_Starship1;
		m_Starship1 = 0;
	}

	if (m_LaunchPad)
	{
		m_LaunchPad->Shutdown();
		delete m_LaunchPad;
		m_LaunchPad = 0;
	}

	if (m_TestStand1)
	{
		m_TestStand1->Shutdown();
		delete m_TestStand1;
		m_TestStand1 = 0;
	}

	if (m_TestStand2)
	{
		m_TestStand2->Shutdown();
		delete m_TestStand2;
		m_TestStand2 = 0;
	}

	if (m_HorizontalTank1) 
	{
		m_HorizontalTank1->Shutdown();
		delete m_HorizontalTank1;
		m_HorizontalTank1 = 0;
	}

	if (m_HorizontalTank2)
	{
		m_HorizontalTank2->Shutdown();
		delete m_HorizontalTank2;
		m_HorizontalTank2 = 0;
	}

	if (m_HorizontalTank3)
	{
		m_HorizontalTank3->Shutdown();
		delete m_HorizontalTank3;
		m_HorizontalTank3 = 0;
	}

	if (m_HorizontalTank4)
	{
		m_HorizontalTank4->Shutdown();
		delete m_HorizontalTank4;
		m_HorizontalTank4 = 0;
	}

	if (m_VerticalTank1)
	{
		m_VerticalTank1->Shutdown();
		delete m_VerticalTank1;
		m_VerticalTank1 = 0;
	}

	if (m_VerticalTank2)
	{
		m_VerticalTank2->Shutdown();
		delete m_VerticalTank2;
		m_VerticalTank2 = 0;
	}

	if (m_RocketPlume1)
	{
		m_RocketPlume1->Shutdown();
		delete m_RocketPlume1;
		m_RocketPlume1 = 0;
	}

	if (m_RocketPlume2)
	{
		m_RocketPlume2->Shutdown();
		delete m_RocketPlume2;
		m_RocketPlume2 = 0;
	}

	if (m_RocketPlume3)
	{
		m_RocketPlume3->Shutdown();
		delete m_RocketPlume3;
		m_RocketPlume3 = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	// Release the sky plane shader object.
	if (m_SkyPlaneShader)
	{
		m_SkyPlaneShader->Shutdown();
		delete m_SkyPlaneShader;
		m_SkyPlaneShader = 0;
	}

	// Release the sky plane object.
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	// Release the sky dome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the sky dome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	return;
}


bool GraphicsClass::Frame(float frameTime)
{
	bool result;
	static float altitude = 0.0f;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}
	// Do the water frame processing.
	m_Water->Frame();

	// Do the sky plane frame processing.
	m_SkyPlane->Frame();

	// Render the refraction of the scene to a texture.
	RenderRefractionToTexture();

	// Render the reflection of the scene to a texture.
	RenderReflectionToTexture();

	// Run the frame processing for the particle system.
	m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	// Update the rocket altitude
	if (launch) {
		altitude += (float)XM_PI * 0.1f;
	}

	// Render the graphics.
	result = Render(altitude);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsEPressed();
	if (keyDown) {
		launch = true;
	}

	keyDown = m_Input->IsAPressed();
	m_Position->MoveLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->MoveRight(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsSpacePressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsShiftPressed();
	m_Position->MoveDownward(keyDown);

	//*Xu. 03/12/2019
	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	//*/
	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseXDelta(), m_Input->GetMouseYDelta());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Input->ResetCursorPos();

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

void GraphicsClass::RenderRefractionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;


	// Setup a clipping plane based on the height of the water to clip everything above it to create a refraction.
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Render the terrain using the reflection shader and the refraction clip plane to produce the refraction effect.
	m_Terrain->Render(m_D3D->GetDeviceContext());
	m_ReflectionShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f,
		clipPlane);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return;
}

void GraphicsClass::RenderReflectionToTexture()
{
	XMFLOAT4 clipPlane;
	XMMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	XMFLOAT3 cameraPosition;


	// Setup a clipping plane based on the height of the water to clip everything below it.
	clipPlane = XMFLOAT4(0.0f, 1.0f, 0.0f, -m_Water->GetWaterHeight());

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the camera reflection view matrix instead of the normal view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	// Translate the sky dome and sky plane to be centered around the reflected camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	m_D3D->TurnOffCulling();
	m_D3D->TurnZBufferOff();

	// Render the sky dome using the reflection view matrix.
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Enable back face culling.
	m_D3D->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_D3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	// Turn off blending and enable the Z buffer again.
	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Render the terrain using the reflection view matrix and reflection clip plane.
	m_Terrain->Render(m_D3D->GetDeviceContext());
	m_ReflectionShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, reflectionViewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f,
		clipPlane);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return;
}

bool GraphicsClass::Render(float rocketAltitude)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix, reflectionViewMatrix, translateMatrix, rotationMatrix;
	bool result;
	XMFLOAT3 cameraPosition;

	//Variables for the fire 
	XMFLOAT3 scrollSpeeds, scales;
	XMFLOAT2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = XMFLOAT3(-1.3f, -2.1f, -2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = XMFLOAT3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = XMFLOAT2(0.1f, 0.2f);
	distortion2 = XMFLOAT2(0.1f, 0.3f);
	distortion3 = XMFLOAT2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	// Clear the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the reflection matrix based on the camera's position and the height of the water.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the world, view, projection, ortho, and base view matrices from the camera and Direct3D objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Turn on alpha blending.
	m_D3D->TurnOnAlphaBlending();

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());
	// Render the particle model using the texture shader.
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(10.f, 10.f, 10.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(10.0f, 10.0f, 10.0f));
	result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Translate the sky dome to be centered around the camera position.
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Turn off back face culling and the Z buffer.
	m_D3D->TurnOffCulling();
	m_D3D->TurnZBufferOff();

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(m_D3D->GetDeviceContext());
	m_SkyDomeShader->Render(m_D3D->GetDeviceContext(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyDome->GetApexColor(), m_SkyDome->GetCenterColor());

	// Turn back face culling back on.
	m_D3D->TurnOnCulling();

	// Enable additive blending so the clouds blend with the sky dome color.
	m_D3D->EnableSecondBlendState();

	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	m_SkyPlaneShader->Render(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());

	// Turn off blending.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on.
	m_D3D->TurnZBufferOn();

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Render the terrain using the terrain shader.
	m_Terrain->Render(m_D3D->GetDeviceContext());
	result = m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Terrain->GetColorTexture(), m_Terrain->GetNormalTexture(), m_Light->GetDiffuseColor(), m_Light->GetDirection(),
		2.0f);
	if (!result)
	{
		return false;
	}

	// Translate to the location of the water and render it.
	worldMatrix = XMMatrixTranslation(250.0f, m_Water->GetWaterHeight(), 250.0f);
	m_Water->Render(m_D3D->GetDeviceContext());
	m_WaterShader->Render(m_D3D->GetDeviceContext(), m_Water->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, reflectionViewMatrix,
		m_RefractionTexture->GetShaderResourceView(), m_ReflectionTexture->GetShaderResourceView(), m_Water->GetTexture(),
		m_Camera->GetPosition(), m_Water->GetNormalMapTiling(), m_Water->GetWaterTranslation(), m_Water->GetReflectRefractScale(),
		m_Water->GetRefractionTint(), m_Light->GetDirection(), m_Water->GetSpecularShininess());

	// MODELS //

	if (launch) {

		// Turn on alpha blending for the fire transparency.
		m_D3D->TurnOnAlphaBlending();

		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
		//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(276.0f, (15.0f + rocketAltitude), 279.0f));
		m_RocketPlume1->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderFireShader(m_D3D->GetDeviceContext(), m_RocketPlume1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_RocketPlume1->GetTexture1(), m_RocketPlume1->GetTexture2(), m_RocketPlume1->GetTexture3(), frameTime, scrollSpeeds,
			scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		if (!result)
		{
			return false;
		}

		m_D3D->GetWorldMatrix(worldMatrix);
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
		//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(274.0f, (15.0f + rocketAltitude), 279.0f));
		m_RocketPlume2->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderFireShader(m_D3D->GetDeviceContext(), m_RocketPlume2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_RocketPlume2->GetTexture1(), m_RocketPlume2->GetTexture2(), m_RocketPlume2->GetTexture3(), frameTime, scrollSpeeds,
			scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		if (!result)
		{
			return false;
		}

		m_D3D->GetWorldMatrix(worldMatrix);
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
		//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
		worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(275.0f, (15.0f + rocketAltitude), 281.0f));
		m_RocketPlume2->Render(m_D3D->GetDeviceContext());
		result = m_ShaderManager->RenderFireShader(m_D3D->GetDeviceContext(), m_RocketPlume2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_RocketPlume2->GetTexture1(), m_RocketPlume2->GetTexture2(), m_RocketPlume2->GetTexture3(), frameTime, scrollSpeeds,
			scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
		if (!result)
		{
			return false;
		}

		// Turn off alpha blending.
		m_D3D->TurnOffAlphaBlending();
	}

	/** Setup the rotation and translation of the starship1 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(275.0f, (51.5f + rocketAltitude), 280.0f));
	// Render the Starship1 model using the light shader.
	m_Starship1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Starship1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_Starship1->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the starship2 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(290.0f, 46.0f, 365.0f));
	// Render the Starship2 model using the light shader.
	m_Starship2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Starship2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Starship2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the TestStand1 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.5f, 1.5f, 1.5f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(275.0f, 12.0f, 280.0f));
	// Render the TestStand1 model using the light shader.
	m_TestStand1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_TestStand1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TestStand1->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the TestStand2 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.5f, 1.5f, 1.5f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(290.0f, 6.5f, 365.0f));
	// Render the TestStand2 model using the light shader.
	m_TestStand2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_TestStand2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TestStand2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the LaunchPad model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.75f, 0.75f, 0.75f));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(30.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(250.0f, 6.0f, 250.0f));
	// Render the LaunchPad model using the light shader.
	m_LaunchPad->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_LaunchPad->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_LaunchPad->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the HorizontalTank1 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(370.0f, 7.0f, 230.0f));
	// Render the HorizontalTank1 model using the light shader.
	m_HorizontalTank1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_HorizontalTank1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_HorizontalTank1->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the HorizontalTank2 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(370.0f, 7.0f, 250.0f));
	// Render the HorizontalTank2 model using the light shader.
	m_HorizontalTank2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_HorizontalTank2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_HorizontalTank2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the HorizontalTank3 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(370.0f, 7.0f, 270.0f));
	// Render the HorizontalTank3 model using the light shader.
	m_HorizontalTank3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_HorizontalTank3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_HorizontalTank3->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the HorizontalTank4 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 1.f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(370.0f, 7.0f, 290.0f));
	// Render the HorizontalTank4 model using the light shader.
	m_HorizontalTank4->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_HorizontalTank4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_HorizontalTank4->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the VerticalTank1 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 0.75f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(325.0f, 7.0f, 280.0f));
	// Render the VerticalTank1 model using the light shader.
	m_VerticalTank1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_VerticalTank1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_VerticalTank1->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	/** Setup the rotation and translation of the VerticalTank2 model.**/
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(1.f, 0.75f, 1.f));
	//worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(90.f/*** /rotation/***/));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(325.0f, 7.0f, 240.0f));
	// Render the VerticalTank2 model using the light shader.
	m_VerticalTank2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_VerticalTank2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_VerticalTank2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}