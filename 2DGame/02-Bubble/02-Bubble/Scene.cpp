#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Bolsas.h"



#define SCREEN_X 191
#define SCREEN_Y 50

#define Pos_felcha_x 104
#define Pos_felcha_y 302


Scene::Scene()
{
	map = NULL;
	fondo = NULL;
	flecha = NULL;
	bolsa = NULL;
	base = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if (fondo != NULL)
		delete fondo;
	if (flecha != NULL)
		delete flecha;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/mapa1.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	fondo = new Fondo();
	flecha = new Flecha();
	bola = new Bola();
	bolsa = new Bolsas();
	base = new Base();
	fondo->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	fondo->setPosition(glm::vec2(0,0));
	fondo->setTileMap(map);
	flecha->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	flecha->setPosition(glm::vec2(Pos_felcha_x, Pos_felcha_y));
	flecha->setTileMap(map);
	bola->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, map);
	bola->setPosition(glm::vec2(Pos_felcha_x+8, Pos_felcha_y+32));
	bola->setDireccion(flecha->getAngulo());
	bolsa->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	bolsa->setPosition(glm::vec2(191-40,385+25));
	bolsa->setTileMap(map);
	base->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	base->setPosition(glm::vec2(250, 385 + 20));
	base->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	flecha->update(deltaTime);
	bola->setDireccion(flecha->getAngulo());
	bola->update(deltaTime);
	map->update(glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	//bolsa->update(deltaTime);
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	fondo->render();
	map->render();
	base->render();
	flecha->render();
	bola->render();
	bolsa->render();
	
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



