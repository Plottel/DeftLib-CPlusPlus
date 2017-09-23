#include "ecs.h"
#include "ecs_system.h"
#include <vector>

namespace deft
{
	namespace ecs
	{
		namespace backend
		{
			std::vector<Rect> entities_;
			Sys_RectRendering rect_rendering_system;

		}

		void process()
		{
			backend::rect_rendering_system.process(backend::entities_);
		}

		void add_entity(Rect entity)
		{
			backend::entities_.push_back(entity);
		}
	}
}