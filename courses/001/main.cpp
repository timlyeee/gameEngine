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


#include "view/View.h"
#include <iostream>


//Vertices for painting 2 triangles which is a rectangle
float vertices[] = {
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    
};
unsigned int indices[] = {
	0, 1, 3,
	1, 2, 3
};

float texCoords[] = {
	0.0f, 0.0f,
	1.0f, 0.0f, 
	0.5f, 1.0f 
};

const int WindowWidth{960};
const int WindowHeight{640};


int main() {

    View* view = new View(WindowWidth, WindowHeight);
	//init glad
	
    if (!view->init()) {
        return -1;
    }
//	//Render Border line
//	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
//	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//
//	// ====== Texture Filtering =========
//	//Read Texture
//	//Create Texture
//	int width, height, nrChannels;
//	stbi_set_flip_vertically_on_load(true);
//	unsigned char *data = stbi_load("../../images/container.jpg", &width, &height, &nrChannels, 0);
//	Texture tex1;
//	tex1.Initialize(data);
//	uint64_t texture1 = tex1.getTexture();
//	stbi_image_free(data);
//
//	data = stbi_load("../../images/awesomeface.png", &width, &height, &nrChannels, 0);
//	Texture tex2;
//	tex2.Initialize(data);
//	uint64_t texture2 = tex2.getTexture();
//	stbi_image_free(data);



	//VAO and VBO
//	unsigned int VBO;//VBO
//	glGenBuffers(1, &VBO);
//
//	//create and bind vao
//	unsigned int VAO;
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//	//Bind VBO vertices to buffer
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//

	//EBO
//	unsigned int EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	//set vertices properties
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	//set vertices color properties
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	//set texture properties
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);
//	std::cout << std::filesystem::current_path();
//	//compile shader to vertex shader, would be an id
//	Shader ourShader("../../include/courses/001/shader.vs", "../../include/courses/001/shader.fs");




	//init view port
	//when the size of window is changed, this callback will be triggered
	
	/*
	//uniform vec
	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	//glGetUniformLocation to search uniform ourColor's location
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

	*/

	// =====Texture Wrap method=====

//	ourShader.use();
//	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // Manually set shader as this
//	ourShader.setInt("texture2", 1); // or set it via texture class

	//main loop

//	while (!glfwWindowShouldClose(window)) {
//		//clear all
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);

		//bind texture on corresponding texture units
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, texture1);
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, texture2);



//		ourShader.use();


		//update uniform
		/*timeValue = glfwGetTime();
		greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		*/

//		glBindVertexArray(VAO);
//		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//input 
		//processInput(window);

		//change color buffer, stencil buffer
//		glfwSwapBuffers(window);
//
//		//mouse event, keyboard event
//		glfwPollEvents();
//	}
    while(!view->shouldClose()){
        view->renderLoop();
    }
    delete view;
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
    return 0;

}
