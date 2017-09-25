#pragma once

#include <string>
#include "../geometry/geometry.h"
#include "../input/input.h"
#include <vector>
#include "gadget.h"

namespace deft
{
	namespace gui
	{
		typedef struct Panel
		{
			Panel(const std::string& panel_name, int x, int y, int w, int h);
			~Panel();

			std::string name;

			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
			virtual void on_left_mouse_down(int mouse_x, int mouse_y);
			virtual void on_key_typed(Key key);

			virtual void on_event(int mouse_x, int mouse_y) {}

			void add_textbox(const std::string& label, const std::string& text);
			void add_text_button(const std::string& label);
			void add_int_slider(const std::string& label, int* var);

			template<class T>
			T* get_gadget(const std::string& name)
			{
				for (auto& gadget : gadgets_)
				{
					if (gadget->name == name)
						return dynamic_cast<T*>(gadget);
				}

				return nullptr;
			}

			void render();

			void move_by(float dx, float dy);
			Rect rect;
			Rect drag_rect();

			std::string clicked();
			const Gadget* last_added();

		private:
			std::vector<Gadget*> gadgets_;
			Vec2 drag_pt_;
			bool is_dragging_ = false;
		} Panel;
	}
}
