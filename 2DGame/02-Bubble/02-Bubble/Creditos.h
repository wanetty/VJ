#ifndef _Creditos_INCLUDE
#define _Creditos_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "BubIni.h"
#include "Text.h"
#include "Fondo.h"



// Creditos contains all the entities of our game.
// It is responsible for updating and render them.


class Creditos
{

public:
	Creditos();
	~Creditos();

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
	
};


#endif // _Creditos_INCLUDE
