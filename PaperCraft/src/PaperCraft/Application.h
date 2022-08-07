#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace PaperCraft
{
	/*
	* Class used to define properties of applications based on PaperCraft engine.
	*/
	class PAPERCRAFT_API Application
	{
	public:
		// Default constructor.
		Application();

		// Default destructor.
		virtual ~Application();

		/*
		* This function is responsible for running the application.
		*/
		void Run();
	};

	// TO BE DEFINED IN CLIENT.
	Application* CreateApplication();
}