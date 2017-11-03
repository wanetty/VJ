#ifndef _BUBINI_INCLUDE
#define _BUBINI_INCLUDE


#include "Sprite.h"

class BubIni
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram,int id);
	void update(int deltaTime);
	void render();
	void setPosition(const glm::vec2 &pos);

private:
	glm::ivec2 posBubIni;
	Texture spritesheet;
	Sprite *sprite;
};
#endif // _BUBINI_INCLUDE