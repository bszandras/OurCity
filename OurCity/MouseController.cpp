#include "MouseController.h"
#include "Window.h"

MouseController* MouseController::instance = nullptr;
MouseController::MouseController()
{
	if (instance != nullptr)
	{
		return;
	}
	instance = this;
	stateThisFrame = MouseState::NOTHING;
}

MouseController::~MouseController()
{
}
#ifndef TESTING
void MouseController::ClearControlFrame()
{
	stateThisFrame = MouseState::NOTHING;
	screenPosition = { 0,0 };
}

void MouseController::UpdateControlFrame(Vector2Data position, MouseState state)
{
	screenPosition = position;
	if (drag)
	{
		if (state != MouseState::CLICK)
		{
			stateThisFrame = MouseState::DRAG;
		}
		else
		{
			drag = false;
			stateThisFrame = MouseState::CLICK;
		}
	}
	else
	{
		if (state == MouseState::DRAG)
		{
			drag = true;
		}
		stateThisFrame = state;
	}
	
	//stateThisFrame = state;
}

Vector2Data MouseController::getScreenPosition()
{
	
	return screenPosition;
}

Vector2Data MouseController::getRecalculateWorldPosition(World* world, Camera* camera)
{
	//std::cout << screenPosition.x << " " << screenPosition.y << std::endl;
 	Vector2Data worldPos = Vector2Tool::ScreenToWorldSpace({ screenPosition.x,screenPosition.y },
		{ (float)Window::instance->getWidth(), (float)Window::instance->getHeight() },
		camera->getPosition(), camera->getZoom(),
		world->getOrigoOffset());
	return worldPos;
}
MouseState MouseController::getMouseState()
{
	return stateThisFrame;
}

Vector2Data MouseController::getWorldDragStart()
{
	return worldDragStart;
}

void MouseController::setDragStart(World* world, Camera* camera)
{
	worldDragStart = getRecalculateWorldPosition(world, camera);
}
#endif