
## glfwInit() : initialize GLFW
	- glfwWindowHint()
	- glfwWindowHint()
	- glfwWindowHint()

## SCREEN CLASS
	- public:
	    # static void framebufferSizeCallback()
	    # Screen()
	    # bool init()
	    # setParameters()
	    # void update()
	    # void newFrame()
	    # bool shouldClose()
	    # void setShouldClose()

	- private:
	    # GLFWwindow* window


### gladLoadGLLoader()

### screen.setParameters()

mesh << texture << shader

## MESH CLASS
	# struct Vertex { pos, normal , texCoord} : storage format and data 
	# Mesh()
	
	- public:
	    # struct Vertex  : applied
	    # void render()
    	# void cleanup()
	
	- private:
	    # void setup() : VAO, VBO, EBO & attrib ptr.
	    	# GL_ARRAY_BUFFER 
	    	# GL_ELEMENT_ARRAY_BUFFER

## TEXTURE CLASS : include <stb/stb_image.h>
	- public:
	    # Texture()
	    # void generate()
	    # void load()
	    # void setFilters()
	    # setFilters()
	    # setWrap()
	    # setWrap()
	    # void setBorderColor()
	    # activate()

## SHADER CLASS ( ".vs path", ".fs path")
	- public:
	    # program id
	    # Shader()
	    # void activate()

	    # string loadShaderSrc()
    	# GLuit compileShader()

	    # void setBool();
	    # void setInt();
	    # void setFloat();
	    # void set3Float();
    	# void set3Float();
	    # void set4Float();
	    # void setMat4();

## LAMP CLASS (".vs path", ".fs path") : LIGHT PROPERTIES WITH CUBE 
	- class Lamp : public Cube {}
		# lightColor
		# PointLight pointlight
		# vec3 ambient, diffuse, specular

		# void render() : set light color
	 



## CUBE CLASS : MODEL : for loop for multiple cubes
	# Cube()
	# init()
	# void render()

	Example : #  glm::vec3 cubePositions[i] :  Cube()


## LIGHTS :
	# struct DirLight {}
	# struct PointLight {}
	# struct SpotLight {}

	# void render*ALL

	Example : #  DirLight dirLight = {}
		  #  glm::vec3 pointLightPositions[i] : Lamp : pointlight
		  #  SpotLight s = {}

## while (!screen.shouldClose()) {}

	# double currentTime = glfwGetTime()
	# deltaTime = currentTime - lastFrame
	# lastFrame = currentTime

	# processInput(deltaTime) : process input	 
	# screen.update() : render
	# shader.activate() :  draw shapes
	# shader.set3Float("viewPos", Camera::defaultCamera.cameraPos)
	# dirLight.render(shader) :

	# lamps[i].pointLight.render()
	# shader.setInt("noPointsLights", 4) :
	# s.position = Camera::defaultCamera.cameraPos : SpotLight s
	# s.direction = Camera::defaultCamera.cameraFront 
	# s.render(shader, 0)
	# shader.setInt("noSpotLights", 1)

		
	# glm::mat4 view = glm::mat4(1.0f) 
	# glm::mat4 projection = glm::mat4(1.0f);
	# view = Camera::defaultCamera.getViewMatrix()
	# projection = glm::perspective()

	# shader.setMat4("view", view);
	# shader.setMat4("projection", projection);

	# cubes[i].render(shader) : for each 4 x times
	# lampShader.activate();

	# lampShader.setMat4("view", view);
	# lampShader.setMat4("projection", projection);

	# lamps[i].render(lampShader) : for each 4 x times
	
	# screen.newFrame() : send new frame  to window
	# glfwPollEvents() 



	# cubes[i].cleanup() : for each 4 x times 

	# lamps[i].cleanup() : for each 4 x times

	# glfwTerminate();
	# return 0;

## void processInput()
## void framebuffer_size_callback()

