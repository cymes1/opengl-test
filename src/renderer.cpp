#include "renderer.h"

void Renderer::clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArray &vertexArray, const IndexBuffer &indexBuffer, const Shader &shader) const
{
    shader.bind();
    vertexArray.bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}
