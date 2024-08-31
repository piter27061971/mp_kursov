#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include "SafeQueue.hpp"

using namespace std::chrono_literals;

class ThreadPool {
	public:
		ThreadPool(int cores);
		~ThreadPool();
		void work();
		void submit(std::vector<std::function<void()>> vectorFunctions, int countSubmits);
	private:
		std::mutex threadMutex;
		std::vector<std::thread> vectorOfThreads;
		SafeQueue<std::function<void()>> safeQueueOfWorks;
		bool isSubmit = false;
};