#include "Base.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Base::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	spritesheet.loadFromFile("images/cat.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(133, 56), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBase.x), float(tileMapDispl.y + posBase.y)));

}

void Base::update(int deltaTime)
{
	sprite->update(deltaTime,true);
	if (Game::instance().getKey(32)) {
		//hacer que salga una bola
	}


}

void Base::render()
{
	sprite->render();
}

void Base::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Base::setPosition(const glm::vec2 &pos)
{
	posBase = pos;
	sprite->setPosition(glm::vec2(float(posBase.x), float(posBase.y)));
}
