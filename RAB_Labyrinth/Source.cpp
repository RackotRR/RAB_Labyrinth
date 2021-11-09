#include <SDL.h> 
#include <iostream> 
#include "RRGameEngine.h"  
  
int main(int argc, char *argv[]) {    
	auto& engine{ RRGameEngine::Instance() };
	try {
		engine.Initialize();
		engine.Run();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	} 
	engine.Shutdown();
	return 0;
}