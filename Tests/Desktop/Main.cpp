#include <Engine/Core/Engine.hpp>
#include <Tests/Common/TestGame.hpp>

int main() {
	using namespace hx3d;

	Core::Engine engine;
	engine.bootEngine();

	TestGame game;	
	engine.runGame(&game);

	return 0;
}
