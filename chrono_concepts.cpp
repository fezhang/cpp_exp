#include "cpp_exp_base.h"
#include <chrono>
#include <iostream>
#include <thread>

using seconds = std::chrono::seconds;
using milliseconds = std::chrono::milliseconds;

namespace {
	//Time durations
	void chrono_time_duration() {
		static_assert(sizeof(seconds) == 8, "seconds size should be 8");

		seconds three_seconds{ 3 };
		std::cout << three_seconds.count() << "s \n";
		std::cout << "seconds,      min:"<< seconds::min().count() <<"s,  max:"<<seconds::max().count()<< "s \n";
		std::cout << "milliseconds, min:" << milliseconds::min().count() << "ms, max:" << milliseconds::max().count() << "ms \n";
	}

	//Time point
	void chrono_time_point() {
		std::chrono::time_point<std::chrono::system_clock, seconds> tp{ seconds{ 10000 } };
	}

	//Clock
	void chrono_clock() {
		auto t0 = std::chrono::steady_clock::now();
		std::this_thread::sleep_for(std::chrono::seconds{1});
		auto t1 = std::chrono::steady_clock::now();

		std::cout << std::chrono::nanoseconds{ t1 - t0 }.count() << "ns\n";
	}
}

void test_chrono() {
	chrono_time_duration();
	chrono_time_point();
	chrono_clock();
}