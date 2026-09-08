#pragma once

#include <chrono>
#include <iomanip>

enum class LogLevel
{
	Info,
	Warn,
	Error
};

class Log
{
public:
	template <typename ...Args>
	static void info(Args&&... args)
	{
		log(LogLevel::Info, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void warn(Args&&... args)
	{
		log(LogLevel::Warn, std::forward<Args>(args)...);
	}

	template <typename ...Args>
	static void error(Args&&... args)
	{
		log(LogLevel::Error, std::forward<Args>(args)...);
	}

private:
	
	static constexpr const char* COLOR_RESET	= "\033[0m";
	static constexpr const char* COLOR_GREEN	= "\033[32m";
	static constexpr const char* COLOR_YELLOW	= "\033[33m";
	static constexpr const char* COLOR_RED		= "\033[31m";


	template <typename ...Args>
	static void log(LogLevel level, Args&&... args)
	{
		auto now = std::chrono::system_clock::now();
		auto time = std::chrono::system_clock::to_time_t(now);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
		std::cout << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
			<< "," << std::setfill('0') << std::setw(3) << ms.count() << " ";

		const char* color = COLOR_RESET;
		const char* str = "";
		switch (level)
		{
			case LogLevel::Info:
				color = COLOR_GREEN;
				str = "[INFO]";
				break;
			case LogLevel::Warn:
				color = COLOR_YELLOW;
				str = "[WARN]";
				break;
			case LogLevel::Error:
				color = COLOR_RED;
				str = "[ERROR]";
				break;
		}

		std::cout << color << str;
		(std::cout << ... << args);
		std::cout << COLOR_RESET << std::endl;
	}
};