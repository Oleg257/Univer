CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = tag
TEST_TARGET = tag-test

SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = test
THIRDPARTYDIR = thirdparty

SRC_MAIN = $(SRCDIR)/main/main.c
SRC_BOARD = $(SRCDIR)/board/board.c
SRC_TEST_MAIN = $(TESTDIR)/main.c
SRC_TEST = $(TESTDIR)/test.c

OBJ_MAIN = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_MAIN))
OBJ_BOARD = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_BOARD))
OBJ_TEST_MAIN = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(SRC_TEST_MAIN))
OBJ_TEST = $(patsubst $(TESTDIR)/%.c,$(OBJDIR)/%.o,$(SRC_TEST))

all: $(BINDIR)/$(TARGET)

test: $(BINDIR)/$(TEST_TARGET)

$(BINDIR)/$(TARGET): $(OBJ_MAIN) $(OBJ_BOARD)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/$(TEST_TARGET): $(OBJ_BOARD) $(OBJ_TEST_MAIN) $(OBJ_TEST)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/board/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) -I$(THIRDPARTYDIR) -c $< -o $@


run_test: test
	./$(BINDIR)/$(TEST_TARGET)

tag: all
	./$(BINDIR)/$(TARGET)

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(OBJDIR)/main/*.o
	rm -f $(OBJDIR)/board/*.o

fclean: clean
	rm -f $(BINDIR)/$(TARGET) $(BINDIR)/$(TEST_TARGET)

.PHONY: all test clean fclean