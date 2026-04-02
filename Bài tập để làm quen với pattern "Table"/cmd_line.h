#ifndef __CMD_LINE_H__
#define __CMD_LINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define MAX_CMD_SIZE            12  // Độ dài tối đa của từ khóa lệnh

#define CMD_TBL_NOT_FOUND       0   // Bảng lệnh rỗng
#define CMD_SUCCESS             1   // Thực thi thành công
#define CMD_NOT_FOUND           2   // Không tìm thấy lệnh
#define CMD_TOO_LONG            3   // Lệnh quá dài


// Hàm xử lý lệnh (nhận vào chuỗi tham số)
typedef int32_t (*pf_cmd_func)(uint8_t* argv);

// Cấu trúc bảng lệnh
typedef struct {
    const int8_t* cmd;    // Từ khóa lệnh (vd: "led")
    pf_cmd_func func;     // Hàm xử lý
    const int8_t* info;   // Mô tả lệnh
} cmd_line_t;


// Phân tích chuỗi và gọi hàm tương ứng từ bảng lệnh
uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command);

#ifdef __cplusplus
}
#endif

#endif // __CMD_LINE_H__
