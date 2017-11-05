
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "SpriteTexto.h"





void SpriteTexto::init(string image, ShaderProgram &shaderProgram,int posx, int posy,int tamx,int tamy)
{
	posSpriteTexto.x = posx;
	posSpriteTexto.y = posy;
	spritesheet.loadFromFile("images/"+image, TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(tamx, tamy), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(posSpriteTexto.x), float(posSpriteTexto.y)));

}

void SpriteTexto::update(int deltaTime)
{
	sprite->update(deltaTime, true);

}

void SpriteTexto::render()
{
	sprite->render();
}


void SpriteTexto::setPosition(const glm::vec2 &pos)
{
	posSpriteTexto = pos;
	sprite->setPosition(glm::vec2(float(posSpriteTexto.x), float(posSpriteTexto.y)));
}
