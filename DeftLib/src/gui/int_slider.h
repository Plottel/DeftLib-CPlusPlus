#pragma once

#include "gadget.h"

namespace deft
{
	namespace gui
	{
		typedef struct IntSlider : Gadget
		{
			static const int SLIDER_BAR_W = 80;
			static const int SLIDER_BAR_H = 3;
			static const int SLIDER_MARKER_W = 3;
			static const int SLIDER_MARKER_H = 10;
			static const int LABEL_PADDING = 25;

			int* val;
			int min, max;
			deft::Rect slider_bar;
			deft::Rect val_marker;

			void set_val(int& value, int min, int max);

			virtual void on_left_mouse_press(int mouse_x, int mouse_y);
			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
			virtual void render();

			virtual void move_by(float x, float y)
			{
				Gadget::move_by(x, y);
				slider_bar.x += x;
				slider_bar.y += y;
				val_marker.x += x;
				val_marker.y += y;
			}

		private:
			virtual void render_selected();
			void clamp_val_marker();
			void update_val();
		} IntSlider;
	}
}
