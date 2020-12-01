#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

// #define GLEW_BUILD
// #include <GL/glew.h>

// #include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray {
private:
  unsigned int m_RendererID;

public:
  // construtor
  VertexArray() { GlCall(glGenVertexArrays(1, &m_RendererID)); }

  // destrutor
  ~VertexArray() { GlCall(glDeleteVertexArrays(1, &m_RendererID)); }

  void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    Bind();
    vb.Bind();

    // layout
    const auto & elements = layout.GetElements();
    unsigned int offset   = 0;

    for (unsigned int i = 0; i < elements.size(); i++) {
      const auto &element = elements[i];

      GlCall(glEnableVertexAttribArray(i));
      GlCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                                   (const void *)offset));
      offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
  }

  void Bind() const { GlCall(glBindVertexArray(m_RendererID)); }
  void UnBind() const { GlCall(glBindVertexArray(0)); }
};

#endif
