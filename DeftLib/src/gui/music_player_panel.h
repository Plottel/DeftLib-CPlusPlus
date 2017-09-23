#pragma once

#include "panel.h"

namespace deft
{
	namespace gui
	{
		typedef struct MusicPlayerPanel : Panel
		{
			static const int DEFAULT_H = 265;
			static const int DEFAULT_W = 200;

			MusicPlayerPanel(std::string panel_name, int x, int y, int w = DEFAULT_W, int h = DEFAULT_H);
			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
		} MusicPlayerPanel;
	}
}
