#ifndef _SPRITE_TEXTURE_INCLUDE
#define _SPRITE_TEXTURE_INCLUDE

#include <vector>
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "AnimKeyframes.h"

class Sprite_texture
{
public:
	static Sprite_texture *createSpriteTexture(glm::vec2 geom[2], glm::vec2 texCoords[2], Texture *spritesheet,ShaderProgram *program);
	Sprite_texture(glm::vec2 geom[2], glm::vec2 texCoords[2], Texture *spritesheet, ShaderProgram *program);
	~Sprite_texture();


	void update(int deltaTime, bool loop);
	void render() const;
	void free();
	void setPosition(const glm::vec2 &pos);
	void setNumberAnimations(int nAnimations);
	void setAnimationSpeed(int animId, int keyframesPerSec);
	void addKeyframe(int animId, const glm::vec2 &frame);
	void changeAnimation(int animId);
	int animation() const;

private:
	Texture *texture;
	ShaderProgram *shaderProgram;
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::vec2 position;
	int currentAnimation, currentKeyframe, nanim;
	float timeAnimation;
	glm::vec2 texCoordDispl;
	vector<AnimKeyframes> animations;

};

#endif // _SPRITE_TEXTURE_INCLUDE