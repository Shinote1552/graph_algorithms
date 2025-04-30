# Компиляторы
CC = gcc
CPP = g++

CFLAGS = -Wall -Werror -Wextra -std=c11
CPPFLAGS = -Wall -Werror -Wextra -std=c++17

STYLE_TYPE = --style=Google
CODE_FORMAT_UTIL = clang-format

DOT_SRC = ../data-samples/dot_structs/
DOT_IMG = ../data-samples/dot_images/

STL_STACK_SRC = graph_algorithms/data_structures/stack/
STL_QUEUE_SRC = graph_algorithms/data_structures/queue/

S21_GRAPH = graph/
S21_GRAPH_ALGORITHMS = graph_algorithms/
MATRIX = graph/matrix/
ACO = graph_algorithms/ACO/
BFS = graph_algorithms/BFS/
DFS = graph_algorithms/DFS/
DSA = graph_algorithms/DSA/
MST = graph_algorithms/MST/
S21_GRAPH_ALGORITHMS_UTILS = graph_algorithms/utils/

CLI_SRC = cli/

TEST_MAIN_DIR = test/
TEST_OUT_BIN = ../code-samples/test_bin/

CLI_BIN = ../code-samples/cli_bin/

TEST_GRAPH = graph/tests/
TEST_GRAPH_ALGORITHMS = graph_algorithms/tests/
GRAPH_WRAPPER = graph/tests/wrapper_for_gtest/
GRAPH_ALGORITHMS_WRAPPER = graph_algorithms/wrapper_for_gtest/

ACO_TEST = graph_algorithms/ACO/tests/
BFS_TEST = graph_algorithms/BFS/tests/
DFS_TEST = graph_algorithms/DFS/tests/
DSA_TEST = graph_algorithms/DSA/tests/
MST_TEST = graph_algorithms/MST/tests/

S21_GRAPH_OBJ = graph/obj/
S21_GRAPH_LIB = graph/lib/
S21_GRAPH_ALGORITHMS_LIB = graph_algorithms/lib/

STL_STACK_OBJ = graph_algorithms/data_structures/stack/obj/
STL_STACK_LIB = graph_algorithms/data_structures/stack/lib/
STL_QUEUE_OBJ = graph_algorithms/data_structures/queue/obj/
STL_QUEUE_LIB = graph_algorithms/data_structures/queue/lib/

MATRIX_OBJ = graph/matrix/obj/

ACO_OBJ = graph_algorithms/ACO/obj/
BFS_OBJ = graph_algorithms/BFS/obj/
DFS_OBJ = graph_algorithms/DFS/obj/
DSA_OBJ = graph_algorithms/DSA/obj/
MST_OBJ = graph_algorithms/MST/obj/
S21_GRAPH_ALGORITHMS_UTILS_OBJ = graph_algorithms/utils/obj/

CLI_OBJ = cli/obj/

SETUP_DIRS = \
$(S21_GRAPH_LIB) \
$(S21_GRAPH_OBJ) \
$(S21_GRAPH_ALGORITHMS_LIB) \
$(MATRIX_OBJ) \
$(STL_STACK_OBJ) \
$(STL_STACK_LIB) \
$(STL_QUEUE_OBJ) \
$(STL_QUEUE_LIB) \
$(ACO_OBJ) \
$(BFS_OBJ) \
$(DFS_OBJ) \
$(DSA_OBJ) \
$(MST_OBJ) \
$(S21_GRAPH_ALGORITHMS_UTILS_OBJ) \
$(DOT_IMG) \
$(DOT_SRC) \
$(CLI_OBJ) \
$(CLI_BIN) \
$(TEST_OUT_BIN)

