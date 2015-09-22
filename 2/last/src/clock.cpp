#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include "clock.h"
#include "gamedata.h"
#include "ioManager.h"

Clock& Clock::getInstance() {
	if (SDL_WasInit(SDL_INIT_VIDEO) == 0)
		throw std::string("Must init SDL before Clock");

	static Clock clock;
	return clock;
}

Clock::Clock() :
	ticks(0),
	fps(0),
	msPerFrame(33),
	started(false),
	paused(false),
	sloMo(false),
	capped(false) {
	start();
}

Clock::Clock(const Clock& c) :
	ticks(c.ticks),
	fps(c.fps),
	msPerFrame(c.msPerFrame),
	started(c.started),
	paused(c.paused),
	sloMo(c.sloMo),
	capped(c.capped) {
	start();
}

void Clock::update() {
	// figure out actual elapsed time since last update
	static std::list<unsigned int> last_SDL_ticks;
	static unsigned int last_delay = 0;

	unsigned int current_SDL_ticks = SDL_GetTicks();

	if (last_SDL_ticks.empty()) // prevent jump at first update
		last_SDL_ticks.push_back(current_SDL_ticks);

	ticks = current_SDL_ticks - last_SDL_ticks.back();
	last_SDL_ticks.push_back(current_SDL_ticks);

	if (capped) {
		if (last_SDL_ticks.size() > 3)
			last_SDL_ticks.pop_front();

		if (last_delay == 0) // just started capping
			last_delay = msPerFrame - ticks - 10; // SDL_Delay adds about 10-15 ms

		unsigned int average = (last_SDL_ticks.back() - last_SDL_ticks.front()) / (last_SDL_ticks.size() - 1);
		unsigned int delay = last_delay + (int)(msPerFrame - average)/2;  // adjust last delay by 1/4 of the error to correct slowly
		delay = std::max(0, (int)delay); // don't do negative delay

		SDL_Delay(delay);
		last_delay = delay;
	}
	else {
		last_delay = 0;
		// ensure there is only 1 entry, could be coming off of capped
		while (last_SDL_ticks.size() > 1)
			last_SDL_ticks.pop_front();
	}

	if (ticks == 0)
		return;

	// slow down the FPS update, only every 10 frames
	static unsigned int updatesSinceFpsUpdate = 0;
	static unsigned int ticksSinceFpsUpdate = 0;

	if (fps == 0) {
		fps = 1000/ticks;
	}
	else if (updatesSinceFpsUpdate >= 10) {
		fps = 1000 * updatesSinceFpsUpdate / ticksSinceFpsUpdate;
		updatesSinceFpsUpdate = 0;
		ticksSinceFpsUpdate = 0;
	}
	else {
		updatesSinceFpsUpdate++;
		ticksSinceFpsUpdate += ticks;
	}

	// ticks is what we report on how much to draw, make adjustments here
	if (sloMo)
		ticks /= 3;

	if (paused)
		ticks = 0;
}

void Clock::start() {
	started = true;
	paused = false;
	msPerFrame = 1000/Gamedata::getInstance().getXmlInt("frameCap");
	capped = Gamedata::getInstance().getXmlBool("framesAreCapped");

	update();
}
