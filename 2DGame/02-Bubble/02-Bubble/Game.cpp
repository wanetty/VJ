#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	menu.init();
	//scene.init(1,0);
	estado = "MENU";
	primero = true;
	
}

bool Game::update(int deltaTime)
{


	if (estado == "JUGANDO") {
		if(!primero)primero = true;
		scene.update(deltaTime);
		/*if (scene.get_perdido()) {
			estado = "PERDIDO";
		}*/
		if (scene.get_completado()) {
				estado = "CREDITOS";
				if (!first_creditos)first_creditos = true;
				creditos.init();
			}
	}
	else if (estado == "MENU") {
		if (primero) {
			aEngine.Init();
			aEngine.LoadEvent("event:/StartGame");
			aEngine.LoadSound("audio/StartGame.wav", false, true);
			aEngine.LoadSound("audio/StartButton.wav", false, true);
			aEngine.PlaySounds("audio/StartGame.wav", Vector3_game{ 0, 0, 0 }, aEngine.VolumeTodB(0.7f));
			primero = false;
		}
		
		if (instance().getKey(13)) {
			aEngine.PlaySounds("audio/StartButton.wav", Vector3_game{ 0, 0, 0 }, aEngine.VolumeTodB(1.0f));
			estado = "JUGANDO";
			scene.init(1, 0);
			aEngine.Shutdown();
		}
		else if (instance().getKey(32)) {
			estado = "INSTRUCCIONES";
			ins.init();
		}

		else {
			menu.update(deltaTime);
			aEngine.Update();
		}
	}
	else if (estado == "INSTRUCCIONES") {
		
		if (instance().getKey(13)) {
			estado = "MENU";
			menu.init();
		}
		else ins.update(deltaTime);
	
	}
	else if (estado == "CREDITOS") {
		if (first_creditos) {
			aCreditos.Init();
			aCreditos.LoadSound("audio/creditos.wav", false, true);
			aCreditos.PlaySounds("audio/creditos.wav", Vector3_game{ 0, 0, 0 }, aEngine.VolumeTodB(.7f));
			first_creditos = false;
		}
		if (instance().getKey(13)) {
			aCreditos.Shutdown();
			estado = "MENU";
			if (!primero)primero = true;
			menu.init();
		}
		else {
			aCreditos.Update();
			creditos.update(deltaTime);
		}
	}
	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (estado == "JUGANDO")scene.render();
	else if (estado == "MENU") menu.render();
	else if (estado == "INSTRUCCIONES") ins.render();
	else if (estado == "CREDITOS") creditos.render();
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





