// demo: CAN-BUS Shield, receive data
#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];

double visc = 0.015625;

MCP_CAN CAN0(10);                               // Set CS to pin 10
char *endptr;

void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_500KBPS);                       // init can bus : baudrate = 500k
  pinMode(2, INPUT);                            // Setting pin 2 for /INT input
  Serial.println("MCP2515 Library Receive Example...");
}

void loop()
{
  if (!digitalRead(7))                         // If pin 2 is low, read receive buffer
  {
    CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
    rxId = CAN0.getCanId();                    // Get message ID
//    Serial.print("ID: ");
//    Serial.print(" ");
//    Serial.print(rxId, HEX);
//    Serial.print("  Data: ");
//    for (int i = 0; i < len; i++)   // Print each byte of the data
//    {
//
//      if (rxBuf[i] < 0x10)                    // If data byte is less than 0x10, add a leading zero
//      {
//        Serial.print("0");
//      }
//      Serial.print(rxBuf[i], HEX);
//      Serial.print(" ");
//    }
    Serial.println();
    if (rxId == 0x1CFD083F) {
      String vis1 = String(rxBuf[1], HEX);
      String vis2 = String(rxBuf[0], HEX);
      String vis = vis1 + vis2;
      int v = hexToDec(vis);
      int viscosity = v *0.015625;
      Serial.print("Viscosity = ");
      Serial.print(viscosity);
      Serial.print(" cP ");
    }
       if (rxId == 0x1CFD083F) {
      String den1 = String(rxBuf[3], HEX);
      String den2 = String(rxBuf[2], HEX);
      String den = den1 + den2;
      int d = hexToDec(den);
      int density = d *0.00003052;
      Serial.print("Density = ");
      Serial.print(density);
      Serial.print(" g/cc ");
    }
      if (rxId == 0x1CFD083F) {
      String die1 = String(rxBuf[7], HEX);
      String die2 = String(rxBuf[6], HEX);
      String die = die1 + die2;
      int diel = hexToDec(die);
      int dielectric = diel *0.00012207;
      Serial.print("Dielectric = ");
      Serial.print(dielectric);
    }
    
    if (rxId == 0x18FEEE3F) {
      String temp1 = String(rxBuf[3], HEX);
      String temp2 = String(rxBuf[2], HEX);
      String temp = temp1 + temp2;
      int a = hexToDec(temp);
      int temperature = (a *0.03125) - 273;
      Serial.print("Oil Temperature = ");
      Serial.print(temperature);
      Serial.print(" C");
    }
    if (rxId == 0x18FF313F) {
       String diag = String(rxBuf[0], HEX);
      int a = hexToDec(diag);
      Serial.print("Diagnosis = ");
      Serial.print(a);
    }
  }
}

unsigned int hexToDec(String hexString) {
  
  unsigned int decValue = 0;
  int nextInt;
  
  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/