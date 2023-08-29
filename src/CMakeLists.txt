# This project will output an executable file
add_executable(${PROJECT_NAME} SnakeCube.cpp util.cpp)

# Include the configuration header in the build
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
