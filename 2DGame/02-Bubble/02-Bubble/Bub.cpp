#include "Bub.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum PlayerAnims
{
	QUIETO, LANZAR_BOLA, COGER_BOLA
};

void Bub::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	lanzada = false;
	vacio = false;
	tiempo = 0;
	spritesheet.loadFromFile("images/bubs.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(66,62), glm::vec2(0.25,0.5), &spritesheet, &shaderProgram);
	
	sprite->setNumberAnimations(3);
	sprite->setAnimationSpeed(QUIETO, 8);
	sprite->addKeyframe(QUIETO, glm::vec2(0.f, 0.f));

	sprite->setAnimationSpeed(COGER_BOLA, 4);
	sprite->addKeyframe(COGER_BOLA, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(COGER_BOLA, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(COGER_BOLA, glm::vec2(0.75f, 0.f)); 
	sprite->addKeyframe(COGER_BOLA, glm::vec2(0.0f, 0.5f));
	
	
	sprite->setAnimationSpeed(LANZAR_BOLA, 8);
	sprite->addKeyframe(LANZAR_BOLA, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(LANZAR_BOLA, glm::vec2(0.50f, 0.5f));
	sprite->addKeyframe(LANZAR_BOLA, glm::vec2(0.75f, 0.5f));

	


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBub.x), float(tileMapDispl.y + posBub.y)));
}

void Bub::update(int deltaTime)
{
	tiempo += deltaTime;
	sprite->update(deltaTime);
	if (Game::instance().getKey(32)) {
		if (sprite->animation() != LANZAR_BOLA && !lanzada) {
			sprite->changeAnimation(LANZAR_BOLA);
			 lanzada = true;
			

		}
	}
	else if (sprite->animation() == LANZAR_BOLA && lanzada){
			lanzada = false;
			sprite->changeAnimation(QUIETO);
			tiempo = 0;
		

	}
		/*else if (vacio && lanzada && (sprite->animation() != COGER_BOLA) && (sprite->animation() != LANZAR_BOLA)) {
			sprite->changeAnimation(COGER_BOLA);
			vacio = false;
			lanzada = false;
			
		}
		else sprite->changeAnimation(QUIETO);*/


	
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
