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
			std::string label;
			Rect rect;

			virtual void on_left_click() {}
			virtual void render() = 0;
		} Gadget;

		typedef struct Panel
		{
			Panel(float x, float y, int w, int h);

			void add_textbox(std::string label, std::string text);
			void add_text_button(std::string label);
			void render();
			Rect rect;

		private:
			std::vector<Gadget*> gadgets_;
		} Panel;

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

		void draw_text_box(TextBox& text_box);
		void draw_text_button(TextButton& text_button);
	}
}
