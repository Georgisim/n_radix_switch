/*
 * common.h
 *
 *  Created on: 2009-11-29
 *      Author: George
 */

#ifndef COMMON_H_
#define COMMON_H_

#define DEBUG

enum enumStats {
	STAT_WARMUP,
	STAT_NORMAL,
	STAT_DRAIN,
	STAT_NODE_READY
};

typedef struct {
	int vc;
	int port;
} Channel_t;


#endif /* COMMON_H_ */
