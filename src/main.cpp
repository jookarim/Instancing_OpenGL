#include "Window.h"
#include "Mesh.h"
#include "Shader.h"

int main()
{
	KE::Window window(1270, 720, "Kemet Engine");
	
	KE::Shader shader("", "");

	window.setWindowIcon("assets/images/pharaoh.png");

	while (!window.shouldClose())
	{
		window.pollEvents();
		//events

		window.clear(255.f, 255.f, 0.f, 255.f);

		//render
		window.swapBuffers();
	}
}