#include "../SimpleSfmlEngine/engine.hpp"
#include "GLOBAL_DEFINITIONS.hpp"
#include "States/SplashState.hpp"
#include <cmath>
#include <iostream>

//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
int main()
{
	sse::Game game(WINDOW_TITLE, [](sse::GameDataRef data) { data->machine.AddState(sse::StateRef(new sse::SplashState(data))); });

	//std::cin.get();
	return 0;
}
