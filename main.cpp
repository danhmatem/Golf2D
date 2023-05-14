#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <string>

#include "RenderWindow.h"
#include "Entity.h"
#include "Ball.h"	
#include "Tile.h"
#include "Hole.h"

using namespace std;

string s;
string lv;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "SDL_Init HAS FAILED. ERROR: " << SDL_GetError() << endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;
	if (TTF_Init() != 0) 
		cout << "TTF_init has failed. Error: " << TTF_GetError() << endl;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLinit = init();

RenderWindow window("Golf Game", 640, 480);

SDL_Texture* ballTexture = window.loadTexture("gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("gfx/point.png");
SDL_Texture* tileDarkTexture32 = window.loadTexture("gfx/tile32_dark.png");
SDL_Texture* tileDarkTexture64 = window.loadTexture("gfx/tile64_dark.png");
SDL_Texture* tileLightTexture32 = window.loadTexture("gfx/tile32_light.png");
SDL_Texture* tileLightTexture64 = window.loadTexture("gfx/tile64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("gfx/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("gfx/powermeter_overlay.png");
SDL_Texture* click2start = window.loadTexture("gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("gfx/splashbg.png");

Mix_Chunk* chargeSfx = Mix_LoadWAV("sfx/charge.mp3");
Mix_Chunk* swingSfx = Mix_LoadWAV("sfx/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("sfx/hole.mp3");


SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("font/font.ttf", 24);
TTF_Font* font68 = TTF_OpenFont("font/font.ttf", 68);


Ball ball = Ball(Vector2f(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0);

Hole hole = Hole(Vector2f(0, 0), holeTexture);

vector<Tile> loadTiles(int level)
{
	vector<Tile> temp = {};
	switch (level)
	{
	case 0:
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 3), tileDarkTexture64));
		
		

		temp.push_back(Tile(Vector2f(64 * 3 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 1:
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 0, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 1, 64 * 3), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(64 * 3, 32 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 3), tileLightTexture64));
		break;
	case 2:
		temp.push_back(Tile(Vector2f(64 * 3, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(64 * 2, 64 * 3), tileDarkTexture64));

		
		temp.push_back(Tile(Vector2f(64 * 3 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 4 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 1 + 64 * 5, 64 * 3), tileLightTexture64));

		temp.push_back(Tile(Vector2f(64 * 4 , 32 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2 , 64 * 6), tileLightTexture64));
		temp.push_back(Tile(Vector2f(64 * 2 + 64 * 5, 64 * 5), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 1 + 32 * 10 + 16, 32 *2), tileDarkTexture32));
		break;
	case 3:
		temp.push_back(Tile(Vector2f(32 * 4, 32 * 7), tileDarkTexture64));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 6, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(64 * 4, 64 * 3), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(64 * 0 + 64 * 5, 64 * 3), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 4 + 64 * 5, 32 * 2), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 6), tileLightTexture32));
		temp.push_back(Tile(Vector2f(32 * 6 + 32 * 10, 32 * 9), tileLightTexture32));
		break;
	case 4:
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 1), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 1, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 3), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 5), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 3, 32 * 10), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 5, 32 * 12), tileDarkTexture32));
		temp.push_back(Tile(Vector2f(32 * 7, 32 * 10), tileDarkTexture32));

	
		temp.push_back(Tile(Vector2f(32 * 8, 32 * 7), tileDarkTexture64));

		temp.push_back(Tile(Vector2f(32 * 2 + 32 * 10, 32 * 2), tileLightTexture32));
		temp.push_back(Tile(Vector2f(32 * 5 + 32 * 10, 32 * 11), tileLightTexture32));

		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 1), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 8 + 32 * 10, 32 * 6), tileLightTexture64));
		temp.push_back(Tile(Vector2f(32 * 3 + 32 * 10, 32 * 11), tileLightTexture64));
		break;
	}
	return temp;
}

int level = 0;
vector<Tile> tiles = loadTiles(level);

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

