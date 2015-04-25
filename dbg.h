#ifndef __dbg_h__
#define __dbg_h__

/* Full credit for this file goes to the author of Learn C the Hard Way,
 * Zed A. Shaw. You were right Zed.
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include "colour.h"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "[" ANSI_MAGENTA "DEBUG" ANSI_RESET "] (%s:%d:%s) " M "\n", __FILENAME__, __LINE__, __func__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[" ANSI_RED "ERROR" ANSI_RESET "] (%s:%d:%s: errno: %s) " M "\n", __FILENAME__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[" ANSI_YELLOW "WARN" ANSI_RESET " ] (%s:%d:%s: errno: %s) " M "\n", __FILENAME__, __LINE__, __func__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[" ANSI_CYAN "INFO" ANSI_RESET " ] (%s:%d:%s) " M "\n", __FILENAME__, __LINE__, __func__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define quiet_check(A) if(!(A)) { errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
