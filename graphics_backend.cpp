#include "graphics_backend.h"

namespace deft
{
	namespace graphics
	{
		namespace backend
		{
			SDL_Window* window;
			SDL_Renderer* renderer;

			void _be_init()
			{
				window = SDL_CreateWindow
				(
					"An SDL2 window",                  // window title
					SDL_WINDOWPOS_UNDEFINED,           // initial x position
					SDL_WINDOWPOS_UNDEFINED,           // initial y position
					640,                               // width, in pixels
					480,                               // height, in pixels
					SDL_WINDOW_OPENGL                  // flags - see below
				);

				renderer = SDL_CreateRenderer
				(
					window,
					-1,
					SDL_RENDERER_ACCELERATED
				);
			}

			void _be_outline_rect(SDL_Rect* rect, Color clr)
			{
				SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
				SDL_RenderDrawRect(renderer, rect);
			}

			void _be_pre_render()
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderClear(renderer);
			}

			void _be_post_render()
			{
				SDL_RenderPresent(renderer);
			}
		}
	}
}