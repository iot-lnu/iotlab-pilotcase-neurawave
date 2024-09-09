#include "Adafruit_AD569x.h"
#include <Arduino.h>
#include <SPI.h>

// Create an object of the AD5693 library
Adafruit_AD569x ad5693;

// Lookup table with the values for the neurawave signal
const uint16_t lut[146] = {

    // linear increasing phase
    0,

    // 1/t phase 72 values
    65535, 49152, 43691, 40960, 39322, 38229, 37449,
    36864, 36409, 36045, 35747, 35499, 35289, 35109, 34953,
    34816, 34696, 34588, 34493, 34406, 34328, 34257, 34193,
    34133, 34079, 34028, 33982, 33938, 33898, 33860, 33825,
    33792, 33761, 33732, 33704, 33678, 33654, 33630, 33608,
    33587, 33567, 33548, 33530, 33513, 33496, 33480, 33465,
    33451, 33437, 33423, 33411, 33398, 33386, 33375, 33364,
    33353, 33343, 33333, 33323, 33314, 33305, 33297, 33288,
    33280, 33272, 33264, 33257, 33250, 33243, 33236, 33230, 32768,

    // linear decreasing  phase
    65535, 0,

    // -1/t -71 values
    16384, 21845, 24576, 26214, 27307, 28087,
    28672, 29127, 29491, 29789, 30037, 30247, 30427, 30583,
    30720, 30840, 30948, 31043, 31130, 31208, 31279, 31343,
    31403, 31457, 31508, 31554, 31598, 31638, 31676, 31711,
    31744, 31775, 31804, 31832, 31858, 31882, 31906, 31928,
    31949, 31969, 31988, 32006, 32023, 32040, 32056, 32071,
    32085, 32099, 32113, 32125, 32138, 32150, 32161, 32172,
    32183, 32193, 32203, 32213, 32222, 32231, 32239, 32248,
    32256, 32264, 32272, 32279, 32286, 32293, 32300, 32306, 32768};


// Determine the size of the lookup table 
const uint16_t arraySize = sizeof(lut) / sizeof(lut[0]);

void setup()
{
  // Set CPU frequency
  setCpuFrequencyMhz(160);

  //Start I2C communication 
  ad5693.begin(0x4C, &Wire);
  // Reset the DAC
  ad5693.reset();
  // Configure the DAC for normal mode, internal reference, and no 2x gain
  ad5693.setMode(NORMAL_MODE, true, false);

  //Initialize the wire library and join the I2C bus as a controller or a peripheral
  Wire.begin();

  //Set I2C communication frequency 
  // You probably will want to set the I2C clock rate to faster
  // than the default 100KHz, try 400K or 800K or even 1M!

  // Wire.setClock(322581); // 128 values CPU 160Mhz - 50 Hz signal

  // 146 values CPU 160Mhz - 50 Hz signal
  Wire.setClock(392150); 

  // 146 values CPU 160Mhz - 30 Hz signal
  // Wire.setClock(200000); 




}

void loop()
{
  // Read values of the lookup table and send it to the DAC
  for (uint8_t i = 0; i < arraySize; i++)
  {
    ad5693.writeUpdateDAC(lut[i]);
  }
}
