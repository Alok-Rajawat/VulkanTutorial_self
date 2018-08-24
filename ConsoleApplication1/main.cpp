#include"pch.h"

#include <vulkan/vulkan.h>

#include<iostream>
#include<cstdlib>
#include<functional>
#include<stdexcept>

class vk {

  void initVulkan( ){ }
  void mainLoop( ){ }
  void cleanup( ){ }
public:

  void run( ) {
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
