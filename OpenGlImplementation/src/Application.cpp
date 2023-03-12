#include<GL/glew.h>

#include <GLFW/glfw3.h>
#include<iostream>
#include"Shader.h"
#include"Texture.h"

int client_height = 750;
int client_width = 1080;
float add = 0;
float x_axis = 0;
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
int main(void)
{
    GLFWwindow* window;
 
    if (!glfwInit())
        return -1;
   

    /* Initialize the library */
   
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(client_width,client_height, "Hello World", NULL, NULL);

   
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
   
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glewInit();
    if (!glfwInit())
        return -1;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    }
    std::cout << glGetString(GL_VERSION) << std::endl;

    float Positions[8] = {
        -1.0f,-1.0f,
         1.0f,1.0f,
         -1.0f,1.0f,
         1.0f,-1.0f
    };
    unsigned int indices[6] = { 0,2,1,0,1,3 };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), Positions, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);

    glfwSetKeyCallback(window, glfwKeyCallback);

    //unsigned int shader = CreateShader(vertexShader,fragmentShader);
    
    Shader shader = Shader("res/Shaders/vertex_shader.shader", "res/Shaders/fragment_shader.shader");

    Texture texture = Texture("res/textures/textest.png");

    texture.Bind();
    shader.Bind(); 

    

    shader.SetUniform1i("u_Texture", 0);
    /* Loop until the user closes the window */
    glfwSetTime(0);
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
 
        shader.SetUniform2f("u_resolution", client_width,client_height);

        shader.SetUniform1f("u_time", glfwGetTime());
        shader.SetUniform1f("u_zoom", add);
        shader.SetUniform1f("u_pan", x_axis);
 
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP)
    {
        switch (action)
        {
        case GLFW_REPEAT:
            add += 0.1;
            break;
        case GLFW_PRESS:
            add += 0.1;
            break;
        case GLFW_RELEASE:
            add += 0.1;
            break;
        default:
            break;
        }
    }
    if (key == GLFW_KEY_DOWN)
    {
        switch (action)
        {
        case GLFW_REPEAT:
            add -= 0.1;
            break;
        case GLFW_PRESS:
            add -= 0.1;
            break;
        case GLFW_RELEASE:
            add -= 0.1;
            break;
        default:
            break;
        }
           
    }
    if (key == GLFW_KEY_LEFT)
    {
        switch (action)
        {
        case GLFW_REPEAT:
            x_axis -= 0.1;
            break;
        case GLFW_PRESS:
            x_axis -= 0.1;
            break;
        case GLFW_RELEASE:
            x_axis -= 0.1;
            break;
        default:
            break;
        }
    }
        if (key == GLFW_KEY_RIGHT)
        {
            switch (action)
            {
            case GLFW_REPEAT:
                x_axis += 0.1;
                break;
            case GLFW_PRESS:
                x_axis += 0.1;
                break;
            case GLFW_RELEASE:
                x_axis += 0.1;
                break;
            default:
                break;
            }
        }
    
}