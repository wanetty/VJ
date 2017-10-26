#ifndef _RUEDA_INCLUDE
#define _RUEDA_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
class Rueda
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime,float ang);
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);


private:
	glm::ivec2 tileMapDispl, posRueda;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	float angulo;
	int tiempo;
};
#endif // _RUEDA_INCLUDE