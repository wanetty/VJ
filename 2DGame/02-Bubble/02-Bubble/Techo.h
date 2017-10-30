#ifndef _TECHO_INCLUDE
#define _TECHO_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Sprite_texture.h"

class Techo
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, TileMap *tileMap);
	void update(int deltaTime);
	void render();
	int get_altura();
	void set_altura(int hight);

private:
	glm::ivec2 tileMapDispl, direccion, posini;
	glm::vec2 posBola;
	ShaderProgram shaderProgrambola;
	float direccionx, direcciony;
	Texture spritesheet;
	Sprite_texture *sprite;
	TileMap *map;
	int altura;
};
#endif 
