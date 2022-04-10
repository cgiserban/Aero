#include "Buffer.h"
namespace Aero
{
	//------------------------------------------------------------------------------------------------------------
	//VBO
	//------------------------------------------------------------------------------------------------------------

	 VertexBuffer::VertexBuffer(float* vertices, uint32_t size) 
	 {
		glCreateBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	inline VertexBuffer::~VertexBuffer() { glDeleteBuffers(1, &vboID); }

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
	}

	void VertexBuffer::unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//------------------------------------------------------------------------------------------------------------
	//IBO
	//------------------------------------------------------------------------------------------------------------

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count)
	{
		bufferCount = count;
		glCreateBuffers(1, &iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer() 
	{
		glDeleteBuffers(1, &iboID);
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	}
	void IndexBuffer::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	uint32_t IndexBuffer::getCount()
	{
		return bufferCount;
	}

}
