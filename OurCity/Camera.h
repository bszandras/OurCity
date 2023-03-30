#pragma once
#include "Vector.h"
class Camera
{
private:
	Vector2Data position;
	float movementSpeed = 120;
	float zoom = 1;
	float minZoom = 0.005f;
	float maxZoom = 4.5f;
	float zoomSpeed = 30;
public:
	Camera();
	Camera(Vector2Data pos);
	~Camera();
	void Move(Vector2Data dir);
	void Zoom(float z);
	Vector2Data getPosition();
	float getZoom();
};