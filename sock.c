/**
 * @file sock.c
 * 
 * @brief シリアルソケットの確保とクローズを行う関数の実装
 * 
 * @copyright Copyright (c) 2025 Tlooks
 */

#include "header/tlks_sock.h"

#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>

/**
 * @brief シリアルソケットを確保する関数
 * 
 * @param[out] fd シリアルソケットのファイルディスクリプタを格納するポインタ
 * @param[out] device_path シリアルデバイスのパスを格納するポインタ
 * @param[out] baudrate ボーレートを格納するポインタ
 *
 * @return 0=成功, 負の数=エラーコード
 * 
 * @note 成功した場合、内部でシリアルポートを確保するため、tlks_close_serialsock関数を呼び出して
 *       シリアルポートを閉じる必要があります。
 */
int tlks_open_serialsock(int *fd, char *device_path, speed_t baudrate) {
    struct termios options;
    int retval = 0;

    /* NULLのチェック */
    if (fd == NULL || device_path == NULL) {
        return -EINVAL; 
    }

    /* シリアルの確保とファイルディスクリプタの設定 */
    *fd = open(device_path, O_RDWR | O_NOCTTY | O_NDELAY);
    if (*fd < 0) {
        retval = errno;
        perror("Error opening serial port");
        goto END;
    }

    tcgetattr(*fd, &options);
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);

    options.c_cflag |= (CLOCAL | CREAD); // ローカル接続と読み取りを有効にする
    options.c_cflag &= ~PARENB; // パリティビットを無効にする
    options.c_cflag &= ~CSTOPB; // ストップビットを1ビットに設定
    options.c_cflag &= ~CSIZE; // データビットサイズをクリア
    options.c_cflag |= CS8; // データビットサイズを8ビットに設定

    tcsetattr(*fd, TCSANOW, &options); // 設定を適用
    ioctl(*fd, TCSETS, &options); // シリアルポートの設定を適用

    return 0; // 成功

END:
    if (*fd >= 0) {
        close(*fd); // エラー時はソケットを閉じる
        *fd = -1; // ファイルディスクリプタをNULLに設定
    }
    return -retval; // エラーコードを返す
}

/**
 * @brief シリアルソケットを閉じる関数
 * 
 * @param[out] fd シリアルソケットのファイルディスクリプタ
 * 
 * @return 0=成功, 負の数=エラーコード
 */
int tlks_close_serialsock(int *fd) {
    int retval = 0;

    if (*fd < 0) {
        return -EBADF; // 無効なファイルディスクリプタ
    }

    retval = close(*fd);
    if (retval < 0) {
        perror("Error closing serial port");
        return -errno; // シリアルポートのクローズに失敗
    }

    *fd = -1; // ファイルディスクリプタをNULLに設定

    return 0; // 成功
}