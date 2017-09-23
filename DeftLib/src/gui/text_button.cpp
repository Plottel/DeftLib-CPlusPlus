#include "text_button.h"
#include "../graphics/graphics_backend.h"

namespace deft
{
	namespace gui
	{
		void TextButton::render()
		{
			SDL_Rect button_rect = graphics::backend::_be_rect_to_sdl_rect(gadget_rect);

			if (selected)
			{
				render_selected();
			}
			else
			{
				graphics::backend::_be_fill_rect(&button_rect, light_gray);
				graphics::backend::_be_outline_rect(&button_rect, black, 3);
			}

			if (name != "")
				graphics::backend::_be_render_text(name.c_str(), gadget_rect.x + 4, gadget_rect.y + 4, static_cast<Color>(black), graphics::backend::font_14);
		}

		void TextButton::render_selected()
		{
			SDL_Rect box_rect = graphics::backend::_be_rect_to_sdl_rect(gadget_rect);

			graphics::backend::_be_fill_rect(&box_rect, dark_gray);
			graphics::backend::_be_outline_rect(&box_rect, light_gray, 3);
		}
	}
}