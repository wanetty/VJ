#include "Bola.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flecha.h"
#include "Game.h"
#include "Bub.h"

# define M_PI 3.14159265358979323846
# define Bola_inipos_x 112
# define Bola_inipos_y 334
# define Time_limite 84500

void Bola::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap, Bub *b)
{
	
	spritesheet.loadFromFile("images/mapbolas.png", TEXTURE_PIXEL_FORMAT_RGBA);
	map = tileMap;
	bub = b;
	shaderProgrambola = shaderProgram;
	tileMapDispl = tileMapPos;
	//set_color(map->get_bola());
	glm::vec2 tambola[2] = { glm::vec2(0, 0), glm::vec2(32, 32) };
	glm::vec2 nbola[2]; //= { glm::vec2(0.3333, 0), glm::vec2(0.67, 0.3333) };
	glm::vec2 tileTexSize = glm::vec2(1.f / 3, 1.f / 3);
	nbola[0] = glm::vec2(float((color - 1) % 3) / 3, float((color - 1) / 3) / 3);
	nbola[1] = nbola[0] + tileTexSize;
	sprite = Sprite_texture::createSpriteTexture(tambola, nbola, &spritesheet, &shaderProgrambola);
	lanzada = false;
	direccion.x = 0;
	direccion.y = 0;
	numlanzadas = 0;
	tiempo = 0;
	posini.x = Bola_inipos_x;
	posini.y = Bola_inipos_y;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));
	elegido = false;
	reinicio = false;
}
void Bola::update(int deltaTime)
{
	sprite->update(deltaTime,false);
	tiempo += deltaTime;
	if ((Game::instance().getKey(32) || tiempo > Time_limite) && !lanzada) {
		lanzada = true;
		bub->setLanzada(lanzada);
		direccionx = cos(angulo);
		direcciony = sin(angulo);
		tiempo = 0;
		++numlanzadas;
	}
	if (lanzada) {
		if (lanzada && posBola.y <= 0) {
			bub->setLanzada(false);
			elegido = true;
			map->set_bola(posBola, color);
			map->comprueba_bolas(posBola, color);
			reinicio = true;
		}
		glm::vec2 derecha = map->comprueba_derecha(posBola);
		if (derecha.x != -1 && derecha.y != -1 && !elegido) {
			bub->setLanzada(false);
			elegido = true;
			map->set_bola(derecha, color);
			map->comprueba_bolas(derecha,color);
			reinicio = true;
		}
		glm::vec2 izquierda = map->comprueba_izquierda(posBola);
		if (izquierda.x != -1 && izquierda.y != -1 && !elegido) {
			bub->setLanzada(false);
			elegido = true;
			map->set_bola(izquierda, color);
			map->comprueba_bolas(izquierda, color);
			reinicio = true;
		}
		glm::vec2 arriba_iz = map->comprueba_arriba_izquierda(posBola);
		if (arriba_iz.x != -1 && arriba_iz.y != -1 && !elegido) {
			bub->setLanzada(false);
			elegido = true;
			map->set_bola(arriba_iz, color);
			map->comprueba_bolas(arriba_iz, color);
			reinicio = true;
		}
		glm::vec2 arriba_der = map->comprueba_arriba_derecha(posBola);
		if (arriba_der.x != -1 && arriba_der.y != -1 && !elegido) {
			bub->setLanzada(false);
			elegido = true;
			map->set_bola(arriba_der, color);
			map->comprueba_bolas(arriba_der, color);
			reinicio = true;
		}
		
		if (posBola.x <= 0 || posBola.x > (8 * 32)-32) {
			direccionx *= -1;
		}
		posBola.x -= direccionx *15.f;
		posBola.y -= direcciony *15.f;
	}
	
	elegido = false;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));

}
void Bola::set_tilemapPos(const glm::ivec2 &tileMapPos) {
	tileMapDispl = tileMapPos;
}
void Bola::reincio_bola(int new_color) {
	set_color(new_color);
	posBola = posini;
	direccionx = 0;
	direcciony = 0;
	lanzada = false;
	reinicio = false;
	tiempo = 0;
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
int Bola::get_lanzadas() {
	return numlanzadas;
}
void Bola::set_pos_ini(const glm::ivec2 &suma) {
	posini += suma;
}
bool Bola::get_lanzada() {
	return lanzada;
}
bool Bola::get_reinicio() {
	return reinicio;
}
void Bola::update_aux(int deltaTime) {
	sprite->update(deltaTime,false);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posBola.x), float(tileMapDispl.y + posBola.y)));
}

