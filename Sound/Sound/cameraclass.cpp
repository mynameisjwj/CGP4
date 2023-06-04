////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = -10.0f;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;

	position = XMLoadFloat3(&m_position);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	XMVECTOR up, DefaultForward, DefaultRight, camForward, camRight, lookAt;
	XMMATRIX rotationMatrix;

	// Setup the vector that points upwards.
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);
	// Setup the position of the camera in the world.


	// Setup where the camera is looking by default

	// Create the rotation matrix from the yaw, pitch, and roll values.

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = XMVector3TransformCoord(DefaultForward, rotationMatrix);
	lookAt = XMVector3Normalize(lookAt);

	XMMATRIX RotateYTempMatrix;

	RotateYTempMatrix = XMMatrixRotationY(yaw);
	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	up = XMVector3TransformCoord(up, rotationMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);
	position += moveLeftRight * camRight;
	position += moveBackForward * camForward;


	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	// Translate the rotated camera position to the location of the viewer.
	lookAt = position + lookAt;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}