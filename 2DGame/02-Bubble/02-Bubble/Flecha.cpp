#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flecha.h"
#include "Game.h"

# define M_PI 3.14159265358979323846 /* pi */
# define grados (2*M_PI)/360


void Flecha::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	angulo = M_PI/2;
	spritesheet.loadFromFile("images/flecha.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(96, 48), glm::vec2(1, 1), &spritesheet, &shaderProgram);

	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlecha.x), float(tileMapDispl.y + posFlecha.y)));

}

void Flecha::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (angulo > (grados * 20))
			angulo -= (grados) * 5; //son 5 grados en radianes
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (angulo < M_PI - grados*20)
			angulo += (grados) * 5;
	}
}

void Flecha::render()
{
	sprite->render_flecha(angulo);
}

void Flecha::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Flecha::setPosition(const glm::vec2 &pos)
{
	posFlecha = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posFlecha.x), float(tileMapDispl.y + posFlecha.y)));
}