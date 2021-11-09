#include "RRGameEngine.h"

void RRGameEngine::Run() { 
	auto& gameIO{ RRGameIO::Instance() };
	auto& controller{ RRController::Instance() };
	auto& gameTime{ RRGameTime::Instance() };
	auto& gameplay{ RRGameplay::Instance() };

	do {
		controller.Update();
		gameTime.Update();
		if (controller.GetKeyState().Click(RRKeyboardState::Keys::ESCAPE)) {
			Stop();
		}

		/* обработка игровой логики */
		gameplay.Update();

		gameIO.Begin(); 
		/* отрисовка всего и вся */ 
		world.DoForEachObject(
			[&](GameObject* object) {
				DrawObject(object, step);
			}
		);
		gameIO.End();
	} while (!shallStop); 
}

void RRGameEngine::Initialize() {
	RRGameIO::Instance().Initialize();
	RRGameplay::Instance().Initialize();

	// create world; 
	for (int x{}; x < RRGameIO::Instance().GetWinWidth(); x += step) {
		for (int y{}; y < RRGameIO::Instance().GetWinHeight(); y += step) {
			constexpr double objects{ 1920 * 0.8 / step * 1080 * 0.8 * step };
			auto wall{ Wall{ Vector2{ x / step, y / step } } };
			wall.AddComponent(DrawingComponent{ RRTextureManager::Instance().GetTexture(TextureType::forest) });
			world.PlaceObject(std::move(wall));
		}
	}
}