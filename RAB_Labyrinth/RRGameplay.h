#pragma once

class RRGameplay {
public:
	static RRGameplay& Instance() {
		static RRGameplay instance;
		return instance;
	}

	void Initialize() {

	}

	void Shutdown() {

	}

	void Update() {

	}

private:
	RRGameplay() = default;
	RRGameplay(RRGameplay&) = delete;
	void operator=(RRGameplay&) = delete;
};