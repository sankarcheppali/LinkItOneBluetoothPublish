#ifndef LinkItOneBluetoothPublish_h
#define LinkItOneBluetoothPublish_h
#include "Arduino.h"
#include "LBT.h"
#include "LBTServer.h"
class LinkItOneBluetoothPublish
{
public:
	LinkItOneBluetoothPublish();
    void beginBT();
	void publish(String str,float *ptr);
	void sync();
	void BTEve();
    
private:
	float *p[20];//pointers to variables
    String s[20];//string(variable name)
    String inputString;         // a string to hold incoming data
    boolean stringComplete ;  // whether the string is complete
    int i;
    byte pIndex;//publisher index 
    //HardwareSerial& _HardSerial;   
};
#endif