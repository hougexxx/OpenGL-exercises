#include <iostream>
#include "glframework/core.h"
#include "glframework/shader.h"
#include "glframework/texture.h"
#include <string>
#include "Wrapper/check.h"
#include "Application/application.h"
#include "glframework/geometry.h"
#include "Application/camera/trackBallCameraControl.h"
#include "Application/camera/perspectiveCamera.h"

PerspectiveCamera* camera = nullptr;
TrackBallCameraControl* cameraControl = nullptr;

using namespace std;

Shader* shader = nullptr;
GLuint VAO = 0;

Texture* hello_texture = nullptr;

Geometry* geometry;

glm::mat4 transform_makima(1.0f);
glm::mat4 transform_hello(1.0f);

glm::mat4 viewMatrix(1.0f);
glm::mat4 perspectiveMatrix(1.0f);

void OnResize(int width, int height) {
	GL_CALL(glViewport(0, 0, width, height));
	std::cout << "OnResize" << std::endl;
}

void OnMouse(int button, int action, int mods) {
	double x, y;
	app->getCursorPostion(&x, &y);
	cameraControl->onMouse(button, action, x, y);
}

void OnKey(int key, int action, int mods) {
	cameraControl->onKey(key, action, mods);
}

void OnCursor(double xpos, double ypos) {

	cameraControl->onCursor(xpos, ypos);
}

void OnScroll(double offset) {
	cameraControl->onScroll(offset);
}

void prepareCamera() {
	camera = new PerspectiveCamera(glm::radians(60.0f), (float)app->getWidth() / (float)app->getHeight(), 1.0f, 1000.0f);
	cameraControl = new TrackBallCameraControl();
	cameraControl->setCamera(camera);
}

void prepareShader() {
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}

void prepareTexture() {
	hello_texture = new Texture("assets/textures/hello.jpg", 1);
}

void prepareVAO() {
	//geometry =  Geometry::createBox(0.02f);
	geometry = Geometry::createSphere(0.02f);
}

void prepareState() {
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	// glClearDepth(0.7f); //设置清理画布时候的深度缓存值
}

void render() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT));
	//使用当前的program
	shader->begin();
	shader->setMatrix4x4("transform", transform_makima);
	shader->setMatrix4x4("viewMatrix", camera->getViewMatrix());
	shader->setMatrix4x4("projectionMatrix", camera->getProjectionMatrix());
  
	hello_texture->bind();	                //active  &  bind  -> texture unit  
	shader->setInt("hello_sampler", 1);  	//set sampler      -> texture unit

	//VAO(array)->>   posVBO(position)  colorVBO(color)  EBO(index)   uv(texture)    
	GL_CALL(glBindVertexArray(geometry->getVao()));
	glDrawElements(GL_TRIANGLES, geometry->getIndicesCount(), GL_UNSIGNED_INT, 0);


	shader->end();
}

int main() {
	
	app->test(); 
	app->init(1920, 1080);//窗口
	app->setResizeCallback(OnResize);
	app->setKeyCallback(OnKey);
	app->setMouseCallback(OnMouse);
	app->setCursorCallback(OnCursor);
	app->setMouseScrollCallback(OnScroll);

	//set viewport and color
	glViewport(0, 0, 1920, 1080);//视口
	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

	//三角形绘制
	prepareTexture();
	prepareShader();
	prepareVAO();
	prepareCamera();
	prepareState();

	//窗体循环
	while (app->update()) {
		render();
	}

	app->destory();
	return 0;
}

