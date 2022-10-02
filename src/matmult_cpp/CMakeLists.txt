cmake_minimum_required(VERSION 3.11.0)
project(matmult)
find_package(PythonExtensions REQUIRED)

# This comes to hand if we also need to use the NumPy C API
exec_program(${PYTHON_EXECUTABLE}
             ARGS "-c \"import numpy; print(numpy.get_include())\""
             OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
             RETURN_VALUE NUMPY_NOT_FOUND
            )
if(NUMPY_NOT_FOUND)
    message(FATAL_ERROR "NumPy headers not found")
endif()

include_directories(SYSTEM ${NUMPY_INCLUDE_DIR})

add_library(_matmult MODULE matmult/_matmult.cpp matmult/libmatmult.cpp matmult/libmatmult.h)


python_extension_module(_matmult)
install(TARGETS _matmult LIBRARY DESTINATION matmult)