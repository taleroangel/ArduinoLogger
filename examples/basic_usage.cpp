#include <Arduino.h>
#include <Logger.h>

void setup()
{
	// First enable Serial
	Serial.begin(9600);
	delay(2000);

	// Begin logger with Serial
	Logger.begin(&Serial, LoggingLevel::ALL);

	// Log!
	Logger.log<LoggingLevel::DEBUG>(F(__FILE__), F("Developer secret!"));
	Logger.log<LoggingLevel::INFO>(F(__FILE__), F("Hello world!"));
	Logger.log<LoggingLevel::WARN>(F(__FILE__), F("This isn't quite right"));
	Logger.log<LoggingLevel::ERROR>(F(__FILE__), F("Things are not working out"));
	Logger.log<LoggingLevel::FATAL>(F(__FILE__), F("Something is messed up"));
}

void loop()
{
}