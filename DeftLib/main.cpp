#include <iostream>
#include "deft.h"
#include <ctype.h>
#include <vector>
#include "panel_types.h"
#include <memory>

using std::vector;

int main(int argc, char* argv[])
{
	deft::init();

	deft::load_sound("hit.wav");
	deft::load_sound("hit_2.wav");	
	deft::load_sound("hit_3.wav");
	deft::load_music("jumpshot.mp3");

	deft::Rect rect = deft::Rect{ 100, 600, 50, 50 };


	// Allocate panels
	deft::RectEditPanel* rect_edit = new deft::RectEditPanel("Rect Editor", 5, 5);
	rect_edit->set_edit_rect(&rect);

	auto asd = std::make_unique<deft::MusicPlayerPanel>("Music Player", 1000, 100);

	deft::add_panel(std::make_unique<deft::Panel>("Music Player", 300, 5));
	//deft::add_panel(asd);

	deft::add_panel(rect_edit);

	while (true)
	{
		deft::process_events();

		//
		// Game Logic
		//

		// Sound
		if (deft::key_typed(deft::_1))
			deft::play_sound("hit.wav");
		if (deft::key_typed(deft::_2))
			deft::play_sound("hit_2.wav");
		if (deft::key_typed(deft::_3))
			deft::play_sound("hit_3.wav");
		if (deft::key_typed(deft::_4))
			deft::loop_sound("hit_2.wav", 3);

		if (deft::input::key_typed(deft::RETURN) && deft::console_is_on())
		{
			// Process console input here.
		}
		
		//
		// Rendering
		//

		// Clear screen
		deft::pre_render();
		{
			deft::fill_rect(rect, deft::blue);

			// Render deft GUI
			deft::render_gui();
		}
		// Refresh screen
		deft::post_render();
	}

	// Deallocate panels
	//delete music;
	delete rect_edit;

	return EXIT_SUCCESS;
}

