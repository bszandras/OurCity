#include "Overlay.h"

Overlay* Overlay::instance;

Overlay::Overlay()
{
	if (instance == nullptr)
	{
		instance = this;

		instance->cursor = new Tile[4];

		for (int i = 0; i < 4; i++)
		{
			(instance->cursor + i)->rect = { (unsigned short)-20,(unsigned short)-20 };
			(instance->cursor + i)->texId = 40;
		}

	}
	else
	{
		// idk
	}
}

Overlay::~Overlay()
{
}

void Overlay::Cursor(bool visible, Vector2Data position)
{
	if (instance == nullptr)
	{
		std::cout << "Overlay instance null" << std::endl;
		return;
	}

	if (!visible)
	{
		instance->cursor->rect = { (unsigned short)-20,(unsigned short)-20 };
		return;
	}
	else
	{
		// position tuti mindig egész szám
		instance->cursorSize = 1;
		instance->cursor->rect = { (unsigned short)position.x, (unsigned short)position.y };
	}
}

void Overlay::MultiCursor(bool visible, Vector2Data positions[], int count)
{
	if (instance == nullptr)
	{
		//std::cout << "Overlay instance null" << std::endl;
		return;
	}

	if (!visible)
	{
		instance->cursorSize = 1;
		instance->cursor->rect = { (unsigned short)-20,(unsigned short)-20 };
		return;
	}
	else
	{
		instance->cursorSize = count;

		for (int i = 0; i < count; i++)
		{
			(instance->cursor + i)->rect = { (unsigned short)positions[i].x, (unsigned short)positions[i].y };
		}
	}
}

Tile* Overlay::getCursor()
{
	if (instance == nullptr)
	{
		//std::cout << "Overlay instance null" << std::endl;
		return nullptr;
	}
	return instance->cursor;
}

int Overlay::getCursorSize()
{
	return instance->cursorSize;
}
