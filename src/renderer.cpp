#include <renderer.hpp>

void renderDebug() {
	ImGui::LabelText("FPS", std::to_string(fps).c_str());
	ImGui::SliderInt("FOV", &fov, 30, 90);
	ImGui::SliderInt("Speed", &speed, 3, 50);
	ImGui::SliderFloat("Sensitivity", &sensitivity, 0.01f, 0.1f);
	ImGui::SliderInt("Render Distance", &renderDistance, 2, 8);
}

void render(GLFWwindow* window, World* world, Camera* camera, Debug* debug) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLenum err = glGetError();
	if(err != GL_NO_ERROR) std::cout << "OpenGL Error -> " << err << std::endl;
	glEnable(GL_DEPTH_TEST);
	world->render(window, camera);
	glDisable(GL_DEPTH_TEST);
	if(debugMode) {
		debug->begin();
		debug->render("Debug", renderDebug);
		debug->end();
	}
}
