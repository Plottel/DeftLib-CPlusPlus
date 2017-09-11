#include "console.h"
#include "graphics_backend.h"
#include "input.h"
#include <string>

namespace deft
{
	namespace console
	{
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

		void update_console()
		{
			// Update console visual display with new key presses
			if (console::console_is_on())
			{
				for (auto& key : input::get_held_keys())
				{
					if (key.size() >= 1) // Only want alphabetical keys (not CTRL, SHIFT, SPACE etc.)
					{
						if (key == "Space")
							_console_input += " ";
						else
							_console_input += key;
					}

				}

				if (input::key_down(BACKSPACE))
					_console_input = "";
			}
		}
	}
}