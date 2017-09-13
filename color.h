#pragma once

namespace deft
{
	struct Color
	{
		float r, g, b, a;
	};

	static const Color red = { 255, 0, 0, 255 };
	static const Color green = { 0, 255, 0, 255 };
	static const Color blue = { 0, 0, 255, 255 };
	static const Color gray = { 108, 123, 139, 255 };
	static const Color light_gray = { 200, 200, 200, 255 };
	static const Color dark_gray = { 65, 65, 65, 255 };
	static const Color black = { 0, 0, 0, 255 };
	static const Color faded_black = { 0, 0, 0, 128 };
	static const Color white = { 255, 255, 255, 0 };
	static const Color yellow = { 238, 238, 0, 255 };
}
