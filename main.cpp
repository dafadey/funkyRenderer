#include <iostream>
#include <limits>
#include "readSTL.h"
#include "draw.h"
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "Glfw Error " << error << ": " << description << '\n' << std::flush;
}

int main(int argc, char* argv[]) {
  std::cout << "Hallo!\n";

  glfwSetErrorCallback(glfw_error_callback);
  
 
  if (!glfwInit()) {
    std::cerr << "interface::init: ERROR: failed init glfw\n";
    return false;
  }
      
  // GL 3.2 + GLSL 150
  const char* glsl_version = "#version 150";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
  
  // Create window with graphics context
  GLFWwindow* window = glfwCreateWindow(800, 600, "dicom2stl", NULL, NULL);
  if (window == NULL) {
    std::cerr << "interface::init: ERROR: failed to create glfw window\n";
    return false;
  }
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  geo g = readSTL("scene.stl");
  geo g_more = readSTL("scene_more.stl");
  geo g_onemore = readSTL("scene_onemore.stl");

  renderer ren;
  ren.init(window);
  
  OGLsurface surf;
  surf.surface_color[0]=0.6;
  surf.surface_color[1]=0.8;
  surf.surface_color[2]=0.3;
  surf.init(&ren);
  surf.update_model(&g);

  OGLsurface surf_more;
  surf_more.surface_color[0]=0.3;
  surf_more.surface_color[1]=0.4;
  surf_more.surface_color[2]=0.8;
  surf_more.init(&ren);
  surf_more.update_model(&g_more);

  OGLsurface surf_onemore;
  surf_onemore.surface_color[0]=0.8;
  surf_onemore.surface_color[1]=0.5;
  surf_onemore.surface_color[2]=0.3;
  surf_onemore.init(&ren);
  surf_onemore.update_model(&g_onemore);


  ren.items.push_back(&surf);
  ren.items.push_back(&surf_more);
  ren.items.push_back(&surf_onemore);
  
  ren.reset_camera();

  glfwSetWindowUserPointer(window, (void*) &ren);

  ren.set_callbacks(window);

  ren.nocallbacks = false;
  while (!glfwWindowShouldClose(window))  {
    glfwWaitEvents();
    //glfwPollEvents();

    glClearColor(.3, .3, .3, 1.);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ren.render();
    glfwSwapBuffers(window);
    glFlush();
  }

  return 0; 
}
