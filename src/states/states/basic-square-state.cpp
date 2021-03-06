#include "basic-square-state.h"
#include <GL/glew.h>
#include <imgui.h>
#include <states/states/menu-state.h>

namespace OpenGlExample::States
{
    BasicSquareState::BasicSquareState(Root &root)
        : State(root)
    {
        float positions[] =
        {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
            -0.5f, -0.5f
        };

        glGenBuffers(1, &vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

        glGenVertexArrays(1, &vertexArrayId);
        glBindVertexArray(vertexArrayId);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        shader = std::make_unique<Shader>("res/shader/basic-square/basic.shader");
        shader->bind();

        glClearColor(0, 0, 0, 0);
    }

    BasicSquareState::~BasicSquareState()
    {
        shader->unbind();
        glDeleteVertexArrays(1, &vertexArrayId);
        glDeleteBuffers(1, &vertexBufferId);
    }

    void BasicSquareState::render()
    {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void BasicSquareState::renderImGui()
    {
        ImGui::Begin("Basic Square");
        if(ImGui::Button("<-"))
        {
            root.createState<MenuState>();
        }
    }
}