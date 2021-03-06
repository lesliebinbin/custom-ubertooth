set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(triple aarch64-linux-gnu)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# This is when mount the target machine's root path / under /mnt/another-disk/armbian/i01

# set(CMAKE_SYSROOT /mnt/another-disk/armbian/i01)
set(CMAKE_SYSROOT /media/lesliebinbin/585ed298-cc37-4648-a0c1-454a8bec64f5)
set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# This is when install the target host architecture in the compile host normally use compile host is debian 10


#set(CMAKE_LIBRARY_PATH "/usr/aarch64-linux-gnu/lib" "/usr/lib/aarch64-linux-gnu")
