#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "cmd_line.h"

// Biến toàn cục dùng để kiểm tra xem handler có được gọi hay không
static int g_called = 0;

// Hàm giả lập handler, mỗi lần được gọi sẽ tăng biến đếm
int32_t fake_handler(uint8_t* argv) {
    g_called++;
    return 0;
}

// Bảng lệnh mẫu để test, kết thúc bằng phần tử NULL
cmd_line_t test_table[] = {
    {(int8_t*)"led",   fake_handler, (int8_t*)"LED"},
    {(int8_t*)"reset", fake_handler, (int8_t*)"RESET"},
    {0, 0, 0}
};

// Mỗi test case chứa toàn bộ input + expected output
typedef struct {
    const char* name;       // Tên test case
    cmd_line_t* table;      // Bảng command đầu vào
    uint8_t* input;         // Chuỗi command test
    uint8_t expected_ret;   // Giá trị return mong đợi
    int expected_called;    // Số lần handler được gọi mong đợi
} test_case_t;

// Danh sách các kịch bản kiểm thử
test_case_t test_cases[] = {
    { "NULL table",        NULL,       (uint8_t*)"led on",  CMD_TBL_NOT_FOUND, 0 },
    { "Valid command",     test_table, (uint8_t*)"led on",  CMD_SUCCESS,       1 },
    { "Command not found", test_table, (uint8_t*)"abc",     CMD_NOT_FOUND,     0 },
    { "Command too long",  test_table, (uint8_t*)"12345...", CMD_TOO_LONG,     0 },
    { "Command with args", test_table, (uint8_t*)"reset n", CMD_SUCCESS,       1 }
};

// Hàm chạy một test case
void run_test(const test_case_t* tc) {
    g_called = 0; // reset trạng thái trước mỗi test

    uint8_t ret = cmd_line_parser(tc->table, tc->input);
    int pass = 1;

    // So sánh giá trị return
    if (ret != tc->expected_ret) {
        pass = 0;
        printf("[FAIL] %s: return = %d, expected = %d\n",
               tc->name, ret, tc->expected_ret);
    }

    // Kiểm tra handler có được gọi đúng số lần không
    if (g_called != tc->expected_called) {
        pass = 0;
        printf("[FAIL] %s: handler_called = %d, expected = %d\n",
               tc->name, g_called, tc->expected_called);
    }

    // In kết quả test
    if (pass) {
        printf("[PASS] %s\n", tc->name);
    }
}

// --- MAIN---
int main(void) {
    int total = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("Running %d tests...\n\n", total);

    // Lặp qua từng test case
    for (int i = 0; i < total; i++) {
        run_test(&test_cases[i]);
    }

    printf("\nDone.\n");
    return 0;
}
