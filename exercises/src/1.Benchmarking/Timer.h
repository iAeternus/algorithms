/**
 * @brief 高精度基准测试计时器
 * @author Ricky
 * @date 2024/3/6
 * @version 2.0
 * 
 * 使用方法
 * 1. 方法一
 * {
 * 		size_t count = 10;
 * 		Timer timer("<name>", <count>);
 * 		for(size_t i = 0; i < count; ++i) {
 * 			test_function( ... );
 * 		}
 * }
 * 
 * 2. 方法二（推荐）
 * Timer::automatic_measurement_of_time([&]() -> void {
 *       test_function( ... );
 * }, "<name>", <count>);
*/
#pragma once

#include <iostream>
#include <chrono>
#include <mutex>
#include <functional>

const std::string RED_COLOR_CODE		= "\033[1;31m";
const std::string GREEN_COLOR_CODE		= "\033[1;32m";
const std::string YELLOW_COLOR_CODE		= "\033[1;33m";
const std::string DEFAULT_COLOR_CODE	= "\033[0m";

const int threshold = 1e8;

class Timer
{
public:
	Timer(const char* name = nullptr, size_t count = 1) :
        name(name), count(count), is_Stopped(false), m_startTimePoint(std::chrono::high_resolution_clock::now())
	{}

	~Timer()
	{
		if (!is_Stopped)
		{
			Stop();
		}
	}

	void Stop()
	{
		auto endTimePoint = std::chrono::high_resolution_clock::now();
		// 转成微秒，更精确
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimePoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

		auto duration = (end - start) / count; // 计算一次的时间
		double ms = duration * 0.001; // 如果要毫秒的话

		if (name)
		{
			std::cout << YELLOW_COLOR_CODE << '[' << name << "] " << DEFAULT_COLOR_CODE;
		}
		std::cout << GREEN_COLOR_CODE << duration << DEFAULT_COLOR_CODE << "us ( ";
		std::cout << GREEN_COLOR_CODE << ms << DEFAULT_COLOR_CODE << "ms )\n";
		is_Stopped = true;
	}

	static void automatic_measurement_of_time(const std::function<void()>& func, const char* name = nullptr, size_t count = 1)
	{
		Timer timer(name, count);
		for(int i = 0; i < count; ++i)
		{
			func();
		}
	}

private:
	const char* name; // 计时器名字
    size_t count; // 目标代码块运行的次数
	bool is_Stopped; // 计时器是否停止
	std::chrono::time_point<std::chrono::high_resolution_clock> m_startTimePoint; // 开始时刻
};