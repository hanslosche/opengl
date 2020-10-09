
## glfwInit() : initialize GLFW
	- glfwWindowHint()
	- glfwWindowHint()
	- glfwWindowHint()

## glfwCreateWindow() : creates a window object
## gladLoadGLLoader()

## shader(): import custom class

## float vertices[] : create attrib
## unsigned int indices [] : create index

## all objects and array object creation
		- unsigned int VBO, VAO, EBO
		- glGenVertexArrays(1, &VAO)
		- glGenBuffers(1, &VAO)
		- glGenBuffers(1, &EBO)

		- glBindVertexArray(VAO)
		- glBindBuffer(GL_ARRAY_BUFFER, VBO)
		- glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,  GL_STATIC_DRAW)

		- glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		- glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW)
## position : attrib pointer
			- glVertexAttribPointer(0)
			- glEnablevertexAttribArray(0)
## color : attrib pointer
			- glVertexAttribPointer(1)
			- glEnablevertexAttribArray(1)
## Rendering
			- while not glfwWindowShouldClose() : render loop until GLFW stops
				- glClearColor()
				- glClear()
				- glBindVertexArray(VAO)
				- shader.activate()

				- glDrawElements()


				- glfwSwapBuffers()
				- glfwPollEvents()

## void processInput()
## void framebuffer_size_callback()

## SHADER CLASS
	# program id
	# Shader()
	# void activate()

	# string loadShaderSrc()
	# GLuit compileShader()

	# void setBool()
	# void setInt()
	# void setFloat()
	# void set4Float()
	# void setMat4()