CODE_FILES = \
	$(wildcard $(TEST_MAIN_DIR)/*.cpp) \
    $(wildcard $(TEST_MAIN_DIR)/*.h) \
    $(wildcard $(TEST_GRAPH)/*.cpp) \
    $(wildcard $(TEST_GRAPH)/*.h) \
    $(wildcard $(TEST_GRAPH_ALGORITHMS)/*.cpp) \
    $(wildcard $(TEST_GRAPH_ALGORITHMS)/*.h) \
    $(wildcard $(GRAPH_WRAPPER)/*.cpp) \
    $(wildcard $(GRAPH_WRAPPER)/*.h) \
    $(wildcard $(GRAPH_ALGORITHMS_WRAPPER)/*.cpp) \
    $(wildcard $(GRAPH_ALGORITHMS_WRAPPER)/*.h) \
    $(wildcard $(TEST_MATRIX)/*.cpp) \
    $(wildcard $(TEST_MATRIX)/*.h) \
    $(wildcard $(ACO_TEST)/*.cpp) \
    $(wildcard $(ACO_TEST)/*.h) \
    $(wildcard $(BFS_TEST)/*.cpp) \
    $(wildcard $(BFS_TEST)/*.h) \
    $(wildcard $(DFS_TEST)/*.cpp) \
    $(wildcard $(DFS_TEST)/*.h) \
    $(wildcard $(DSA_TEST)/*.cpp) \
    $(wildcard $(DSA_TEST)/*.h) \
    $(wildcard $(MST_TEST)/*.cpp) \
    $(wildcard $(MST_TEST)/*.h) \
    $(wildcard $(STL_STACK_SRC)/*.cpp) \
    $(wildcard $(STL_STACK_SRC)/*.h) \
    $(wildcard $(STL_QUEUE_SRC)/*.cpp) \
    $(wildcard $(STL_QUEUE_SRC)/*.h) \
    $(wildcard $(S21_GRAPH)/*.c) \
    $(wildcard $(S21_GRAPH)/*.h) \
    $(wildcard $(S21_GRAPH_ALGORITHMS)/*.c) \
    $(wildcard $(S21_GRAPH_ALGORITHMS)/*.h) \
	$(wildcard $(MATRIX)/*.c) \
    $(wildcard $(MATRIX)/*.h) \
	$(wildcard $(S21_GRAPH_ALGORITHMS_UTILS)/*.c) \
	$(wildcard $(S21_GRAPH_ALGORITHMS_UTILS)/*.h) \
	$(wildcard $(ACO)/*.c) \
	$(wildcard $(ACO)/*.h) \
	$(wildcard $(BFS)/*.c) \
	$(wildcard $(BFS)/*.h) \
	$(wildcard $(DFS)/*.c) \
	$(wildcard $(DFS)/*.h) \
	$(wildcard $(DSA)/*.c) \
	$(wildcard $(DSA)/*.h) \
	$(wildcard $(MST)/*.c) \
	$(wildcard $(MST)/*.h)

# Файлы для компиляции тестов

TEST_SOURCES = \
	$(wildcard $(TEST_MAIN_DIR)/*.cpp) \
    $(wildcard $(TEST_GRAPH)/*.cpp) \
    $(wildcard $(TEST_GRAPH_ALGORITHMS)/*.cpp) \
    $(wildcard $(ACO_TEST)/*.cpp) \
    $(wildcard $(BFS_TEST)/*.cpp) \
    $(wildcard $(DFS_TEST)/*.cpp) \
    $(wildcard $(DSA_TEST)/*.cpp) \
    $(wildcard $(MST_TEST)/*.cpp) \
    $(wildcard $(GRAPH_WRAPPER)/*.cpp) \
    $(wildcard $(GRAPH_ALGORITHMS_WRAPPER)/*.cpp)

UNAME_S := $(shell uname -s)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(OS),Windows_NT)  # Windows (MSYS2, MinGW)
	LIBS = -lgtest -lgmock -pthread
	INCLUDE_PATHS = -IE:/MSYS2/ucrt64/include
	LIBRARY_PATHS = -LE:/MSYS2/ucrt64/lib
	STATIC_LIBS = -lstdc++ -static

	COLOR_RESET = 
	COLOR_GREEN = 
	COLOR_YELLOW = 
	COLOR_ORANGE =
	COLOR_RED = 
	COLOR_BLUE = 
	COLOR_PURPLE = 
	COLOR_CYAN = 
	COLOR_WHITE = 
	COLOR_BOLD = 
	
	PREF_TO_PRINT = echo "
	POSTF_TO_PRINT = "
	POSTF_TO_COLOR = $(COLOR_RESET)

else ifeq ($(UNAME_S),Linux)  # Linux
	LIBS = -lgtest -lgmock -pthread -lm -lrt
	INCLUDE_PATHS =
	LIBRARY_PATHS =
	STATIC_LIBS = -lstdc++ -static

	COLOR_RESET = \033[0m
	COLOR_BLACK = \033[40m
	COLOR_GREEN = \033[32m
	COLOR_YELLOW = \033[33m
	COLOR_ORANGE = \033[38;5;208m
	COLOR_RED = \033[31m
	COLOR_BLUE = \033[34m
	COLOR_PURPLE = \033[35m
	COLOR_CYAN = \033[36m
	COLOR_WHITE = \033[37m
	COLOR_BOLD = \033[1m
	
	PREF_TO_PRINT = echo "
	POSTF_TO_PRINT = "
	POSTF_TO_COLOR = $(COLOR_RESET)
else ifeq ($(UNAME_S),Darwin)  # macOS
	LIBS = -lgtest -lgmock -pthread
	INCLUDE_PATHS = -I/usr/local/include
	LIBRARY_PATHS = -L/usr/local/lib

# macOS 10.x
	STATIC_LIBS = -lstdc++ -static -Wl,-no_pie

	COLOR_RESET = \033[0m
	COLOR_BLACK = \033[40m
	COLOR_GREEN = \033[32m
	COLOR_YELLOW = \033[33m
	COLOR_ORANGE = \033[38;5;208m
	COLOR_RED = \033[31m
	COLOR_BLUE = \033[34m
	COLOR_PURPLE = \033[35m
	COLOR_CYAN = \033[36m
	COLOR_WHITE = \033[37m
	COLOR_BOLD = \033[1m

	PREF_TO_PRINT = echo "
	POSTF_TO_PRINT = "
	POSTF_TO_COLOR = $(COLOR_RESET)
else
	$(error Unsupported operating system to build with make: $(UNAME_S))
endif

# MAIN TARGETS
all: \
main_asist
reb: \
clean main_asist
main_asist: \
format test


run_tests: 
	./../code-samples/test_bin/main_test

run_cli:
	./../code-samples/cli_bin/GAC

run_cli_static:
	./../code-samples/cli_bin/GAC_static

cli: \
../../code-samples/cli_bin/GAC \
cli_builded_message

cli_static: \
../../code-samples/cli_bin/GAC_static \
cli_static_builded_message

test: ../../code-samples/test_bin/main_test
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_RED) .Running tests -> ............... $(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@./../code-samples/test_bin/main_test
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_RED) ............... -> Tests completed. $(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

gcov_report: setup_dirs ./../code-samples/test_bin/main_test_gcov
	@echo "Running tests with coverage..."
	@./../code-samples/test_bin/main_test_gcov
	@echo "Generating coverage data..."
	@lcov --directory . --capture --output-file ./../code-samples/test_bin/coverage.info
	@lcov --ignore-errors inconsistent,unused --extract ./../code-samples/test_bin/coverage.info \
        "$(PWD)/graph/*" \
        "$(PWD)/graph_algorithms/*" \
        "$(PWD)/graph_algorithms/ACO/*" \
        "$(PWD)/graph_algorithms/BFS/*" \
        "$(PWD)/graph_algorithms/DFS/*" \
        "$(PWD)/graph_algorithms/DSA/*" \
        "$(PWD)/graph_algorithms/MST/*" \
        --output-file ./../code-samples/test_bin/filtered.info
	@genhtml ./../code-samples/test_bin/filtered.info --output-directory ./../code-samples/test_bin/coverage_report
	@open ./../code-samples/test_bin/coverage_report/index.html
	@lcov --list ./../code-samples/test_bin/filtered.info

# MAIN TARGETS

mem_leaks:
	CK_FORK=no valgrind -s --track-origins=yes --tool=memcheck --leak-check=full \
	--show-leak-kinds=all --log-file=RESULT_VALGRIND.txt ../code-samples/cli_bin/GAC

filter:
	lcov --ignore-errors empty,unused,inconsistent --extract res.info $(GCOV_FILTERED_FILES) -o res_filtered.info

clean:
	@rm -rf $(SETUP_DIRS) $(TEST_OUT_BIN)main_test *.gcno *.gcda\
	coverage.info coverage.info \
	./../code-samples/test_bin/coverage_report \
	coverage_report
	@$(PREF_TO_PRINT)$(COLOR_RED)Project cleaned.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

setup_dirs:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_GREEN)^_^ Setup_dirs... $(SETUP_DIRS)$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@mkdir -p $(SETUP_DIRS)

ALL_LIB_FTEST = \
$(S21_GRAPH_ALGORITHMS_LIB)s21_graph_algorithms.a \
$(S21_GRAPH_LIB)s21_graph.a \
$(STL_STACK_LIB)stack.a \
$(STL_QUEUE_LIB)queue.a

ALL_LIB_FCLI = \
$(CLI_OBJ)graph_algorithms_cli.o \
$(ALL_LIB_FTEST)

ALL_LIB_FGCOV = \
$(MATRIX_OBJ)matrix.o \
$(S21_GRAPH_OBJ)s21_graph_gcov.o \
$(ACO_OBJ)ant_colony_optimization_gcov.o \
$(BFS_OBJ)breadth_first_search_gcov.o \
$(DFS_OBJ)depth_first_search_gcov.o \
$(DSA_OBJ)dijkstra_gcov.o \
$(DSA_OBJ)floyd_warshall_gcov.o \
$(MST_OBJ)prims_gcov.o \
$(S21_GRAPH_ALGORITHMS_UTILS_OBJ)utils_gcov.o \
$(STL_STACK_LIB)stack.a \
$(STL_QUEUE_LIB)queue.a

CPP_COMPILE_PROCESS = $(CPP) $(CPPFLAGS) 
CC_COMPILE_PROCESS = $(CC) $(CFLAGS)

../../code-samples/test_bin/main_test: \
s21_graph \
s21_graph_algorithms \
lines_stl_start \
stack \
lines_stl_end \
queue \
lines_stl_medium
	@$(CPP_COMPILE_PROCESS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) \
    $(TEST_SOURCES) \
    $(ALL_LIB_FTEST) $(LIBS) -o $(TEST_OUT_BIN)main_test

./../code-samples/test_bin/main_test_gcov: \
graph/matrix/obj/matrix.o \
graph/obj/s21_graph_gcov.o \
graph_algorithms/ACO/obj/ant_colony_optimization_gcov.o \
graph_algorithms/BFS/obj/breadth_first_search_gcov.o \
graph_algorithms/DFS/obj/depth_first_search_gcov.o \
graph_algorithms/DSA/obj/dijkstra_gcov.o \
graph_algorithms/DSA/obj/floyd_warshall_gcov.o \
graph_algorithms/MST/obj/prims_gcov.o \
graph_algorithms/utils/obj/utils_gcov.o \
stack \
queue
	@$(CPP_COMPILE_PROCESS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) \
	$(TEST_SOURCES) \
	$(ALL_LIB_FGCOV) $(LIBS) $(GCOV_FLAGS) -o $(TEST_OUT_BIN)main_test_gcov

../../code-samples/cli_bin/GAC: \
s21_graph \
s21_graph_algorithms \
lines_stl_start \
stack \
lines_stl_end \
queue \
lines_stl_medium \
lines_cli_start \
cli/obj/graph_algorithms_cli.o \
lines_cli_end
	@$(CC_COMPILE_PROCESS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) \
	$(ALL_LIB_FCLI) $(LIBS) -lstdc++ -o $(CLI_BIN)GAC

../../code-samples/cli_bin/GAC_static: \
s21_graph \
s21_graph_algorithms \
lines_stl_start \
stack \
lines_stl_end \
queue \
lines_stl_medium \
lines_cli_start \
cli/obj/graph_algorithms_cli.o \
lines_cli_end
	@$(CC_COMPILE_PROCESS) $(STATIC_LIBS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) \
	$(ALL_LIB_FCLI) $(LIBS) -lstdc++ -o $(CLI_BIN)GAC_static

s21_graph_algorithms: \
setup_dirs \
lines_graph_algorithms_start \
graph_algorithms/lib/s21_graph_algorithms.a \
lines_graph_algorithms_end

s21_graph: \
setup_dirs \
lines_graph_start \
graph/lib/s21_graph.a \
lines_graph_end

stack: \
graph_algorithms/data_structures/stack/lib/stack.a
queue: \
graph_algorithms/data_structures/queue/lib/queue.a

S21_GRAPH_ALGORITHMS_DELIMETR = @$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLUE)___GRAPH_ALGORITHMS_______________________________$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
lines_graph_algorithms_start: 
	$(S21_GRAPH_ALGORITHMS_DELIMETR)	
lines_graph_algorithms_end: 
	$(S21_GRAPH_ALGORITHMS_DELIMETR)	
S21_GRAPH_DELIMETR = @$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_ORANGE)___GRAPH__________________________________________$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
lines_graph_start: 
	$(S21_GRAPH_DELIMETR)	
lines_graph_end: 
	$(S21_GRAPH_DELIMETR)

STL_DELIMETR = @$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_PURPLE)___STL____________________________________________$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
lines_stl_start: 
	$(STL_DELIMETR)	
lines_stl_medium:
	$(STL_DELIMETR)
lines_stl_end: 
	$(STL_DELIMETR)

CLI_DELIMETR = @$(PREF_TO_PRINT)$(COLOR_BLUE)$(COLOR_RED)___CLI____________________________________________$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
lines_cli_start: 
	$(CLI_DELIMETR)
lines_cli_end: 
	$(CLI_DELIMETR)
cli_builded_message:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLUE)\n\nCLI builded. Path =\t$(CLI_BIN)GAC$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
cli_static_builded_message:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLUE)\n\nCLI_static builded. Path =\t$(CLI_BIN)GAC_static$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

# STATIC LIBS
graph_algorithms/lib/s21_graph_algorithms.a: \
graph_algorithms/ACO/obj/ant_colony_optimization.o \
graph_algorithms/BFS/obj/breadth_first_search.o \
graph_algorithms/DFS/obj/depth_first_search.o \
graph_algorithms/DSA/obj/dijkstra.o \
graph_algorithms/DSA/obj/floyd_warshall.o \
graph_algorithms/MST/obj/prims.o \
graph_algorithms/utils/obj/utils.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLUE)\tBuilding static lib s21_graph_algorithms.a...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

	@ar rcs \
	$(S21_GRAPH_ALGORITHMS_LIB)s21_graph_algorithms.a \
	$(ACO_OBJ)ant_colony_optimization.o \
	$(BFS_OBJ)breadth_first_search.o \
	$(DFS_OBJ)depth_first_search.o \
	$(DSA_OBJ)dijkstra.o \
	$(DSA_OBJ)floyd_warshall.o \
	$(MST_OBJ)prims.o \
	$(S21_GRAPH_ALGORITHMS_UTILS_OBJ)utils.o

	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLUE)\tstatic s21_graph_algorithms built.\n\tIn: $(S21_GRAPH_ALGORITHMS_LIB)s21_graph_algorithms.a$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph/lib/s21_graph.a: \
graph/obj/s21_graph.o \
graph/matrix/obj/matrix.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_ORANGE)\tBuilding static lib s21_graph.a...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

	@ar rcs \
	$(S21_GRAPH_LIB)s21_graph.a \
	$(S21_GRAPH_OBJ)s21_graph.o \
	$(MATRIX_OBJ)matrix.o

	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_ORANGE)\tstatic s21_graph built.\n\tIn: $(S21_GRAPH_LIB)s21_graph_algorithms.a$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/data_structures/stack/lib/stack.a: \
graph_algorithms/data_structures/stack/obj/stack.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_PURPLE)\tBuilding static lib stack.a...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

	@ar rcs $(STL_STACK_LIB)stack.a \
	$(STL_STACK_OBJ)stack.o

	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_PURPLE)\tstatic stack built.\n\tIn: $(STL_STACK_LIB)stack.a$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
graph_algorithms/data_structures/queue/lib/queue.a: \
graph_algorithms/data_structures/queue/obj/queue.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_PURPLE)\tBuilding static lib queue.a...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

	@ar rcs \
	$(STL_QUEUE_LIB)queue.a \
	$(STL_QUEUE_OBJ)queue.o

	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_PURPLE)\tstatic queue built.\n\tIn: $(STL_QUEUE_LIB)queue.a$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
# STATIC LIBS END

# OBJ LIBS
graph/obj/s21_graph.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_YELLOW)\t\tCompiling s21_graph.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(S21_GRAPH)s21_graph.c  -o $(S21_GRAPH_OBJ)s21_graph.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_YELLOW)\t\ts21_graph.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph/matrix/obj/matrix.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)\t\tCompiling matrix.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(MATRIX)matrix.c -o $(MATRIX_OBJ)matrix.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)\t\tmatrix.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/ACO/obj/ant_colony_optimization.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling ant_colony_optimization.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(ACO)ant_colony_optimization.c -o $(ACO_OBJ)ant_colony_optimization.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tant_colony_optimization.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/BFS/obj/breadth_first_search.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling breadth_first_search.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(BFS)breadth_first_search.c -o $(BFS_OBJ)breadth_first_search.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tbreadth_first_search.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/DFS/obj/depth_first_search.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling depth_first_search.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(DFS)depth_first_search.c -o $(DFS_OBJ)depth_first_search.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tdepth_first_search.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/DSA/obj/dijkstra.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling dijkstra.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(DSA)dijkstra.c -o $(DSA_OBJ)dijkstra.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tdijkstra.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/DSA/obj/floyd_warshall.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling floyd_warshall.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(DSA)floyd_warshall.c -o $(DSA_OBJ)floyd_warshall.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tfloyd_warshall.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/MST/obj/prims.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling prims.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(MST)prims.c -o $(MST_OBJ)prims.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tprims.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/utils/obj/utils.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling utils.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(S21_GRAPH_ALGORITHMS_UTILS)utils.c -o $(S21_GRAPH_ALGORITHMS_UTILS_OBJ)utils.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tutils.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

cli/obj/graph_algorithms_cli.o:
	@$(PREF_TO_PRINT)$(COLOR_BLUE)$(COLOR_RED)\t\tCompiling graph_algorithms_cli.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(CLI_SRC)graph_algorithms_cli.c -o $(CLI_OBJ)graph_algorithms_cli.o
	@$(PREF_TO_PRINT)$(COLOR_BLUE)$(COLOR_RED)\t\tgraph_algorithms_cli.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	
# Компиляция C++ файлов в .o
graph_algorithms/data_structures/stack/obj/stack.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)\t\tCompiling stack.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CPP_COMPILE_PROCESS) -c $(STL_STACK_SRC)stack.cpp -o $(STL_STACK_OBJ)stack.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)\t\tstack.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/data_structures/queue/obj/queue.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)\t\tCompiling queue.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CPP_COMPILE_PROCESS) -c $(STL_QUEUE_SRC)queue.cpp -o $(STL_QUEUE_OBJ)queue.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)\t\tqueue.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)


# GCOV
graph/obj/s21_graph_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_YELLOW)\t\tCompiling s21_graph.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(S21_GRAPH)s21_graph.c $(GCOV_FLAGS)  -o $(S21_GRAPH_OBJ)s21_graph_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_YELLOW)\t\ts21_graph_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/ACO/obj/ant_colony_optimization_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling ant_colony_optimization.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(ACO)ant_colony_optimization.c $(GCOV_FLAGS) -o $(ACO_OBJ)ant_colony_optimization_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tant_colony_optimization_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/BFS/obj/breadth_first_search_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling breadth_first_search.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(BFS)breadth_first_search.c $(GCOV_FLAGS) -o $(BFS_OBJ)breadth_first_search_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tbreadth_first_search_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/DFS/obj/depth_first_search_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling depth_first_search.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(DFS)depth_first_search.c -o $(DFS_OBJ)depth_first_search_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tdepth_first_search_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/DSA/obj/dijkstra_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling dijkstra.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(DSA)dijkstra.c $(GCOV_FLAGS) -o $(DSA_OBJ)dijkstra_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tdijkstra_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/DSA/obj/floyd_warshall_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling floyd_warshall.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(DSA)floyd_warshall.c $(GCOV_FLAGS) -o $(DSA_OBJ)floyd_warshall_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tfloyd_warshall_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/MST/obj/prims_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling prims.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(MST)prims.c $(GCOV_FLAGS) -o $(MST_OBJ)prims_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tprims_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

graph_algorithms/utils/obj/utils_gcov.o:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tCompiling utils.o...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@$(CC_COMPILE_PROCESS) -c $(S21_GRAPH_ALGORITHMS_UTILS)utils.c $(GCOV_FLAGS) -o $(S21_GRAPH_ALGORITHMS_UTILS_OBJ)utils_gcov.o
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_CYAN)\t\tutils_gcov.o compiled.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

# OBJ LIBS END

check-style:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLACK)Checking code style...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@echo $(CODE_FILES) | xargs -n 1 $(CODE_FORMAT_UTIL) $(STYLE_TYPE) -n
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLACK)Code style check completed.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)

format:
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLACK)Formatting code...$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)
	@echo $(CODE_FILES) | xargs -n 1 $(CODE_FORMAT_UTIL) $(STYLE_TYPE) -i
	@$(PREF_TO_PRINT)$(COLOR_BOLD)$(COLOR_BLACK)Code formatting completed.$(POSTF_TO_COLOR)$(POSTF_TO_PRINT)