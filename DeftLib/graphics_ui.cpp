#include "graphics_ui.h"
#include "graphics_backend.h"
#include "geometry.h"
#include "audio.h"
#include <math.h>

#include <iostream>
#include <stdlib.h>

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

			void _be_on_left_mouse_press(int mouse_x, int mouse_y)
			{
				// Handle input for the clicked on panel, if any.
				for (auto& panel : _be_panels)
				{
					if (geometry::pt_rect_collide(mouse_x, mouse_y, panel->rect))
					{
						panel->on_left_mouse_press(mouse_x, mouse_y);
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
			for (auto& gadget : gadgets_)
			{
				if (gadget->selected)
					return gadget->name;
			}

			return "";
		}

		void Panel::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			for (auto& gadget : gadgets_)
			{
				if (gadget->selected)
				{
					gadget->on_left_mouse_release(mouse_x, mouse_y);
					gadget->selected = false;
					return;
				}
			}
		}

		void Panel::on_left_mouse_press(int mouse_x, int mouse_y)
		{
			for (auto& gadget : gadgets_)
			{
				if (geometry::pt_rect_collide(mouse_x, mouse_y, gadget->rect))
				{
					gadget->selected = true;
					gadget->on_left_mouse_press(mouse_x, mouse_y);
					return;
				}
			}
		}		

		const int TEXTBOX_HEIGHT = 100;
		const int TEXT_BUTTON_HEIGHT = 40;
		const int INT_SLIDER_HEIGHT = 20;
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

			if (selected)
				render_selected();

			if (name != "")
				backend::_be_render_text(name.c_str(), rect.x + 7, rect.y + 7, static_cast<Color>(black), backend::font_16);

			if (text != "")
				backend::_be_render_text(text.c_str(), rect.x + 7, rect.y + TEXTBOX_LABEL_HEIGHT, static_cast<Color>(black), backend::font_12);
		}

		void TextBox::render_selected()
		{
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(rect);

			backend::_be_fill_rect(&box_rect, dark_gray);
			backend::_be_outline_rect(&box_rect, light_gray, 3);
		}

		void TextButton::render()
		{
			SDL_Rect button_rect = backend::_be_rect_to_sdl_rect(rect);

			if (selected)
			{
				render_selected();
			}
			else
			{
				backend::_be_fill_rect(&button_rect, light_gray);
				backend::_be_outline_rect(&button_rect, black, 3);
			}

			if (name != "")
				backend::_be_render_text(name.c_str(), rect.x + 4, rect.y + 4, static_cast<Color>(black), backend::font_14);
		}

		void TextButton::render_selected()
		{
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(rect);

			backend::_be_fill_rect(&box_rect, dark_gray);
			backend::_be_outline_rect(&box_rect, light_gray, 3);
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

		void Panel::add_int_slider(std::string label, int* var)
		{
			IntSlider* slider = new IntSlider();

			slider->name = label;

			// If first element, position top left corner
			if (gadgets_.size() == 0)
			{
				slider->rect = Rect
				{
					rect.x + PANEL_PADDING + IntSlider::LABEL_PADDING,
					rect.y + PANEL_PADDING,
					IntSlider::SLIDER_BAR_W,
					INT_SLIDER_HEIGHT
				};
			}
			else
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				slider->rect = Rect
				{
					rect.x + PANEL_PADDING + IntSlider::LABEL_PADDING,
					last_gadget->rect.y + last_gadget->rect.h + PANEL_PADDING,
					IntSlider::SLIDER_BAR_W,
					INT_SLIDER_HEIGHT
				};
			}

			slider->slider.w = IntSlider::SLIDER_MARKER_W;
			slider->slider.h = IntSlider::SLIDER_MARKER_H;
			slider->slider.y = (slider->rect.y + (slider->rect.h / 2)) - (slider->slider.h / 2); // Middle of IntSlider rect
			slider->slider.x = slider->rect.x + IntSlider::LABEL_PADDING;

			gadgets_.push_back(slider);
		}

		void IntSlider::set_var(int& var, int min, int max)
		{
			this->var = &var;
			this->min = min;
			this->max = max;
		}

		void IntSlider::on_left_mouse_press(int mouse_x, int mouse_y)
		{
			if (geometry::pt_rect_collide(mouse_x, mouse_y, slider))
			{
				slider.x = mouse_x - (slider.w / 2);
				// Horizontal slider, Y does not change.

				if (slider.x < rect.x)
					slider.x = rect.x;
				else if (slider.x + slider.w > rect.x + rect.w)
					slider.x = rect.x + rect.w;

				selected = true;
			}
		}

		void IntSlider::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			slider.x = mouse_x - (slider.w / 2);

			if (selected && var != nullptr)
			{

				float val_per_pixel = rect.w / fabs(min - max);

				if (slider.x < rect.x)
				{
					*var = min;
					slider.x = rect.x + 10;
				}
				else if (slider.x + slider.w > rect.x + rect.w)
				{
					*var = max;
					slider.x = rect.x + rect.w - ((slider.w / 2) + 10);
				}
				else
				{
					// start = slider.x;
					// end = slider.x + slider.w;
					// distance for 100% = slider.w;
					// actual distance = slider_bar.x - slider.x

					// pcnt_done = actual_dist / max_dist


					// pcnt_done = 
					// value = max * pcnt_done;
					*var = min + ((mouse_x - rect.x) * val_per_pixel);
					slider.x = mouse_x - (slider.w / 2);
				}
			}

			selected = false;
		}

		void IntSlider::render()
		{
			if (selected)
				render_selected();
			else
			{
				SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(rect);
				SDL_Rect slider_rect = backend::_be_rect_to_sdl_rect(slider);

				backend::_be_fill_rect(&box_rect, light_gray);
				backend::_be_outline_rect(&box_rect, black, 3);
				backend::_be_fill_rect(&slider_rect, blue);
			}

			backend::_be_render_text(name.c_str(), rect.x - IntSlider::LABEL_PADDING + 5, rect.y + 5, static_cast<Color>(black), deft::graphics::backend::font_14);

			if (var != nullptr)
				backend::_be_render_text(std::to_string(*var).c_str(), rect.x + IntSlider::SLIDER_BAR_W + 5, rect.y + 5, static_cast<Color>(black), deft::graphics::backend::font_14);
		}

		void IntSlider::render_selected()
		{
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(rect);
			SDL_Rect slider_rect = backend::_be_rect_to_sdl_rect(slider);
			backend::_be_fill_rect(&box_rect, light_gray);
			backend::_be_outline_rect(&box_rect, black, 3);
			backend::_be_fill_rect(&slider_rect, white);
		}
	}
}