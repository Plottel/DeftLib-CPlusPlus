#include "graphics_ui.h"
#include "graphics_backend.h"
#include "geometry.h"
#include "audio.h"

#include <iostream>

namespace deft
{
	namespace graphics
	{
		void Panel::render()
		{
			SDL_Rect sdl_rect = backend::_be_rect_to_sdl_rect(rect);

			backend::_be_fill_rect(&sdl_rect, light_gray);
			backend::_be_outline_rect(&sdl_rect, dark_gray, 5);

			for (auto& gadget : gadgets_)
				gadget->render();
		}

		namespace backend
		{
			std::vector<Panel*> _be_panels;

			void _be_on_left_mouse_release(int mouse_x, int mouse_y)
			{
				// Handle input for the clicked on panel, if any.
				for (auto& panel : _be_panels)
				{
					if (geometry::pt_rect_collide(mouse_x, mouse_y, panel->rect))
					{
						panel->on_left_mouse_release(mouse_x, mouse_y);
						return;
					}
				}
			}

			void _be_render_gui()
			{
				for (auto& panel : _be_panels)
					panel->render();
			}
		}	

		void render_gui()
		{
			backend::_be_render_gui();
		}

		std::string Panel::clicked()
		{
			if (active_gadget_ == nullptr)
				return "";
			return active_gadget_->name;
		}

		void Panel::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			if (active_gadget_)
			{
				active_gadget_->on_left_mouse_release(mouse_x, mouse_y);
				// Mouse not on any active gadget.
				active_gadget_ = nullptr;
			}
		}

		void Panel::on_left_mouse_press(int mouse_x, int mouse_y)
		{
			// Reset active gadget
			active_gadget_ = nullptr;

			for (auto& gadget : gadgets_)
			{
				if (geometry::pt_rect_collide(mouse_x, mouse_y, gadget->rect))
				{
					active_gadget_ = gadget;
					return;
				}
			}
		}

		MusicPlayerPanel::MusicPlayerPanel(std::string panel_name, float x, float y, int w, int h)
			: Panel(panel_name, x, y, w, h)
		{
			add_text_button("Play Music");
			add_text_button("Pause Music");
			add_text_button("Resume Music");
			add_text_button("Stop Music");
			add_text_button("Toggle Music");
		}

		void MusicPlayerPanel::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			Panel::on_left_mouse_release(mouse_x, mouse_y);

			if (clicked() == "Play Music")
				audio::play_music("jumpshot.mp3");
			if (clicked() == "Pause Music")
				audio::pause_music();
			if (clicked() == "Resume Music")
				audio::resume_music();
			if (clicked() == "Stop Music")
				audio::stop_music();
			if (clicked() == "Toggle Music")
				audio::toggle_music();				
		}

		const int TEXTBOX_HEIGHT = 100;
		const int TEXT_BUTTON_HEIGHT = 40;
		const int PANEL_PADDING = 10;

		void add_panel(Panel* panel)
		{
			backend::_be_panels.push_back(panel);
		}

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

			if (name != "")
				backend::_be_render_text(name.c_str(), rect.x + 7, rect.y + 7, static_cast<Color>(black), backend::font_16);

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

			if (name != "")
				backend::_be_render_text(name.c_str(), rect.x + 4, rect.y + 4, static_cast<Color>(black), backend::font_14);
		}

		Panel::Panel(std::string panel_name, float x, float y, int w, int h)
		{
			name = panel_name;
			rect = Rect{ x, y, w, h };
		}

		Panel::~Panel()
		{
			for (auto& gadget : gadgets_)
				delete gadget;
		}

		void Panel::add_textbox(std::string label, std::string text)
		{
			TextBox* box = new TextBox();

			box->name = label;
			box->text = text;

			// If first element, position top left corner.
			if (gadgets_.empty())
			{
				box->rect = Rect
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

				box->rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->rect.y + last_gadget->rect.h + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXTBOX_HEIGHT
				};
			}

			gadgets_.push_back(box);
		}

		Gadget* Panel::last_added()
		{
			if (gadgets_.empty())
				return nullptr;
			return gadgets_[gadgets_.size() - 1];
		}

		void Panel::add_text_button(std::string label)
		{
			TextButton* button = new TextButton();

			button->name = label;

			// If first element, position top left corner
			if (gadgets_.size() == 0)
			{
				button->rect = Rect
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

				button->rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->rect.y + last_gadget->rect.h + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXT_BUTTON_HEIGHT
				};
			}			

			gadgets_.push_back(button);
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

			if (textbox.name != "")
				backend::_be_render_text(textbox.name.c_str(), textbox.rect.x + 7, textbox.rect.y + 7, static_cast<Color>(black), backend::font_16);

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

			if (text_button.name != "")
				backend::_be_render_text(text_button.name.c_str(), text_button.rect.x + 4, text_button.rect.y + 4, static_cast<Color>(black), backend::font_14);
		}
	}
}