#include "graphics_ui.h"
#include "graphics_backend.h"

#include <iostream>

namespace deft
{
	namespace graphics
	{
		void draw_textbox(TextBox& textbox)
		{
			int TEXTBOX_LABEL_HEIGHT = 20;

			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(textbox.rect);
			SDL_Rect label_rect = SDL_Rect{ (int)textbox.rect.x, (int)textbox.rect.y, textbox.rect.w, TEXTBOX_LABEL_HEIGHT };

			backend::_be_fill_rect(&box_rect, textbox.background_color);
			backend::_be_fill_rect(&label_rect, blue);

			if (textbox.label != "")
				backend::_be_render_text(textbox.label.c_str(), textbox.rect.x, textbox.rect.y, textbox.text_color);

			if (textbox.text != "")
				backend::_be_render_text(textbox.text.c_str(), textbox.rect.x, textbox.rect.y + TEXTBOX_LABEL_HEIGHT, textbox.text_color);
		}
	}
}