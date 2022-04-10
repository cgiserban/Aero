#pragma once
#include "GL/glew.h"

#include <cstdint>

namespace Aero
{
	class VertexBuffer
	{
	public:
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void bind();
		void unbind();

	private:
		uint32_t vboID;


	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count);
		~IndexBuffer();

		void bind();
		void unbind();
		uint32_t getCount();
		
	private:
		uint32_t iboID;
		uint32_t bufferCount;
	};



}