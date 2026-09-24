#include <DS1621.h>

DS1621::DS1621(uint8_t address) : address_(address){}

DS1621::Status DS1621::begin()
{
	Wire.begin();
	return configure();
}

DS1621::Status DS1621::configure(uint8_t configuration)
{
	return writeRegister(CONFIG_REGISTER, configuration);
}

DS1621::Status DS1621::startConversion()
{
	return writeCommand(START_CONVERT_COMMAND);
}

DS1621::Status DS1621::readTemperatureC(float &temperatureC)
{
	uint8_t rawTemperature[2];
	Status status = readRegister(TEMPERATURE_REGISTER, rawTemperature, sizeof(rawTemperature));
	if (status != OK)
	{
		return status;
	}

	temperatureC = static_cast<int8_t>(rawTemperature[0]);

    if (rawTemperature[1] & 0x80)
    {
        temperatureC += 0.5f;
    }
	return OK;
}

const char *DS1621::statusMessage(Status status) const
{
	switch (status)
	{
	case OK:
		return "OK";
	case ERR_TOO_LONG:
		return "I2C transmit buffer too long";
	case ERR_ADDR_NACK:
		return "I2C address NACK";
	case ERR_DATA_NACK:
		return "I2C data NACK";
	case ERR_OTHER:
		return "I2C transmission error";
	case ERR_SHORT_READ:
		return "I2C short read";
	case ERR_NOT_READY:
		return "I2C data not ready";
	default:
		return "Unknown DS1621 status";
	}
}

DS1621::Status DS1621::writeCommand(uint8_t command)
{
	Wire.beginTransmission(address_);
	Wire.write(command);
	return mapWireStatus(Wire.endTransmission());
}

DS1621::Status DS1621::writeRegister(uint8_t registerAddress, uint8_t value)
{
	Wire.beginTransmission(address_);
	Wire.write(registerAddress);
	Wire.write(value);
	return mapWireStatus(Wire.endTransmission());
}

DS1621::Status DS1621::readRegister(uint8_t registerAddress, uint8_t *buffer, uint8_t length)
{
	Wire.beginTransmission(address_);
	Wire.write(registerAddress);
	Status status = mapWireStatus(Wire.endTransmission(false));
	if (status != OK)
	{
		return status;
	}

	uint8_t received = Wire.requestFrom(address_, length);
	if (received != length)
	{
		while (Wire.available())
		{
			Wire.read();
		}
		return ERR_SHORT_READ;
	}

	for (uint8_t index = 0; index < length; ++index)
	{
		if (!Wire.available())
		{
			return ERR_SHORT_READ;
		}
		buffer[index] = Wire.read();
	}
	return OK;
}

DS1621::Status DS1621::mapWireStatus(uint8_t wireStatus) const
{
	switch (wireStatus)
	{
	case 0:
		return OK;
	case 1:
		return ERR_TOO_LONG;
	case 2:
		return ERR_ADDR_NACK;
	case 3:
		return ERR_DATA_NACK;
	default:
		return ERR_OTHER;
	}
}

