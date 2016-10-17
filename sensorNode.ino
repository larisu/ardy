//TO DO!
//**************************
//- remove wifi
//- Arduino Nano

#include <DHT.h>;

#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value
float value;// Stores CO value
float light;

/* MQ-7 Carbon Monoxide Sensor Circuit with Arduino */

const int AOUTpin=0;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
const int AOUTpinLight=1;
#define SSID "larisa3"
#define PASS "littlest"
#define IP "184.106.153.149" // thingspeak.com
String GET = "GET /update?key=DTWKMJPR1K1S19XK&field1=";




boolean connectToWiFi()
{
   Serial.println("AT+CWMODE=1");
  delay(2000);
  String cmd="AT+CWJAP=\"";
  cmd+=SSID;
  cmd+="\",\"";
  cmd+=PASS;
  cmd+="\"";
  Serial.println(cmd);
  delay(5000);
  if(Serial.find("OK")){
    return true;
  }else{
    return false;
  }
}



void setup() {
  // initialize serial:
  dht.begin();
  Serial.begin(9600);
  Serial.println("AT");
  delay(5000);
  if(Serial.find("OK")){
    connectToWiFi();
  }
}

void loop() {
 hum = dht.readHumidity();
 temp= dht.readTemperature();
  hum = (int)hum;
  temp = (int)temp;
  value= analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
  light=analogRead(AOUTpinLight);
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += IP;
  cmd += "\",80";
  Serial.println(cmd);
  delay(2000);
  if(Serial.find("Error")){    
    return;
  }
  cmd = GET;
  cmd += String(hum);
  cmd += "&field2=";
  cmd += String(temp);
  cmd += "&field3=";
  cmd += String(value);
   cmd += "&field4=";
  cmd += String(light);
  cmd += "\r\n";
  Serial.print("AT+CIPSEND=");
  Serial.println(cmd.length());
  
  if(Serial.find(">")){
    Serial.print(cmd);
  }else{
    Serial.println("AT+CIPCLOSE");
  }
  for (int i=0 ; i<=24; i++)
  {
  delay(5000);
  }
  
  //delay(5000);
  //delay(5000); 
}
