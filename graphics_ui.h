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
			Rect rect;

			virtual void on_left_mouse_release(int mouse_x, int mouse_y) {}
			virtual void on_left_mouse_press(int mouse_x, int mouse_y) {}
			virtual void render() = 0;
		} Gadget;

		typedef struct Panel
		{
			Panel(std::string panel_name, float x, float y, int w, int h);
			~Panel();

			std::string name;

			virtual void on_left_mouse_release(int mouse_x, int mouse_y) = 0;
			virtual void on_left_mouse_press(int mouse_x, int mouse_y) = 0;

			void add_textbox(std::string label, std::string text);
			void add_text_button(std::string label);
			void render();
			Rect rect;

			std::string clicked();
			Gadget* last_added();

		private:
			std::vector<Gadget*> gadgets_;
			Gadget* active_gadget_;
		} Panel;

		typedef struct MusicPlayerPanel : Panel
		{
			MusicPlayerPanel(std::string panel_name, float x, float y, int w, int h);
			virtual void on_left_mouse_release(int mouse_x, int mouse_y);
			virtual void on_left_mouse_press(int mouse_x, int mouse_y);
		} MusicPlayerPanel;

		typedef struct TextBox : Gadget
		{
			std::string text;
			virtual void render();
		} TextBox;

		typedef struct TextButton : Gadget
		{
			bool selected = false;
			virtual void render();
		} TextButton;


		namespace backend
		{
			void _be_on_left_mouse_release(int mouse_x, int mouse_y);
			void _be_on_left_mouse_press(int mouse_x, int mouse_y);
		}

		void add_panel(Panel* panel);

		void render_gui();
		void draw_text_box(TextBox& text_box);
		void draw_text_button(TextButton& text_button);
	}
}
