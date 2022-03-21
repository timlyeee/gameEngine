/**
 * @file main001.cpp
 * @author Timlyeee
 * @brief THIS FILE IS WRITTEN FOR AND ONLY FOR CODING PRACTICE. 
 * SHOULD NOT BE USED ON COMMERCIAL REGION.
 * Course 001: Create a rectangle with 2 different texture, image read by stb_image.
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 */

#include "renderer/Texture.h"
#include "view/View.h"
#include <iostream>
#include "shaders/Shader.h"

static void processInput(GLFWwindow *window, glm::vec3 &camPos, glm::vec3 &camFront, glm::vec3 &camUp, float &cameraSpeed) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camPos += cameraSpeed * camFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camPos -= cameraSpeed * camFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camPos -= glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camPos += glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
}

//Vertices for painting 2 triangles which is a rectangle
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
// world space positions of our cubes
// glm::vec3 cubePositions[] = {
// 	glm::vec3(0.0f,  0.0f,  0.0f),
// 	glm::vec3(2.0f,  5.0f, -15.0f),
// 	glm::vec3(-1.5f, -2.2f, -2.5f),
// 	glm::vec3(-3.8f, -2.0f, -12.3f),
// 	glm::vec3(2.4f, -0.4f, -3.5f),
// 	glm::vec3(-1.7f,  3.0f, -7.5f),
// 	glm::vec3(1.3f, -2.0f, -2.5f),
// 	glm::vec3(1.5f,  2.0f, -2.5f),
// 	glm::vec3(1.5f,  0.2f, -1.5f),
// 	glm::vec3(-1.3f,  1.0f, -1.5f)
// };


unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};


const int WindowWidth{800};
const int WindowHeight{600};


int main() {
	
    View* view = new View(WindowWidth, WindowHeight);
	//init glad

	
	glfwSetInputMode(view->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!view->init()) {
        return -1;
    }
	//Render Border line
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	
	glEnable(GL_DEPTH_TEST);
	
	Texture tex1(true, false);
	tex1.Initialize("E:/EG/petitEngine/images/container.jpg");
	auto texture1 = tex1.getTexture();

	Texture tex2(false, true);
	tex2.Initialize("E:/EG/petitEngine/images/awesomeface.png");
	auto texture2 = tex2.getTexture();
	
	//VAO and VBO
	unsigned int VBO;//VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int lightingVAO;
	glGenVertexArrays(1, &lightingVAO);
	glBindVertexArray(lightingVAO);
	//set vertices properties
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);





	//create and bind vao
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//Bind VBO vertices to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//

	//set vertices properties
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//set normal properties
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	//compile shader to vertex shader, would be an id. object shader
	Shader lightingShader("E:/EG/petitEngine/courses/007_material/shader_lighting.vs", "E:/EG/petitEngine/courses/007_material/shader_lighting.fs");	

	// =====Texture Wrap method=====

	lightingShader.use();

	// create transformations
	glm::mat4 projection = glm::perspective(glm::radians(View::camera.Zoom), (float)WindowWidth/(float)WindowHeight, 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(0.0f, (float)WindowWidth, 0.0f, (float)WindowHeight, 0.1f, 100.0f);//ortho projection

	glm::mat4 viewMat = glm::mat4(1.0f);
	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	//viewMat = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
	//	glm::vec3(0.0f,0.0f,0.0f),
	//	glm::vec3(0.0f,1.0f,0.0f));

	viewMat = View::camera.GetViewMatrix();

	
	lightingShader.setMat4("projection", projection);
	lightingShader.setMat4("view", viewMat);


	Shader objectShader("E:/EG/petitEngine/courses/007_material/shader.vs", "E:/EG/petitEngine/courses/007_material/shader.fs");
	objectShader.use();
	objectShader.setMat4("projection", projection);
	objectShader.setMat4("view", viewMat);

	//Set material
	objectShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
	objectShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
	objectShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
	objectShader.setFloat("material.shininess", 32.0f);

	objectShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	objectShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f); // �����յ�����һЩ�Դ��䳡��
	objectShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

	objectShader.setVec3("light.position", lightPos);

	//delta time
	float currentFrame = glfwGetTime();
	float lastFrame = currentFrame;
	float deltaTime = currentFrame - lastFrame;
	float cameraSpeed = 2.5f * deltaTime;
	while(!view->shouldClose()) {
		view->clear();

		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		cameraSpeed = 2.5f * deltaTime;
		glfwPollEvents();
		processInput(view->getWindow(), View::camera.Position, View::camera.Front, View::camera.Up, cameraSpeed);
		projection = glm::perspective(glm::radians(View::camera.Zoom), (float)WindowWidth / (float)WindowHeight, 0.1f, 100.0f);
		lightingShader.setMat4("projection", projection);
		// camera/view transformation
		glm::mat4 viewMat = View::camera.GetViewMatrix();
		lightingShader.setMat4("view", viewMat);
        
		//bind texture on corresponding texture units



		// get matrix's uniform location and set matrix
		lightingShader.use();
		glBindVertexArray(lightingVAO);
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		//float angle = 20.0f * i;
		//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		lightingShader.setMat4("model", model);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		objectShader.setMat4("projection", projection);
		objectShader.setMat4("view", viewMat);
		objectShader.setVec3("viewPos", View::camera.Position);
		objectShader.use();
		glBindVertexArray(VAO);
		glm::mat4 objectModel = glm::mat4(1.0f);
		objectModel = glm::translate(objectModel, glm::vec3(0.0f));
		objectShader.setMat4("model", objectModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		view->swap();
    }
    delete view;
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
    return 0;

}
