#pragma once
#include <string>

namespace deft
{
	namespace audio
	{
		void init();
		void quit();
		void load_sound(std::string name);
		void play_sound(std::string name);
		void loop_sound(std::string name, int count);
		void load_music(std::string name);
		void play_music(std::string name);
		void pause_music();
		void resume_music();
		void stop_music();
		void toggle_music();
	}
}
