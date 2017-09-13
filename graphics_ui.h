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
			std::string label;
			std::string text;
			Rect rect;
		} TextBox;

		typedef struct
		{
			std::string text;
			Rect rect;
		} TextButton;

		void draw_text_box(TextBox& text_box);
		void draw_text_button(TextButton& text_button);
	}
}
