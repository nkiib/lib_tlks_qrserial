/**
 * @file command.c
 * 
 * @brief コマンドを送受信する関数の実装
 * 
 * @copyright Copyright (c) 2025 Tlooks
 */

#include "header/tlks_command.h"

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

/**
 * @brief コマンドをシリアルポートに送信する関数
 * 
 * @param fd シリアルポートのファイルディスクリプタ
 * @param cmd 送信するコマンド文字列
 * 
 * @return 0=成功、負の数=エラーコード
 */
int tlks_send_command(int fd, const char *cmd) {
    size_t total = 0;
    size_t length = strlen(cmd);

    while (total < length) {
        ssize_t written = write(fd, cmd + total, length - total);
        if (written < 0) {
            perror("write");
            return -errno;
        }
        total += written;
    }

    return (int)total;
}

/**
 * @brief シリアルからレスポンスを受ける関数
 * 
 * @param[in] fd シリアルポートのファイルディスクリプタ
 * @param[out] buf 受信したデータを格納するバッファ
 * @param[in] buf_size バッファのサイズ
 * 
 * @return 0=成功、負の数=エラーコード
 */
int tlks_read_response(int fd, char *buf, size_t buf_size) {
    int len;
    int retval;
    
    len = read(fd, buf, buf_size - 1);
    if (len < 0) {
        retval = errno;
        perror("read");
        return -retval;
    }

    buf[len] = '\0'; // Null終端
    return len;
}