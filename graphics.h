#pragma once
#include "color.h"
#include <string>

namespace deft
{
	namespace graphics
	{
		void init();

		void outline_rect(float x, float y, float w, float h, Color clr);
		void text(std::string text, float x, float y, Color& clr);

		void pre_render();
		void post_render();


		void quit();
	}
}