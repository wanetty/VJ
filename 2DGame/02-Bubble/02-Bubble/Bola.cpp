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

void Bola::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap)
{
	
	spritesheet.loadFromFile("images/mapbolas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	map = tileMap;
	posbolsa = 0;
	shaderProgrambola = shaderProgram;
	tileMapDispl = tileMapPos;
	set_color(map->get_bola(posbolsa));
	++posbolsa;
	lanzada = false;
	direccion.x = 0;
	direccion.y = 0;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));

}
void Bola::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (Game::instance().getKey(32) && !lanzada) {
		lanzada = true;
		direccionx = cos(angulo);
		direcciony = sin(angulo);
	}
	if (lanzada) {
		glm::vec2 derecha = map->comprueba_derecha(posBola);
		glm::vec2 izquierda = map->comprueba_izquierda(posBola);
		glm::vec2 arriba = map->comprueba_arriba(posBola);
		if (derecha.x != -1 && derecha.y != -1) {
			lanzada = false;
			map->set_bola(derecha, color);
			this->reincio_bola();
		}
		else if (izquierda.x != -1 && izquierda.y != -1) {
			lanzada = false;
			map->set_bola(izquierda, color);
			this->reincio_bola();
		}
		else if (arriba.x != -1 && arriba.y != -1) {
			lanzada = false;
			map->set_bola(arriba, color);
			this->reincio_bola();
		}
		if (posBola.x <= 0 || posBola.x > (8 * 32) - 16) {
			direccionx *= -1;
		}
		posBola.x -= direccionx *10.f;
		posBola.y -= direcciony *10.f;
	}
	if (lanzada && posBola.y <= 0 ) {
		lanzada = false;
		map->set_bola(posBola, color);
		this->reincio_bola();

	}
	
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));

}
void Bola::reincio_bola() {
	set_color(map->get_bola(posbolsa));
	++posbolsa;
	if (map->get_sizebolsa() <= posbolsa) posbolsa = 0;
	posBola.x = Bola_inipos_x;
	posBola.y = Bola_inipos_y;
	direccionx = 0;
	direcciony = 0;
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
void Bola::set_color(const int colour) {
 	color = colour;
	glm::vec2 tambola[2] = { glm::vec2(0, 0), glm::vec2(32, 32) };
	glm::vec2 nbola[2]; //= { glm::vec2(0.3333, 0), glm::vec2(0.67, 0.3333) };
	glm::vec2 tileTexSize = glm::vec2(1.f / 3, 1.f / 3);
	nbola[0] = glm::vec2(float((color - 1) % 3) / 3, float((color - 1) / 3) / 3);
	nbola[1] = nbola[0] + tileTexSize;
	sprite = Sprite_texture::createSpriteTexture(tambola, nbola, &spritesheet, &shaderProgrambola);
}

