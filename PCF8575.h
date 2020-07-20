#pragma once
//
//    FILE: PCF8575.h
//  AUTHOR: Rob Tillaart
//    DATE: 2020-07-20
// VERSION: 0.0.1
// PURPOSE: Arduino library for PCF8575 - 16 channel I2C IO expander
//     URL: https://github.com/RobTillaart/PCF8575
//
// HISTORY:
// based upon PCF8574 library
//
// see PCF8575.cpp file
//

#include "Arduino.h"
#include "Wire.h"

#define PCF8575_LIB_VERSION "0.0.1"

#define PCF8575_OK          0x00
#define PCF8575_PIN_ERROR   0x81
#define PCF8575_I2C_ERROR   0x82


class PCF8575
{
public:
    explicit PCF8575(const uint8_t deviceAddress);

#if defined (ESP8266) || defined(ESP32)
     void    begin(uint8_t sda, uint8_t scl, uint16_t val = 0xFFFF);
#endif
    void     begin(uint16_t val = 0xFFFF);

    uint16_t read16();
    uint8_t  read(uint8_t pin);
    uint16_t value() const { return _dataIn; };

    void     write16(const uint16_t value);
    void     write(const uint8_t pin, const uint8_t value);
    uint16_t valueOut() const { return _dataOut; }

    //  added 0.1.07/08 Septillion
    uint16_t readButton16()  { return readButton16(_buttonMask); }
    uint16_t readButton16(const uint16_t mask = 0xFFFF);
    uint16_t readButton(const uint8_t pin);
    void     setButtonMask(uint16_t mask) { _buttonMask = mask; };

    // rotate, shift, toggle, reverse expect all lines are output
    void     toggle(const uint8_t pin);
    void     toggleMask(const uint16_t mask = 0xFFFF);    // default invertAll()
    void     shiftRight(const uint8_t n = 1);
    void     shiftLeft(const uint8_t n = 1);
    void     rotateRight(const uint8_t n = 1);
    void     rotateLeft(const uint8_t n = 1);
    void     reverse();

    int      lastError();

private:
    uint8_t  _address;
    uint16_t _dataIn;
    uint16_t _dataOut;
    uint16_t _buttonMask;
    int      _error;
};


// -- END OF FILE --
