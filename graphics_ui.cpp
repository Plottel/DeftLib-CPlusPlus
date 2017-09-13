#include "graphics_ui.h"
#include "graphics_backend.h"

#include <iostream>

namespace deft
{
	namespace graphics
	{
		void draw_textbox(TextBox& textbox)
		{
			int TEXTBOX_LABEL_HEIGHT = 25;

			// Textbox area.
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(textbox.rect);
			// Area for label (top of textbox)
			SDL_Rect label_rect = SDL_Rect{ (int)textbox.rect.x, (int)textbox.rect.y, textbox.rect.w, TEXTBOX_LABEL_HEIGHT };

			// Fill border and colour label area on top
			backend::_be_fill_rect(&box_rect, light_gray);
			backend::_be_outline_rect(&label_rect, black, 3);
			backend::_be_outline_rect(&box_rect, black, 3);

			if (textbox.label != "")
				backend::_be_render_text(textbox.label.c_str(), textbox.rect.x + 7, textbox.rect.y + 7, static_cast<Color>(black), backend::font_16);

			if (textbox.text != "")
				backend::_be_render_text(textbox.text.c_str(), textbox.rect.x + 7, textbox.rect.y + TEXTBOX_LABEL_HEIGHT, static_cast<Color>(black), backend::font_12);

		}
	}
}