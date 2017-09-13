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
		
		namespace
		{
			int _mouse_x = 0;
			int _mouse_y = 0;
			bool _left_mouse_down = false;;
			bool _right_mouse_down = false;;
		}		

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
			_left_mouse_down = false;
			_right_mouse_down = false;

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
				auto b = e.button.button;

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

				case SDL_MOUSEMOTION:
					SDL_GetMouseState(&_mouse_x, &_mouse_y);
					break;

				case SDL_MOUSEBUTTONDOWN:
					_left_mouse_down = b == SDL_BUTTON_LEFT;
					_right_mouse_down = b == SDL_BUTTON_RIGHT;
					break;

				default:
					break;
				}					
			}
		}

		bool mouse_down(MouseButton button)
		{
			if (button == LEFT_MOUSE)
				return _left_mouse_down;
			else if (button == RIGHT_MOUSE)
				return _right_mouse_down;
		}

		int mouse_x()
		{
			return _mouse_x;
		}

		int mouse_y()
		{
			return _mouse_y;
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