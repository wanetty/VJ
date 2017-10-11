#ifndef _FONDO_INCLUDE
#define _FONDO_INCLUDE


#include "Sprite.h"
#include "TileMap.h"





class Fondo
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

private:
	
	glm::ivec2 tileMapDispl, posfondo;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

};

#endif // _FONDO_INCLUDE

