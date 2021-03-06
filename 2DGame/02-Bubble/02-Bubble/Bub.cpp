#include "Bub.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum PlayerAnims
{
	QUIETO, LANZAR_BOLA, RAPIDO, PARPADEA
};

void Bub::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	
	
	tiempo = 0;
	spritesheet.loadFromFile("images/bubs3.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(45,50), glm::vec2(0.25,0.5), &spritesheet, &shaderProgram);
	
	sprite->setNumberAnimations(4);
	
	sprite->setAnimationSpeed(QUIETO, 8);
	sprite->addKeyframe(QUIETO, glm::vec2(0.f, 0.f));

	
	sprite->setAnimationSpeed(PARPADEA, 8);
	sprite->addKeyframe(PARPADEA, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(PARPADEA, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(QUIETO, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(RAPIDO, 8);
	sprite->addKeyframe(RAPIDO, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(RAPIDO, glm::vec2(0.75f, 0.5f));

	
	
	sprite->setAnimationSpeed(LANZAR_BOLA, 10);
	sprite->addKeyframe(LANZAR_BOLA, glm::vec2(0.75f, 0.0f));
	sprite->addKeyframe(LANZAR_BOLA, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(LANZAR_BOLA, glm::vec2(0.25f, 0.5f));

	


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBub.x), float(tileMapDispl.y + posBub.y)));
}

void Bub::update(int deltaTime)
{
	tiempo += deltaTime;
	sprite->update(deltaTime,true);
	if (sprite->animation() != LANZAR_BOLA && lanzada) {
		sprite->changeAnimation(LANZAR_BOLA);
		tiempo = 0;
	}

	else if (sprite->animation() == LANZAR_BOLA && tiempo > 300) {
		sprite->changeAnimation(QUIETO);
		lanzada = false;
		tiempo = 0;

	}
	else if ((sprite->animation() == QUIETO || sprite->animation() == PARPADEA) && tiempo > 3000) {
		sprite->changeAnimation(RAPIDO);
	}
	
	/*else if (sprite->animation() == QUIETO && tiempo > 2000) {
		sprite->changeAnimation(PARPADEA);
		if (tiempo > 4000) sprite->changeAnimation(RAPIDO);
	}
	*/

	else if (sprite->animation() == PARPADEA && tiempo >= 300) {
		sprite->changeAnimation(QUIETO);
		tiempo = 0;
	}
	
	

}

void Bub::render()
{
	sprite->render();
}

void Bub::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bub::setPosition(const glm::vec2 &pos)
{
	posBub = pos;
	sprite->setPosition(glm::vec2(float(posBub.x), float(posBub.y)));
}
void Bub::setLanzada(bool lanzada)
{
	this->lanzada = lanzada;
}
