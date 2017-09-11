#pragma once

#include <string>

namespace deft
{
	namespace console
	{
		void toggle_console();
		bool console_is_on();
		void update_console();
		const std::string& console_input();
	}
}
