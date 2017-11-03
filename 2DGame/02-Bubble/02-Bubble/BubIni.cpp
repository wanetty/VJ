#include "BubIni.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


enum PlayerAnims
{
	IZQUIERDA,DERECHA
};

void BubIni::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram,int id)
{


	
	spritesheet.loadFromFile("images/bubini.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(85, 75), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(IZQUIERDA, 6);
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.25f, 0.f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.5f, 0.f));
	sprite->addKeyframe(IZQUIERDA, glm::vec2(0.75f, 0.f));


	sprite->setAnimationSpeed(DERECHA, 6);
	sprite->addKeyframe(DERECHA, glm::vec2(0.0f, 0.5f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.25f, 0.5f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.5f, 0.5f));
	sprite->addKeyframe(DERECHA, glm::vec2(0.75f, 0.5f));

	sprite->changeAnimation(id);

	sprite->setPosition(glm::vec2(float(posBubIni.x), float(+posBubIni.y)));
}

void BubIni::update(int deltaTime)
{
	
	sprite->update(deltaTime, true);
	

}

void BubIni::render()
{
	sprite->render();
}


void BubIni::setPosition(const glm::vec2 &pos)
{
	posBubIni = pos;
	sprite->setPosition(glm::vec2(float(posBubIni.x), float(posBubIni.y)));
}

