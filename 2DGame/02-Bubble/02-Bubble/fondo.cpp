#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "fondo.h"
#include "Game.h"

void Fondo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, string image)
{
	spritesheet.loadFromFile(image, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(640, 480), glm::vec2(1,1), &spritesheet, &shaderProgram);
	

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(posfondo.x), float(posfondo.y)));

}
void Fondo::render()
{
	sprite->render();
}



void Fondo::setPosition(const glm::vec2 &pos)
{
	posfondo = pos;
	sprite->setPosition(glm::vec2(float(posfondo.x), float(posfondo.y)));
}