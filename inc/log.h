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


// Logging functions - output log to both ITM and serial port
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
	printf(line);\
	ITM_write(line);\
}
#else
#define info(line)
#endif

#if LOG_LEVEL <= WARN
#define warn(line) {\
	printf(line);\
	ITM_write(line);\
}
#else
#define warn(line)
#endif

#define error(line) {\
	printf(line);\
	ITM_write(line);\
}


// Debug functions - only output to ITM in debug configuration
#ifdef DEBUG

#if LOG_LEVEL <= VERBOSE
#define debug_log(line) {\
	ITM_write(line);\
}
#else
#define debug_log(line)
#endif

#if LOG_LEVEL <= INFO
#define debug_info(line) {\
	ITM_write(line);\
}
#else
#define debug_info(line)
#endif

#if LOG_LEVEL <= WARN
#define debug_warn(line) {\
	ITM_write(line);\
}
#else
#define debug_warn(line)
#endif

#define debug_error(line) {\
	ITM_write(line);\
}

#else

#define debug_log(line)
#define debug_info(line)
#define debug_warn(line)
#define debug_error(line)

#endif



#endif /* LOG_H_ */
