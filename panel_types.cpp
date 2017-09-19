

#include "panel_types.h"
#include "audio.h"

namespace deft
{
	namespace graphics
	{
		MusicPlayerPanel::MusicPlayerPanel(std::string panel_name, float x, float y, int w, int h)
			: Panel(panel_name, x, y, w, h)
		{
			add_text_button("Play Music");
			add_text_button("Pause Music");
			add_text_button("Resume Music");
			add_text_button("Stop Music");
			add_text_button("Toggle Music");
		}

		void MusicPlayerPanel::on_left_mouse_release(int mouse_x, int mouse_y)
		{
			if (clicked() == "Play Music")
				audio::play_music("jumpshot.mp3");
			if (clicked() == "Pause Music")
				audio::pause_music();
			if (clicked() == "Resume Music")
				audio::resume_music();
			if (clicked() == "Stop Music")
				audio::stop_music();
			if (clicked() == "Toggle Music")
				audio::toggle_music();

			// Unselect gadgets
			Panel::on_left_mouse_release(mouse_x, mouse_y);
		}

		RectEditPanel::RectEditPanel(std::string panel_name, float x, float y, int w, int h)
			: Panel(panel_name, x, y, w, h)
		{
			add_int_slider("X", nullptr);
			add_int_slider("Y", nullptr);
			add_int_slider("W", nullptr);
			add_int_slider("H", nullptr);
		}

		deft::Rect* RectEditPanel::edit_rect()
		{
			return var;
		}

		void RectEditPanel::set_edit_rect(deft::Rect* edit_rect)
		{
			var = edit_rect;
			get_gadget<IntSlider>("W")->set_var(var->w, 1, 100);
			get_gadget<IntSlider>("H")->set_var(var->h, 1, 100);
		}
	}
}