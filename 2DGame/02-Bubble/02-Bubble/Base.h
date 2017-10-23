#ifndef _BASE_INCLUDE
#define _BASE_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
class Base
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);


private:
	glm::ivec2 tileMapDispl, posBase;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};
#endif // _BASE_INCLUDE


