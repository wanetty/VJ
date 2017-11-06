#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE

#include "AudioEngineGame.h"
#include "Scene.h"
#include "Menu.h"
#include "Instrucciones.h"
#include "Creditos.h"



#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480




// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

public:
	Game() {}
	
	
	static Game &instance()
	{
		static Game G;
	
		return G;
	}
	
	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);
	
	bool getKey(int key) const;
	bool getSpecialKey(int key) const;

private:
	bool bPlay;                       // Continue to play game?
	Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256];// Store key states so that 
	Menu menu;

	string estado;      
	Instrucciones ins;// we can have access at any time
	CAudioEngine_Game aEngine,aCreditos;
	bool primero, first_creditos;
	Creditos creditos;


};


#endif // _GAME_INCLUDE


