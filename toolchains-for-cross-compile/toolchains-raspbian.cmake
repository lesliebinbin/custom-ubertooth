set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(triple arm-linux-gnueabihf)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++-10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER_TARGET ${triple})
# This is when mount the target machine's root path / under /mnt/another-disk/raspbian/i01
set(CMAKE_FIND_ROOT_PATH /mnt/another-disk/armbian/i01)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# This is when install the target host architecture in the compile host normally use compile host is debian 10
set(CMAKE_LIBRARY_PATH "/usr/arm-linux-gnueabihf/lib" "/usr/lib/arm-linux-gnueabihf")
