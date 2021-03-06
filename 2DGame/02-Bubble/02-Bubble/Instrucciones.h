#ifndef _INSTRUCCIONES_INCLUDE
#define _INSTRUCCIONES_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "BubIni.h"
#include "Text.h"
#include"fondo.h"



// Instrucciones contains all the entities of our game.
// It is responsible for updating and render them.


class Instrucciones
{

public:
	Instrucciones();
	~Instrucciones();

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
	BubIni *bubi;
	Text text;
	float tiempo;
};


#endif // _INSTRUCCIONES_INCLUDE
