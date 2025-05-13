cmake_minimum_required(VERSION 3.30)
project(hello_raylib_with_cmake C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# اضافه کردن مسیر محلی raylib
add_subdirectory(vendor/raylib)

# تعریف فایل‌های منبع
file(GLOB SOURCES "src/*.c")

if(NOT SOURCES)
    message(FATAL_ERROR "No source files found in src/")
endif()

# ایجاد اجرایی از فایل‌های منبع
add_executable(main ${SOURCES})
target_include_directories(main PRIVATE include)
target_include_directories(main PRIVATE assets)
target_link_libraries(main PRIVATE raylib)
