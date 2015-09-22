#include <SDL/SDL.h>
#include <vector>
#include "ioManager.h"
#include "clock.h"
#include "sprite.h"

class Manager {
public:
	Manager();
	~Manager();
	void play();

private:
	const bool env;
	const IOManager* io;
	Clock& clock;

	SDL_Surface* const screen;

	SDL_Surface* bgSurface;
	const Frame* const bgFrame;
	Sprite bg;

	SDL_Surface* sushiSurface;
	const Frame* const sushiFrame;

	SDL_Surface* chopsticksSurface;
	const Frame* const chopsticksFrame;

	std::vector<Sprite> objects;

	bool makeVideo;
	int frameCount;
	std::string username;
	int frameMax;
	const std::string TITLE;
	const std::string NAME;

	void draw() const;
	void update();

	Manager(const Manager&);
	Manager& operator=(const Manager&);
	void drawBackground() const;
};
