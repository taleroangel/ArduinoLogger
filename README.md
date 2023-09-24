# ArduinoLogger 📜
Arduino Logging framework, easy Logging for microcontrollers using the Arduino framework

## ⚡️ Usage

1. First include the Logging.h header, once the file is included a global object called ___Logger___ will be available in every file that includes it
```c++
#include <Logger.h>
```

2. Enable the interface you want to use, in this example the Serial interface will be used. once initialized pass it's memory address to the ___Logger___ object via __begin()__ method. you may also specify a ___LoggingLevel___, if not specified the default is __LoggingLevel::ALL__
```c++
Serial.begin(9600);
Logger.begin(&Serial, LoggingLevel::ALL);
```

3. You are now able to log, specify the logging level via template and put a TAG and a MESSAGE as parameters.
```c++
Logger.log<LoggingLevel::INFO>("My Tag", "Hello world!");
```

The resulting log will be:
```
INFO  [My Tag]  Hello world!
```

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
| ALL   | Show everything                                             |

Access these levels by using the __LoggingLevel__ enum

## 📚️ Multiple Outputs __(NOT READY 🤕)__
- ESP boards supports logging to multiple outputs
- AVR boards can only log to one output, but multiple _LoggerClass_ instances can be created
  
In order to enable this feature you must define [__LOGGER_ALLOW_MULTIPLE_OUTPUTS__](#Options) macro before importing the library

	#define LOGGER_ALLOW_MULTIPLE_OUTPUTS
	#import <Logger.h>

### TODO 🚨:
ESP devices throw Exception(9) because std::initializer_list is storing __pointers__ to the Print object

This is due to a memory alignment problem in ESP devices:
[Problem here](https://readmodifywrite.github.io/blog/html/2016/12/15/2016_12_15_memory_alignment_esp8266.html)

## 🛠️ Macro Options

* __LOGGER_ALLOW_MULTIPLE_OUTPUTS__: Enable multiple outputs, changes __begin()__ function behaviour
* __LOGGER_DISABLE_GLOBAL_INSTANCE__: Disable global ___Logger___ instance, you need to create your own ___LoggerClass___ instances
