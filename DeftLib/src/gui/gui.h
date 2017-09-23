#pragma once

#include "panel.h"

namespace deft
{
	namespace gui
	{
		namespace backend
		{
			void _be_on_left_mouse_release(int mouse_x, int mouse_y);
			void _be_on_left_mouse_down(int mouse_x, int mouse_y);
		}

		void add_panel(Panel* panel);
		void render_gui();
	}
}
