#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>


#include "shaderClass.h"

class camera {

	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);


		bool firstClick = true;
		int width;
		int height;
		
		double multiplier = 2;
		float speed = 0.1f;
		float sensitivity = 100.0f;

		float currentFrame;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		

		camera(int width, int height, glm::vec3 Position);
		
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane, bool viewChange);
		void Matrix(shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window, double multiplier);

};
#endif