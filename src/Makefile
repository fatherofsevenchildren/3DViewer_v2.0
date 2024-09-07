
CC				=	g++
CFLAGS		=	-Wall -Wextra $(WE)  -std=c++17
WE 				= -Werror
FSAN 			= -fsanitize=address
LDFLAGS 	= -lgtest -pthread -lgmock

GCFLAGS 	= -fprofile-arcs -ftest-coverage
VG_FLAGS	= --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
TEST 		= test
SRC_MODEL 	= $(wildcard ./backend/model/*.cpp)
SRC_AFFINE 	= $(wildcard ./backend/affine_strategy/*.cpp)

PRJ = pattern_3d_viwer
SRC	= $(wildcard ./backend/*/*.cpp)
OBJ	= $(SRC:.cc=.o) $(SRC:.cpp=.o)
BUILD_DIR = ../build/
TEST = test
LIB = l$(PRJ).a
FILE_TEST =	$(wildcard ./../unit_test/s21_*.cpp)

all: style_check gcov_report leaks dist dvi install open


%.o: %.cc %.cpp
	@ $(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJ)
	@	echo "+-------------------+"
	@	echo "|     MAKE_LIB      |"
	@	echo "+-------------------+"
	@	ar -rcs $(BUILD_DIR)$@ $^
	@ mkdir tmp
	@	find . -type f -name '*.o' | xargs -I {} sh -c 'mv {} ./tmp'

$(TEST): clean $(LIB)
	@ echo "+-------------------+"
	@ echo "|     UNIT_TEST     |"
	@ echo "+-------------------+"
	@ $(CC) $(CFLAGS) $(FILE_TEST) -L. $(BUILD_DIR)$(LIB) -o $(BUILD_DIR)$@ $(LDFLAGS)
	@ ./$(BUILD_DIR)$(TEST)

clean:
	@ echo "*--------------*"
	@ echo "|     CLEAN    |"
	@ echo "*--------------*"
	@ rm -f ./*.info ./$(BUILD_DIR)$(LIB) ./*.out ./$(BUILD_DIR)$(TEST)
	@ rm -rf ./tmp
	@ find . -type f -name '*.out' | xargs -I {} sh -c 'rm -f {}'
	@ find . -type f -name '*.o' | xargs -I {} sh -c 'echo "File deleted {} " && rm -f {}'
	@ find . -type f -name '*.gcno' -or -name '*.gcda' -or -name '$(PRJ).info' \
				| xargs -I {} sh -c 'echo "File deleted {} " && rm -f {}'
	@ rm -rf coverage test.dSYM *.zip

gcov_report: clean $(LIB)
	@ echo "+-------------------+"
	@ echo "|    GCOV_REPORT    |"
	@ echo "+-------------------+"
	@ $(CC) --coverage $(GCFLAGS) $(CFLAGS) $(LDFLAGS) $(FILE_TEST) $(BUILD_DIR)$(LIB) $(SRC) -o $(TEST)
	@ ./$(TEST)
	@ mv ./*_test.gcno ./*_test.gcda ./tmp
	@ mv ./$(TEST) $(BUILD_DIR)
	

install: uninstall
	@ echo "*-------------------------*"
	@ echo "| ┬─┬ノ( º _ ºノ) INSTALL |"
	@ echo "*-------------------------*"
	@ cd frontend/3dViwer && qmake && make && make clean && rm Makefile && mv 3dViwer.app ../../../build/3dViwer_2.0.app

uninstall:
	@ echo "*--------------------------*"
	@ echo "| ( ╯°□°)╯ ┻━━┻ UNINSTALL  |"
	@ echo "*--------------------------*"
	@ rm -rf $(BUILD_DIR)3dViwer_2.0.app

open:
	@ echo "*--------------------------------*"
	@ echo "|  ( ͡° ͜ʖ ͡° )つ──☆*:・ﾟ OPEN CALC |"
	@ echo "*--------------------------------*"
	@ open $(BUILD_DIR)
	@ ./../build/3dViwer_2.0.app/Contents/MacOS/3dViwer

dvi:
	@ echo "*---------------*"
	@ echo "|  OPEN README  |"
	@ echo "*---------------*"
	@ open readme.html

dist: clean
	@ echo "*---------------*"
	@ echo "|     DIST      |"
	@ echo "*---------------*"
	@ rm -rf ../Temp_3dViwer_2/
	@ mkdir ../Temp_3dViwer_2
	@ mkdir ../Temp_3dViwer_2/src
	@ cp -r ../src/* ../Temp_3dViwer_2/src
	@ mv ../Temp_3dViwer_2/src .
	@ zip -0rq 3dViwer_2.0.zip src
	@ rm -rf ../Temp_3dViwer_2 src

#! only for school Mac
docker_setup:
	@ echo "+-------------------+"
	@ echo "|    DOCKER_SETUP   |"
	@ echo "+-------------------+"
	@ rm -rf ~/Library/Containers/com.docker.docker
	@ mkdir -p ~/goinfre/Docker/Data
	@ ln -s ~/goinfre/Docker ~/Library/Containers/com.docker.docker
	@ open ~/../../Applications/Docker.app

valgrind_check:
	@ echo "+-------------------+"
	@ echo "|    DOCKER_RUN     |"
	@ echo "+-------------------+"
	@ sh $(BUILD_DIR)run.sh

valgrind:
	@	echo "+-------------------+"
	@	echo "|   VALGRIND_LEAK   |"
	@	echo "+-------------------+"
	@	CK_FORK=no valgrind  $(VG_FLAGS) ./$(BUILD_DIR)$(TEST)

leaks:
	@	echo "+-------------------+"
	@	echo "|     LEAKS_RUN     |"
	@	echo "+-------------------+"
	@	leaks -atExit -- ./$(BUILD_DIR)$(TEST)

style_check:
	@ echo "+-------------------+"
	@ echo "|    STYLE_CHECK    |"
	@ echo "+-------------------+"
	@ find . -type f -name '*.cc' -or -name '*.cpp' -or -name '*.h' | xargs -I {} sh -c 'echo "File {} checked" && clang-format -style=Google -n {}'
	@ clang-format -style=Google -n $(FILE_TEST)

style_set: clean
	@	echo "+-------------------+"
	@	echo "|     STYLE_SET     |"
	@	echo "+-------------------+"
	@	find . -type f -name '*.cc' -or -name '*.cpp' -or -name '*.h' | xargs -I {} sh -c 'echo "File {} set Google style" && clang-format -style=Google -i {}'
	@	clang-format -style=Google -i $(FILE_TEST)

rebuild: clean all




.PHONY: test

