#pragma once

#include "gadget.h"

namespace deft
{
	namespace gui
	{
		typedef struct TextButton : Gadget
		{
			virtual void render();

		private:
			virtual void render_selected();
		} TextButton;
	}
}
