#include "LBT.h"
#include "LBTServer.h"
extern "C" {
#include "stdlib.h"
}
#include <LinkItOneBluetoothPublish.h>
extern "C" {
char * dtostrf(double __val,signed char __width,unsigned char __prec,char * __s); // one way
 }
 LinkItOneBluetoothPublish::LinkItOneBluetoothPublish(void) 
 {
      i=0;
      inputString="";
      stringComplete=false;
      pIndex=0;
}
    void LinkItOneBluetoothPublish::beginBT()
    {
      LBTServer.begin((uint8_t *)"LinkIt_One");
    }

void LinkItOneBluetoothPublish::publish(String str,float *ptr)
 {
   s[pIndex]=str;
   p[pIndex]=ptr;
   pIndex++;
 }


void LinkItOneBluetoothPublish::sync()
{
     BTEve();
    if (stringComplete) {
    for(i=0;i<pIndex;i++)
    {
       //check for =, if = is there then it is put request
       if(inputString.indexOf('=')==-1){ //this is a get request
        if(s[i].equalsIgnoreCase(inputString.substring(2,inputString.indexOf('>'))))
        {
         // LBTServer.print(inputString.substring(2,inputString.indexOf('>'))+":");
          uint8_t buf[8];
          char *s=(char *)buf;
          dtostrf(*p[i],4,2,s);
          buf[4]='\r';
          buf[5]='\n';
          buf[6]=0;
          LBTServer.write(buf,6);
          //Serial.println("Sent the response");
        }
    }
      else //this is a put request
      {
        if(s[i].equalsIgnoreCase(inputString.substring(2,inputString.indexOf('='))))
        {
          //LBTServer.print(inputString.substring(2,inputString.indexOf('='))+":");
          *p[i]=inputString.substring(inputString.indexOf('=')+1,inputString.indexOf('>')).toFloat();
             uint8_t buf[8];
             char *s=(char *)buf;
          dtostrf(*p[i],4,2,s);
          buf[4]='\r';
          buf[5]='\n';
          buf[6]=0;
          LBTServer.write(buf,6);
           //Serial.println("Sent the response");

        }

      }

    }
    //LBTServer.println(inputString);

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
if connection is not made, will wait for 2 sec for new connections
  BTEve occurs whenever a new data comes in the
 Bluetooth.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void LinkItOneBluetoothPublish::BTEve() {
  if(LBTServer.connected())
  {
    while (LBTServer.available()&& !stringComplete) {
    // get the new byte:
    char inChar = (char)LBTServer.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '>') {
      stringComplete = true;
    }
  }
  }
  else
  {
    LBTServer.accept(5);
  }
}
