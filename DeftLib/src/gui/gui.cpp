#include "gui.h"

namespace deft
{
	namespace gui
	{
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

			void _be_on_left_mouse_down(int mouse_x, int mouse_y)
			{
				// Handle input for the clicked on panel, if any.
				for (auto& panel : _be_panels)
				{
					if (geometry::pt_rect_collide(mouse_x, mouse_y, panel->rect))
					{
						panel->on_left_mouse_down(mouse_x, mouse_y);
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

		void add_panel(Panel* panel)
		{
			backend::_be_panels.push_back(panel);
		}

		void render_gui()
		{
			backend::_be_render_gui();
		}
	}
}