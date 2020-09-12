/*
 * log.h
 *
 *  Created on: Sep 12, 2020
 *      Author: MStefan99
 */

#ifndef LOG_H_
#define LOG_H_


#define VERBOSE 0
#define INFO 1
#define WARNING 2
#define ERROR 3


#define LOG_LEVEL INFO


#ifdef DEBUG
	#define debug(level, line) {\
		if (level >= LOG_LEVEL) {\
			ITM_write(line);\
		}\
	}

	#define log(level, line) {\
		if (level >= LOG_LEVEL) {\
			ITM_write(line);\
			printf(line);\
		}\
	}
#else
	#define debug(level, line)

	#define log(level, line) {\
		if (level >= LOG_LEVEL) {\
			printf(line);\
		}\
	}
#endif


#endif /* LOG_H_ */
