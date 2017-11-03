#ifndef _BOLA_INCLUDE
#define _BOLA_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Sprite_texture.h"
#include "Bub.h"

class Bola
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap, Bub *bub);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setDireccion(float x);
	void reincio_bola(int new_color);
	void set_color(const int colour);
	int get_lanzadas();
	bool get_lanzada();
	bool get_reinicio();
	void set_tilemapPos(const glm::ivec2 &tileMapPos);
	void set_pos_ini(const glm::ivec2 &suma);
	void update_aux(int deltaTime);
	
private:
	glm::ivec2 tileMapDispl,direccion, posini;
	glm::vec2 posBola;
	ShaderProgram shaderProgrambola;
	float direccionx,direcciony;
	Texture spritesheet;
	Sprite_texture *sprite;
	TileMap *map;
	float angulo;
	bool lanzada, elegido, reinicio;
	int color, numlanzadas, tiempo;
	Bub *bub;
};
#endif // _BOLA_INCLUDE

