#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "AssetManager.h"

int main()
{
	KE::Window window(1270, 720, "Kemet Engine");

	auto shader = KE::AssetManager::getInstance().loadShader("Shader", { "assets/shaders/vertex.txt", "assets/shaders/fragment.txt" });


	window.setWindowIcon("assets/images/pharaoh.png");

	KE::Mesh mesh(  
		{ {{0.f, 0.5f, 0.f}, {0.f, 1.f}}, {{0.5f, -0.5f, 0.f}, {1.f, 0.f}}, {{-0.5f, -0.5f, 0.f}, {0.f, 0.f}} },
		{ 0, 1, 2 }
	);

	KE::Transform transform;
	transform.setPosition(glm::vec3(0.f, 0.5, 0.f));
	transform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	transform.setRotation(glm::vec3(0.f, 0.f, 45.f));

	while (!window.shouldClose())
	{
		window.pollEvents();

		window.clear(255.f, 255.f, 0.f, 255.f);

		shader->useProgram();

		shader->setUniformMat4("uModel", transform.getTransformMatrix());

		mesh.draw();

		window.swapBuffers();
	}
}