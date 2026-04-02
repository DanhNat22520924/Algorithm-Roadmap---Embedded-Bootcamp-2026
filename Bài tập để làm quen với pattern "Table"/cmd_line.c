#include <string.h>
#include "cmd_line.h"

uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command) {

    uint8_t cmd[MAX_CMD_SIZE];   // buffer chứa keyword
    uint8_t* p_command = command;
    uint8_t cmd_index = 0;
    uint8_t index_check = 0;

    // Check table NULL
    if (cmd_table == (cmd_line_t*)0) {
        return CMD_TBL_NOT_FOUND;
    }

    // Lấy keyword đầu tiên (vd: "led" từ "led on 1")
    while (*p_command) {
        if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') {
            cmd[cmd_index] = 0;
            break;
        } else {
            cmd[cmd_index++] = *(p_command++);

            if (cmd_index >= MAX_CMD_SIZE) {
                return CMD_TOO_LONG;
            }
        }
    }

    // Trường hợp không có space (vd: "led")
    if (cmd_index > 0 && cmd[cmd_index - 1] != 0) {
        cmd[cmd_index] = 0;
    }

    // Duyệt table tìm command
    while (cmd_table[index_check].cmd) {

        if (strcmp((const char*)cmd_table[index_check].cmd,
                   (const char*)cmd) == 0) {

            // Gọi handler
            cmd_table[index_check].func(command);
            return CMD_SUCCESS;
        }

        index_check++;
    }

    return CMD_NOT_FOUND;
}
