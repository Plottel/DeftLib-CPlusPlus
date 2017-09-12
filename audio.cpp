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

		void loop_sound(string name, int count)
		{
			Mix_PlayChannel(-1, sounds[name], count - 1); // SDL loops for one extra?
		}

		void load_sound(std::string name)
		{
			sounds[name] = Mix_LoadWAV(name.c_str());
		}

		void quit()
		{
			// TODO: Free chunks
			Mix_Quit();
		}
	}
}