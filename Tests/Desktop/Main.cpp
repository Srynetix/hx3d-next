#include <Engine/Core/Engine.hpp>
#include <Tests/Common/TestGame.hpp>

int main() {
	using namespace hx3d;

	Core::Engine engine;
	TestGame game;

	engine.runGame(&game);

	return 0;
}
