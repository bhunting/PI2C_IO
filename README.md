# PI2C_IO

Demo / Test code to play with interfacing between the RasPi and various I2C devices, including a custom Arduino I2C slave.

Testing on the Pi side

pi@raspberrypi:~$ sudo i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- 31 -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- 71 -- -- -- -- -- --

0x31 is the custom Arduino slave

0x71 is the sparkfun 7-Segment-Display

Writing to the sparkfun display us the command write_i2c_block_data with the command 0x76 to clear the display and then an array of the bytes to display.

pi@raspberrypi:~$ sudo python
Python 2.7.3 (default, Mar 18 2014, 05:13:23)
[GCC 4.6.3] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> import smbus
>>> i2c = smbus.SMBus(1)
>>> i2c.write_byte(0x71, 0x31)
>>> i2c.write_byte(0x71, 0x32)
>>> i2c.write_byte(0x71, 0x33)
>>> i2c.write_byte(0x71, 0x76)
>>> i2c.write_byte(0x71, 0x33)
>>> i2c.write_byte(0x71, 0x32)
>>> i2c.write_byte(0x71, 0x76)
>>> i2c.write_i2c_block_data(0x71,0x76,[1,2,3,4])
>>> i2c.write_i2c_block_data(0x71,0x76,[5,6,7,8])
>>> i2c.write_i2c_block_data(0x71,0x76,[1,2,3,4])
>>> i2c.write_i2c_block_data(0x71,0x76,[5,6,7,8])
>>>




Interesting links along the way

http://www.raspberry-projects.com/pi/programming-in-python/i2c-programming-in-python/using-the-i2c-interface-2

http://www.gammon.com.au/forum/?id=10896
http://dsscircuits.com/articles/arduino-i2c-slave-guide


https://www.sparkfun.com/products/11442
https://learn.sparkfun.com/tutorials/using-the-serial-7-segment-display/all
https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Basic-Usage
https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Customizing%20the%20Display
https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Special-Commands
https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Serial-7-Segment-Display-Datasheet
http://cdn.sparkfun.com/datasheets/Components/LED/Serial-7-Segment-Display-v31.pdf


https://learn.sparkfun.com/tutorials/mma8452q-accelerometer-breakout-hookup-guide
https://github.com/sparkfun/MMA8452_Accelerometer
https://learn.adafruit.com/adafruit-htu21d-f-temperature-humidity-sensor/overview
https://learn.adafruit.com/adafruit-tmp007-sensor-breakout?view=all

https://www.sparkfun.com/products/10140
https://www.sparkfun.com/datasheets/Kits/Frequency-Counter-v11.pdf


