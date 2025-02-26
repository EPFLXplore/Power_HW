/*
 * System.h
 *
 *  Created on: Oct 12, 2024
*/

#ifndef RootTask_H_
#define RootTask_H_

#include <cstdio>

const uint8_t TEST_BUF_SIZE = 64;
char test_buf_init[TEST_BUF_SIZE];
char test_buf_loop[TEST_BUF_SIZE];

class System {
public:
	static void init();
	static void loop();
};
//#ifdef __cplusplus
//}
//#endif
#endif /* SYSTEM_H_ */
