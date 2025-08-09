#pragma once
#include "Core.h"

namespace TrekEngine
{
	class Trek_API Application
	{
		public:
			Application();
			virtual ~Application();

			void Run();
	};

	Application* CreateApplication();
}


