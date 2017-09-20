#pragma once
#include "color.h"
#include "geometry.h"
#include <string>

namespace deft
{
	namespace graphics
	{
		void init();

		void outline_rect(float x, float y, float w, float h, Color clr, int thickness=1);
		void outline_rect(Rect rect, Color clr, int thickness=1);

		void fill_rect(float x, float y, float w, float h, Color clr);
		void fill_rect(Rect rect, Color clr);
		
		void outline_circle(Circle circle, Color clr);
		void fill_circle(Circle circle, Color clr);

		void text(std::string text, float x, float y, Color& clr);

		void pre_render();
		void post_render();


		void quit();
	}
}