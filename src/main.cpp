#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIN_WIDTH = 800;
const uint32_t WIN_HEIGHT = 600;

class HelloTriangleApplication
{
public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        m_Window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Vulkan Tutorial", nullptr, nullptr);
    }
    void initVulkan()
    {
        createInstance();
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        vkDestroyInstance(m_Instance, nullptr);

        glfwDestroyWindow(m_Window);

        glfwTerminate();
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // GLFW Get Extensions
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // Specify Validation Layers
        createInfo.enabledLayerCount = 0;

        // Create the instance

        if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to Create Vulkan Instance");
        }
        std::cout << "Vulkan Instance Created Successfully" << std::endl;

        // Check extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::cout << "Extensions Available: " << extensionCount << std::endl;

        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "Available extensions: " << std::endl;
        for (const auto &extension : extensions)
        {
            std::cout << '\t' << extension.extensionName << std::endl;
        }
    }

private:
    VkInstance m_Instance;
    GLFWwindow *m_Window;
};

int main()
{
    HelloTriangleApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}