#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Game.h"
#include "Menu.h"


#define SCREEN_X 191
#define SCREEN_Y 50

#define bubix 125
#define bubiy 280
#define bubdx 445
#define bubdy 265

Menu::Menu()
{

	fondo = NULL;

}

Menu::~Menu()
{
	
	if (fondo != NULL)
		delete fondo;

}


void Menu::init()
{
	initShaders();
	fondo = new Fondo();
	fondo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/menu.png");
	fondo->setPosition(glm::vec2(0, 0));
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
	play = false;
	bubi = new BubIni();
	bubd = new BubIni();
	bubi->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram,0);
	bubi->setPosition(glm::vec2(bubix, bubiy));
	bubd->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	bubd->setPosition(glm::vec2(bubdx, bubdy));
	// Select which font you want to use
	if (!text.init("fonts/OpenSans-Regular.ttf"))
		//if(!text.init("fonts/OpenSans-Bold.ttf"))
		//if(!text.init("fonts/DroidSerif.ttf"))
		cout << "Could not load font!!!" << endl;
}

void Menu::update(int deltaTime)
{
	currentTime += deltaTime;
	bubi->update(deltaTime);
	bubd->update(deltaTime);
	/*if (Game::instance().getSpecialKey(32)) {
		play = true;
	}*/

}

void Menu::render()
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
	bubd->render();
	text.render("Videogames!!!", glm::vec2(10, 480 - 20), 32, glm::vec4(1, 1, 1, 1));

}

void Menu::initShaders()
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

bool Menu::getPlay() {
	return play;
}