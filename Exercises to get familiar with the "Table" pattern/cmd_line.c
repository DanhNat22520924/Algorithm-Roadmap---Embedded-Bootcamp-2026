#include <string.h>
#include "cmd_line.h"

// Parse lệnh và thực thi handler tương ứng
uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command) {

    uint8_t cmd[MAX_CMD_SIZE];  // Buffer lưu từ khóa lệnh
    uint8_t* p_command = command;
    uint8_t cmd_index = 0;
    uint8_t index_check = 0;

    // --- KIỂM TRA ĐẦU VÀO ---
    if (cmd_table == (cmd_line_t*)0) {
        return CMD_TBL_NOT_FOUND;
    }

    // --- TÁCH TỪ KHÓA LỆNH (Vd: "led on 1" -> "led") ---
    while (*p_command) {
        // Kết thúc khi gặp khoảng trắng hoặc xuống dòng
        if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') {
            cmd[cmd_index] = 0;
            break;
        } 
        else {
            cmd[cmd_index++] = *(p_command++);

            // Kiểm tra tràn buffer từ khóa
            if (cmd_index >= MAX_CMD_SIZE) {
                return CMD_TOO_LONG;
            }
        }
    }

    // Đảm bảo kết thúc chuỗi nếu lệnh không có khoảng trắng
    if (cmd_index > 0 && cmd[cmd_index - 1] != 0) {
        cmd[cmd_index] = 0;
    }

    // --- TÌM KIẾM TRONG BẢNG LỆNH ---
    while (cmd_table[index_check].cmd) {
        // So sánh từ khóa đã tách với bảng lệnh
        if (strcmp((const char*)cmd_table[index_check].cmd, 
                   (const char*)cmd) == 0) {
            
            // Thực thi hàm tương ứng và truyền toàn bộ chuỗi input
            cmd_table[index_check].func(command);
            return CMD_SUCCESS;
        }
        index_check++;
    }

    return CMD_NOT_FOUND; // Không tìm thấy lệnh phù hợp
}
