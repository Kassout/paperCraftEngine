#pragma once

#ifdef PPCF_PLATFORM_WINDOWS

// extern => Specify the compiler that this function exist *somewhere*, any source file that includes this will be able to use "CreateApplication()".
// TODO: add functional comment.
extern PaperCraft::Application* PaperCraft::CreateApplication();

// Controls operation of the program.
int main(int argc, char** argv)
{
	// Initialize log.
	PaperCraft::Log::Init();

	// Log test.
	PPCF_CORE_WARN("Initialized log!");

	// Log test 2.
	int a = 5;
	PPCF_INFO("Hello! Var={0}", a);
	
	// Initialize PaperCraft application.
	auto app = PaperCraft::CreateApplication();

	// Run PaperCraft application.
	app->Run();

	// Delete PaperCraft application.
	delete app;
}

#endif