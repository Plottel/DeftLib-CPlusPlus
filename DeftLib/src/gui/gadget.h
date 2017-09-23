#pragma once

#include "../geometry/geometry.h"
#include <string>

namespace deft
{
	namespace gui
	{
		typedef struct Gadget
		{
			std::string name;
			Rect gadget_rect;
			Rect val_rect;

			bool selected = false;

			virtual void on_left_mouse_release(int mouse_x, int mouse_y) {}
			virtual void on_left_mouse_press(int mouse_x, int mouse_y) {}
			virtual void render() = 0;

			virtual void move_by(float x, float y)
			{
				gadget_rect.x += x;
				gadget_rect.y += y;
				val_rect.x += x;
				val_rect.y += y;
			}

		private:
			virtual void render_selected() = 0;
		} Gadget;
	}
}
