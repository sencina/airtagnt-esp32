// #include <Arduino.h>

// extern void test_sim800_module(void);
// extern void send_SMS(void);
// extern void updateSerial(void);

// void setup() {
//   Serial.begin(115200);
//   Serial2.begin(9600);
//   delay(3000);
//   test_sim800_module();
//   send_SMS();
// }
// void loop() {
//   updateSerial();
// }
// void test_sim800_module()
// {
//   Serial2.println("AT");
//   updateSerial();
//   Serial.println();
//   Serial2.println("AT+CSQ");
//   updateSerial();
//   Serial2.println("AT+CCID");
//   updateSerial();
//   Serial2.println("AT+CREG?");
//   updateSerial();
//   Serial2.println("ATI");
//   updateSerial();
//   Serial2.println("AT+CBC");
//   updateSerial();
//   Serial.println(__FUNCTION__);
// }
// void updateSerial()
// {
//   delay(500);
//   while (Serial.available())
//   {
//     Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
//   }
//   while (Serial2.available())
//   {
//     Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
//   }
// }
// void send_SMS()
// {
//   Serial2.println("AT+CMGF=1"); // Configuring TEXT mode
//   updateSerial();
//   Serial2.println("AT+CMGS=\"1141800170\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
//   updateSerial();
//   Serial2.print("Circuit Digest"); //text content
//   updateSerial();
// Serial.println();
//   Serial.println("Message Sent");
//   Serial2.write(26);
// }

#include <Arduino.h>
#include <HardwareSerial.h>

// HardwareSerial Serial2(2);


void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial2.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  Serial.println("Between whiles");
  while(Serial2.available()) 
  {
    Serial.println(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

int incomingByte = 0;
int i = 1;
void setup()
{
  
  Serial.begin(9600);
  
 
  Serial2.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("Initializing..."); 
  delay(1000);

  // Serial2.write("AT");
  // updateSerial();
  // Serial.println("sent AT");

  // Serial2.write("AT+CMGF=1"); 
  // updateSerial();
  // Serial2.write("AT+CMGS=\"+541141800170\""); // enter your phone number here (prefix country code)
  // updateSerial();
  // Serial2.write("Hello from Superb Tech"); // enter your message here
  // updateSerial();
  // Serial2.write(26);
  Serial2.write("AT");
  delay(5000);
  Serial.println("after delay");
  // while(Serial2.available()) 
  // {
  //   Serial.println("entered");
  //   Serial.print(Serial2.read());//Forward what Software Serial received to Serial Port
  // }
  // Serial.println("Sali del while");
}

void loop()
{
  Serial2.write("AT");
  Serial.println("mando un AT");
  // while (Serial.available()) 
  // {
  //   Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  // }
  Serial.println(Serial2.available());
  delay(5000);
  if (Serial2.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    Serial.println("Loopeando " + String(i));
    i++;

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }

  delay(7000);
  Serial.println("hola");

}