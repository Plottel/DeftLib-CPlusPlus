#pragma once

#include "graphics_ui.h"

namespace deft
{
	namespace graphics
	{
		typedef struct MusicPlayerPanel : Panel
		{
			static const int DEFAULT_H = 265;
			static const int DEFAULT_W = 200;

			MusicPlayerPanel(std::string panel_name, int x, int y, int w=DEFAULT_W, int h=DEFAULT_H);
			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
		} MusicPlayerPanel;



		typedef struct RectEditPanel : Panel
		{
			static const int DEFAULT_H = 150;
			static const int DEFAULT_W = 200;

			deft::Rect* edit_rect();
			void set_edit_rect(deft::Rect* edit_rect);

			RectEditPanel(std::string panel_name, int x, int y, int w=DEFAULT_W, int h=DEFAULT_H);

		private:
			deft::Rect* var;
		} RectEditPanel;
	}
}



