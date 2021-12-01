#include "Renderer.h"

void Renderer::setSize(Vec2i screenSize)
{
	screenScale.x = (float)(screenSize.y) / (float)(screenSize.x);
	screenScale.y = 1;
	screenScale.z = 1;
}
