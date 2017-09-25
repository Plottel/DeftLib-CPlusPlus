#pragma once

#include "panel.h"

namespace deft
{
	namespace gui
	{
		namespace backend
		{
			Panel* panel_at(int x, int y);
			void on_left_mouse_released(int mouse_x, int mouse_y);
			void on_left_mouse_down(int mouse_x, int mouse_y);
			void on_key_typed(deft::Key key);
		}

		void handle_input_events();
		void add_panel(Panel* panel);
		void render_gui();
	}
}
