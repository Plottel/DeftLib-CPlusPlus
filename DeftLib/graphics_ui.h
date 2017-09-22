#pragma once

#include <string>
#include <vector>
#include "geometry.h"
#include "color.h"

namespace deft
{
	namespace graphics
	{
		typedef struct Gadget
		{
			std::string name;
			Rect gadget_rect;
			Rect val_rect;

			bool selected = false;

			virtual void on_left_mouse_release(int mouse_x, int mouse_y) {}
			virtual void on_left_mouse_press(int mouse_x, int mouse_y) {}
			virtual void render() = 0;

		private:
			virtual void render_selected() = 0;
		} Gadget;

		typedef struct Panel
		{
			Panel(std::string panel_name, int x, int y, int w, int h);
			~Panel();

			std::string name;

			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
			virtual void on_left_mouse_press(int mouse_x, int mouse_y);

			void add_textbox(std::string label, std::string text);
			void add_text_button(std::string label);
			void add_int_slider(std::string label, int* var);

			template<class T>
			T* get_gadget(std::string name)
			{
				for (auto& gadget : gadgets_)
				{
					if (gadget->name == name)
						return dynamic_cast<T*>(gadget);
				}

				return nullptr;
			}

			void render();
			Rect rect;

			std::string clicked();
			Gadget* last_added();

		private:
			std::vector<Gadget*> gadgets_;
		} Panel;

		
		typedef struct TextBox : Gadget
		{
			std::string text;
			virtual void render();

		private:
			virtual void render_selected();
		} TextBox;

		typedef struct TextButton : Gadget
		{
			virtual void render();

		private:
			virtual void render_selected();
		} TextButton;


		typedef struct IntSlider : Gadget
		{
			static const int SLIDER_BAR_W = 80;
			static const int SLIDER_BAR_H = 3;
			static const int SLIDER_MARKER_W = 3;
			static const int SLIDER_MARKER_H = 10;
			static const int LABEL_PADDING = 50;

			int* val;
			int min, max;
			deft::Rect slider_bar;
			deft::Rect val_marker;

			void set_val(int& value, int min, int max);

			virtual void on_left_mouse_press(int mouse_x, int mouse_y);
			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
			virtual void render();

		private:
			virtual void render_selected();
			void clamp_val_marker();
			void update_val();
		} IntSlider;


		namespace backend
		{
			void _be_on_left_mouse_release(int mouse_x, int mouse_y);
			void _be_on_left_mouse_press(int mouse_x, int mouse_y);
		}

		void add_panel(std::unique_ptr<Panel> panel);

		void render_gui();
	}
}
