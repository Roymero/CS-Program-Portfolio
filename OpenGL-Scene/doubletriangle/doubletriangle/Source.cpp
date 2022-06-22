#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>

#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"camera.h"

// Roy Romero
// Click and Hold the left mouse button down and you can use the mouse to look around:
// You can also control the camera with these buttons
// W for forward
// S for backwards
// A for left
// D for right
// Q for up
// E for down
// P to switch camera view between Orthographic and perspective. 
// Scroll the mousewheel up to increase camera speed
// Scroll the mousewheel down to decrease camera speed.
// Esc to close window
// This project has relative paths
// zoom out to see full scene


const unsigned int width = 800;
const unsigned int height = 800;


GLfloat vertices[] = 
{ //     X,   Y,    Z       /        Colors      /   TexCoord  /          Normals
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side


	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};


GLfloat vertices2[] = {

	-0.1f, 0.0f,  0.1f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.1f, 0.0f,  0.1f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.1f, 0.0f,  0.1f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.3f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side


	-0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.3f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.1f, 0.0f, -0.1f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.1f, 0.0f,  0.1f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.3f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.1f, 0.0f,  0.1f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.1f, 0.0f,  0.1f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.3f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // 


};



GLfloat VerticesRect[]{

	-0.1f, -0.9f,  0.1f,    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,     0.0f, 0.5f, 0.8f, //left bottom front
	-0.1f, -0.9f, -0.1f,    0.0f, 1.0f, 0.0f,	5.0f, 0.0f,     0.0f, 0.5f,  -0.8f, //left bottom rear

	 0.1f, -0.9f, -0.1f,    0.0f, 0.0f, 1.0f,	0.0f, 0.0f,    0.0f, 0.5f,  -0.8f, //right bottom rear
	 0.1f, -0.9f,  0.1f,    1.0f, 1.0f, 1.0f,	5.0f, 0.0f,    0.0f, 0.5f,  0.8f,  // right bottom front

	-0.1f,  0.1f,  0.1f,    1.0f, 1.0f, 1.0f,	5.0f, 0.0f,    0.0f, 0.5f,  0.8f, // left upper front
	-0.1f,  0.1f, -0.1f,    0.0f, 1.0f, 0.0f,	0.0f, 0.0f,     0.0f, 0.5f,  -0.8f, // left upper rear

	 0.1f,  0.1f, -0.1f,    0.0f, 1.0f, 0.0f,	5.0f, 0.0f,     0.0f, 0.5f, - 0.8f, //right upper rear
	 0.1f,  0.1f,  0.1f,    0.0f, 1.0f, 0.0f,	0.0f, 0.0f,     0.0f, 0.5f,  0.8f, // right upper front




};

GLfloat VerticesPlane[]{

	-1.5f, -0.1f,  1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,    0.0f, 0.0f, 0.0f,
	-1.5f, -0.1f, -1.0f,    0.0f, 1.0f, 0.0f,    5.0f, 0.0f,    0.0f, 0.0f, 0.0f,
	 1.5f, -0.1f, -1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, 0.0f,
	 1.5f, -0.1f,  1.0f,    1.0f, 1.0f, 1.0f,    5.0f, 0.0f,    0.0f, 0.0f, 0.0f,
	-1.5f,  0.1f,  1.0f,    1.0f, 1.0f, 1.0f,    2.5f, 5.0f,    0.0f, 0.0f, 0.0f,
	-1.5f,  0.1f, -1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, 0.0f,
	 1.5f,  0.1f, -1.0f,    1.0f, 1.0f, 1.0f,    5.0f, 0.0f,    0.0f, 0.0f, 0.0f,
	 1.5f,  0.1f,  1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 0.0f,    0.0f, 0.0f, 0.0f,
};



GLuint IndicesRect[]{

	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7

};

// Indices for vertices order
GLuint indices[] =
{

	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side

};



GLfloat lightVertices[] =
{
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f


};

GLuint lightIndices[] =
{

	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7


};




// scroll input, I couldn't figure out how to keep scrollback inside my camera class

double multiplier = 2.0;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	if (yoffset >= 1.0f) {
		multiplier = 5.0;
	}
	if (yoffset <= -1.0f) {
		multiplier = 2.0;
	}
}
bool viewChange = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		if (viewChange == true) {
			viewChange = false;
		}
		else if (viewChange == false) {
			viewChange = true;
		}
	}
}

