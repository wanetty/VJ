#include "Arco.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Arco::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	spritesheet.loadFromFile("images/arco.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(81, 37), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posArco.x), float(tileMapDispl.y + posArco.y)));

}

void Arco::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey(32)) {
		//hacer que salga una bola
	}


}

void Arco::render()
{
	sprite->render();
}

void Arco::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Arco::setPosition(const glm::vec2 &pos)
{
	posArco = pos;
	sprite->setPosition(glm::vec2(float(posArco.x), float(posArco.y)));
}
