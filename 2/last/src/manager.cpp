#include <iostream>
#include <string>
#include <iomanip>
#include "sprite.h"
#include "gamedata.h"
#include "manager.h"

Manager::~Manager() {
	// Manager made it, so Manager needs to delete it
	SDL_FreeSurface(bgSurface);
	SDL_FreeSurface(sushiSurface);
	SDL_FreeSurface(chopsticksSurface);
	delete bgFrame;
	delete sushiFrame;
	delete chopsticksFrame;
	objects.clear();
}

Manager::Manager() :
	env(SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center"))),
	io(&IOManager::getInstance()),
	clock(Clock::getInstance()),
	screen(io->getScreen()),

	bgSurface(io->loadAndSet(
	              Gamedata::getInstance().getXmlStr("background/file"),
	              Gamedata::getInstance().getXmlBool("background/transparency"))),
	bgFrame(new Frame("background", bgSurface)),
	bg("background", bgFrame),

	sushiSurface(io->loadAndSet(
	                  Gamedata::getInstance().getXmlStr("sushi/file"),
	                  Gamedata::getInstance().getXmlBool("sushi/transparency"))),
	sushiFrame(new Frame("sushi", sushiSurface)),

	chopsticksSurface(io->loadAndSet(
	                  Gamedata::getInstance().getXmlStr("chopsticks/file"),
	                  Gamedata::getInstance().getXmlBool("chopsticks/transparency"))),
	chopsticksFrame(new Frame("chopsticks", chopsticksSurface)),

	objects(),

	makeVideo(false),
	frameCount(0),
	username(Gamedata::getInstance().getXmlStr("username")),
	frameMax(Gamedata::getInstance().getXmlInt("frameMax")),
	TITLE(Gamedata::getInstance().getXmlStr("screenTitle")),
	NAME(Gamedata::getInstance().getXmlStr("screenName")) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		throw string("Unable to initialize SDL: ");

	atexit(SDL_Quit);
	int numSushi = Gamedata::getInstance().getXmlInt("numSushi");
	int numChopsticks = Gamedata::getInstance().getXmlInt("numChopsticks");
	objects.reserve(numSushi + numChopsticks);

	for (int i = 0; i < numSushi; i++) {
		objects.push_back(Sprite("sushi", sushiFrame));
		const Vector2f& velocity = objects.back().getVelocity();

		objects.back().setVelocity(Vector2f(
			(rand() % 2 ? 1 : -1) * Gamedata::getRandInRange(velocity[0]/5, velocity[0]),
			(rand() % 2 ? 1 : -1) * Gamedata::getRandInRange(velocity[1]/5, velocity[1])
		));
	}

	for (int i = 0; i < numChopsticks; i++) {
		objects.push_back(Sprite("chopsticks", chopsticksFrame));
		const Vector2f& velocity = objects.back().getVelocity();

		objects.back().setVelocity(Vector2f(
			(rand() % 2 ? 1 : -1) * Gamedata::getRandInRange(velocity[0]/5, velocity[0]),
			(rand() % 2 ? 1 : -1) * Gamedata::getRandInRange(velocity[1]/5, velocity[1])
		));
	}
}

void Manager::draw() const {
	bg.draw();

	for (unsigned long i = 0; i < objects.size(); i++)
		objects[i].draw();

//	clock.draw();
	io->printMessageCenteredAt(TITLE, 10);
	io->printMessageValueAt("fps:  ", clock.getFps(), 10, 10);
	io->printMessageValueAt("time: ", clock.getElapsedSeconds(), 10, 30);
	io->printMessageAt(NAME, 10, Gamedata::getInstance().getXmlInt("view/height") - 30);
	SDL_Flip(screen);
}

void Manager::update() {
	clock.update();
	Uint32 ticks = clock.getTicksSinceLastFrame();

	for (unsigned long i = 0; i < objects.size(); i++)
		objects[i].update(ticks);

	if (makeVideo && frameCount < frameMax) {
		std::stringstream strm;
		strm << "frames/" << username << '.'
		     << std::setfill('0') << std::setw(4)
		     << frameCount++ << ".bmp";
		std::string filename(strm.str());
		std::cout << "Making frame: " << filename << std::endl;
		SDL_SaveBMP(screen, filename.c_str());
	}
}

void Manager::play() {
	SDL_Event event;
	bool done = false;

	while (not done) {
		while (SDL_PollEvent(&event)) {
			Uint8* keystate = SDL_GetKeyState(NULL);

			if (event.type ==  SDL_QUIT) {
				done = true;
				break;
			}

			if (event.type == SDL_KEYDOWN) {
				if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
					done = true;
					break;
				}

				if (keystate[SDLK_F3]) {
					clock.toggleSloMo();
					break;
				}

				if (keystate[SDLK_F4] && !makeVideo) {
					std::cout << "Making video frames" << std::endl;
					makeVideo = true;
				}

				if (keystate[SDLK_p])
					clock.togglePause();
			}
		}

		draw();
		update();
	}
}
