#pragma once

#include "graphics.h"
#include "color.h"
#include "input.h"
#include "console.h"

namespace deft
{
	using namespace graphics;
	using namespace input;
	using namespace console;
	using deft::Key;

	void init()
	{
		graphics::init();
	}
}
