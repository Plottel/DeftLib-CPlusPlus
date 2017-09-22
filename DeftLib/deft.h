#pragma once

#include "graphics.h"
#include "color.h"
#include "input.h"
#include "console.h"
#include "audio.h"
#include "geometry.h"
#include <algorithm>
#include <cctype>
#include "graphics_ui.h"
#include "ecs.h"

#define DEFT_SHORTHAND


namespace deft
{
#ifdef DEFT_SHORTHAND
	using namespace graphics;
	using namespace input;
	using namespace audio;
	using namespace console;
	using namespace geometry;
	using deft::Key;
#endif

	void init()
	{
		graphics::init();
		audio::init();
		console::init();
	}

	void process_events()
	{
		input::get_input();
		console::update_console();

		if (input::mouse_released(LEFT_MOUSE))
			graphics::backend::_be_on_left_mouse_release(input::mouse_x(), input::mouse_y());

		if (input::mouse_down(LEFT_MOUSE)) // NOTE: mouse_down ATM
			graphics::backend::_be_on_left_mouse_press(input::mouse_x(), input::mouse_y());


		if (input::key_typed(O))
			console::toggle_console();
	}

	void process_systems()
	{
		ecs::process();
	}

	void quit()
	{
		graphics::quit();
		audio::quit();
	}
}
