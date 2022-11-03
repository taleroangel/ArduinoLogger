/**
 * @file Logger.h
 * @author Ángel Talero (angelgotalero@outlook.com)
 * @brief Arduino Logging framework, enables logging to multiple outputs
 * @version 0.1
 * @date 2022-11-01
 *
 * @copyright Copyright (c) 2022. Angel D. Talero
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <Arduino.h>

#ifdef LOGGER_ALLOW_MULTIPLE_OUTPUTS
#include <initializer_list>
#endif

/**
 * @enum LoggingLevel
 * @brief Logging levels based on Log4J levels
 */
enum class LoggingLevel
{
	OFF,
	FATAL,
	ERROR,
	WARN,
	INFO,
	DEBUG,
	ALL,
};

/**
 * @brief Strings with LoggingLevel names
 *
 */
constexpr const char *LOGGING_LEVEL_NAMES
	[static_cast<uint8_t>(LoggingLevel::ALL)] PROGMEM = {
		"",
		"FATAL",
		"ERROR",
		"WARN",
		"INFO",
		"DEBUG",
};

class LoggerClass
{
	/* --------- Variables --------- */
private:
#ifdef LOGGER_ALLOW_MULTIPLE_OUTPUTS
	std::initializer_list<Print *> printers;
#else
	Print *printer = nullptr;
#endif
	LoggingLevel level = LoggingLevel::OFF;

	/* --------- Public member functions --------- */
public:
#ifdef LOGGER_ALLOW_MULTIPLE_OUTPUTS
	/**
	 * @brief Attach multiple system printers (Print class)
	 * ej: {&Serial, &customFile, &Other}
	 *
	 * @param printers List of Pointers to printers
	 * @param level Logging level
	 */
	inline void begin(std::initializer_list<Print *> &&printers, LoggingLevel level)
	{
		this->printers = printers;
		this->level = level;
	}
#else
	/**
	 * @brief Attach a system printer (Print class)
	 * ej: &Serial
	 *
	 * @param printer Pointer to printer class
	 * @param level Logging level
	 */
	inline void begin(Print *printer, LoggingLevel level)
	{
		this->printer = printer;
		this->level = level;
	}
#endif

	LoggerClass() = default;

	/**
	 * @brief Get current logging level
	 * @note Logging level can only be set when begin() is invoked
	 * @return LoggingLevel Logging level
	 */
	inline LoggingLevel get_level() const
	{
		return this->level;
	}

	/**
	 * @brief Make a new log
	 * @note OFF and ALL logging levels are not valid
	 * @tparam level Logging level as a template parameter
	 * @tparam TagType Type of the TAG string
	 * @tparam MessageType  Type of the message string
	 * @param tag TAG of the log (Usually a component name or __FILE__ macro)
	 * @param content Content of the log
	 */
	template <LoggingLevel level, typename TagType, typename MessageType>
	void log(TagType tag, MessageType content);
};

#ifndef LOGGER_DISABLE_GLOBAL_INSTANCE
/**
 * @brief Logging class global instance
 * @note can be disabled by defining LOGGER_DISABLE_GLOBAL_INSTANCE
 */
extern LoggerClass Logger;
#endif

/* --------- Template declarations --------- */
template <LoggingLevel level, typename TagType, typename MessageType>
void LoggerClass::log(TagType tag, MessageType content)
{
	// Check current logging level
	if (level > this->level ||
		level == LoggingLevel::OFF ||
		level == LoggingLevel::ALL)
		return;

#ifdef LOGGER_ALLOW_MULTIPLE_OUTPUTS
	for (Print *printer : this->printers)
	{
		// Check bad printer
		if (printer == nullptr)
			continue;
#endif
		// Print to files
		printer->print(LOGGING_LEVEL_NAMES[static_cast<uint8_t>(level)]);
		printer->print(F("\t["));
		printer->print(tag);
		printer->print(F("]\t"));
		printer->println(content);
		printer->flush();

#ifdef LOGGER_ALLOW_MULTIPLE_OUTPUTS
	}
#endif
}

#endif // __LOGGER_H__