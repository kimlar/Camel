
//#include "Engine/FastGPU.h"

// Include our stuff
#include "Engine/Engine.h"

int main(void)
{
	Engine* engine = new Engine();
	engine->Run();
	delete engine;

	return 0;
}
