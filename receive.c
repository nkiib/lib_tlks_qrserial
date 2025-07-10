#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>

/**
 * @brief シリアルからのデータを受け取る関数
 * 
 * @param fd シリアルポートのファイルディスクリプタ
 * @param buf 受信したデータを格納するバッファ
 * @param buf_size バッファのサイズ
 * 
 * @return 0=成功、負の数=エラーコード
 */
int tlks_read_signal(int fd, char* buf, size_t buf_size) {
    while (1) {
        int n = read(fd, buf, buf_size - 1);
        if (n > 0) {
            buf[n] = '\0'; // NULL終端
            break;
        } else if (n < 0) {
            perror("read");
            return -errno;
            break;
        }
    }

    return 0;
}