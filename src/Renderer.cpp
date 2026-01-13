#include "Renderer.h"
#include "Mesh.h"

namespace KE
{
	void Renderer::DrawInstanced(Mesh& mesh, uint32_t count)
	{
		mesh.bind();
		glDrawElementsInstanced(GL_TRIANGLES, mesh.getIndices().size(), GL_UNSIGNED_INT, nullptr, count);
	}
}
