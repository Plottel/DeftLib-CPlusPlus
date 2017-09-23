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
		map<string, Mix_Music*> musics;
		bool _is_playing_music = false;

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

		void load_sound(std::string name, std::string path)
		{
			sounds[name] = Mix_LoadWAV(path.c_str());
		}

		void load_music(std::string name, std::string path)
		{
			musics[name] = Mix_LoadMUS(path.c_str());
		}

		void play_music(std::string name)
		{
			Mix_PlayMusic(musics[name], -1);
			_is_playing_music = true;
		}

		void pause_music()
		{
			Mix_PauseMusic();
			_is_playing_music = false;
		}

		void resume_music()
		{
			Mix_ResumeMusic();
			_is_playing_music = true;
		}

		void toggle_music()
		{
			if (_is_playing_music)
				pause_music();
			else
				resume_music();
		}

		void stop_music()
		{
			// If music is playing
			if (Mix_PlayingMusic() > 0)
			{
				Mix_HaltMusic();
				_is_playing_music = false;
			}				
		}

		void quit()
		{
			// TODO: Free chunks
			// TODO: Free musics
			Mix_Quit();
		}
	}
}