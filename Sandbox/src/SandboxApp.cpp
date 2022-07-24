#include <PaperCraft.h>

class Sandbox : public PaperCraft::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

PaperCraft::Application* PaperCraft::CreateApplication()
{
	return new Sandbox();
}