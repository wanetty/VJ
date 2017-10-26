#include "Tubo.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"




void Tubo::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	spritesheet.loadFromFile("images/tubo.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(52, 48), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posTubo.x), float(tileMapDispl.y + posTubo.y)));

}

void Tubo::update(int deltaTime)
{
	sprite->update(deltaTime,true);
	if (Game::instance().getKey(32)) {
		//hacer que salga una bola
	}


}

void Tubo::render()
{
	sprite->render();
}

void Tubo::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Tubo::setPosition(const glm::vec2 &pos)
{
	posTubo = pos;
	sprite->setPosition(glm::vec2(float(posTubo.x), float(posTubo.y)));
}
