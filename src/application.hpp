#ifndef TRI_APPLICATION_HPP
#define TRI_APPLICATION_HPP


#include "window.hpp"
#include "logicaldevice.hpp"
#include "physicaldevice.hpp"
#include "instance.hpp"

namespace tri {
    struct application {
        tri::window wd;
        tri::instance inst;
        tri::physical_device phydev;
        tri::logical_device logdev;
        //
        application()
            : wd{},
            inst{} ,
            phydev{inst.m_instance},
            logdev{phydev}
            // Ctor
        {}
        ~application()  // Dtor
        {}

        bool run() {
            while (!glfwWindowShouldClose(wd.m_window)) glfwPollEvents();
            return true;
        }

    };
}  // namespace tri
#endif
