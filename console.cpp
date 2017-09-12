#include "console.h"
#include "graphics_backend.h"
#include "input.h"
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <functional>

namespace deft
{
	namespace console
	{
		std::vector<std::string> split_string(std::string& string, const char& splitter)
		{
			std::vector<std::string> result;
			std::istringstream stream(string);
			std::string s;

			while (std::getline(stream, s, ' '))
				result.push_back(s);

			return result;
		}

		//std::function<return_type(paramter_type_1, paramter_type_2, paramter_type_3)

		typedef struct
		{
			void* func;
			int arg_count;
		} ConsoleCallBack;

		std::map < std::string, void(*)()> actions;

		std::map<std::string, ConsoleCallBack> _console_callbacks;

		std::string _console_input = "";
		bool _is_reading_console_input;


		void toggle_console()
		{
			_console_input = "";
			_is_reading_console_input = !_is_reading_console_input;
		}

		bool console_is_on()
		{
			return _is_reading_console_input;
		}

		const std::string& console_input()
		{
			return _console_input;
		}

		// NOTE: Cannot have spaces in "name"
		// NOTE: Name must be all caps.
		void add_console_command(std::string name, void* callback_func, int arg_count)
		{
			_console_callbacks[name] = { callback_func, arg_count };
		}

		void update_console()
		{
			// Update console visual display with new key presses
			if (console::console_is_on())
			{
				for (auto& key : input::get_held_keys())
				{
					if (key.size() == 1) // Only want alpha chars (not SPACE, RETURN etc.)
						_console_input += key;
					else
					{
						if (key == "Space")
							_console_input += " ";
					}
				}

				// Reset console on BACKSPACE
				if (input::key_down(BACKSPACE))
					_console_input = "";

				// Process console command on RETURN / ENTER
				if (input::key_down(RETURN))
				{
					auto input_words = split_string(_console_input, ',');

					auto callback = _console_callbacks[input_words[0]];

					for (int i = 1; i <= callback.arg_count; ++i)
					{
						// Make array of arguments to pass to function
					}
						
					// Add check for if (containskey)
					//_console_callbacks[]
				}


			}
		}
	}
}