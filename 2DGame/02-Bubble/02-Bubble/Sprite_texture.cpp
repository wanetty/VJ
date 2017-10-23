#include "Sprite_texture.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>



Sprite_texture *Sprite_texture::createSpriteTexture(glm::vec2 geom[2], glm::vec2 texCoords[2], Texture *spritesheet, ShaderProgram *program)
{
	Sprite_texture *quad = new Sprite_texture(geom, texCoords, spritesheet, program);

	return quad;
}

Sprite_texture::Sprite_texture(glm::vec2 geom[2], glm::vec2 texCoords[2], Texture *spritesheet, ShaderProgram *program)
{
	float vertices[24] = { geom[0].x, geom[0].y, texCoords[0].x, texCoords[0].y,
		geom[1].x, geom[0].y, texCoords[1].x, texCoords[0].y,
		geom[1].x, geom[1].y, texCoords[1].x, texCoords[1].y,
		geom[0].x, geom[0].y, texCoords[0].x, texCoords[0].y,
		geom[1].x, geom[1].y, texCoords[1].x, texCoords[1].y,
		geom[0].x, geom[1].y, texCoords[0].x, texCoords[1].y };
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program->bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program->bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void *)(2 * sizeof(float)));
	texture = spritesheet;
	shaderProgram = program;
	currentAnimation = -1;
}


Sprite_texture::~Sprite_texture()
{
}
void Sprite_texture::update(int deltaTime)
{
	if (currentAnimation >= 0)
	{
		timeAnimation += deltaTime;
		while (timeAnimation > animations[currentAnimation].millisecsPerKeyframe)
		{
			timeAnimation -= animations[currentAnimation].millisecsPerKeyframe;
			currentKeyframe = (currentKeyframe + 1) % animations[currentAnimation].keyframeDispl.size();
		}
		texCoordDispl = animations[currentAnimation].keyframeDispl[currentKeyframe];
	}
}
void Sprite_texture::render() const
{
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.f));
	shaderProgram->setUniformMatrix4f("modelview", modelview);
	shaderProgram->setUniform2f("texCoordDispl", texCoordDispl.x, texCoordDispl.y);
	glEnable(GL_TEXTURE_2D);
	texture->use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_TEXTURE_2D);
}
void Sprite_texture::free()
{
	glDeleteBuffers(1, &vbo);
}
void Sprite_texture::setPosition(const glm::vec2 &pos)
{
	position = pos;
}