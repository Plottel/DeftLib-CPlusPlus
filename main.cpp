#include <iostream>
#include "deft.h"
#include <ctype.h>

using namespace deft;
using std::vector;


int main(int argc, char* argv[])
{
	deft::init();

	load_sound("scratch");

	float x = 100;
	float y = 100;

	while (true)
	{
		get_input();
		update_console();

		// Clear screen
		pre_render();
		{
			if (key_typed(O))
				toggle_console();

			if (key_down(A))
				x -= 0.05;
			if (key_down(D))
				x += 0.05;
			if (key_down(W))
				y -= 0.05;
			if (key_down(S))
				y += 0.05;

			if (key_down(S))
				play_sound();

			outline_rect(x, y, 30, 30, red);
		}
		// Refresh screen
		post_render();
	}

	return EXIT_SUCCESS;
}

