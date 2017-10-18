#include "Mapa.h"



Mapa::Mapa(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{


}
void Mapa:: render() const {
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void Mapa:: free() {
	glDeleteBuffers(1, &vbo);
}

Mapa::~Mapa()
{
}
