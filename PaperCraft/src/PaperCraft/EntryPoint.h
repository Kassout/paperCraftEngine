#pragma once

#ifdef PPCF_PLATFORM_WINDOWS

extern PaperCraft::Application* PaperCraft::CreateApplication();

int main(int argc, char** argv)
{
	auto app = PaperCraft::CreateApplication();
	app->Run();
	delete app;
}

#endif