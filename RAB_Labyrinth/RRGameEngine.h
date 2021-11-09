#pragma once
#include "RRGameTime.h"
#include "RRController.h" 
#include "RRGameIO.h"
#include "RRTextureManager.h"
#include "RRGameplay.h"

#include "World.h"
#include "DrawingComponent.h"
#include "Wall.h"
 

class RRGameEngine {
	static constexpr int step{ 48 };
public:
	static RRGameEngine& Instance() {
		static RRGameEngine instance;
		return instance;
	}

	void Initialize();

	void Run();

	void Stop() {
		shallStop = true;	
	}

	void Shutdown() { 
		RRGameIO::Instance().Shutdown();
		RRGameplay::Instance().Shutdown();
	}
private:
	World world;
	bool shallStop{ false };


	RRGameEngine() = default;
	RRGameEngine(RRGameEngine&) = delete;
	void operator=(RRGameEngine&) = delete;
};