#include "Bolsas.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Bolsas::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	spritesheet.loadFromFile("images/bolsas.png", TEXTURE_PIXEL_FORMAT_RGB);
	sprite = Sprite::createSprite(glm::ivec2(128, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBolsas.x), float(tileMapDispl.y + posBolsas.y)));

}

void Bolsas::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey(32)) {
		//hacer que salga una bola
	}


}

void Bolsas::render()
{
	sprite->render();
}

void Bolsas::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Bolsas::setPosition(const glm::vec2 &pos)
{
	posBolsas = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBolsas.x), float(tileMapDispl.y + posBolsas.y)));
}

