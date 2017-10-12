#ifndef _FLECHA_INCLUDE
#define _FLECHA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"





class Flecha
{
public:	
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 tileMapDispl, posFlecha;
	float angulo;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};


#endif // _FLECHA_INCLUDE

