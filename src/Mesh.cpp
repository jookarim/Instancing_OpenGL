#include "Mesh.h"

namespace KE
{
	void Mesh::createMesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
	{
		m_vertices = std::move(vertices);
		m_indices = std::move(indices);

		glCreateVertexArrays(1, &m_vao);
		glCreateBuffers(1, &m_vbo);
		glCreateBuffers(1, &m_ibo);

		glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(Vertex));
		glVertexArrayElementBuffer(m_vao, m_ibo);

		glNamedBufferData(m_vbo, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);
		glNamedBufferData(m_ibo, sizeof(uint32_t) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW);//corrected: used m_indices.data() not m_vertices.data()

		glEnableVertexArrayAttrib(m_vao, 0);
		glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_vao, 0, 0);

		glEnableVertexArrayAttrib(m_vao, 1);
		glVertexArrayAttribFormat(m_vao, 1, 2, GL_FLOAT, GL_FALSE, 12);
		glVertexArrayAttribBinding(m_vao, 1, 0);
	}

	void Mesh::destroyMesh()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);

		m_vao = m_vbo = m_ibo = 0;
	}

	Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint32_t>&& indices)
	{
		createMesh(std::move(vertices), std::move(indices));
	}

	Mesh::~Mesh() noexcept
	{
		destroyMesh();
	}

	void Mesh::draw() const
	{
		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
	}

	Mesh::Mesh(Mesh&& other) : m_vao(other.m_vao),
		m_vbo(other.m_vbo),
		m_ibo(other.m_ibo),
		m_vertices(std::move(other.m_vertices)),
		m_indices(std::move(other.m_indices))
	{
		other.m_vao = 0;
		other.m_vbo = 0;
		other.m_ibo = 0;
	}

	Mesh& Mesh::operator=(Mesh&& other)
	{
		if (this == &other) return *this;
		destroyMesh();

		m_vao = other.m_vao;
		m_vbo = other.m_vbo;
		m_ibo = other.m_ibo;
		m_vertices = std::move(other.m_vertices);
		m_indices = std::move(other.m_indices);

		other.m_vao = 0;
		other.m_vbo = 0;
		other.m_ibo = 0;

		return *this;
	}
}
