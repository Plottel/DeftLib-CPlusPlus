#pragma once

#include "graphics.h"
#include "color.h"
#include "input.h"
#include "console.h"
#include "audio.h"
#include "geometry.h"
#include <algorithm>
#include <cctype>

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
	}

	void quit()
	{
		graphics::quit();
		audio::quit();
	}

	std::string to_lower(std::string string)
	{
		transform(string.begin(), string.end(), string.begin(), ::tolower);
		return string;
	}
}
