#pragma once
#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

template<class T>
class SafeQueue {
	public:
		void push(T work) {
			std::unique_lock<std::mutex> lockMutex(queueMutex);
			queueOfWorks.push(work);
			cond_variable.notify_one();
		};
		T pop() {
			std::unique_lock<std::mutex> lockMutex(queueMutex);
			cond_variable.wait(lockMutex, [this]() { return !queueOfWorks.empty(); });
			T work = std::move(queueOfWorks.front());
			queueOfWorks.pop();
			return work;
		};
		int size() {
			std::unique_lock<std::mutex> lock(queueMutex);
			return queueOfWorks.size();
		};

		bool empty() {
			std::unique_lock<std::mutex> lock(queueMutex);
			return queueOfWorks.empty();
		}

		void front() {
			std::unique_lock<std::mutex> lock(queueMutex);
			queueOfWorks.front()();
		};

	private:
		std::queue<T> queueOfWorks;
		std::mutex queueMutex;
		std::condition_variable cond_variable;
};
