#include "graphics_ui.h"
#include "graphics_backend.h"

#include <iostream>

namespace deft
{
	namespace graphics
	{
		namespace backend
		{
			std::vector<TextBox> _be_text_boxes;
			std::vector<TextButton> _be_text_buttons;
		}

		const int TEXTBOX_HEIGHT = 100;
		const int TEXT_BUTTON_HEIGHT = 40;
		const int PANEL_PADDING = 10;

		void TextBox::render()
		{
			int TEXTBOX_LABEL_HEIGHT = 25;

			// Textbox area.
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(rect);
			// Area for label (top of textbox)
			SDL_Rect label_rect = SDL_Rect{ (int)rect.x, (int)rect.y, rect.w, TEXTBOX_LABEL_HEIGHT };

			// Fill border and colour label area on top
			backend::_be_fill_rect(&box_rect, light_gray);
			backend::_be_outline_rect(&label_rect, black, 3);
			backend::_be_outline_rect(&box_rect, black, 3);

			if (label != "")
				backend::_be_render_text(label.c_str(), rect.x + 7, rect.y + 7, static_cast<Color>(black), backend::font_16);

			if (text != "")
				backend::_be_render_text(text.c_str(), rect.x + 7, rect.y + TEXTBOX_LABEL_HEIGHT, static_cast<Color>(black), backend::font_12);
		}

		void TextButton::render()
		{
			SDL_Rect button_rect = backend::_be_rect_to_sdl_rect(rect);

			if (selected)
			{
				backend::_be_fill_rect(&button_rect, mid_gray);
				backend::_be_outline_rect(&button_rect, black, 5);
			}
			else
			{
				backend::_be_fill_rect(&button_rect, light_gray);
				backend::_be_outline_rect(&button_rect, black, 3);
			}

			if (label != "")
				backend::_be_render_text(label.c_str(), rect.x + 4, rect.y + 4, static_cast<Color>(black), backend::font_14);
		}

		Panel::Panel(float x, float y, int w, int h)
		{
			rect = Rect{ x, y, w, h };
		}

		void Panel::render()
		{
			SDL_Rect sdl_rect = backend::_be_rect_to_sdl_rect(rect);

			backend::_be_fill_rect(&sdl_rect, light_gray);
			backend::_be_outline_rect(&sdl_rect, dark_gray, 5);

			for (auto& gadget : gadgets_)
				gadget->render();
		}

		void Panel::add_textbox(std::string label, std::string text)
		{
			TextBox box;

			box.label = label;
			box.text = text;

			// If first element, position top left corner.
			if (gadgets_.empty())
			{
				box.rect = Rect
				{
					rect.x + PANEL_PADDING,
					rect.y + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXTBOX_HEIGHT
				};
			}
			else // If other elements exist, position below lowest element.
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				box.rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->rect.y + last_gadget->rect.h + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXTBOX_HEIGHT
				};
			}			

			backend::_be_text_boxes.push_back(box);
			gadgets_.push_back(&backend::_be_text_boxes[backend::_be_text_boxes.size() - 1]);
		}

		void Panel::add_text_button(std::string label)
		{
			TextButton button;

			button.label = label;
			button.selected = false;

			// If first element, position top left corner
			if (gadgets_.empty())
			{
				button.rect = Rect
				{
					rect.x + PANEL_PADDING,
					rect.y + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXT_BUTTON_HEIGHT
				};
			}
			else // If other elements exist, position below lowest element.
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				button.rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->rect.y + last_gadget->rect.h + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXT_BUTTON_HEIGHT
				};
			}			

			backend::_be_text_buttons.push_back(button);
			gadgets_.push_back(&backend::_be_text_buttons[backend::_be_text_buttons.size() - 1]);
		}

		void draw_text_box(TextBox& textbox)
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

		void draw_text_button(TextButton& text_button)
		{
			SDL_Rect button_rect = backend::_be_rect_to_sdl_rect(text_button.rect);

			if (text_button.selected)
			{
				backend::_be_fill_rect(&button_rect, mid_gray);
				backend::_be_outline_rect(&button_rect, black, 5);
			}				
			else
			{
				backend::_be_fill_rect(&button_rect, light_gray);
				backend::_be_outline_rect(&button_rect, black, 3);
			}			

			if (text_button.label != "")
				backend::_be_render_text(text_button.label.c_str(), text_button.rect.x + 4, text_button.rect.y + 4, static_cast<Color>(black), backend::font_14);
		}
	}
}