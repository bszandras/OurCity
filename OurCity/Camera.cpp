#include "Camera.h"

Camera::Camera()
{
	position = { 0.0f,0.0f };
}

Camera::Camera(Vector2Data pos)
{
	position = pos;
}

Camera::~Camera()
{
}

void Camera::Move(Vector2Data dir)
{
	dir = Vector2Tool::Scale(dir, movementSpeed);
	dir = Vector2Tool::Scale(dir, 1/zoom);
	position = Vector2Tool::Add(position, dir);
}
void Camera::Zoom(float z)
{
	zoom += z * zoomSpeed * zoom;
	if (zoom < minZoom)
	{
		zoom = minZoom;
	}
	else if (zoom > maxZoom)
	{
		zoom = maxZoom;
	}
}
Vector2Data Camera::getPosition()
{
	return position;
}
float Camera::getZoom()
{
	return zoom;
}
