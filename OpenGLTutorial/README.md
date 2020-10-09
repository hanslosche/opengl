# build and compile our shader program: shaders are little programs that rest on the GPU 
	Ins and outs: shaders are nothing more than programs transforming inputs to outputs. 
		- GLSL : defined the in and out keywords specifically for that purpose. 
			- vertex shader : receive some form of input
			- uniforms : another way to pass data from our application on the CPU to the shaders on the GPU
			- fragment shader : requires a vec4 color output variable, 
				- since the fragment shaders needs to generate a final output color.

# vertex data/input : drawing something we have to first give OpenGL some input vertex data
	- Normalized Device Coordinates (NDC) : Space where x, y and z values vary from -1.0 to 1.0
	- define 3D position

# Vertex shader : written in the shader language GLSL ( OpenGL Shading Language)
	- main()
		- gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

	- compiling a shader 
		- glCreateShader() : create a shader object; arg1: ShaderType
		- glShaderSource() : ("assets/vertex_core.glsl") replace source code of a given shader object
		- glCompileShader() : check if compliation was successful
			- glGetShaderiv() : way to query infos from the shader object
			- glGetShaderInfolog() : retrieve the error message

# Fragment shader : all about calculating the color output of your pixels
	- main()
		- FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);

	- compiling a shader 
		- glCreateShader() : create a shader object; arg1: ShaderType
		- glShaderSource() : ("assets/fragment_core.glsl") replace source code of a given shader object
		- glCompileShader() : check if compliation was successful
			- glGetShaderiv(): way to query infos from the shader object
			- glGetShaderInfolog() : retrieve the error message

# Create a Program & Link Shader : To use the recently compiled shaders we have to link them to a shader program object.
	- glCreateProgram() :  returns the ID reference to the newly created program object.
	- glAttachShader()*2 : attach compiled vertexShader & fragmentShader with program object
	- glLinkProgram() : links all the attaceds shaders in one final shader program object
	- glUseProgram() : sets given program object as the active shader program
		- glGetProgramiv() : way to query infos from the programm object
		- glGetProgramInfolog() : retrieve the error message
	- glDeleteShader() : once we've linked them into the program object; we no longer need them anymore

	Right now we sent the input vertex data to the GPU and instructed the GPU how it should process the vertex data 
	within a vertex and fragment shader. We're almost there, but not quite yet. 
	OpenGL does not yet know how it should interpret the vertex data in memory and how it 
	should connect the vertex data to the vertex shader's attributes.


#BINDING
# Vertex Array Object (VAO)*required : makes switching between different vertex data and attribute configurations as easy			     
					- glBindVertexArray() : binds a vertex array object

# Vertex buffer object (VBO) : way to send vertex data to the graphics pipeline: the vertex shader
	- vertex buffer objects : can store large numbers of vertices in the GPU memory
		- glGenBuffers() : binds the buffer object to a buffer type target
		- glBufferData() : allocates and stores data in the buffer object

# Element Buffer Object (EBO) :  indexed drawing - solves the problem of overlapping vertices
	- vertex buffer objects : can store large numbers of vertices in the GPU memory
		- glGenBuffers() : binds the buffer object to a buffer type target
		- glBufferData() : allocates and stores data in the buffer object

		As you can see, there is some overlap on the vertices specified. We specify bottom right 
		and top left twice! This is an overhead of 50% since the same rectangle could also be
		specified with only 4 vertices, instead of 6. 

# Linking Vertex Atttribute : vertex shader allows us to specify any input we want in the form of vertex attributes
	- glVertexAttribPointer : tells openGL how it should interpret the vertex data ( per vertex attribute)
	- glEnableVertexAttribArray() : vertex attributes are disabled by


	From that point on we have everything set up: we initialized the vertex data in a buffer using
	a vertex buffer object, set up a vertex and fragment shader and told OpenGL how to link the vertex data
	to the vertex shader's vertex attributes.



# main :
	- glClearColor()
	- glClear()
	- glUseProgram():  Installs a program object as part of current rendering state
	- glBindVertexArray : binds a vertex array object
	- glDrawArrays()*VBO : draw the amount of vertices found in the VBO ( vertex buffer object)
	- glDrawElements()*EBO : does indexed drawing
		- takes the VBO and EBO bound and renders the VBO vertices at the order found in the EBO
		- advantage over glDrawArrays : removes duplicates

save , get
recording , querying

https://learnopengl.com/Getting-started/Hello-Triangle
http://www.songho.ca/opengl/
