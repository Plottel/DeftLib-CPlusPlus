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
		// Process events
		input::pump_input_events();

		// With processed events, handle subsystem events.
		gui::handle_input_events();
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
