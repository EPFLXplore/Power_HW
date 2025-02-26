/*
 * Threads.h
 *
 * Created on: June 21, 2024
 *	  Author : Federico Bise
 *
 */


#ifndef THREADS_H
#define THREADS_H

#include "FreeRTOS.h"


class Thread {
public:
	Thread(const char* name);
	Thread(const char* name, osPriority priority);
	Thread(const char* name, uint32_t stackSize);
	Thread(const char* name, osPriority priority, uint32_t stackSize);

	virtual void init() = 0;
	virtual void loop() = 0;

	bool isRunning();
	void terminate();

	void setTickDelay(uint32_t ms);
	uint32_t getTickDelay();

private:
	uint32_t delay;
	osThreadAttr_t thread_attributes;
	bool running = true;
	const char* name;
	osThreadId handle;

};


#endif /* THREADS_H */
