/* #include "../include/LCommon.h"
#include "../include/LConfig.h"

#include "../include/shader_m.h"
#include "../include/camera.h"
#include "../include/model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
        std::cout << "key_callback";
		// if (scene)
		// 	scene->animate(!(scene->animating()));
	}
	
}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Load Ogre", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    std::cout<<"1" <<std::endl;

    

    //glDebugMessageCallback(GLUtils::debugCallback, NULL);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0,
      GL_DEBUG_SEVERITY_NOTIFICATION, -1 , "Start debugging");

    // build and compile shaders
    // -------------------------
    Shader oitShader("../res/shaders/oit.vs", "../res/shaders/oit.fs");
    oitShader.use();
    glClearColor(0.5f,0.5f,0.5f,1.0f);
    
    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glEnable( GL_BLEND );

    // Init objects
    // float vertices[] = {
    //     // positions          // normals           // texture coords
    //     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    //      0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    //      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    //      0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    //     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    //      0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    //      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    //      0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    //     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    //     -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    //     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //     -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //     -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    //     -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    //      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    //      0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    //      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //      0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    //      0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    //      0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    //     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    //      0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    //      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    //      0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    //     -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    //     -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    //     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    //      0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    //      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    //      0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    //     -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    //     -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    // };

    // // positions of the point lights
    // glm::vec3 pointLightPositions[] = {
    //     glm::vec3( -0.3f,  0.8f, 0.0f),
    //     glm::vec3( -0.4f,  0.8f, 1.0f),
    //     glm::vec3( -0.5f,  0.8f, 2.0f),
    //     glm::vec3( -0.6f,  0.8f, 3.0f)
    // };

    // // first, configure the cube's VAO (and VBO)
    // unsigned int VBO, lightVAO;    
    // glGenBuffers(1, &VBO);
    // glGenVertexArrays(1, &lightVAO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glBindVertexArray(lightVAO);
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // Load textures
    unsigned int diffuseMap = loadTexture("../res/models/teapotB/textures/Chaynik_Diffuse.png");
    unsigned int specularMap = loadTexture("../res/models/teapotB/textures/Chaynik_Specular.png");

    //std::cout << "Textures: " << diffuseMap << " - " <<specularMap << std::endl;

    // load models
    // -----------
    //Model ourModel("../res/models/ogre/bs_ears.obj");
    //Model ourModel("../res/models/nanosuit/nanosuit.obj");
    Model ourModel("../res/models/teapotB/Chaynik.obj");
    

    // Init shader storage
    GLuint buffers[2], fsQuad, headPtrTex;
    GLuint clearBuf;
    GLuint pass1Index, pass2Index;
    float angle = 0.0, tPrev = 0.0, rotSpeed = 3.141592653589793/8;
    enum BufferNames {
        COUNTER_BUFFER = 0,
        LINKED_LIST_BUFFER
    };

    glGenBuffers(2, buffers);
    GLuint maxNodes = 20 * SCR_WIDTH * SCR_HEIGHT;
    GLint nodeSize = 5 * sizeof(GLfloat) + sizeof(GLuint); // The size of a linked list node

    // Our atomic counter
    glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, buffers[COUNTER_BUFFER]);
    glBufferData(GL_ATOMIC_COUNTER_BUFFER, sizeof(GLuint), NULL, GL_DYNAMIC_DRAW);

    // The buffer for the head pointers, as an image texture
    glGenTextures(1, &headPtrTex);
    glBindTexture(GL_TEXTURE_2D, headPtrTex);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32UI, SCR_WIDTH, SCR_HEIGHT);
    glBindImageTexture(0, headPtrTex, 0, GL_FALSE, 0, GL_READ_WRITE, GL_R32UI);

    // The buffer of linked lists
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, buffers[LINKED_LIST_BUFFER]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, maxNodes * nodeSize, NULL, GL_DYNAMIC_DRAW);

    //oitShader.setUniform("MaxNodes", maxNodes);
    oitShader.use();
    oitShader.setInt("MaxNodes", maxNodes);

    vector<GLuint> headPtrClearBuf(SCR_WIDTH*SCR_HEIGHT, 0xffffffff);
    glGenBuffers(1, &clearBuf);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, clearBuf);
    glBufferData(GL_PIXEL_UNPACK_BUFFER, headPtrClearBuf.size() * sizeof(GLuint), &headPtrClearBuf[0], GL_STATIC_COPY);

    std::cout<<"all about storage" << std::endl;

    GLuint programHandle = oitShader.ID;
    pass1Index = glGetSubroutineIndex( programHandle, GL_FRAGMENT_SHADER, "pass1");
    pass2Index = glGetSubroutineIndex( programHandle, GL_FRAGMENT_SHADER, "pass2");

    // Set up a  VAO for the full-screen quad
    GLfloat verts[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, -1.0f, 1.0f, 0.0f };
    GLuint bufHandle;
    glGenBuffers(1, &bufHandle);
    glBindBuffer(GL_ARRAY_BUFFER, bufHandle);
    glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(GLfloat), verts, GL_STATIC_DRAW);

    // Set up the vertex array object
    glGenVertexArrays( 1, &fsQuad );
    glBindVertexArray(fsQuad);

    glBindBuffer(GL_ARRAY_BUFFER, bufHandle);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    glEnableVertexAttribArray(0);  // Vertex position

    glBindVertexArray(0);

    const int samples = 50;
    float time[samples];
    int index = 0;

    while (!glfwWindowShouldClose(window))
    {
        //Scene Update
        float t = glfwGetTime();
        float deltaT = t - tPrev;
        if(tPrev == 0.0f) deltaT = 0.0f;
            tPrev = t;
        // if( animating() ) {
        //     angle += deltaT * rotSpeed;
        //     if( angle > 360.0 ) angle -= 360.0f;
        // }

        // Scene Render
        // Clean Buffers
        GLuint zero = 0;
        glBindBufferBase(GL_ATOMIC_COUNTER_BUFFER, 0, buffers[COUNTER_BUFFER] );
        glBufferSubData(GL_ATOMIC_COUNTER_BUFFER, 0, sizeof(GLuint), &zero);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, clearBuf);
        glBindTexture(GL_TEXTURE_2D, headPtrTex);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_RED_INTEGER, GL_UNSIGNED_INT, NULL);

        // Pass1
        glUniformSubroutinesuiv( GL_FRAGMENT_SHADER, 1, &pass1Index);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        // glm::mat4 view = glm::lookAt(glm::vec3(11.0f * cos(angle),2.0f,11.0f * sin(angle)), vec3(0.0f,0.0f,0.0f), vec3(0.0f,1.0f,0.0f));
        // projection = glm::perspective( glm::radians(50.0f), (float)width/height, 1.0f, 1000.0f);

        glDepthMask( GL_FALSE );

        // draw scene
        oitShader.setVec4("LightPosition", 0,0,0,1);
        oitShader.setVec3("LightIntensity", 0.9f, 0.9f, 0.9f);
                
        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);
        
        oitShader.setVec4("Kd", 0.2f, 0.2f, 0.9f, 0.55f);
        // render the loaded model        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.12f, 1.0f)); // translate it down so it's at the center of the scene
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
        
        glm::mat4 mv = view * model;
        
        oitShader.setMat3("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
        oitShader.setMat4("ModelViewMatrix", mv);
        oitShader.setMat4("MVP", projection * mv);
        ourModel.Draw(oitShader);

        // oitShader.setVec4("Kd", 0.9f, 0.2f, 0.2f, 0.4f);
        // // render the loaded model        
        // model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, -0.12f, 1.0f)); // translate it down so it's at the center of the scene
        // model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
        // model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));	// it's a bit too big for our scene, so scale it down
        
        // mv = view * model;
        
        // oitShader.setMat3("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
        // oitShader.setMat4("ModelViewMatrix", mv);
        // oitShader.setMat4("MVP", projection * mv);
        // ourModel.Draw(oitShader);

        glFinish();

        // Pass2
        glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
        glUniformSubroutinesuiv( GL_FRAGMENT_SHADER, 1, &pass2Index);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        view = glm::mat4(1.0f);
        projection = glm::mat4(1.0f);
        model = glm::mat4(1.0f);

        mv = view * model;
        
        oitShader.setMat3("NormalMatrix", glm::mat3(glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2])));
        oitShader.setMat4("ModelViewMatrix", mv);
        oitShader.setMat4("MVP", projection * mv);
        
         // Draw a screen filler
        glBindVertexArray(fsQuad);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        glBindVertexArray(0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Update FPS
        time[index] = glfwGetTime();
        index = (index + 1) % samples;

        if( index == 0 ) {
            float sum = 0.0f;
            for( int i = 0; i < samples-1 ; i++ )
                sum += time[i + 1] - time[i];
            float fps = samples / sum;

            stringstream strm;
            strm << "Please work!";
            strm.precision(4);
            strm << " (fps: " << fps << ")";
            glfwSetWindowTitle(window, strm.str().c_str());
        }
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    exit( EXIT_SUCCESS );
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
} */