#include <GL/glew.h>
#include <cstdint>

namespace KE
{
	class Mesh;

	class Renderer
	{
	private:
		Renderer() = default;
		~Renderer() = default;

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;
	public:
		static void DrawInstanced(Mesh& mesh, uint32_t count);
	};
}