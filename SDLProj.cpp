#include <iostream>
#include "deft.h"


int main(int argc, char* argv[])
{
	deft::init();

	while (true)
	{
		deft::get_input();
		deft::pre_render();
		deft::outline_rect(100, 100, 100, 100, deft::red);
		deft::post_render();
	}

	return EXIT_SUCCESS;
}

