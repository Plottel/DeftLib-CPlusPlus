#include "input.h"
#include <SDL.h> 


namespace deft
{
	namespace input
	{
		const int SDL_KEY_COUNT = 322;

		SDL_Event e;
		bool _keydown[SDL_KEY_COUNT];

		void get_input()
		{
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					// Do some quit thing.
				}
				if (e.type == SDL_KEYUP)
					_keydown[e.key.keysym.sym] = false;

				// Set corresponding key down to true
				if (e.type == SDL_KEYDOWN) 
					_keydown[e.key.keysym.sym] = true;
			}
		}

		bool key_down(Key key)
		{
			return _keydown[key];
		}
	}
}