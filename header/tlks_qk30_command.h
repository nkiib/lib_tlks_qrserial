/**
 * @file tlks_qk30_command.h
 * @author Koki Nishida
 */

#ifndef TLKS_QK30_COMMAND_H
#define TLKS_QK30_COMMAND_H

/*スピーカー鳴動 60ms*/
/* 60ms*/
#define TLKS_QK30_SP_SHORT "IT0\r\n"
/* 420ms */
#define TLKS_QK30_SP_LONG "IT1\r\n"

/* LED点灯 */
/* 青色点灯 */
#define TLKS_QK30_LED_BLUE "ID0\r\n"
/* 青色点滅 */
#define TLKS_QK30_LED_BLUE_F "ID1\r\n"
/* 緑色点灯 */
#define TLKS_QK30_LED_GREEN "ID2\r\n"
/* 緑色点滅 */
#define TLKS_QK30_LED_GREEN_F "ID3\r\n"
/* 赤色点灯 */
#define TLKS_QK30_LED_RED "ID4\r\n"
/* 赤色点滅 */
#define TLKS_QK30_LED_RED_F "ID5\r\n"


#endif