#include <SDL.h>
#include <string>
#include <deque>

class Manager;

class Clock {
public:
	static Clock& getInstance();  // This class is a Singleton
	unsigned int getTicksSinceLastFrame() const	{ return ticks; }

	void toggleSloMo()		{ sloMo = !sloMo; }
	void togglePause()		{ paused = !paused; }
	void toggleFrameCap()	{ capped = !capped; }

	bool isStarted() const	{ return started; }
	bool isPaused() const	{ return paused; }

	int getFps() const		{ return fps; }
	int getElapsedSeconds() const { return SDL_GetTicks() / 1000; }

	void start();
	void update();  // Increments time/ticks

private:
	unsigned int ticks;
	float fps;
	unsigned int msPerFrame;
	bool started;
	bool paused;
	bool sloMo;
	bool capped;

	Clock();
	Clock(const Clock&);
	Clock& operator=(const Clock&);
};

