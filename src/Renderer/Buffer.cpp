#include "Buffer.h"
namespace Aero
{
	//------------------------------------------------------------------------------------------------------------
	//VBO
	//------------------------------------------------------------------------------------------------------------

	 VertexBuffer::VertexBuffer(float* vertices, uint32_t size, GLenum drawType) 
	 {
		glCreateBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, drawType);
	}
	
	 VertexBuffer::VertexBuffer(std::vector<Vertex>vertices, uint32_t size, GLenum drawType)
	 {
		 glCreateBuffers(1, &vboID);
		 glBindBuffer(GL_ARRAY_BUFFER, vboID);
		 glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], drawType);
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

	void VertexBuffer::setLayout(const BufferLayout& Layout)
	{
		layout = Layout;
	}

	//------------------------------------------------------------------------------------------------------------
	//IBO
	//------------------------------------------------------------------------------------------------------------

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count, GLenum drawType)
	{
		bufferCount = count;
		glCreateBuffers(1, &iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(uint32_t), indices, drawType);
	}

	IndexBuffer::IndexBuffer(std::vector<uint32_t>indices, uint32_t count, GLenum drawType)
	{
		bufferCount = count;
		glCreateBuffers(1, &iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), &indices[0], drawType);
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

	//------------------------------------------------------------------------------------------------------------
	//VAO
	//------------------------------------------------------------------------------------------------------------

	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

	}

	VertexArray::VertexArray(VertexBuffer* VBO, IndexBuffer* IBO)
	{
		glCreateVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);

		setVertexBuffer(VBO);
		setIndexBuffer(IBO);

	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1,&vaoID);
	}

	void VertexArray::bind()
	{
		glBindVertexArray(vaoID);
	}

	void VertexArray::unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::setVertexBuffer(VertexBuffer* VBO)
	{
		glBindVertexArray(vaoID);
		VBO->bind();

		uint32_t elemindex = 0;
		
		for (const auto& element : VBO->getLayout())
		{
			glEnableVertexAttribArray(elemindex);
			glVertexAttribPointer(elemindex, element.getElementCount(), ShaderDataTypeToOpenGL(element.type),
				GL_FALSE, VBO->getLayout().getStride(), (void*)element.offset);
			elemindex++;
		}

		vbos.push_back(VBO);

	}

	void VertexArray::setIndexBuffer(IndexBuffer* IBO)
	{
		glBindVertexArray(vaoID);
		ibo = IBO;
		ibo->bind();


	}

}
