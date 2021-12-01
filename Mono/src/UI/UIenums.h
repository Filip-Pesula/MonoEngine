#pragma once
namespace UI
{
	enum class MouseState
	{
		FREE,
		PRESS,
		HOLD,
		RELEAS
	};
	struct DrawModes {
		static const int no_Texture = 0;
		static const int plane_Texture = 1;
		static const int tiled_Texture = 2;
	};
}
