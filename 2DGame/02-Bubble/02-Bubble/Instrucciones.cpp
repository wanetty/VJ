#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Instrucciones.h"


#define SCREEN_X 191
#define SCREEN_Y 50

#define bubix 30
#define bubiy 410


Instrucciones::Instrucciones()
{

	fondo = NULL;

}

Instrucciones::~Instrucciones()
{

	if (fondo != NULL)
		delete fondo;

}


void Instrucciones::init()
{
	initShaders();
	fondo = new Fondo();
	fondo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/instrucciones.png");
	fondo->setPosition(glm::vec2(0, 0));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	play = false;
	bubi = new BubIni();
	bubi->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 0);
	bubi->setPosition(glm::vec2(bubix, bubiy));

	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
}

void Instrucciones::update(int deltaTime)
{
	tiempo += deltaTime;
	currentTime += deltaTime;
	bubi->update(deltaTime);

	/*if (Game::instance().getSpecialKey(32)) {
	play = true;
	}*/

}

void Instrucciones::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render();
	bubi->render();
	if (tiempo > 500) {
		text.render("Pulsa enter para volver!", glm::vec2(450, 472), 15, glm::vec4(1, 1, 1, 1));

	}
	if (tiempo > 1000) tiempo = 0;

}

void Instrucciones::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

bool Instrucciones::getPlay() {
	return play;
}