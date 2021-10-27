cmake_minimum_required(VERSION 2.8)

project(Production_practice)

# set(CMAKE_PREFIX_PATH "/home/kongqi/libtorch")
# find_package(Torch REQUIRED)
find_package(OpenCV 4.2 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(jsoncpp REQUIRED)


get_target_property(JSON_INC_PATH jsoncpp_lib INTERFACE_INCLUDE_DIRECTORIES)
include_directories(${JSON_INC_PATH})
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/easypr)
include_directories(${PROJECT_SOURCE_DIR}/aip-cpp-sdk-4.15.7)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenSSL_INCLUDE_DIRS})

# include_directories(${Torch_INCLUDE_DIRS})
aux_source_directory(./src SrcFiles)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(${PROJECT_NAME} ${SrcFiles})
# link_libraries(${JSONCPP_LIBRARYS})
link_directories(${OpenCV_LIBRARY_DIRS})
link_directories(${OpenSSL_LIBRARY_DIRS})

# link_directories(${Torch_LIBRARY_DIRS})

# target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${TORCH_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS}  jsoncpp_lib ${OpenSSL_LIBS} ${PROJECT_SOURCE_DIR}/lib/libcurl-d.so crypto ${PROJECT_SOURCE_DIR}/lib/libeasypr.so wiringPi)