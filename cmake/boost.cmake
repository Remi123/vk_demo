message (STATUS "Boost.cmake Configuration")

#include and lib directory for boost.
#set(BOOST_INCLUDEDIR /usr/include/)
#set(BOOST_LIBRARYDIR /usr/lib/)

find_package(Boost 1.73 REQUIRED 
            COMPONENTS system )

message(STATUS "Boost version:" ${Boost_VERSION})

message (STATUS "End Boost.cmake")
