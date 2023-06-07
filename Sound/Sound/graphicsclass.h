////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"

#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "textclass.h"

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

	bool Initialize(int, int, HWND);
	void Shutdown();
	void SetTitle();
	bool Frame();
	bool Frame(int, int, int, int);
	bool isEnter = false;
	XMMATRIX Getbase();
	CameraClass* m_Camera;

private:
	bool Render(float);

private:

	XMMATRIX baseViewMatrix;
	D3DClass* m_D3D;
	ModelClass* m_NormalWall;
	ModelClass* m_Bird;
	ModelClass* m_LongWall;
	ModelClass* m_Floor;
	ModelClass* m_Model;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	LightClass* m_Plight;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	BitmapClass* m_Title;
	ModelClass* m_Pin;

	TextClass* m_Text;
};

#endif