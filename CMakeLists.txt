cmake_minimum_required(VERSION 3.10)
project(FwBaseTest)

#Определяем операционную систему Windows или Linux
if(WIN32)
    add_compile_definitions(WINDOWS)
elseif(UNIX)
    add_compile_definitions(LINUX)
else()
    message(FATAL_ERROR "TARGET SYSTEM IS NOT WINDOWS OR UNIX-LIKE.")
endif()

# Путь к катклогу для генерируемых файлов
set(EXE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
# Путь к каталогу для исполнительных файлов
set(EXECUTABLE_OUTPUT_PATH ${EXE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${EXE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${EXE_OUTPUT_DIRECTORY})
# Путь к каталогу для дианмически подключаемых библиотек
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${EXE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${EXE_OUTPUT_DIRECTORY})
# Путь к каталогу для статических библиотек
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${EXE_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${EXE_OUTPUT_DIRECTORY})

# Стандарт языка
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Список директорий с заголовочными файлами
set(INCLUDES ./include ./src)

# Подключение библиотеки google для тестирования
add_subdirectory(googletest)

# Подключение стандартной библиотеки
if(WIN32)
    set(LIB)
elseif(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11)
    set(LIB stdc++fs)
endif()

# Список файлов с исходным кодом
set(CPP ./src/fw_base_test.cpp)

# СОЗДАНИЕ ДИРЕКТОРИИ BIN BUILD
FILE(MAKE_DIRECTORY ./bin ./build)

# Каталоги с include файлами
include_directories(${INCLUDES})

# Генерация исполняемого файла
add_executable(FwBaseTest ${CPP})

# Подключение библиотек
target_link_libraries(FwBaseTest gtest_main ${LIB})

# Включение тестирования
enable_testing()

include(GoogleTest)

gtest_discover_tests(FwBaseTest)