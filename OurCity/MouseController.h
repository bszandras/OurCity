#pragma once
#include "Vector.h"
#include "World.h"
#include "Camera.h"
enum MouseState
{
	NOTHING,
	CLICK,
	DRAG
};
class MouseController
{
private:
	static MouseController* instance;
	MouseState stateThisFrame;
	Vector2Data screenPosition;
public:
	MouseController();
	~MouseController();
	void ClearControlFrame();
	void UpdateControlFrame(Vector2Data position);
	Vector2Data getScreenPosition();
	Vector2Data getWorldPosition(World* world, Camera* camera);
};