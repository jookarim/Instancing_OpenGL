#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Camera.h"

int main()
{
	KE::Window window(1270, 720, "Kemet Engine");

	auto shader = KE::AssetManager::getInstance().loadShader("Shader", { "assets/shaders/vertex.txt", "assets/shaders/fragment.txt" });
	auto texture = KE::AssetManager::getInstance().loadTexture("Brick", "assets/images/brick.png");


	window.setWindowIcon("assets/images/pharaoh.png");

	KE::Mesh mesh(  
		{ {{0.f, 0.5f, 0.f}, {0.f, 1.f}}, {{0.5f, -0.5f, 0.f}, {1.f, 0.f}}, {{-0.5f, -0.5f, 0.f}, {0.f, 0.f}} },
		{ 0, 1, 2 }
	);

	KE::Transform transform;
	transform.setPosition(glm::vec3(0.f, 0.5, 0.f));
	transform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	transform.setRotation(glm::vec3(0.f, 0.f, 45.f));
	
	KE::Camera camera;
	camera.setAspect(window.getWidth(), window.getHeight());
	camera.setPosition({ 0.f, 0.f, 10.f });

	while (!window.shouldClose())
	{
		window.pollEvents();

		window.clear(255.f, 255.f, 0.f, 255.f);

		shader->useProgram();

		shader->setUniformInt("uTexture", 0);
	
		glm::mat4 mvp = camera.getProjectionMatrix() * camera.getViewMatrix() * transform.getTransformMatrix();

		shader->setUniformMat4("uMVP", mvp);

		texture->bind(0);

		mesh.draw();

		window.swapBuffers();
	}
}