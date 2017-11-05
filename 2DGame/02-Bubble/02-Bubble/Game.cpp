#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	menu.init();
	scene.init(1,0);
	estado = "MENU";
}

bool Game::update(int deltaTime)
{

	if (estado == "JUGANDO") {
		scene.update(deltaTime);
		if (scene.get_perdido()) {
			estado == "PERDIDO";
		}
	}

	else if (estado == "MENU") {
		if (instance().getKey(13)) {
			estado = "JUGANDO";
			scene.init(1,0);
			
		}
		else {
		menu.update(deltaTime);
		}
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (estado == "JUGANDO")scene.render();
	else if (estado == "MENU") menu.render();
}

void Game::keyPressed(int key)
{
	if(key == 27) // Escape code
		bPlay = false;
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}





