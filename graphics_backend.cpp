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

				font = TTF_OpenFont("console_font.ttf", 12);
				

				std::cout << TTF_GetError() << std::endl;
			}

			void _be_outline_rect(SDL_Rect* rect, Color clr)
			{
				SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);
				SDL_RenderDrawRect(renderer, rect);
			}

			void _be_fill_circle(float x, float y, int radius, Color clr)
			{
				SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);

				for (int w = 0; w < radius * 2; ++w)
				{
					for (int h = 0; h < radius * 2; ++h)
					{
						int dx = radius - w; // horizontal offset
						int dy = radius - h; // vertical offset

						if ((dx*dx + dy*dy) <= (radius * radius))
							SDL_RenderDrawPoint(renderer, x + dx, y + dy);

					}
				}
			}

			void _be_outline_circle(float x, float y, int radius, Color clr)
			{
				// Draw a circle using Bresenham's circle drawing method.
				SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);

				int x2 = 0;
				int y2 = radius;
				int p = 3 - (2 * radius);

				while (x2 <= y2)
				{
					SDL_RenderDrawPoint(renderer, x + x2, y + y2);
					SDL_RenderDrawPoint(renderer, x - x2, y + y2);
					SDL_RenderDrawPoint(renderer, x + x2, y - y2);
					SDL_RenderDrawPoint(renderer, x - x2, y - y2);
					SDL_RenderDrawPoint(renderer, x + y2, y + x2);
					SDL_RenderDrawPoint(renderer, x + y2, y - x2);
					SDL_RenderDrawPoint(renderer, x - y2, y + x2);
					SDL_RenderDrawPoint(renderer, x - y2, y - x2);

					x2 = x2 + 1;

					if (p<0)
						p = p + 4 * (x2)+6;
					else
					{
						p = p + 4 * (x2 - y2) + 10;
						y2 = y2 - 1;
					}
				}
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
					graphics::backend::_be_render_text("- CONSOLE -", 10, 10, red);
					if (console::console_input() != "")						
						graphics::backend::_be_render_text(console::console_input().c_str(), 10, 30, blue);
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