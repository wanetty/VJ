#ifndef _BOLA_INCLUDE
#define _BOLA_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Bola
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setDireccion(float x);
	
private:
	glm::vec2 tileMapDispl, posBola,direccion;
	float direccionx,direcciony;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float angulo;
	bool lanzada;

	
};
#endif // _BOLA_INCLUDE

