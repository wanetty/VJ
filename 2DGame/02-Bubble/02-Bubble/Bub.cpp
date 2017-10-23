#include "Bub.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Bub::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	spritesheet.loadFromFile("images/Bub2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(72, 60), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBub.x), float(tileMapDispl.y + posBub.y)));

}

void Bub::update(int deltaTime)
{
	


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
