#include "Threads.h"

#define DEFAULT_STACK_SIZE (1024)

void thread_life(void* arg){
	Thread* thread = (Thread*) arg;

	osDelay(100 / portTICK_PERIOD_MS);

	thread->init();

	while(thread->isRunning()) {
		thread->loop();
		osDelay(thread->getTickDelay() / portTICK_PERIOD_MS);
	}

	delete thread;

	vTaskDelete(nullptr);

	while(true){
		osDelay(1000 / portTICK_PERIOD_MS);
	}
}


Thread::Thread(const char* name) : Thread(name, (osPriority) osPriorityNormal) {};

Thread::Thread(const char* name, osPriority priority) : Thread(name, priority, DEFAULT_STACK_SIZE){};

Thread::Thread(const char* name, uint32_t stackSize) : Thread(name, (osPriority) osPriorityNormal, stackSize){};

Thread::Thread(const char* name, osPriority priority, uint32_t stackSize) : delay(10) {
	const osThreadAttr_t thread_attributes = {
			.name = (char*) name,
			.stack_size = stackSize,
			.priority = (osPriority_t) priority,
	};
	this->handle = (osThreadId) osThreadNew(&thread_life, this, &thread_attributes);
	this->name = name;
}


bool Thread::isRunning() {
	return running;
}

void Thread::terminate() {
	this->running = false;
}

void Thread::setTickDelay(uint32_t ms) {
	this->delay = ms;
}

uint32_t Thread::getTickDelay() {
	return this->delay;
}
