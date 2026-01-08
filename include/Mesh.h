#pragma once

#include <GL/glew.h>
#include <vector>
#include <cstdint>
#include <cstddef>
#include "Vertex.h"

namespace KE
{
	class Mesh
	{
	private:
		std::vector<Vertex> m_vertices{};
		std::vector<uint32_t> m_indices{};

		uint32_t m_vao{}, m_vbo{}, m_ibo{};
		void createMesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
		void destroyMesh();
	public:
		Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices);
		~Mesh() noexcept;

		void draw() const;

		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		Mesh(Mesh&& other);
		Mesh& operator=(Mesh&& other);

		const std::vector<Vertex>& getVertices() const { return m_vertices; }
		const std::vector<uint32_t>& getIndices() const { return m_indices; }
	};
}

