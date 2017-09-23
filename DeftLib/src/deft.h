#pragma once

#include "graphics/graphics.h"
#include "graphics/color.h"
#include "input/input.h"
#include "audio/audio.h"
#include "geometry/geometry.h"
#include "gui/gui.h"
#include "ecs/ecs.h"



#include <algorithm>
#include <cctype>

#define DEFT_SHORTHAND


namespace deft
{
#ifdef DEFT_SHORTHAND
	using namespace graphics;
	using namespace input;
	using namespace audio;
	using namespace geometry;
	using namespace gui;
	using deft::Key;
#endif

	void init()
	{
		graphics::init();
		audio::init();
	}

	void process_events()
	{
		input::get_input();

		if (input::mouse_released(LEFT_MOUSE))
			gui::backend::_be_on_left_mouse_release(input::mouse_x(), input::mouse_y());

		if (input::mouse_down(LEFT_MOUSE)) // NOTE: mouse_down ATM
			gui::backend::_be_on_left_mouse_press(input::mouse_x(), input::mouse_y());
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
