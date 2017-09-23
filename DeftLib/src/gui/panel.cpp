#include "panel.h"
#include "../graphics/graphics_backend.h"
#include "gadget_types.h"
#include "../input/input.h"

namespace deft
{
	namespace gui
	{
		const int TEXTBOX_HEIGHT = 100;
		const int TEXT_BUTTON_HEIGHT = 40;
		const int INT_SLIDER_HEIGHT = 20;
		const int PANEL_PADDING_X = 15;
		const int PANEL_PADDING_Y = 10;

		void Panel::render()
		{
			SDL_Rect sdl_rect = graphics::backend::_be_rect_to_sdl_rect(rect);
			SDL_Rect sdl_drag_rect = graphics::backend::_be_rect_to_sdl_rect(drag_rect());

			graphics::backend::_be_fill_rect(&sdl_rect, light_gray);
			graphics::backend::_be_fill_rect(&sdl_drag_rect, black);
			graphics::backend::_be_outline_rect(&sdl_rect, dark_gray, 5);
			graphics::backend::_be_outline_rect(&sdl_drag_rect, deft::dark_gray, 5);

			for (auto& gadget : gadgets_)
				gadget->render();

			if (name != "")
				graphics::backend::_be_render_text(name.c_str(), rect.x + 5, rect.y + 5, static_cast<Color>(deft::white), graphics::backend::font_16);
		}

		std::string Panel::clicked()
		{
			if (!input::mouse_released(deft::LEFT_MOUSE))
				return "";

			for (auto& gadget : gadgets_)
			{
				if (gadget->selected)
					return gadget->name;
			}

			return "";
		}

		void Panel::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			// Handle sub panel event.
			on_event(mouse_x, mouse_y);


			is_dragging_ = false;

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

		void Panel::move_by(float x, float y)
		{
			rect.x += x;
			rect.y += y;

			for (auto& gadget : gadgets_)
				gadget->move_by(x, y);
		}

		Rect Panel::drag_rect()
		{
			return Rect{ rect.x, rect.y, rect.w, 20 };
		}

		void Panel::on_left_mouse_down(int mouse_x, int mouse_y)
		{
			// Handle sub panel event.
			on_event(mouse_x, mouse_y);

			// Drag panel
			if (geometry::pt_rect_collide(mouse_x, mouse_y, drag_rect()))
			{
				if (!is_dragging_)
				{
					is_dragging_ = true;
					drag_pt_ = Vec2{ (float)mouse_x, (float)mouse_y };
				}
				else
				{
					// Move by the amount mouse moved since last check
					move_by(mouse_x - drag_pt_.x, mouse_y - drag_pt_.y);

					// Update drag point.
					drag_pt_ = Vec2{ (float)mouse_x, (float)mouse_y };
				}
			}
			else // Process gadget events.
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
					rect.x + PANEL_PADDING_X,
					rect.y + 20 + PANEL_PADDING_Y,
					rect.w - (PANEL_PADDING_X * 2),
					TEXTBOX_HEIGHT
				};
			}
			else // If other elements exist, position below lowest element.
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				box->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING_X,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING_Y,
					rect.w - (PANEL_PADDING_X * 2),
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
					rect.x + PANEL_PADDING_X,
					rect.y + 20 + PANEL_PADDING_Y ,
					rect.w - (PANEL_PADDING_X * 2),
					TEXT_BUTTON_HEIGHT
				};
			}
			else // If other elements exist, position below lowest element.
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				button->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING_X,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING_Y,
					rect.w - (PANEL_PADDING_X * 2),
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
					rect.x + PANEL_PADDING_X + IntSlider::LABEL_PADDING,
					rect.y + 20 + PANEL_PADDING_Y + (INT_SLIDER_HEIGHT / 2) - (IntSlider::SLIDER_BAR_H / 2),
					IntSlider::SLIDER_BAR_W,
					IntSlider::SLIDER_BAR_H
				};

				gadget->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING_X,
					rect.y + 20 + PANEL_PADDING_Y,
					rect.w - (PANEL_PADDING_X * 2),
					INT_SLIDER_HEIGHT
				};
			}
			else // If elements exist, position below bottom element
			{
				Gadget* last_gadget = gadgets_[gadgets_.size() - 1];

				gadget->slider_bar = Rect
				{
					rect.x + PANEL_PADDING_X + IntSlider::LABEL_PADDING,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING_Y + (INT_SLIDER_HEIGHT / 2) - (IntSlider::SLIDER_BAR_H / 2),
					IntSlider::SLIDER_BAR_W,
					IntSlider::SLIDER_BAR_H
				};

				gadget->gadget_rect = Rect
				{
					rect.x + PANEL_PADDING_X,
					last_gadget->gadget_rect.y + last_gadget->gadget_rect.h + PANEL_PADDING_Y,
					rect.w - (PANEL_PADDING_X * 2),
					INT_SLIDER_HEIGHT
				};
			}

			gadget->val_marker.w = IntSlider::SLIDER_MARKER_W;
			gadget->val_marker.h = IntSlider::SLIDER_MARKER_H;
			gadget->val_marker.y = (gadget->gadget_rect.y + (gadget->gadget_rect.h / 2)) - (gadget->val_marker.h / 2); // Middle of IntSlider rect
			gadget->val_marker.x = gadget->gadget_rect.x + IntSlider::LABEL_PADDING;

			gadgets_.push_back(gadget);
		}
	}
}