int main()
{
	// Initialize GLFWS
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "Final Project", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	glfwSetScrollCallback(window, scroll_callback);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);
	// boolean to switch camera



	// Generates Shader object using shaders default.vert and default.frag
	shader shaderProgram("default.vert", "default.frag");

	



	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO1.unbind();
	VBO1.unbind();
	EBO1.unbind();

	// Working on some lighting but using this shader class to color the rectangle part of my object.

	shader lightShader("light.vert", "light.frag");


	// Generates Vertex Buffer Object and links it to vertices
	VAO lightVAO;
	lightVAO.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));

	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));

	// Linking attributes
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);


	lightVAO.unbind();
	lightVBO.unbind();
	lightEBO.unbind();


	glm::vec4 lightColor = glm::vec4(4.0f, 1.2f, 0.0f, 1.0f);

	glm::vec3 lightPos = glm::vec3(0.5f, 1.2f, 1.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 pyramidPos = glm::vec3(0.0f, -0.2f, 0.0f);
	glm::mat4 pyramidModel = glm::mat4(1.0f);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	shaderProgram.activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	//second pyramid top


	shader shaderProgram2("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO2;
	VAO2.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO2(vertices2, sizeof(vertices2));
	// Generates Element Buffer Object and links it to indices
	EBO EBO2(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO2.LinkAttrib(VBO2, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO2.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO2.LinkAttrib(VBO2, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO2.unbind();
	VBO2.unbind();
	EBO2.unbind();


	// Next Cube

	shader lightShader2("light.vert", "light.frag");


	// Generates Vertex Buffer Object and links it to vertices
	VAO lightVAO2;
	lightVAO2.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO2(lightVertices, sizeof(lightVertices));

	// Generates Element Buffer Object and links it to indices
	EBO lightEBO2(lightIndices, sizeof(lightIndices));

	// Linking attributes
	lightVAO2.LinkAttrib(lightVBO2, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);


	lightVAO2.unbind();
	lightVBO2.unbind();
	lightEBO2.unbind();


	glm::vec4 lightColor2 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glm::vec3 lightPos2 = glm::vec3(-1.5f, -0.5f, 1.5f);
	glm::mat4 lightModel2 = glm::mat4(1.0f);
	lightModel2 = glm::translate(lightModel2, lightPos2);


	glm::vec3 pyramidPos2 = glm::vec3(-1.0f, 0.8f, -0.5f);
	glm::mat4 pyramidModel2 = glm::mat4(1.0f);
	pyramidModel2 = glm::translate(pyramidModel2, pyramidPos2);


	lightShader2.activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader2.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel2));
	glUniform4f(glGetUniformLocation(lightShader2.ID, "lightColor"), lightColor2.x, lightColor2.y, lightColor2.z, lightColor2.w);

	
	shaderProgram2.activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram2.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel2));
	glUniform4f(glGetUniformLocation(shaderProgram2.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram2.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	
	// Third Pyramid Head


	shader shaderProgram3("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO3;
	VAO3.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO3(vertices2, sizeof(vertices2));
	// Generates Element Buffer Object and links it to indices
	EBO EBO3(indices, sizeof(indices));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO3.LinkAttrib(VBO3, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO3.LinkAttrib(VBO3, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO3.LinkAttrib(VBO3, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO3.unbind();
	VBO3.unbind();
	EBO3.unbind();


	glm::vec3 pyramidPos3 = glm::vec3(1.0f, 0.8f, -0.5f);
	glm::mat4 pyramidModel3 = glm::mat4(1.0f);
	pyramidModel3 = glm::translate(pyramidModel3, pyramidPos3);

	shaderProgram3.activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram3.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel3));
	glUniform4f(glGetUniformLocation(shaderProgram3.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram3.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	shader shaderProgram4("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO4;
	VAO4.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO4(VerticesRect, sizeof(VerticesRect));
	// Generates Element Buffer Object and links it to indices
	EBO EBO4(IndicesRect, sizeof(IndicesRect));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO4.LinkAttrib(VBO4, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO4.LinkAttrib(VBO4, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO4.LinkAttrib(VBO4, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO4.unbind();
	VBO4.unbind();
	EBO4.unbind();


	glm::vec3 rectPos1 = glm::vec3(1.0f, 0.7f, -0.5f);
	glm::mat4 rectModel1 = glm::mat4(1.0f);
	rectModel1 = glm::translate(rectModel1, rectPos1);

	shaderProgram4.activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram4.ID, "model"), 1, GL_FALSE, glm::value_ptr(rectModel1));
	glUniform4f(glGetUniformLocation(shaderProgram4.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram4.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	shader shaderProgram5("default.vert", "default.frag");



	// Generates Vertex Array Object and binds it
	VAO VAO5;
	VAO5.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO5(VerticesRect, sizeof(VerticesRect));
	// Generates Element Buffer Object and links it to indices
	EBO EBO5(IndicesRect, sizeof(IndicesRect));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO5.LinkAttrib(VBO5, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO5.LinkAttrib(VBO5, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO5.LinkAttrib(VBO5, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

	// Unbind all to prevent accidentally modifying them
	VAO5.unbind();
	VBO5.unbind();
	EBO5.unbind();


	glm::vec3 rectPos2 = glm::vec3(-1.0f, 0.7f, -0.5f);
	glm::mat4 rectModel2 = glm::mat4(1.0f);
	rectModel2 = glm::translate(rectModel2, rectPos2);

	shaderProgram5.activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram5.ID, "model"), 1, GL_FALSE, glm::value_ptr(rectModel2));
	glUniform4f(glGetUniformLocation(shaderProgram5.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram5.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);





	shader shaderProgram6("default.vert", "default.frag");

	VAO VAO6;
	VAO6.bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO6(VerticesPlane, sizeof(VerticesPlane));
	// Generates Element Buffer Object and links it to indices
	EBO EBO6(IndicesRect, sizeof(IndicesRect));

	// Links VBO attributes such as coordinates and colors to VAO
	VAO6.LinkAttrib(VBO6, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO6.LinkAttrib(VBO6, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO6.LinkAttrib(VBO6, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
					   
	// Unbind all to prevent accidentally modifying them
	VAO6.unbind();
	VBO6.unbind();
	EBO6.unbind();


	glm::vec3 rectPos3 = glm::vec3(0.0f, -0.3f, -0.2f);
	glm::mat4 rectModel3 = glm::mat4(1.0f);
	rectModel3 = glm::translate(rectModel3, rectPos3);

	shaderProgram6.activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram6.ID, "model"), 1, GL_FALSE, glm::value_ptr(rectModel3));
	glUniform4f(glGetUniformLocation(shaderProgram6.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram6.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);



	// Adding Texture 
	Texture cat("obs.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	cat.texUnit(shaderProgram, "tex0", 0);

	Texture meow("obs.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	meow.texUnit(shaderProgram2, "tex0", 0);

	Texture Houdini("obs.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	Houdini.texUnit(shaderProgram3, "tex0", 0);


	meow.texUnit(shaderProgram4, "tex0", 0);
	meow.texUnit(shaderProgram5, "tex0", 0);


	Texture woods("wood.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	woods.texUnit(shaderProgram6, "tex0", 0);








	glEnable(GL_DEPTH_TEST);


	camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use


		camera.Inputs(window, multiplier);
		camera.updateMatrix(45.0f, 0.1f, 100.0f, viewChange);

		shaderProgram.activate();
	
		
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		camera.Matrix(shaderProgram, "camMatrix");
	

		// If key P was pressed the boolean changes
		// The type of view changes betwen orthographic and perspective 
		// depending on the state of the boolean

		glfwSetKeyCallback(window, key_callback);

		// Binds texture so that is appears in rendering
		// Obsidian texture (1st texture)
		cat.bind();
		// Bind the VAO so OpenGL knows to use it
		// Pyramid in front (Pyramid) first Object
		VAO1.bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


	    // First spire top
		shaderProgram2.activate();
		camera.Matrix(shaderProgram2, "camMatrix");
		meow.bind();
		VAO2.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);




		// second spire top
		shaderProgram3.activate();
		camera.Matrix(shaderProgram3, "camMatrix");
		Houdini.bind();
		VAO3.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);



		// First spire base   // This with the first spire top make the second object
		shaderProgram4.activate();
		camera.Matrix(shaderProgram4, "camMatrix");
		VAO4.bind();
		glDrawElements(GL_TRIANGLES, sizeof(IndicesRect) / sizeof(int), GL_UNSIGNED_INT, 0);




		// Second spire base  // This with the second spire top make the third object
		shaderProgram5.activate();
		camera.Matrix(shaderProgram5, "camMatrix");
		VAO5.bind();
		glDrawElements(GL_TRIANGLES, sizeof(IndicesRect) / sizeof(int), GL_UNSIGNED_INT, 0);



		// plane with wood object (plane) 4th object
		shaderProgram6.activate();
		camera.Matrix(shaderProgram6, "camMatrix");
		// Second Texture
		woods.bind();
		VAO6.bind();


		glDrawElements(GL_TRIANGLES, sizeof(IndicesRect) / sizeof(int), GL_UNSIGNED_INT, 0);




		// First light source
		lightShader.activate();
		camera.Matrix(lightShader, "camMatrix");
		lightVAO.bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		

		// Second light source
		lightShader2.activate();
		camera.Matrix(lightShader2, "camMatrix");
		lightVAO2.bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		
	    // Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.del();
	VBO1.del();
	EBO1.del();
	cat.del();
	shaderProgram.del();

	VAO2.del();
	VBO2.del();
	EBO2.del();
	meow.del();
	shaderProgram2.del();

	VAO3.del();
	VBO3.del();
	EBO3.del();
	Houdini.del();
	shaderProgram3.del();


	VAO4.del();
	VBO4.del();
	EBO4.del();
	shaderProgram4.del();


	VAO5.del();
	VBO5.del();
	EBO5.del();
	shaderProgram5.del();

	VAO6.del();
	VBO6.del();
	EBO6.del();
	shaderProgram6.del();


	lightVAO.del();
	lightVBO.del();
	lightEBO.del();
	lightShader.del();

	lightVAO2.del();
	lightVBO2.del();
	lightEBO2.del();
	lightShader2.del();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}