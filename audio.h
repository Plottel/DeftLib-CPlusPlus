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
	}
}
