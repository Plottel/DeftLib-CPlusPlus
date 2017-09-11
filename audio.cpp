#include "audio.h"
#include <SDL_mixer.h>
#include <string>
#include <map>

using std::string;
using std::map; 

namespace deft
{
	namespace audio
	{
		map<string, Mix_Chunk*> sounds;

		void init()
		{
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);		
		}

		void play_sound(string name)
		{
			Mix_PlayChannel(-1, sounds[name], 0);
		}

		void loud_sound(string name)
		{
			sounds[name] = Mix_LoadWAV((name + ".wav").c_str());
		}

		void quit()
		{
			for (auto& chunk : sounds.value_comp)
				Mix_FreeChunk(chunk);

			Mix_Quit();
		}
	}
}