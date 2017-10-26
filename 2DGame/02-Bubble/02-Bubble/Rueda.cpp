#include "Rueda.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"

enum PlayerAnims
{
	QUIETO, DERECHA, IZQUIERDA
};


void Rueda::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{

	spritesheet.loadFromFile("images/ruedas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(61, 31), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posRueda.x), float(tileMapDispl.y + posRueda.y)));

}

void Rueda::update(int deltaTime)
{
	sprite->update(deltaTime,false);
	if (Game::instance().getKey(32)) {
		
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
