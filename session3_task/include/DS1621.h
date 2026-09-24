#include <Arduino.h>
#include <Wire.h>

class DS1621
{
public:
	enum Status : uint8_t
	{
		OK = 0,
		ERR_TOO_LONG = 1,
		ERR_ADDR_NACK = 2,
		ERR_DATA_NACK = 3,
		ERR_OTHER = 4,
		ERR_SHORT_READ = 5,
		ERR_NOT_READY = 6
	};

	static const uint8_t CONFIG_REGISTER = 0xAC;
	static const uint8_t START_CONVERT_COMMAND = 0xEE;
	static const uint8_t TEMPERATURE_REGISTER = 0xAA;

	explicit DS1621(uint8_t address = 0x48);

	Status begin();
	Status configure(uint8_t configuration = 0x00);
	Status startConversion();
	Status readTemperatureC(float &temperatureC);
	const char *statusMessage(Status status) const;

private:
	uint8_t address_;

	Status writeCommand(uint8_t command);
	Status writeRegister(uint8_t registerAddress, uint8_t value);
	Status readRegister(uint8_t registerAddress, uint8_t *buffer, uint8_t length);
	Status mapWireStatus(uint8_t wireStatus) const;

};