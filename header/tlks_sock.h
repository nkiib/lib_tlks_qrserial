/**
 * @file tlks_sock.h
 * @author Koki Nishida
 */

#ifndef TLKS_SOCK_H
#define TLKS_SOCK_H

#include <asm-generic/termbits-common.h>

extern int tlks_open_serialsock(int *fd, char *device_path, speed_t baudrate);

extern int tlks_close_serialsock(int *fd);

#endif