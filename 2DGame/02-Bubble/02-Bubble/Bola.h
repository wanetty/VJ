#ifndef _BOLA_INCLUDE
#define _BOLA_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Sprite_texture.h"

class Bola
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setDireccion(float x);
	void reincio_bola();
	void set_color(const int colour);
	
private:
	glm::ivec2 tileMapDispl,direccion;
	glm::vec2 posBola;
	ShaderProgram shaderProgrambola;
	float direccionx,direcciony;
	Texture spritesheet;
	Sprite_texture *sprite;
	TileMap *map;
	float angulo;
	bool lanzada, elegido;
	int color,posbolsa;
};
#endif // _BOLA_INCLUDE

