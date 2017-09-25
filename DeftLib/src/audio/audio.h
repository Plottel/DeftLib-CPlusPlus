#pragma once
#include <string>

namespace deft
{
	namespace audio
	{
		void init();
		void quit();
		void load_sound(const std::string& name, const std::string& path);
		void play_sound(const std::string& name);
		void loop_sound(const std::string& name, int count);
		void load_music(const std::string& name, const std::string& path);
		void play_music(const std::string& name);
		void pause_music();
		void resume_music();
		void stop_music();
		void toggle_music();
	}
}
