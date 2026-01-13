#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Camera.h"
#include "ShaderStorageBuffer.h"
#include "Renderer.h"
#include <iostream>

struct TransformGPU
{
	std::vector<glm::mat4> modelMatrices;
};

int main()
{
	KE::Window window(1270, 720, "Kemet Engine");

	auto shader = KE::AssetManager::getInstance().loadShader("Shader", { "assets/shaders/vertex.txt", "assets/shaders/fragment.txt" });
	auto texture = KE::AssetManager::getInstance().loadTexture("Brick", "assets/images/brick.png");

	window.setWindowIcon("assets/images/pharaoh.png");

	KE::Mesh mesh = KE::Mesh::generateCube();

	KE::Transform transform;
	transform.setPosition(glm::vec3(0.f, 0.5, 0.f));
	transform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	transform.setRotation(glm::vec3(0.f, 45.f, 0.f));
	
	KE::Transform secondTransform;
	secondTransform.setPosition(glm::vec3(0.5f, 0.5, 0.f));
	secondTransform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
	secondTransform.setRotation(glm::vec3(0.f, 45.f, 0.f));

	KE::Camera camera;
	camera.setAspect(window.getWidth(), window.getHeight());
	camera.setPosition({ 0.f, 0.f, 5.f });

	TransformGPU transformData;

	for (int i = 0; i < 1000; ++i)
	{
		KE::Transform transform;
		transform.setPosition(glm::vec3(static_cast<float>(i), 0.5, static_cast<float>(i)));
		transformData.modelMatrices.push_back(transform.getTransformMatrix());
	}

	KE::ShaderStorageBuffer<glm::mat4> transformSSBO(0, transformData.modelMatrices);

	while (!window.shouldClose())
	{
		std::cout << transformSSBO.getData().size() << "\n";

		transformData.modelMatrices[0] = glm::mat4(1.f);
		transformData.modelMatrices[0] = glm::translate(transformData.modelMatrices[0], glm::vec3(0.f, 0.f, -5.f));
		
		transformSSBO.uploadData(transformData.modelMatrices);

		window.pollEvents();

		window.clear(255.f, 255.f, 0.f, 255.f);

		shader->useProgram();

		shader->setUniformInt("uTexture", 0);
	
		glm::mat4 vp = camera.getProjectionMatrix() * camera.getViewMatrix();

		shader->setUniformMat4("uVP", vp);

		texture->bind(0);

		KE::Renderer::DrawInstanced(mesh, transformSSBO.getData().size());

		window.swapBuffers();
	}
}