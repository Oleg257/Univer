#include "../src/board/board.h"
#include "../thirdparty/ctest.h"

CTEST(board_suite, ctest_initialize_board_test)
{
    initialize_board();

    int num = 1;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] != num++) {
                ASSERT_TRUE(0);
            }
        }
    }
    ASSERT_TRUE(is_solved());

    ASSERT_TRUE(1);
}

CTEST(board_suite, ctest_mixing_board_test)
{
    mixing_board();

    int count[SIZE * SIZE] = {0};
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int num = board[row][col];
            count[num]++;
            ASSERT_TRUE(num >= 0 && num < SIZE * SIZE);
        }
    }
    for (int i = 0; i < SIZE * SIZE; i++) {
        ASSERT_TRUE(count[i] == 1);
    }
}

CTEST(board_suite, ctest_make_move_test)
{
    initialize_board();

    make_move('w');
    ASSERT_EQUAL(0, board[2][3]);
    ASSERT_EQUAL(12, board[3][3]);
    make_move('s');
    ASSERT_EQUAL(0, board[3][3]);
    ASSERT_EQUAL(12, board[2][3]);
    make_move('a');
    ASSERT_EQUAL(0, board[3][2]);
    ASSERT_EQUAL(15, board[3][3]);
    make_move('d');
    ASSERT_EQUAL(0, board[3][3]);
    ASSERT_EQUAL(15, board[3][2]);
}

CTEST(board_suite, ctest_print_board_test)
{
    initialize_board();
    print_board();

    ASSERT_EQUAL(1, board[0][0]);
    ASSERT_EQUAL(2, board[0][1]);
    ASSERT_EQUAL(3, board[0][2]);
    ASSERT_EQUAL(4, board[0][3]);
    ASSERT_EQUAL(5, board[1][0]);
    ASSERT_EQUAL(6, board[1][1]);
    ASSERT_EQUAL(7, board[1][2]);
    ASSERT_EQUAL(8, board[1][3]);
    ASSERT_EQUAL(9, board[2][0]);
    ASSERT_EQUAL(10, board[2][1]);
    ASSERT_EQUAL(11, board[2][2]);
    ASSERT_EQUAL(12, board[2][3]);
    ASSERT_EQUAL(13, board[3][0]);
    ASSERT_EQUAL(14, board[3][1]);
    ASSERT_EQUAL(15, board[3][2]);
}