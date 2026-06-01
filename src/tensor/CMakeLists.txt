add_executable(tensor_main main.cpp)

target_include_directories(tensor_main PRIVATE
    ${CMAKE_SOURCE_DIR}/src/tensor
)

target_compile_options(tensor_main PRIVATE -Wall -Wextra)