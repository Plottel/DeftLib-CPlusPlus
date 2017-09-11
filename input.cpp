#include "input.h"
#include <SDL.h>

namespace deft
{
	namespace input
	{
		SDL_Event e;

		void get_input()
		{
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					// Do some quit thing.
				}
			}
		}
	}
}