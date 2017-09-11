#pragma once

#include "graphics.h"
#include "color.h"
#include "input.h"
#include "console.h"

#define DEFT_SHORTHAND


namespace deft
{
#ifdef DEFT_SHORTHAND
	using namespace graphics;
	using namespace input;
	using namespace console;
	using deft::Key;
#endif

	void init()
	{
		graphics::init();
	}
}
