#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "BubIni.h"
#include "Text.h"



// Menu contains all the entities of our game.
// It is responsible for updating and render them.


class Menu
{

public:
	Menu();
	~Menu();

	void init();
	void update(int deltaTime);
	void render();
	bool getPlay();

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	Fondo *fondo;
	bool play;
	BubIni *bubi, *bubd;
	Text text;
	float tiempo;
};


#endif // _MENU_INCLUDE
