BUILD_PATH=../bin/
CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
EXTRAFLAGS=-fsanitize=leak -fsanitize=address -fsanitize=undefined -fsanitize=unreachable -fno-sanitize-recover -fstack-protector 

all: check rebuild

build: clean pong pong_extra pong_interactive pong_interactive_extra

rebuild: clean_all pong pong_extra pong_interactive pong_interactive_extra clean

pong: clean pong.c pong_engine.c
	$(CC) $(CFLAGS) pong.c pong_engine.c -o  $(BUILD_PATH)pong -lncurses

pong_extra: clean pong.c pong_engine.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) pong.c pong_engine.c -o  $(BUILD_PATH)pong_extra -lncurses

pong_interactive: clean pong_interactive.c pong_interactive_engine.c
	$(CC) $(CFLAGS) pong_interactive.c pong_interactive_engine.c -o  $(BUILD_PATH)pong_interactive -lncurses

pong_interactive_extra: clean pong_interactive.c pong_interactive_engine.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS)  pong_interactive.c pong_interactive_engine.c -o  $(BUILD_PATH)pong_interactive_extra -lncurses

clean_all:
	rm -rf *.o *.a *.so $(BUILD_PATH)*
	
clean:
	rm -rf *.o *.a

check:
	clang-format -n *.c
	clang-format -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

run:
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)pong
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes $(BUILD_PATH)pong_interactive

run_no_valgrind:
	$(BUILD_PATH)pong_extra
	$(BUILD_PATH)pong_interactive_extra


