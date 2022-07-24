#pragma once

#ifdef PPCF_PLATFORM_WINDOWS

extern PaperCraft::Application* PaperCraft::CreateApplication();

int main(int argc, char** argv)
{
	PaperCraft::Log::Init();
	PPCF_CORE_WARN("Initialized log!");
	int a = 5;
	PPCF_INFO("Hello! Var={0}", a);
	

	auto app = PaperCraft::CreateApplication();
	app->Run();
	delete app;
}

#endif