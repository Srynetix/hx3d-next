#include <Engine/Core/Engine.hpp>
#include <SmashGame/Common/SmashGame.hpp>

int main() {
	using namespace hx3d;

	Core::Engine engine;
	engine.bootEngine();

	SmashGame game;
	engine.runGame(&game);

	return 0;
}
