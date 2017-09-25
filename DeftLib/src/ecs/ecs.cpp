#include "ecs.h"
#include "ecs_system.h"
#include <vector>

namespace deft
{
	namespace ecs
	{
		namespace backend
		{
			std::vector<Rect> entities;
			Sys_RectRendering rect_rendering_system;
		}

		void process()
		{
			backend::rect_rendering_system.process(backend::entities);
		}

		void add_entity(Rect entity)
		{
			backend::entities.push_back(entity);
		}
	}
}