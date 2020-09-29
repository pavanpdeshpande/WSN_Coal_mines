#include <SPI.h> 
#include <RF24.h>
#include <DHT.h>

//Constants
#define DHTPIN 4     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
const int flamePin = 3;
int smokeA0 = A5;
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

int buzz=5;
RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};
 
float a[5];
int Flame = HIGH;

void setup()
{
  Serial.begin(9600);
  delay(1000);
     pinMode(flamePin, INPUT);
     pinMode(smokeA0, INPUT);
     pinMode(buzz,OUTPUT);
    dht.begin(); 

  myRadio.begin();  
  myRadio.setChannel(116); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(1000);
}

void loop()
{
   a[0] = dht.readHumidity(); 
   a[1]= dht.readTemperature();
    Flame = digitalRead(flamePin);
      if(Flame==LOW)
    {  a[2]=1;//Fire!!
     digitalWrite(buzz,HIGH);
    }else
    {
      a[2]=0; //NO  fire
      digitalWrite(buzz,LOW);
    }
  a[3] = analogRead(smokeA0);    //smoke detected
  myRadio.write(&a, sizeof(a)); 

}
