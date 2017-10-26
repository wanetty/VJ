#include "Rueda.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum PlayerAnims
{
	QUIETO, DERECHA, IZQUIERDA,PARPADEO
};
# define M_PI 3.14159265358979323846

void Rueda::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	tiempo = 0;
	spritesheet.loadFromFile("images/ruedas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(70, 50), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(4);
	
	
	sprite->setAnimationSpeed(QUIETO, 8);
	sprite->addKeyframe(QUIETO, glm::vec2(0.0f, 0.0f));
	
	sprite->setAnimationSpeed(PARPADEO, 8);
	sprite->addKeyframe(PARPADEO, glm::vec2(0.25f, 0.0f));
	sprite->addKeyframe(PARPADEO, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(PARPADEO, glm::vec2(0.75f, 0.0f));

	sprite->setAnimationSpeed(DERECHA, 20);
	sprite->addKeyframe(DERECHA, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.0f, 0.25f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.75f, 0.25f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.0f, 0.75f));


	sprite->setAnimationSpeed(IZQUIERDA, 20);
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.75f, 0.25f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.5f, 0.25f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.25f, 0.25f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.0f, 0.25f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.25f, 0.75f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.0f, 0.75f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.0f, 0.5f));

	sprite->changeAnimation(0);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posRueda.x), float(tileMapDispl.y + posRueda.y)));

}

void Rueda::update(int deltaTime, float ang)
{
	sprite->update(deltaTime,true);
	tiempo += deltaTime;
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (sprite->animation() != IZQUIERDA) {
			sprite->changeAnimation(IZQUIERDA);
			
			tiempo = 0;
		}
		
	}
	
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (sprite->animation() != DERECHA) {
			sprite->changeAnimation(DERECHA);
			
			tiempo = 0;
		}
		
	}

	else if (sprite->animation() == QUIETO && tiempo > 2000) {
		sprite->changeAnimation(PARPADEO);
		tiempo = 0;
	}
	
	else if (sprite->animation() != QUIETO && tiempo > 400)
	{
		sprite->changeAnimation(QUIETO);
	}

	

}

void Rueda::render()
{
	sprite->render();
}

void Rueda::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Rueda::setPosition(const glm::vec2 &pos)
{
	posRueda = pos;
	sprite->setPosition(glm::vec2(float(posRueda.x), float(posRueda.y)));
}
