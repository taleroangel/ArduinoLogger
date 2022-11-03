# ArduinoLogger 📜
Arduino Logging framework, easy Logging for microcontrollers using the Arduino framework ⚡️

## 🌡️ Logging levels
Based on Log4J Logging levels

| Level | Description                                                 |
| ----- | ----------------------------------------------------------- |
| OFF   | Turns off logging                                           |
| FATAL | Severe errors that cause premature termination              |
| ERROR | Other runtime errors or unexpected conditions               |
| WARN  | Other runtime situations that are undesirable or unexpected |
| INFO  | Interesting runtime events (startup/shutdown)               |
| DEBUG | Detailed information on the flow through the system         |
| ALL   | Most detailed information                                   |

Access these levels by using the __LoggingLevel__ enum

## 📚️ Multiple Outputs
- ESP boards supports logging to multiple outputs
- AVR boards can only log to one output, but multiple _LoggerClass_ instances can be created
  
In order to enable this feature you must define [__LOGGER_ALLOW_MULTIPLE_OUTPUTS__](#Options) macro before importing the library

	#define LOGGER_ALLOW_MULTIPLE_OUTPUTS
	#import <Logger.h>

## 🛠️ Macro Options

* __LOGGER_ALLOW_MULTIPLE_OUTPUTS__: Enable multiple outputs, changes __begin()__ function behaviour
* __LOGGER_DISABLE_GLOBAL_INSTANCE__:
