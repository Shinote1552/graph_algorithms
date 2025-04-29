cmake_minimum_required(VERSION 3.12)
project(GraphAlgorithms C CXX)

# Настройки компилятора
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# Настройки для разных ОС
if(WIN32)
    # Пути к Google Test для Windows (MSYS2)
    set(GTEST_INCLUDE_DIR "E:/MSYS2/ucrt64/include")
    set(GTEST_LIBRARY_DIR "E:/MSYS2/ucrt64/lib")
    set(LIBS gtest gmock pthread)
    set(STATIC_LIBS -static -lstdc++)
elseif(APPLE)
    # macOS settings
    find_package(GTest REQUIRED)
    # Use the imported targets provided by FindGTest
    set(LIBS GTest::GTest GTest::Main gmock)
    # Don't use -static on macOS
    set(STATIC_LIBS "")
    # Add necessary system libraries
    find_library(COCOA_LIBRARY Cocoa)
    find_library(CORE_FOUNDATION_LIBRARY CoreFoundation)
    list(APPEND LIBS ${COCOA_LIBRARY} ${CORE_FOUNDATION_LIBRARY} pthread)
elseif(UNIX)
    # Linux settings
    find_package(GTest REQUIRED)
    set(LIBS GTest::GTest GTest::Main gmock pthread m rt)
    set(STATIC_LIBS -static -lstdc++)
endif()


# Подключение include-директорий
if(WIN32)
    include_directories(${GTEST_INCLUDE_DIR})
    link_directories(${GTEST_LIBRARY_DIR})
endif()

# Пути к директориям
set(ROOT_DIR ${CMAKE_SOURCE_DIR})
set(CODE_SAMPLES_DIR ${ROOT_DIR}/code-samples)
set(DATA_SAMPLES_DIR ${ROOT_DIR}/data-samples)
set(OUTPUT_BIN_DIR ${CODE_SAMPLES_DIR}/test_bin)
set(CLI_BIN_DIR ${CODE_SAMPLES_DIR}/cli_bin)

# Создание выходных директорий
file(MAKE_DIRECTORY ${OUTPUT_BIN_DIR})
file(MAKE_DIRECTORY ${CLI_BIN_DIR})

# Граф
add_library(s21_graph STATIC
    src/graph/s21_graph.c
    src/graph/matrix/matrix.c
)

target_include_directories(s21_graph PUBLIC
    ${ROOT_DIR}/src/graph
    ${ROOT_DIR}/src/graph/matrix
)

# Алгоритмы графа
add_library(s21_graph_algorithms STATIC
    src/graph_algorithms/ACO/ant_colony_optimization.c
    src/graph_algorithms/BFS/breadth_first_search.c
    src/graph_algorithms/DFS/depth_first_search.c
    src/graph_algorithms/DSA/dijkstra.c
    src/graph_algorithms/DSA/floyd_warshall.c
    src/graph_algorithms/MST/prims.c
    src/graph_algorithms/utils/utils.c
)

target_include_directories(s21_graph_algorithms PUBLIC
    ${ROOT_DIR}/src/graph_algorithms
    ${ROOT_DIR}/src/graph_algorithms/ACO
    ${ROOT_DIR}/src/graph_algorithms/BFS
    ${ROOT_DIR}/src/graph_algorithms/DFS
    ${ROOT_DIR}/src/graph_algorithms/DSA
    ${ROOT_DIR}/src/graph_algorithms/MST
    ${ROOT_DIR}/src/graph_algorithms/utils
)

# Структуры данных
add_library(stack STATIC src/graph_algorithms/data_structures/stack/stack.cpp)
target_include_directories(stack PUBLIC ${ROOT_DIR}/src/graph_algorithms/data_structures/stack)

add_library(queue STATIC src/graph_algorithms/data_structures/queue/queue.cpp)
target_include_directories(queue PUBLIC ${ROOT_DIR}/src/graph_algorithms/data_structures/queue)

# CLI (всегда динамическая сборка)
add_executable(GAC src/cli/graph_algorithms_cli.c)
target_link_libraries(GAC s21_graph s21_graph_algorithms stack queue ${LIBS} stdc++)
set_target_properties(GAC PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLI_BIN_DIR})

# Статическая сборка только для Windows и Linux
if(NOT APPLE)
    add_executable(GAC_static src/cli/graph_algorithms_cli.c)
    target_link_libraries(GAC_static s21_graph s21_graph_algorithms stack queue ${LIBS} ${STATIC_LIBS})
    set_target_properties(GAC_static PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CLI_BIN_DIR})
    
    # Добавляем цель run_cli_static только если статическая сборка доступна
    add_custom_target(run_cli_static COMMAND ${CLI_BIN_DIR}/GAC_static)
endif()

# Тесты
file(GLOB TEST_SOURCES
    src/test/*.cpp
    src/graph/tests/*.cpp
    src/graph_algorithms/tests/*.cpp
    src/graph_algorithms/ACO/tests/*.cpp
    src/graph_algorithms/BFS/tests/*.cpp
    src/graph_algorithms/DFS/tests/*.cpp
    src/graph_algorithms/DSA/tests/*.cpp
    src/graph_algorithms/MST/tests/*.cpp
    src/graph/tests/wrapper_for_gtest/*.cpp
    src/graph_algorithms/wrapper_for_gtest/*.cpp
)

add_executable(main_test ${TEST_SOURCES})
target_link_libraries(main_test 
    s21_graph 
    s21_graph_algorithms 
    stack 
    queue 
    ${LIBS}
)

if(APPLE)
    target_link_libraries(main_test 
        "-stdlib=libc++"
    )
endif()

set_target_properties(main_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

# Цели для удобства
add_custom_target(run_tests COMMAND ${OUTPUT_BIN_DIR}/main_test)
add_custom_target(run_cli COMMAND ${CLI_BIN_DIR}/GAC)

# Форматирование кода
find_program(CLANG_FORMAT "clang-format")
if(CLANG_FORMAT)
    file(GLOB_RECURSE ALL_SOURCE_FILES
        src/*.cpp
        src/*.h
        src/*.c
        src/*.hpp
    )
    
    add_custom_target(format_code
        COMMAND ${CLANG_FORMAT} -style=Google -i ${ALL_SOURCE_FILES}
        COMMENT "Formatting code..."
    )
    
    add_custom_target(check_style
        COMMAND ${CLANG_FORMAT} -style=Google -n ${ALL_SOURCE_FILES}
        COMMENT "Checking code style..."
    )
endif()

# Пользовательские цели
if(APPLE)
    add_custom_target(build_all DEPENDS main_test GAC)
else()
    add_custom_target(build_all DEPENDS main_test GAC GAC_static)
endif()

add_custom_target(rebuild_all COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target clean
                             COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target build_all)
add_custom_target(clean_build COMMAND ${CMAKE_COMMAND} -E remove_directory ${OUTPUT_BIN_DIR} ${CLI_BIN_DIR})
