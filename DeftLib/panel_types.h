#pragma once

#include "graphics_ui.h"

namespace deft
{
	namespace graphics
	{
		typedef struct MusicPlayerPanel : Panel
		{
			MusicPlayerPanel(std::string panel_name, float x, float y, int w, int h);
			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
		} MusicPlayerPanel;



		typedef struct RectEditPanel : Panel
		{
			deft::Rect* edit_rect();
			void set_edit_rect(deft::Rect* edit_rect);

			RectEditPanel(std::string panel_name, float x, float y, int w, int h);

		private:
			deft::Rect* var;
		} RectEditPanel;
	}
}



