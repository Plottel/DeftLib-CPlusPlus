#pragma once

#include <string>
#include "graphics_ui.h"

namespace deft
{
	namespace console
	{
		//Text, rect, bg color
		extern deft::graphics::TextBox console_textbox;

		void init();
		void toggle_console();
		bool console_is_on();
		void update_console();
		const std::string& console_input();
	}
}