int state = 0; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
	if (level > 4)
	{
		state = 2;
		return;
	}
	
	ball.setVelocity(0, 0);
	ball.setScale(1, 1);
	ball.setWin(false);

	tiles = loadTiles(level);

	switch (level)
	{
	case 0:
		
		ball.setPos(24 + 32 * 4, 24 + 32 * 11);
		hole.setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 2);
		break;
	case 1:
		
		ball.setPos(24 + 32 * 4, 24 + 32 * 11);
		hole.setPos(24 + 32 * 4, 22 + 32 * 2);
		break;
	case 2:
		
		ball.setPos(8 + 32 * 7 + 32 * 10, 8 + 32 * 10);		
		hole.setPos(8 + 32 * 4 + 32 * 10, 6 + 32 * 3);
		break;
	case 3:		
		ball.setPos(24 + 32 * 4, 24 + 32 * 5);		
		hole.setPos(24 + 32 * 4 + 32 * 10, 22 + 32 * 11);
		break;
	case 4:	
		ball.setPos(24 + 32 * 2, 24 + 32 * 12);
		hole.setPos(8 + 32 * 5 + 32 * 10, 6 + 32 * 1);
		break;
	}
}

const char* getStrokeText()
{
	int biggestStroke = 0;
	biggestStroke = ball.getStrokes();
	s = "STROKES: " + to_string(biggestStroke);
	return s.c_str();
}

const char* getLevelText(int side)
{
	int Level = (level + 1);
	if (side == 1)
	{
		Level++;
	}
	lv = to_string(Level);
	lv = "Level: " + lv;
	return lv.c_str();
}

void update()
{

	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

	mousePressed = false;
	//Get our controls and events
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
	}

	if (state == 1)
	{
		
		ball.update(deltaTime, mouseDown, mousePressed, tiles, hole, chargeSfx, swingSfx, holeSfx);
		if (ball.getScale().x < -1) {
			level++;
			loadLevel(level);
		}
	}
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	
	window.render(hole);
	
	if (ball.isWin())
	{
		window.render(ball.getPos().x, ball.getPos().y + 4, ballShadowTexture);
	}
	for (Entity& e : ball.getPoints())
	{
		window.render(e);
	}
	window.render(ball);

	for (Tile& t : tiles)
	{
		window.render(t);
	}
	
	for (Entity& e : ball.getPowerBar())
	{
		window.render(e);
	}
	window.render(ball.getPowerBar().at(0).getPos().x, ball.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);

	if (state != 2)
	{
		window.render(640 / 2 - 132/2, 480 - 32, levelTextBgTexture);
		window.renderCenter(0, 240 - 16 + 3, getLevelText(0), font24, black);
		window.renderCenter(0, 240 - 16, getLevelText(0), font24, white);

		window.render(640 / 2 - 196 / 2, 0, uiBgTexture);
		window.renderCenter(0, -240 + 16 + 3, getStrokeText(), font24, black);
		window.renderCenter(0, -240 + 16, getStrokeText(), font24, white);
	}
	else
	{
		window.render(0, 0, endscreenOverlayTexture);
		window.renderCenter(0, 3 - 32, "YOU WIN!", font48, black);
		window.renderCenter(0, -32, "YOU WIN!", font48, white);
		window.renderCenter(0, 3 + 32, getStrokeText(), font32, black);
		window.renderCenter(0, 32, getStrokeText(), font32, white);
	}

	window.display();
}

void titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
		if (!swingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			swingPlayed = true;
		}
		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			}
		}

		window.clear();
		window.render(0, 0, bgTexture);
		window.render(0, 0, splashBgTexture);
		window.renderCenter(0, 4,"W E L C O M E", font32, black);
		window.renderCenter(0, 0 ,  "W E L C O M E",font32, white);
		window.display();
	}
	else
	{
		if (!secondSwingPlayed)
		{
			Mix_PlayChannel(-1, swingSfx, 0);
			secondSwingPlayed = true;
		}
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency());

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				gameRunning = false;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					Mix_PlayChannel(-1, holeSfx, 0);
					state = 1;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		
		window.render(0, 0, click2start);
		window.renderCenter(0, 4, "MINI - GOLF", font68, black);
		window.renderCenter(0, 0, "MINI - GOLF", font68, white);
		
		window.renderCenter(0, 240 - 48 + 3 - 16 * 5, "LEFT CLICK TO START", font32, black);
		window.renderCenter(0, 240 - 48 - 16 * 5, "LEFT CLICK TO START", font32, white);
		window.display();
	}
}
void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}
int main(int argc, char* args[])
{
	loadLevel(level);
	while (gameRunning)
	{
		game();
	}

	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}
