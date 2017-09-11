#include <iostream>
#include "deft.h"
#include <SDL.h>

using namespace deft;

int main(int argc, char* argv[])
{
	deft::init();

	float x = 100;
	float y = 100;

	while (true)
	{
		get_input();

		// Clear screen
		pre_render();
		{
			for (int i = 0; i < 200; ++i)
				text("IM RENDERING SOME MOFOFLIPPIN TEXT", 200 + (i * 2), 200 + (i * 2), red);


			if (key_typed(SPACE))
				x += 50;
			if (key_released(SPACE))
				x -= 50;

			if (key_down(A))
				x -= 0.05;
			if (key_down(D))
				x += 0.05;
			if (key_down(W))
				y -= 0.05;
			if (key_down(S))
				y += 0.05;

			outline_rect(x, y, 30, 30, red);
		}
		// Refresh screen
		post_render();
	}

	return EXIT_SUCCESS;
}

