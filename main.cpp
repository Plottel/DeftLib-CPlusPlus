#include <iostream>
#include "deft.h"
#include <ctype.h>

using namespace deft;
using std::vector;


int main(int argc, char* argv[])
{
	deft::init();

	load_sound("hit.wav");
	load_sound("hit_2.wav");
	load_sound("hit_3.wav");
	load_music("jumpshot.mp3");

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

			// Sound
			if (key_typed(_1))
				play_sound("hit.wav");
			if (key_typed(_2))
				play_sound("hit_2.wav");
			if (key_typed(_3))
				play_sound("hit_3.wav");
			if (key_typed(_4))
				loop_sound("hit_2.wav", 3);

			// Music
			if (key_typed(_5))
				play_music("jumpshot.mp3");
			if (key_typed(_6))
				pause_music();
			if (key_typed(_7))
				resume_music();
			if (key_typed(_8))
				stop_music();
			if (key_typed(_9))
				toggle_music();


			outline_rect(x, y, 30, 30, red);
		}
		// Refresh screen
		post_render();
	}

	return EXIT_SUCCESS;
}

