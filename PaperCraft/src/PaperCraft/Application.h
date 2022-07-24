#pragma once

#include "Core.h"

namespace PaperCraft
{
	class PAPERCRAFT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// TO BE DEFINED IN CLIENT.
	Application* CreateApplication();
}