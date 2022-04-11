#pragma once
#include "GL/glew.h"
#include <cstdint>
#include <string>
#include <vector>
#include <initializer_list>
#include "Core/Log.h"

namespace Aero
{

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4, Mat3, Mat4
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:				return 4;
			case ShaderDataType::Float2:			return 4 * 2;
			case ShaderDataType::Float3:			return 4 * 3;
			case ShaderDataType::Float4:			return 4 * 4;
			
			case ShaderDataType::Int:				return 4;
			case ShaderDataType::Int2:				return 4 * 2;
			case ShaderDataType::Int3:				return 4 * 3;
			case ShaderDataType::Int4:				return 4 * 4;

			case ShaderDataType::Mat3:				return 4 * 3 * 3;
			case ShaderDataType::Mat4:				return 4 * 4 * 4;
		}

		AERO_CLIENT_ERROR("Unknown Shader Data Type!");
		return 0;

	}


	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:				return GL_FLOAT;
			case ShaderDataType::Float2:			return GL_FLOAT;
			case ShaderDataType::Float3:			return GL_FLOAT;
			case ShaderDataType::Float4:			return GL_FLOAT;

			case ShaderDataType::Int:				return GL_INT;
			case ShaderDataType::Int2:				return GL_INT;
			case ShaderDataType::Int3:				return GL_INT;
			case ShaderDataType::Int4:				return GL_INT;

			case ShaderDataType::Mat3:				return GL_FLOAT;
			case ShaderDataType::Mat4:				return GL_FLOAT;
		}

		AERO_CLIENT_ERROR("Unknown Shader Data Type for conversion!");
		return 0;
	}

	struct BufferElement
	{
	
		std::string name;
		uint32_t size;
		uint32_t offset;
		ShaderDataType type;


		BufferElement(ShaderDataType Type, const std::string& Name) :
			name(Name), type(Type), size(ShaderDataTypeSize(Type)), offset(0) {}
		
		uint32_t getElementCount() const
		{
			switch (type)
			{
				case ShaderDataType::Float:				return 1;
				case ShaderDataType::Float2:			return 2;
				case ShaderDataType::Float3:			return 3;
				case ShaderDataType::Float4:			return 4;

				case ShaderDataType::Int:				return 1;
				case ShaderDataType::Int2:				return 2;
				case ShaderDataType::Int3:				return 3;
				case ShaderDataType::Int4:				return 4;

				case ShaderDataType::Mat3:				return 3 * 3;
				case ShaderDataType::Mat4:				return 4 * 4;
			}

			AERO_CLIENT_ERROR("Unknown Shader Data Type!");
			return 0;

		};

	};

	class BufferLayout
	{
	public:
		BufferLayout(){}

		BufferLayout(const std::initializer_list<BufferElement>& Elements) :
			elements(Elements) 
		{
			computeStrideAndOffset();
		}

		const std::vector<BufferElement>& getElements() const { return elements; }
		uint32_t getStride() const{ return elementsStride; }

		std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		std::vector<BufferElement>::iterator end() { return elements.end(); }
	
		std::vector<BufferElement>::const_iterator begin() const { return elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements.end(); }

	private:

		void computeStrideAndOffset()
		{
			uint32_t off = 0;
			elementsStride = 0;
			for (auto& elem : elements)
			{
				elem.offset = off;
				off += elem.size;
				elementsStride += elem.size;
			}
		}

	private:
		std::vector<BufferElement> elements;
		uint32_t elementsStride;

	};



	class VertexBuffer
	{
	public:
		VertexBuffer(float* vertices, uint32_t size, GLenum drawType);
		~VertexBuffer();

		void bind();
		void unbind();
		void setLayout(const BufferLayout& Layout);
		const BufferLayout& getLayout() { return layout; };

	private:
		uint32_t vboID;
		BufferLayout layout;

	};

	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t count, GLenum drawType);
		~IndexBuffer();

		void bind();
		void unbind();
		uint32_t getCount();
		
	private:
		uint32_t iboID;
		uint32_t bufferCount;
	};

	class VertexArray
	{
	public:

		VertexArray();
		~VertexArray();

		void bind();
		void unbind();

	private:
		uint32_t vaoID;
	};


}