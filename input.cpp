#include "input.h"
#include <SDL.h> 
#include <vector>
#include <algorithm>

#include <iostream>

namespace deft
{
	namespace input
	{
		const int SDL_KEY_COUNT = 322;

		SDL_Event e;
		bool _down_keys[SDL_KEY_COUNT];
		bool _typed_keys[SDL_KEY_COUNT];
		bool _released_keys[SDL_KEY_COUNT];
		
		// Refreshed each frame with new key down and key up events.
		// Used to keep track of typed and released states.
		std::vector<Key> _new_key_events;

		std::vector<std::string> get_held_keys()
		{
			std::vector<std::string> result;
			for (auto& key : _new_key_events)
			{
				if (_typed_keys[key])
					result.push_back(std::string(SDL_GetKeyName(key)));
			}

			return result;
		}

		void get_input()
		{
			// Events from last frame no longer relevant.
			// Typed and released is false for last frame's key events.
			for (auto& key : _new_key_events)
			{
				_typed_keys[key] = false;
				_released_keys[key] = false;
			}				
			_new_key_events.clear(); // Ready to process new events


			while (SDL_PollEvent(&e) != 0)
			{
				SDL_Keycode key;

				switch (e.type)
				{
				case SDL_QUIT:
					// Do some quit thing.
					break;

				case SDL_KEYDOWN:
					key = e.key.keysym.sym;

					if (!isascii(key))
						key = e.key.keysym.scancode;

					_down_keys[key] = true;

					if (e.key.repeat == 0)
						_typed_keys[key] = true;
					_new_key_events.push_back((Key)key);
					break;

				case SDL_KEYUP:
					key = e.key.keysym.sym;

					if (!isascii(key))
						key = e.key.keysym.scancode;

					_down_keys[key] = false;
					_released_keys[key] = true;
					_new_key_events.push_back((Key)key);
					break;


				default:
					break;
				}					
			}
		}

		bool key_down(Key key)
		{
			return _down_keys[key];
		}
		

		bool key_typed(Key key)
		{
			return _typed_keys[key];
		}

		bool key_released(Key key)
		{
			return _released_keys[key];
		}
	}
}