#include <iostream>
#include "Application.h"

int main(int, char const**)
{
	Application* game = Application::Istance();
	
	game->Init();
	
	game->Run();
	
	game->Destroy();
	
	exit(0);
}




