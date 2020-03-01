message (STATUS "Boost.cmake Configuration")

set(Boost_INCLUDE_DIR /home/mariefrance/Documents/SDKs/boost/)

find_package(Boost 1.72 REQUIRED system )

message(STATUS "Boost version:" ${Boost_VERSION})

message (STATUS "End Boost.cmake")
