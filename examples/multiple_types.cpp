#include <Arduino.h>
#include <Logger.h>

void setup()
{
	// Enable Serial
	Serial.begin(9600);
	delay(2000);

	// Enable logger
	Logger.begin(&Serial, LoggingLevel::ALL);

	// Logs with different types
	Logger.log<LoggingLevel::DEBUG>(F("char *"), "You can print char *");
	Logger.log<LoggingLevel::INFO>(F("String"), String("Or a String class"));
	Logger.log<LoggingLevel::WARN>(F("F() or PSTR()"), F("Or a PSTR() macro"));
	Logger.log<LoggingLevel::ERROR>("Hi, i'm a char * tag", F("TAG can also have different types"));

	// Printable class
	class Foo : public Printable
	{
	public:
		const char *class_name = "FooClass";

		Foo() = default;

		inline size_t printTo(Print &p) const
		{
			return p.println("This is a printable class");
		}
	} foo;

	// It is also posible to print your own objects
	Logger.log<LoggingLevel::FATAL>(foo.class_name, foo);
}

void loop()
{
}