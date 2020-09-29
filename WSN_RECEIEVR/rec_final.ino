#include <SPI.h>  
#include <RF24.h>

RF24 myRadio (7, 8); 
 

byte addresses[][6] = {"0"}; 

float a[5];

void setup() 
{
  Serial.begin(9600);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(116); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{
     // Serial.print("\nPackage:");

  if ( myRadio.available()) 
  {

  
    while (myRadio.available())
    {
      myRadio.read( &a, sizeof(a) );
    }

      Serial.print("\n data received :\n ");
    Serial.print("\n humidity :");
    Serial.print(a[0]);
    Serial.print("\n Temperature : ");
    Serial.print(a[1]);
      Serial.print("°C");
   if(a[2]==1)
   Serial.print("\n Fire detected \n");
   else
   Serial.print("\n No Fire ");
    Serial.print("\n smoke in PPM :");
    Serial.println(a[3]);
    delay(4000);
  }
}
