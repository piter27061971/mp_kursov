#include "ThreadPool.h"

ThreadPool::ThreadPool(int cores) {
	for (int i = 0; i < cores; ++i) {
		vectorOfThreads.push_back(std::thread(&ThreadPool::work, this));
	}
}

ThreadPool::~ThreadPool() {
	for (auto& thread : vectorOfThreads) {
		thread.join();
	}
}

void ThreadPool::submit(std::vector<std::function<void()>> vectorFunctions, int countSubmits) {
	for (int i = 0; i < countSubmits; ++i) {
		for (size_t j = 0; j < vectorFunctions.size(); ++j) {
			safeQueueOfWorks.push(vectorFunctions.at(j));
		}
		std::this_thread::sleep_for(1s);
	}
	isSubmit = true;
}

void ThreadPool::work() {
	while (!isSubmit) {
		std::unique_lock<std::mutex> lockMutex(threadMutex);
		if (!safeQueueOfWorks.empty()) {
			std::cout << "work id: " << std::this_thread::get_id() << std::endl;
			safeQueueOfWorks.front();
			safeQueueOfWorks.pop();
		}
		else {
			std::this_thread::yield();
		}
		lockMutex.unlock();
	}
}
