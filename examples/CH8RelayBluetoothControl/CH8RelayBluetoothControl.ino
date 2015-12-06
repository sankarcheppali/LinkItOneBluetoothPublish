/*
* 8CHRealyControlBluetooth
 *Control 8 Relays using BlueTooth  Android app
 * Created: 12/6/2015 7:37:21 AM
 * Author : uma sankar
 LoadMapping
 Load1-6
 Load2-7
 Load3-8
 Load4-9
 Load5-10
 Load6-11
 Load7-12
 Load8-13
*/
#include "Arduino.h"
#include "LBT.h"
#include "LBTServer.h"
#include <stdlib.h>

#include <LinkItOneBluetoothPublish.h>

#define ln1Pin 6
#define ln2Pin 7
#define ln3Pin 8
#define ln4Pin 9
#define ln5Pin 10
#define ln6Pin 11
#define ln7Pin 12
#define ln8Pin 13


LinkItOneBluetoothPublish bt;

float ln[9];
long milli=0;

void setup()
{
  int i=0;
  Serial.begin(9600);
  Serial.println("starting the application");
  bt.beginBT();
  //Serial.println("BT Started");
  for(i=6;i<14;i++)
  pinMode(13, OUTPUT);

  bt.publish("ln1", &ln[1]); //ln-load normal (without speed control)
  bt.publish("ln2", &ln[2]);
  bt.publish("ln3", &ln[3]);
  bt.publish("ln4", &ln[4]);
  bt.publish("ln5", &ln[5]);
  bt.publish("ln6", &ln[6]);
  bt.publish("ln7", &ln[7]);
  bt.publish("ln8", &ln[8]);
}

void loop()
{
  
  digitalWrite(ln1Pin, (uint8_t)ln[1]);
  digitalWrite(ln2Pin, (uint8_t)ln[2]);
  digitalWrite(ln3Pin, (uint8_t)ln[3]);
  digitalWrite(ln4Pin, (uint8_t)ln[4]);
  digitalWrite(ln5Pin,(uint8_t) ln[5]);
  digitalWrite(ln6Pin, (uint8_t)ln[6]);
  digitalWrite(ln7Pin,(uint8_t) ln[7]);
  digitalWrite(ln8Pin,(uint8_t) ln[8]);
  bt.sync();//This method will check for any incoming messages in Bluetooth 
}
