#include "gui.h"
#include "../input/input.h"

namespace deft
{
	namespace gui
	{
		namespace backend
		{
			std::vector<Panel*> panels;			

			Panel* panel_at(int x, int y)
			{
				for (auto& panel : panels)
				{
					if (geometry::pt_rect_collide(x, y, panel->rect))
						return panel;
				}

				return nullptr;
			}

			void on_left_mouse_released(int mouse_x, int mouse_y)
			{
				Panel* panel_clicked_on = panel_at(mouse_x, mouse_y);

				if (panel_clicked_on != nullptr)
					panel_clicked_on->on_left_mouse_release(mouse_x, mouse_y);
			}

			void on_left_mouse_down(int mouse_x, int mouse_y)
			{
				Panel* panel_clicked_on = panel_at(mouse_x, mouse_y);

				if (panel_clicked_on != nullptr)
					panel_clicked_on->on_left_mouse_down(mouse_x, mouse_y);
			}

			void on_key_typed(Key key)
			{

			}
		}

		void handle_input_events()
		{
			for (auto& e : input::get_input_events())
			{
				if (e.event == KEY_TYPED)
					backend::on_key_typed(e.key);
				else if (e.event == MOUSE_DOWN)
				{
					if (e.btn == LEFT_MOUSE)
						backend::on_left_mouse_down(e.mouse_pos.x, e.mouse_pos.y);
				}					
				else if (e.event == MOUSE_RELEASED)
				{
					if (e.btn == LEFT_MOUSE)
						backend::on_left_mouse_released(e.mouse_pos.x, e.mouse_pos.y);
				}
			}
		}

		void add_panel(Panel* panel)
		{
			backend::panels.push_back(panel);
		}

		void render_gui()
		{
			for (auto& panel : backend::panels)
				panel->render();
		}
	}
}