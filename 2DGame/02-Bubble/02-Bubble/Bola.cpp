#include "Bola.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flecha.h"
#include "Game.h"

void Bola::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	
	spritesheet.loadFromFile("images/bola.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1, 1), &spritesheet, &shaderProgram);
	lanzada = false;
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));

}
void Bola::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey(32)) {
		lanzada = true;
	}
	else if (Game::instance().getKey('r')){
		lanzada = false;
		posBola.x = 16.5 * map->getTileSize();
		posBola.y = 23 * map->getTileSize();
	}
	if (lanzada) {
		posBola.x += 8;
		posBola.y -= 8;
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));

}
void Bola::render()
{
	sprite->render();
}
void Bola::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}
void Bola::setPosition(const glm::vec2 &pos)
{
	posBola = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));
}

