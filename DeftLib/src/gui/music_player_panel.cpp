#include "music_player_panel.h"
#include "../audio/audio.h"

namespace deft
{
	namespace gui
	{
		MusicPlayerPanel::MusicPlayerPanel(std::string panel_name, int x, int y, int w, int h)
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
	}
}