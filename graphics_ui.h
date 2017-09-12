#pragma once

#include <string>
#include "geometry.h"
#include "color.h"

namespace deft
{
	namespace graphics
	{
		typedef struct
		{
			std::string text;
			Rect rect;
			Color background_color;
			Color text_color;
		} TextBox;

		void draw_textbox(TextBox& text_box);
	}
}
