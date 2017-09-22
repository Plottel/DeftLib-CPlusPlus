#include "graphics_ui.h"
#include "graphics_backend.h"
#include "geometry.h"
#include "audio.h"
#include <math.h>
#include <iomanip>
#include <sstream>

#include <iostream>
#include <stdlib.h>
#include <memory>

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
			std::vector<std::unique_ptr<Panel>> _be_panels;

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
				if (geometry::pt_rect_collide(mouse_x, mouse_y, gadget->gadget_rect))
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

		void TextBox::render()
		{
			int TEXTBOX_LABEL_HEIGHT = 25;

			// Textbox area.
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(gadget_rect);
			// Area for label (top of textbox)
			SDL_Rect label_rect = SDL_Rect{ (int)gadget_rect.x, (int)gadget_rect.y, gadget_rect.w, TEXTBOX_LABEL_HEIGHT };

			// Fill border and colour label area on top
			backend::_be_fill_rect(&box_rect, light_gray);
			backend::_be_outline_rect(&label_rect, black, 3);
			backend::_be_outline_rect(&box_rect, black, 3);

			if (selected)
				render_selected();

			if (name != "")
				backend::_be_render_text(name.c_str(), gadget_rect.x + 7, gadget_rect.y + 7, static_cast<Color>(black), backend::font_16);

			if (text != "")
				backend::_be_render_text(text.c_str(), gadget_rect.x + 7, gadget_rect.y + TEXTBOX_LABEL_HEIGHT, static_cast<Color>(black), backend::font_12);
		}

		void TextBox::render_selected()
		{
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(gadget_rect);

			backend::_be_fill_rect(&box_rect, dark_gray);
			backend::_be_outline_rect(&box_rect, light_gray, 3);
		}

		void TextButton::render()
		{
			SDL_Rect button_rect = backend::_be_rect_to_sdl_rect(gadget_rect);

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
				backend::_be_render_text(name.c_str(), gadget_rect.x + 4, gadget_rect.y + 4, static_cast<Color>(black), backend::font_14);
		}

		void TextButton::render_selected()
		{
			SDL_Rect box_rect = backend::_be_rect_to_sdl_rect(gadget_rect);

			backend::_be_fill_rect(&box_rect, dark_gray);
			backend::_be_outline_rect(&box_rect, light_gray, 3);
		}

		void add_panel(std::unique_ptr<Panel> panel)
		{
		}

		Panel::Panel(std::string panel_name, int x, int y, int w, int h)
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
				box->gadget_rect = Rect
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

				box->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING,
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
				button->gadget_rect = Rect
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

				button->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					TEXT_BUTTON_HEIGHT
				};
			}

			gadgets_.push_back(button);
		}

		void Panel::add_int_slider(std::string label, int* var)
		{
			IntSlider* gadget = new IntSlider();

			gadget->name = label;

			// If first element, position top left corner
			if (gadgets_.size() == 0)
			{
				gadget->slider_bar = Rect
				{
					rect.x + PANEL_PADDING + IntSlider::LABEL_PADDING,
					rect.y + PANEL_PADDING + (INT_SLIDER_HEIGHT / 2) - (IntSlider::SLIDER_BAR_H / 2),
					IntSlider::SLIDER_BAR_W,
					IntSlider::SLIDER_BAR_H
				};

				gadget->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING,
					rect.y + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					INT_SLIDER_HEIGHT
				};
			}
			else // If elements exist, position below bottom element
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				gadget->slider_bar = Rect
				{
					rect.x + PANEL_PADDING + IntSlider::LABEL_PADDING,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING + (INT_SLIDER_HEIGHT / 2) - (IntSlider::SLIDER_BAR_H / 2),
					IntSlider::SLIDER_BAR_W,
					IntSlider::SLIDER_BAR_H
				};

				gadget->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING,
					rect.w - (PANEL_PADDING * 2),
					INT_SLIDER_HEIGHT
				};
			}

			gadget->val_marker.w = IntSlider::SLIDER_MARKER_W;
			gadget->val_marker.h = IntSlider::SLIDER_MARKER_H;
			gadget->val_marker.y = (gadget->gadget_rect.y + (gadget->gadget_rect.h / 2)) - (gadget->val_marker.h / 2); // Middle of IntSlider rect
			gadget->val_marker.x = gadget->gadget_rect.x + IntSlider::LABEL_PADDING;

			gadgets_.push_back(gadget);
		}

		void IntSlider::set_val(int& var, int min, int max)
		{
			this->val = &var;
			this->min = min;
			this->max = max;
		}

		void IntSlider::clamp_val_marker()
		{
			if (val_marker.x < slider_bar.x)
				val_marker.x = slider_bar.x;
			else if (val_marker.x + val_marker.w > slider_bar.x + slider_bar.w)
				val_marker.x = slider_bar.x + slider_bar.w - val_marker.w;
		}

		void IntSlider::update_val()
		{
			//    percentHealth = (currentHealth / maxHealth) * 100; //get's health percentage.

			//float val_per_pixel = slider_bar.w / fabs(min - max);

			if (val_marker.x <= slider_bar.x)
				*val = min;
			else if (val_marker.x + val_marker.w >= slider_bar.x + slider_bar.w)
				*val = max;
			else
			{
				int max_dist = slider_bar.w;
				int cur_dist = val_marker.x - slider_bar.x;

				*val = max * ((float)((float)cur_dist / (float)max_dist));
			
				//*val = min + ((val_marker.x - slider_bar.x) * val_per_pixel);
			}
		}

		void IntSlider::on_left_mouse_press(int mouse_x, int mouse_y)
		{
			if (geometry::pt_rect_collide(mouse_x, mouse_y, gadget_rect))
			{
				selected = true;
				val_marker.x = mouse_x - (val_marker.w / 2);	// Horizontal slider, Y does not change.
				clamp_val_marker();

				if (val != nullptr)
					update_val();
			}
		}		

		void IntSlider::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			val_marker.x = mouse_x - (val_marker.w / 2);

			if (selected && val != nullptr)
			{
				clamp_val_marker();
				update_val();
			}

			selected = false;
		}

		void IntSlider::render()
		{
			SDL_Rect sdl_slider_bar = backend::_be_rect_to_sdl_rect(slider_bar);
			SDL_Rect sdl_val_marker = backend::_be_rect_to_sdl_rect(val_marker);

			backend::_be_fill_rect(&sdl_slider_bar, black);
			backend::_be_fill_rect(&sdl_val_marker, blue);

			backend::_be_render_text(name.c_str(), gadget_rect.x, gadget_rect.y + 5, static_cast<Color>(black), deft::graphics::backend::font_14);

			if (val != nullptr)
			{
				std::stringstream stream;
				stream << std::setprecision(3) << *val;

				backend::_be_render_text(stream.str().c_str(), gadget_rect.x + gadget_rect.w - PANEL_PADDING - 5, gadget_rect.y + 5, static_cast<Color>(black), deft::graphics::backend::font_14);
			}				
		}

		void IntSlider::render_selected()
		{
		}
	}
}