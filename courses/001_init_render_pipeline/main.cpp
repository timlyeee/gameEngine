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
	//Render Border line
	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glewInit();

	
	Texture tex1(true, false);
	tex1.Initialize("images/container.jpg");
	auto texture1 = tex1.getTexture();

	Texture tex2(false, true);
	tex2.Initialize("images/awesomeface.png");
	auto texture2 = tex2.getTexture();
	



	//VAO and VBO
	unsigned int VBO;//VBO
	glGenBuffers(1, &VBO);

	//create and bind vao
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	//Bind VBO vertices to buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//EBO
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set vertices properties
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//set vertices color properties
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//set texture properties
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	//compile shader to vertex shader, would be an id
	Shader ourShader("courses/001/shader.vs", "courses/001/shader.fs");
	ourShader.use();
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // Manually set shader as this
	ourShader.setInt("texture2", 1); // or set it via shader class

    while(!view->shouldClose()) {
        view->clear();
		//bind texture on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		
		ourShader.use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		view->swap();
    }
    delete view;
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
    return 0;

}
