/**
 * @file debug.c
 * 
 * @brief デバッグ用の処理
 * 
 * @copyright Copyright (c) 2025 Tlooks
 */

#include "header/tlks_qrserial.h"
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = -1;
    int retval = 0;
    char device_path[] = "/dev/serial/by-id/usb-DENSO_WAVE_INC._USB_Device-if00";
    speed_t baudrate = B9600;
    char buf[256];

    // QRコードのシリアル通信を初期化
    retval = tlks_open_serialsock(&fd, device_path, baudrate);
    if (retval != 0) {
        fprintf(stderr, "初期化失敗: %d\n", retval);
        return 1;
    }

    printf("QRコードシリアル通信が初期化されました。fd=%d\n", fd);

    // コマンドを送信
    tlks_send_command(fd, "ID2\r\n");

    tlks_read_signal(fd, buf, 256);

    printf("受信: %s\n", buf);

    tlks_close_serialsock(&fd);
    return 0;
}