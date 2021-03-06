cmake_minimum_required (VERSION 2.8.3)
project(pai)

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif()

include(CheckCXXCompilerFlag)
include(CheckCXXSourceRuns)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # Quench annoying deprecation warnings when compiling GLFW on OSX
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|Intel)$")
  CHECK_CXX_COMPILER_FLAG("-std=c++14" HAS_CPP14_FLAG)
  CHECK_CXX_COMPILER_FLAG("-std=c++11" HAS_CPP11_FLAG)

  if (HAS_CPP14_FLAG)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
  elseif (HAS_CPP11_FLAG)
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
  else()
    message(FATAL_ERROR "Unsupported compiler -- pybind11 requires C++11 support!")
  endif()
endif()

if (APPLE)
  find_library(cocoa_library Cocoa)
  find_library(opengl_library OpenGL)
  find_library(corevideo_library CoreVideo)
  find_library(iokit_library IOKit)
  list(APPEND NANOGUI_EXTRA_LIBS ${cocoa_library} ${opengl_library} ${corevideo_library} ${iokit_library})
  list(APPEND LIBNANOGUI_EXTRA_SOURCE src/darwin.mm)
 endif()

# Disable building extras we won't need (pure C++ project)
set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON  OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL       OFF CACHE BOOL " " FORCE)

add_subdirectory(ext/nanogui)

#set(ILMBASE_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
#set(OPENEXR_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
#set(ILMBASE_NAMESPACE_VERSIONING OFF CACHE BOOL " " FORCE)
#set(OPENEXR_NAMESPACE_VERSIONING OFF CACHE BOOL " " FORCE)

#add_subdirectory(ext/openexr)
#set_property(TARGET IexMath eLut toFloat b44ExpLogTable dwaLookups CopyIlmBaseLibs IlmThread Half Iex Imath IlmImf PROPERTY FOLDER "dependencies")

#set(OPENEXR_INCLUDE_DIRS
#${CMAKE_CURRENT_SOURCE_DIR}/ext/openexr/IlmBase/Imath
#${CMAKE_CURRENT_SOURCE_DIR}/ext/openexr/IlmBase/Iex
#${CMAKE_CURRENT_SOURCE_DIR}/ext/openexr/IlmBase/Half
#${CMAKE_CURRENT_SOURCE_DIR}/ext/openexr/OpenEXR/IlmImf
#${CMAKE_CURRENT_SOURCE_DIR}/ext/openexr/OpenEXR/config
#${CMAKE_CURRENT_SOURCE_DIR}/ext/openexr/IlmBase/config)

set(GLFW_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/nanogui/ext/glfw/include)
set(GLEW_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/nanogui/ext/glew/include)
set(NANOVG_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/nanogui/ext/nanovg/src)
set(NANOGUI_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/nanogui/include)
set(EIGEN_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/ext/nanogui/ext/eigen)

set(PCG32_INCLUDE_DIR
   ${CMAKE_CURRENT_SOURCE_DIR}/ext/pcg32)

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
# target_link_libraries(<your exe or lib> ${PYTHON_LIBRARIES})

# On top of adding the path to nanogui/include, you may need extras
include_directories(
    # Include directory
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    # Random number generator
    ${PCG32_INCLUDE_DIR}/
    # GLFW library for OpenGL context creation
    ${GLFW_INCLUDE_DIR}
    # GLEW library for accessing OpenGL functions
    ${GLEW_INCLUDE_DIR}
    # NanoVG drawing library
    ${NANOVG_INCLUDE_DIR}
    # NanoGUI user interface library
    ${NANOGUI_INCLUDE_DIR}
    ${NANOGUI_EXTRA_INCS}
    # OpenEXR high dynamic range bitmap library
    ${OPENEXR_INCLUDE_DIRS}
    ext
)

if(APPLE)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -flto -Wno-unused-result -fno-strict-aliasing")
else()
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -flto -Wno-unused-result -fno-strict-aliasing -Wlto-type-mismatch")
endif()

add_executable(pai
    # Header Files
    include/pai/entity.h
    include/pai/game.h
    include/pai/ground.h
    include/pai/player.h

    # Implementation Files
    src/main.cpp
    src/game.cpp
    src/entity.cpp
    src/ground.cpp
    src/player.cpp
)

#OPENEXR_INCLUDE_DIRS
set(CompilerFlags
      CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS
      CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL
      CMAKE_C_FLAGS_RELWITHDEBINFO COMPILE_DEFINITIONS U_CMAKE_BUILD_TYPE
      CMAKE_MACOSX_RPATH
       PCG32_INCLUDE_DIR
      GLFW_INCLUDE_DIR GLEW_INCLUDE_DIR
      NANOVG_INCLUDE_DIR NANOGUI_INCLUDE_DIR EIGEN_INCLUDE_DIR
      NANOGUI_EXTRA_LIBS
)

# Lastly, additional libraries may have been built for you.  In addition to linking
# against NanoGUI, we need to link against those as well.
target_link_libraries(pai nanogui ${NANOGUI_EXTRA_LIBS} ${PYTHON_LIBRARIES})
