set(CUDACXX /opt/cuda/bin/nvcc)
set(CMAKE_CUDA_COMPILER ${CUDACXX})

file(GLOB_RECURSE KERNAL_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cu")

add_library(kernal
    ${KERNAL_SOURCES}
)

target_include_directories (kernal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_target_properties(kernal PROPERTIES
    CMAKE_CUDA_STANDARD 17
)

set_property(TARGET kernal PROPERTY CUDA_SEPARABLE_COMPILATION ON)

set_property(TARGET kernal PROPERTY CUDA_ARCHITECTURES 75)