set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP 1)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(module)

target_sources(module
    PUBLIC
        module.cpp
)

target_sources(module
    PUBLIC
    FILE_SET
        all_my_modules
    TYPE
        CXX_MODULES
    FILES
        Math.ixx
        Math_Time.ixx
        MathPartition_1.ixx
        MathPartition_2.ixx
)
