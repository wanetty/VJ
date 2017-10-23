#ifndef _TUBO_INCLUDE
#define _TUBO_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
class Tubo
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);


private:
	glm::ivec2 tileMapDispl, posTubo;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};
#endif // _TUBO_INCLUDE