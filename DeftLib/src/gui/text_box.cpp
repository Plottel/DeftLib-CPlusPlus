#include "text_box.h"
#include "../graphics/graphics_backend.h"

namespace deft
{
	namespace gui
	{
		void TextBox::render()
		{
			int TEXTBOX_LABEL_HEIGHT = 25;

			// Textbox area.
			SDL_Rect box_rect = graphics::backend::r_to_sdlr(gadget_rect);
			// Area for label (top of textbox)
			SDL_Rect label_rect = SDL_Rect{ (int)gadget_rect.x, (int)gadget_rect.y, gadget_rect.w, TEXTBOX_LABEL_HEIGHT };

			// Fill border and colour label area on top
			graphics::backend::fill_r(&box_rect, light_gray);
			graphics::backend::outline_r(&label_rect, black, 3);
			graphics::backend::outline_r(&box_rect, black, 3);

			if (selected)
				render_selected();

			if (name != "")
				graphics::backend::render_text(name.c_str(), gadget_rect.x + 7, gadget_rect.y + 7, static_cast<Color>(black), graphics::backend::font_16);

			if (text != "")
				graphics::backend::render_text(text.c_str(), gadget_rect.x + 7, gadget_rect.y + TEXTBOX_LABEL_HEIGHT, static_cast<Color>(black), graphics::backend::font_12);
		}

		void TextBox::render_selected()
		{
			SDL_Rect box_rect = graphics::backend::r_to_sdlr(gadget_rect);

			graphics::backend::fill_r(&box_rect, dark_gray);
			graphics::backend::outline_r(&box_rect, light_gray, 3);
		}
	}
}