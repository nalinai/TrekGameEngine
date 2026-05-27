#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void APIENTRY debug_message_callback(GLenum source, GLenum type, GLuint id, 
                                           GLenum severity, GLsizei length, 
                                           const GLchar* message, const void* userParam)
{
    std::string source_str, type_str, severity_str;

    switch (source) {
        case GL_DEBUG_SOURCE_API:             source_str = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_str = "WINDOW_SYSTEM"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_str = "SHADER_COMPILER"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_str = "THIRD_PARTY"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_str = "APPLICATION"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_str = "OTHER"; break;
        default:                               source_str = "UNKNOWN"; break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               type_str = "ERROR"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_str = "DEPRECATED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_str = "UNDEFINED_BEHAVIOR"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_str = "PORTABILITY"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_str = "PERFORMANCE"; break;
        case GL_DEBUG_TYPE_MARKER:              type_str = "MARKER"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_str = "PUSH_GROUP"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_str = "POP_GROUP"; break;
        case GL_DEBUG_TYPE_OTHER:               type_str = "OTHER"; break;
        default:                                type_str = "UNKNOWN"; break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         severity_str = "HIGH"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severity_str = "MEDIUM"; break;
        case GL_DEBUG_SEVERITY_LOW:          severity_str = "LOW"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_str = "NOTIFICATION"; break;
        default:                             severity_str = "UNKNOWN"; break;
    }

    std::cerr << "[" << source_str << "] [" << type_str << "] [" << severity_str << "] "
              << "ID: " << id << " - " << message << "\n";
}

int main() {

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Set OpenGL context hints for 4.6 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Trek Engine", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Load OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Enable debug messaging
    if (glDebugMessageCallback) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(debug_message_callback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        std::cout << "Debug context enabled\n";
    }

    // Print OpenGL info
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";

    glfwSetKeyCallback(window, key_callback);

    // Set clear color to dark gray
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Game logic and rendering will go here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
