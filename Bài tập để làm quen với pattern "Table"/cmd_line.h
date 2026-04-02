/**
 ******************************************************************************
 * @file    cmd_line.h
 * @brief   Command line parser header (table-driven design)
 * @author  You
 ******************************************************************************
 */

#ifndef __CMD_LINE_H__
#define __CMD_LINE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* ===================== CONFIG ===================== */

/**
 * @brief Max length of command keyword
 * Ví dụ: "temperature" (11 ký tự) vẫn OK
 */
#define MAX_CMD_SIZE            12

/* ===================== RETURN CODE ===================== */

/**
 * @brief Command table is NULL
 */
#define CMD_TBL_NOT_FOUND       0

/**
 * @brief Command executed successfully
 */
#define CMD_SUCCESS             1

/**
 * @brief Command not found in table
 */
#define CMD_NOT_FOUND           2

/**
 * @brief Command keyword too long
 */
#define CMD_TOO_LONG            3

/* ===================== TYPE DEFINITIONS ===================== */

/**
 * @brief Function pointer cho command handler
 * @param argv: full command string (vd: "led on 1")
 */
typedef int32_t (*pf_cmd_func)(uint8_t* argv);

/**
 * @brief Command table structure
 */
typedef struct {
    const int8_t* cmd;   // command keyword (vd: "led")
    pf_cmd_func func;    // handler function
    const int8_t* info;  // mô tả (optional)
} cmd_line_t;

/* ===================== API ===================== */

/**
 * @brief Parse command và gọi function tương ứng
 * 
 * @param cmd_table: bảng command
 * @param command: chuỗi input
 * 
 * @return:
 *  - CMD_SUCCESS
 *  - CMD_NOT_FOUND
 *  - CMD_TOO_LONG
 *  - CMD_TBL_NOT_FOUND
 */
uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command);

#ifdef __cplusplus
}
#endif

#endif // __CMD_LINE_H__
