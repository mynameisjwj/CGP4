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
	bool Frame();
	bool Frame(int, int, int, int);
	void setAmbient();
	void setAmbient_off();
	void setDiffuse();
	void setDiffuse_off();
	void setSpeculer();
	void setSpeculer_off();
	void setColor(char);
	bool isAmbient = false;
	bool isDiffuse = false;
	bool isSpeculer = false;
	CameraClass* m_Camera;
private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	ModelClass* m_Model;
	ModelClass* m_Floor;
	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	LightClass* m_Plight;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;

	TextClass* m_Text;
};

#endif