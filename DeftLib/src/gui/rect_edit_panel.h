#pragma once

#include "panel.h"

namespace deft
{
	namespace gui
	{
		typedef struct RectEditPanel : Panel
		{
			static const int DEFAULT_H = 160;
			static const int DEFAULT_W = 160;

			const deft::Rect* edit_rect();
			void set_edit_rect(deft::Rect* edit_rect);

			RectEditPanel(const std::string& panel_name, int x, int y, int w = DEFAULT_W, int h = DEFAULT_H);

		private:
			deft::Rect* var;
		} RectEditPanel;
	}
}