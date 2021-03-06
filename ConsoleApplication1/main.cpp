#include"pch.h"

#define GLFW_INCLUDE_VULKAN
#include<glfw/glfw3.h>

#include<iostream>
#include<cstdlib>
#include<functional>
#include<stdexcept>
#include<vector>

const int WIDTH = 800;
const int HEIGHT = 600;


class vk {

  GLFWwindow *window;
  VkInstance vkInstance;

  void initWindow(){

    glfwInit( );
    glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );

    window = glfwCreateWindow( WIDTH, HEIGHT, "vulkan", nullptr, nullptr );
  }

  void initVulkan( ){
    createInstance( );
  }

  void mainLoop( ) {
    while( !glfwWindowShouldClose( window ) ) {
      glfwPollEvents( );
    }
  }

  void createInstance(){
    VkApplicationInfo appInfo = { };
    VkInstanceCreateInfo createInfo = { };

    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION( 1, 0, 0 );
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION( 1, 0, 0 );
    appInfo.apiVersion = VK_API_VERSION_1_0;

    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions( &glfwExtensionCount );

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;
    createInfo.enabledLayerCount = 0;

    VkResult vkresult = vkCreateInstance( &createInfo, nullptr, &vkInstance );
    if( vkresult != VK_SUCCESS )
      throw std::runtime_error( "failed to create instance!" );

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties( nullptr, &extensionCount, nullptr );
    std::vector<VkExtensionProperties> extensions( extensionCount );
    vkEnumerateInstanceExtensionProperties( nullptr, &extensionCount, extensions.data() );

    std::cout << "Available extensions :" << extensionCount << std::endl;
    for( auto& extension : extensions )
      std::cout << "\t" << extension.extensionName << std::endl;
  }

  void cleanup( ){
    vkDestroyInstance( vkInstance, nullptr );

    glfwDestroyWindow( window );
    glfwTerminate( );
  }

public:

  void run( ) {
    initWindow( );
    initVulkan( );
    mainLoop( );
    cleanup( );
  }
};

int main( ) {
  vk app;

  try {
    app.run( );
  } catch(const std::exception &e){
    std::cerr << e.what( ) << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
