// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

unsigned char command = 0;
int i = 0;
int loopCnt = 0;
unsigned char rcvEvtCnt = 0;
unsigned char reqEvtCnt = 0;
unsigned char rcvFlag = 0;
unsigned char rcvCnt = 0;
char buf[32];

short datastore[6];

//This sets up the two analog inputs
void setupAnalog()
{
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
}

void sendAnalog (const byte which)
{
  unsigned short val = analogRead (which);
  //val &= 0x3FF; // mask off 10 bits
  Wire.write ((const uint8_t *)&val, 2);
}  // end of sendSensor

void setup() 
{
  Serial.begin(9600);
  Wire.begin(0x31);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent);
  setupAnalog();
}

void loop() 
{
  delay(1000);

  Serial.print(loopCnt++);
  Serial.print(" : rcv - ");
  Serial.print(rcvEvtCnt);
  Serial.print(" : req - ");
  Serial.print(reqEvtCnt);
  Serial.println("");
    
  if( rcvFlag != 0 )
  {
    rcvFlag = 0;
    for( i = 0; i < rcvCnt; i++ )
    {
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");
  }
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() 
{
  reqEvtCnt++;
  command = buf[0];
  switch( command )
  {
    case 0x11:
    Wire.write((const uint8_t *)datastore, sizeof(datastore));
    break;

    case 0x22:
    Wire.write((const uint8_t *)&loopCnt, 2);
    break;

    case 0x26:
    sendAnalog(A6);
    break;

    case 0x27:
    sendAnalog(A7);
    break;

    case 0x28:
    Wire.write(buf, 4);
    break;

    default:
    Wire.write(72); 
    break;
  }
}

void receiveEvent( int count ) 
{
  rcvEvtCnt++;
  rcvFlag = 1;
  rcvCnt = 0;
  while (Wire.available()) 
  {
    char c = Wire.read(); // receive byte as a character
    buf[rcvCnt++] = c;
  }
}



