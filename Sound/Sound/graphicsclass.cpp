////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_NormalWall = 0;
	m_Bird = 0;
	m_LongWall = 0;
	m_Floor = 0;
	m_LightShader = 0;
	m_Light = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_Bitmap = 0;
	m_Title = 0;
	m_Text = 0;
	m_Pin = 0;

}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;

	

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

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);	// for cube
//	m_Camera->SetPosition(0.0f, 0.5f, -3.0f);	// for chair
		
	// Create the model object.
	m_NormalWall = new ModelClass;
	if(!m_NormalWall)
	{
		return false;
	}

	// Initialize the model object.
	result = m_NormalWall->Initialize(m_D3D->GetDevice(), L"./data/Maze.obj", L"./data/Wall.dds");
//	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Bird = new ModelClass;
	if (!m_Bird)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Bird->InitializeBird(m_D3D->GetDevice(), L"./data/Bird.obj", L"./data/Bird.dds");
	//	result = m_Model->Initialize(m_D3D->GetDevice(), L"./data/chair.obj", L"./data/chair_d.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}


	m_Floor = new ModelClass;
	if (!m_Floor)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Floor->InitializeGround(m_D3D->GetDevice(), L"./data/Floor_Big.obj", L"./data/brick_tiled.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_Pin = new ModelClass;
	if (!m_Pin)
	{
		return false;
	}
	result = m_Pin->InitializeGround(m_D3D->GetDevice(), L"./data/pin.obj", L"./data/base.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light->SetDirection(-1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(32.0f);


	m_Plight = new LightClass;
	if (!m_Plight)
	{
		return false;
	}

	// Initialize the first light object.
	m_Plight->SetDiffuseColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Plight->SetPosition(0.0f, 0.0f, -5.0f);

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/sky.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	m_Title = new BitmapClass;
	if (!m_Title)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Title->InitializeTitle(m_D3D->GetDevice(), screenWidth, screenHeight, L"./data/Title.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
//	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model object.
	if(m_NormalWall)
	{
		m_NormalWall->Shutdown();
		delete m_NormalWall;
		m_NormalWall = 0;
	}

	if (m_Bird)
	{
		m_Bird->Shutdown();
		delete m_Bird;
		m_Bird = 0;
	}

	/*if (m_LongWall)
	{
		m_LongWall->Shutdown();
		delete m_LongWall;
		m_LongWall = 0;
	}*/

	if (m_Floor)
	{
		m_Floor->Shutdown();
		delete m_Floor;
		m_Floor = 0;
	}

	if (m_Pin)
	{
		m_Pin->Shutdown();
		delete m_Pin;
		m_Pin = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}


	if (m_Plight)
	{
		delete m_Plight;
		m_Plight = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}
	
	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}
	
	if (m_Title)
	{
		m_Title->Shutdown();
		delete m_Title;
		m_Title = 0;
	}
	

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}

bool GraphicsClass::Frame()
{
	bool result;

	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += XM_PI * 0.005f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::Frame(int fps, int cpu, int screenWidth, int screenHeight)
{
	bool result;
	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0001f;
	if (rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Set the frames per second.
	result = m_Text->SetFPS(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCPU(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the location of the mouse.
	result = m_Text->SetScreenResolution(screenWidth, screenHeight, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetObj(m_NormalWall->GetInstanceCount() + m_Floor->GetInstanceCount() + m_Bird->GetInstanceCount() + m_Pin->GetInstanceCount(), m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	result = m_Text->SetPoly(m_NormalWall->GetIndexCount()/3 + m_Floor->GetIndexCount()/3 + m_Bird->GetIndexCount()/3 + m_Pin->GetIndexCount()/3, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Render the graphics scene.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	// Set the position of the camera.
//	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, worldMatrix2, worldMatrix6, viewMatrix, projectionMatrix, orthoMatrix, worldMatrix3, worldMatrix4, scalingMatrix4, worldMatrix5, scalingMatrix5;
	bool result;
	XMFLOAT3 cameraPosition, modelPosition;
	float rota;
	double angle;
	worldMatrix6 =XMMatrixTranslation(0.0f, 15.0f, 0.0f);
	
	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	m_D3D->GetOrthoMatrix(orthoMatrix);
	worldMatrix2 = XMMatrixTranslation(4.0f, 0.0f, 0.0f);
	scalingMatrix4 = XMMatrixScaling(3.2f, 2.3f, 0.0f);
	scalingMatrix5 = XMMatrixScaling(4.0f, 2.4f, 0.0f);
	worldMatrix4 = scalingMatrix4*worldMatrix;
	worldMatrix5 = scalingMatrix5 * worldMatrix;
	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 275, 170);
	if (!result)
	{
		return false;
	}

	// Render the bitmap with the texture shader.
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix4, Getbase(), orthoMatrix, m_Bitmap->GetTexture());
	if (!result)
	{
		return false;
	}



	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();
	if (isEnter == false)
	{
		result = m_Title->Render(m_D3D->GetDeviceContext(), 270, 175);
		if (!result)
		{
			return false;
		}

		// Render the bitmap with the texture shader.
		result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Title->GetIndexCount(), worldMatrix5, Getbase(), orthoMatrix, m_Title->GetTexture());
		if (!result)
		{
			return false;
		}
	}

	if (isEnter == true)
	{
		result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}
	

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_NormalWall->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_NormalWall->GetIndexCount(),
		m_NormalWall->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_NormalWall->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		m_Light->GetDiffuseColor(), m_Plight->GetPosition());
	if(!result)
	{
		return false;
	}

	m_Bird->Render(m_D3D->GetDeviceContext());


	worldMatrix3 = XMMatrixTranslation(60.0f,0.0f, 0.0f) * XMMatrixRotationY(rotation) * XMMatrixTranslation(60.0f, 0.0f, 0.0f);
	// Render the model using the light shader.
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Bird->GetIndexCount(),
		m_Bird->GetInstanceCount(), worldMatrix3, viewMatrix, projectionMatrix,
		m_Bird->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		m_Light->GetDiffuseColor(), m_Plight->GetPosition());
	if (!result)
	{
		return false;
	}


	m_Floor->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Floor->GetIndexCount(),
		m_Floor->GetInstanceCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Floor->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		m_Light->GetDiffuseColor(), m_Plight->GetPosition());
	if (!result)
	{
		return false;
	}

	cameraPosition = m_Camera->GetPosition();

	modelPosition.x = 21.0f;
	modelPosition.y = 30.0f;
	modelPosition.z = 63.0f;

	angle = atan2(modelPosition.x - cameraPosition.x, modelPosition.z - cameraPosition.z) * (180.0 / XM_PI);
	rota = (float)angle * 0.0174532925f;
	worldMatrix = XMMatrixRotationY(rota);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(modelPosition.x, modelPosition.y, modelPosition.z));

	m_Pin->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_Pin->GetIndexCount(),
		1, worldMatrix, viewMatrix, projectionMatrix,
		m_Pin->GetTexture(),
		m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
		m_Light->GetDiffuseColor(), m_Plight->GetPosition());
	if (!result)
	{
		return false;
	}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

XMMATRIX GraphicsClass::Getbase()
{
	return baseViewMatrix;
}