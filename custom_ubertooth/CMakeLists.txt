# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
aux_source_directory(src ALL_SRCS)
find_library(ubertooth_lib ubertooth REQUIRED)
find_library(bluetooth_lib bluetooth REQUIRED)
find_library(btbb_lib btbb REQUIRED)
find_path(usb_path libusb-1.0/libusb.h REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)
set(usb_include_dir "${usb_path}/libusb-1.0")
include_directories(includes ${usb_include_dir})
add_library(custom_ubertooth ${ALL_SRCS})
target_link_libraries(custom_ubertooth ${ubertooth_lib} ${bluetooth_lib} ${btbb_lib} nlohmann_json::nlohmann_json)
set_target_properties(custom_ubertooth PROPERTIES POSITION_INDEPENDENT_CODE ON)
