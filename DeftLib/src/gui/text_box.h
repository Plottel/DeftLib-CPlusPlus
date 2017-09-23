#pragma once

#include "gadget.h"

namespace deft
{
	namespace gui
	{
		typedef struct TextBox : Gadget
		{
			std::string text;
			virtual void render();

		private:
			virtual void render_selected();
		} TextBox;
	}
}
