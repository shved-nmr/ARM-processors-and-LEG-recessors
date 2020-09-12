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
#define WARN 2
#define ERROR 3


#define LOG_LEVEL INFO


#ifdef DEBUG
#define debug(line) {\
	ITM_write(line);\
}
#else
#define debug(line)
#endif


#if LOG_LEVEL <= VERBOSE
#define log(line) {\
	printf(line);\
	ITM_write(line);\
}
#else
#define log(line)
#endif


#if LOG_LEVEL <= INFO
#define info(line) {\
	ITM_write(line);\
	printf(line);\
}
#else
#define info(line)
#endif


#if LOG_LEVEL <= WARN
#define warn(line) {\
		ITM_write(line);\
		printf(line);\
}
#else
#define warn(line)
#endif


#define error(line) {\
	ITM_write(line);\
	printf(line);\
}

#endif /* LOG_H_ */
