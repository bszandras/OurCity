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

void MouseController::ClearControlFrame()
{
	stateThisFrame = MouseState::NOTHING;
	screenPosition = { 0,0 };
}

void MouseController::UpdateControlFrame(Vector2Data position)
{
	screenPosition = position;
	stateThisFrame = MouseState::MOVED;
}

Vector2Data MouseController::getScreenPosition()
{
	
	return screenPosition;
}

Vector2Data MouseController::getWorldPosition(World* world, Camera* camera)
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
