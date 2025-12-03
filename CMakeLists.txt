# Minimum version required for CMake (always use a recent one)
cmake_minimum_required(VERSION 3.28.3)

# 1. Define the project name
project(audiofx)

# 2. Specify the C++ standard to use (essential for modern C++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. Create the executable target
# List ALL your .cpp source files here.
add_executable(AudioFX
    main.cpp
    Volume.cpp
    Effect.cpp
    WavFile.cpp
    Bitcrusher.cpp
)

# 4. Tell the compiler where to find your header files
# Assuming you place AudioFile.h (and all other .h files) in an 'include' folder
target_include_directories(AudioFX 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_CURRENT_SOURCE_DIR}/include 
)