#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "Abhimanyu";
const char* password =  "passkey99";
 
void setup() {
 
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  WiFi.enableSTA(true); 
  WiFi.begin(ssid, password); 
  Serial.println("Connecting to WiFi..");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.print(".");
  }
 
  Serial.println("Connected to the WiFi network");
  digitalWrite(2,HIGH);
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
 
}
int ctr=0; 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
 
   HTTPClient http;   
   Serial.println("Sending Data");
   http.begin("http://192.168.43.230:8000/upload");  //Specify destination for HTTP request
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");             //Specify content-type header
//  
   String data="param1=value"+String(ctr)+"&"+"param2=value"+String(ctr+1);
   int httpResponseCode = http.POST(data);   //Send the actual POST request
   ctr=ctr+1;
 
   if(httpResponseCode>0){
 
    String response = http.getString();                       //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(0.01*1000);  //Send a request every 10 seconds
 
}
