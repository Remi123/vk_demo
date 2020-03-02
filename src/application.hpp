
#include "window.hpp"
#include "instance.hpp"

namespace tri {
struct application {
  tri::window wd;
  tri::instance inst;

  application() : wd{}, inst{}  // Ctor
  {}
  ~application()  // Dtor
  {}

  bool run() {
    while (!glfwWindowShouldClose(wd.m_window)) glfwPollEvents();
    return true;
  }
};
}  // namespace tri
