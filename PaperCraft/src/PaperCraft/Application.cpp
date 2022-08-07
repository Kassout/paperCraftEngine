#include "Application.h"

#include "PaperCraft/Events/ApplicationEvent.h"
#include "PaperCraft/Log.h"

namespace PaperCraft
{
	PaperCraft::Application::Application()
	{
	}

	PaperCraft::Application::~Application()
	{
	}

	void Application::Run()
	{
		// Event test.
		WindowResizeEvent e(1280, 720);
		
		// Check application event category.
		if (e.IsInCategory(EventCategoryApplication))
		{
			// Write log trace of application event category.
			PPCF_TRACE(e);
		}

		// Check input event category.
		if (e.IsInCategory(EventCategoryInput))
		{
			// Write log trace of input event category.
			PPCF_TRACE(e);
		}

		// TODO: WARNING => Infinite loop.
		while (true);
	}
}