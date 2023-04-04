#pragma once
#include "Vector.h"
#include "World.h"
#include "Camera.h"
enum MouseState
{
	NOTHING,
	CLICK,
	DRAG,
	MOVED
};
class MouseController
{
private:
	static MouseController* instance;
	MouseState stateThisFrame;
	bool drag = false;
	Vector2Data screenPosition;

	Vector2Data worldDragStart;
public:
	MouseController();
	~MouseController();
	void ClearControlFrame();
	void UpdateControlFrame(Vector2Data position, MouseState state);
	Vector2Data getScreenPosition();
	Vector2Data getRecalculateWorldPosition(World* world, Camera* camera);
	MouseState getMouseState();
	Vector2Data getWorldDragStart();
	void setDragStart(World* world, Camera* camera);
};