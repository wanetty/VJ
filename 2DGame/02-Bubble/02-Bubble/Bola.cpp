#include "Bola.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flecha.h"
#include "Game.h"

# define M_PI 3.14159265358979323846
# define Bola_inipos_x 112
# define Bola_inipos_y 334

void Bola::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	
	spritesheet.loadFromFile("images/mapbolas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.333333333, 0.333333333), &spritesheet, &shaderProgram);
	lanzada = false;
	tileMapDispl = tileMapPos;
	direccion.x = 0;
	direccion.y = 0;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));

}
void Bola::update(int deltaTime)
{
	sprite->update(deltaTime);
	int TileBolax = (posBola.x) / 32;
	int TileBolay = (posBola.y) / 32;
	int Color = 1;
	if (Game::instance().getKey(32) && !lanzada) {
		lanzada = true;
		direccionx = cos(angulo);
		direcciony = sin(angulo);
	}
	else if (Game::instance().getKey('r')){
		lanzada = false;
		posBola.x = Bola_inipos_x;
		posBola.y = Bola_inipos_y;
		direccionx = 0;
		direcciony = 0;
	}
	if (posBola.y <= 0 ) {
		lanzada = false;
		map->set_bola(TileBolax, TileBolay, Color);
		posBola.x = Bola_inipos_x;
		posBola.y = Bola_inipos_y;
		direccionx = 0;
		direcciony = 0;

	}
	if (lanzada && !map->comprueba_posicion(TileBolax, TileBolay)) {
		lanzada = false;
		map->set_bola(TileBolax, TileBolay, Color);
		posBola.x = Bola_inipos_x;
		posBola.y = Bola_inipos_y;
		direccionx = 0;
		direcciony = 0;
	}
	if (lanzada) {
		if (posBola.x <=  0 || posBola.x > (8*32)-16) {
			direccionx *= -1;
		}	
		posBola.x -= direccionx *10.f;
		posBola.y -= direcciony *10.f;
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
void Bola::setDireccion(float x) {
	angulo = x;
}

