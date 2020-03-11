#ifndef TRI_APPLICATION_HPP
#define TRI_APPLICATION_HPP

#include "globals.hpp"
#include "window.hpp"
#include "instance.hpp"
#include "logicaldevice.hpp"
#include "physicaldevice.hpp"

namespace tri {

    struct application {
        tri::window wd;
        tri::instance inst;
        tri::physical_device phydev;
        tri::logical_device logdev;
        //
        application()
            : 
            wd{},
            inst{wd} ,
            phydev{inst.m_instance},
            logdev{phydev}
            // Ctor
        {}
        ~application()  // Dtor
        {}

        bool run() {
            while (!glfwWindowShouldClose(tri::m_window)) glfwPollEvents();
            return true;
        }

    };
}  // namespace tri
#endif
