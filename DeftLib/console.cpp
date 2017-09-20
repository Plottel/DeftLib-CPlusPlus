#include "console.h"
#include "graphics_backend.h"
#include "graphics_ui.h"
#include "input.h"
#include <string>
#include <map>
#include <cctype>
#include <sstream>
#include <functional>
#include "geometry.h"
#include <iostream>
#include <algorithm>

namespace deft
{
	namespace console
	{
		std::string to_lower(std::string string)
		{
			transform(string.begin(), string.end(), string.begin(), ::tolower);
			return string;
		}

		bool _is_reading_console_input = false;
		graphics::TextBox console_textbox;

		void init()
		{
			console_textbox = graphics::TextBox();

			console_textbox.name = "- CONSOLE -";
			console_textbox.rect = Rect{ 10, 10, 100, 100 };
			console_textbox.text = "";
		}

		std::vector<std::string> split_string(std::string& string, const char& splitter)
		{
			std::vector<std::string> result;
			std::istringstream stream(string);
			std::string s;

			while (std::getline(stream, s, ' '))
				result.push_back(s);

			return result;
		}


		void toggle_console()
		{
			console_textbox.text = "";
			_is_reading_console_input = !_is_reading_console_input;
		}

		bool console_is_on()
		{
			return _is_reading_console_input;
		}

		const std::string& console_input()
		{
			return console_textbox.text;
		}	

		void update_console()
		{
			// Update console visual display with new key presses
			if (console::console_is_on())
			{
				for (auto& key : input::get_held_keys())
				{
					if (key.size() == 1) // Only want alpha chars (not SPACE, RETURN etc.)
						console_textbox.text += to_lower(std::string(key.c_str()));
					else
					{
						if (key == "Space")
							console_textbox.text += " ";
					}
				}

				// Reset console on BACKSPACE
				if (input::key_down(BACKSPACE))
					console_textbox.text = "";
			}
		}
	}
}