#include "graphics_backend.h"
#include "input.h"
#include "console.h"
#include <iostream>

namespace deft
{
	namespace graphics
	{
		namespace backend
		{
			SDL_Window* window;
			SDL_Renderer* renderer;

			TTF_Font* font = NULL;

			void _be_init()
			{
				SDL_Init(SDL_INIT_EVERYTHING);
				TTF_Init();

				std::cout << SDL_GetError() << std::endl;


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

				font = TTF_OpenFont("lazy.ttf", 12);
				

				std::cout << TTF_GetError() << std::endl;
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
				// Debug rendering here.

				if (console::console_is_on())
				{
					if (console::console_input() != "")
					{
						graphics::backend::_be_render_text("- CONSOLE -", 10, 10, red);
						graphics::backend::_be_render_text(console::console_input().c_str(), 10, 20, red);
					}
				}				

				SDL_RenderPresent(renderer);
			}

			void _be_quit()
			{
				SDL_DestroyWindow(window);
				SDL_DestroyRenderer(renderer);


				TTF_CloseFont(font);

				SDL_Quit();
			}

			void _be_render_text(const char* text, float x, float y, Color& clr)
			{
				SDL_Color sdl_clr = { clr.r, clr.g, clr.b, clr.a };

				SDL_Surface* text_surface = TTF_RenderText_Solid(font, text, sdl_clr);
				SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
				SDL_Rect render_target = { x, y, text_surface->w, text_surface->h };
		
				SDL_RenderCopy(renderer, text_texture, NULL, &render_target);

				SDL_FreeSurface(text_surface);
				SDL_DestroyTexture(text_texture);
			}
		}
	}
}