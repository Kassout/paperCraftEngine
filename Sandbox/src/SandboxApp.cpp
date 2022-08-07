#include <PaperCraft.h>

/*
* Class representing the application manager as a PaperCraft starting point.
*/
class Sandbox : public PaperCraft::Application
{
public:
	// Default constructor.
	Sandbox()
	{

	}

	// Default destructor.
	~Sandbox()
	{

	}
};

/*
* This function is responsible for initializing a new Sandbox PaperCraft's application.
* 
* @return new Sandbox PaperCraft's application.
*/
PaperCraft::Application* PaperCraft::CreateApplication()
{
	return new Sandbox();
}