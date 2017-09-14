#include <iostream>
#include "deft.h"
#include <ctype.h>
#include <vector>

using std::vector;
using namespace deft;


int main(int argc, char* argv[])
{
	deft::init();

	load_sound("hit.wav");
	load_sound("hit_2.wav");
	load_sound("hit_3.wav");
	load_music("jumpshot.mp3");

	Rect r1 = { 100, 100, 20, 20 };
	Rect r2 = { 300, 300, 75, 75 };

	Circle c1 = { 250, 250, 45 };
	Circle c2 = { 350, 100, 20 };

	Color r_clr = red;

	TextBox box;

	box.rect.w = 100;
	box.rect.h = 40;
	box.rect.x = 200;
	box.rect.y = 200;
	box.label = "A Textbox";
	box.text = "Im texting here.";

	TextButton button = { "Play Music", Rect{600, 600, 80, 30} };

	while (true)
	{
		get_input();
		update_console();

		//
		// Game Logic
		//
#pragma region Game Logic
		if (key_typed(O))
			toggle_console();

		if (key_down(A))
			c1.x -= 0.05;
		if (key_down(D))
			c1.x += 0.05;
		if (key_down(W))
			c1.y -= 0.05;
		if (key_down(S))
			c1.y += 0.05;

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

		//if (input::mouse_released(LEFT_MOUSE))
			//play_music("jumpshot.mp3");

		if (input::mouse_pressed(LEFT_MOUSE))
			button.selected = pt_rect_collide(mouse_x(), mouse_y(), button.rect);

		if (input::mouse_released(LEFT_MOUSE))
			button.selected = false;

		if (input::key_typed(RETURN) && console_is_on())
		{
			std::cout << console_input() << std::endl;

			// Process console input
			if (console_input() == "play music")
				play_music("jumpshot.mp3");
		}
#pragma endregion Game Logic


		
		//
		// Rendering
		//

		// Clear screen
		pre_render();
		{
			if (circles_collide(c1, c2))
				r_clr = green;
			else
				r_clr = blue;

			outline_rect(r1, r_clr, 5);
			outline_rect(r2, r_clr, 12);
			outline_circle(c1, r_clr);
			outline_circle(c2, r_clr);

			draw_text_box(box);
			draw_text_button(button);


			// Render console
			if (console_is_on())
				draw_text_box(console::console_textbox);

		}
		// Refresh screen
		post_render();
	}

	return EXIT_SUCCESS;
}

