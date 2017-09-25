#include "int_slider.h"
#include "../graphics/graphics_backend.h"
#include <sstream>
#include <iomanip>


namespace deft
{
	namespace gui
	{
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
			SDL_Rect sdl_slider_bar = graphics::backend::r_to_sdlr(slider_bar);
			SDL_Rect sdl_val_marker = graphics::backend::r_to_sdlr(val_marker);

			graphics::backend::fill_r(&sdl_slider_bar, black);
			graphics::backend::fill_r(&sdl_val_marker, blue);

			graphics::backend::render_text(name.c_str(), gadget_rect.x, gadget_rect.y + 5, static_cast<Color>(black), deft::graphics::backend::font_14);

			if (val != nullptr)
			{
				std::stringstream stream;
				stream << std::setprecision(3) << *val;

				graphics::backend::render_text(stream.str().c_str(), gadget_rect.x + IntSlider::SLIDER_BAR_W + 30, gadget_rect.y + 5, static_cast<Color>(black), deft::graphics::backend::font_14);
			}
		}

		void IntSlider::render_selected()
		{
		}
	}
}