#include "rect_edit_panel.h"
#include "int_slider.h"

namespace deft
{
	namespace gui
	{
		RectEditPanel::RectEditPanel(const std::string& panel_name, int x, int y, int w, int h)
			: Panel(panel_name, x, y, w, h)
		{
			add_int_slider("X", nullptr);
			add_int_slider("Y", nullptr);
			add_int_slider("W", nullptr);
			add_int_slider("H", nullptr);
		}

		const deft::Rect* RectEditPanel::edit_rect()
		{
			return var;
		}

		void RectEditPanel::set_edit_rect(deft::Rect* edit_rect)
		{
			var = edit_rect;
			get_gadget<IntSlider>("W")->set_val(edit_rect->w, 1, 300);
			get_gadget<IntSlider>("H")->set_val(edit_rect->h, 1, 300);

			get_gadget<IntSlider>("X")->set_val((int&)edit_rect->x, 1, 900);
			get_gadget<IntSlider>("Y")->set_val((int&)edit_rect->y, 1, 900);
		}
	}
}