/**
 * @file tlks_command.h
 * @author Koki Nishida
 */

#ifndef TLKS_COMMAND_H
#define TLKS_COMMAND_H

#include <unistd.h>

int tlks_send_command(int fd, const char *cmd);

int tlks_read_response(int fd, char *buf, size_t buf_size);

int tlks_read_signal(int fd, char *buf, size_t buf_size);

#endif