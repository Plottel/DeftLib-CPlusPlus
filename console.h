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
		void add_console_command(std::string name, void* callback_func, void* callback_args, int arg_count);
	}
}
