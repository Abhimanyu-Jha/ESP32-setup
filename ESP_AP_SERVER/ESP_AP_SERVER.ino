// Load Wi-Fi library
#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

const char* local_ssid = "Abhimanyu";
const char* local_password =  "passkey99";


// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

void setup() {
  Serial.begin(115200);
  
  
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();

  // Connect to Jio-fi
  // Connect to Wi-Fi network with SSID and password
  WiFi.enableSTA(true); 
  WiFi.begin(local_ssid, local_password); 
  Serial.println("Connecting to WiFi(Hotspot)...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.print(".");
  }
 
  Serial.println("Connected to the WiFi(Hotspot) network");
  Serial.print("Hotspot IP Address: ");
  Serial.println(WiFi.localIP());
  
}
int ctr=0;
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
//        Serial.write(c);                    // print it out the serial monitor
        header += c;
      }
    }
    Serial.println("Contents of Header:");
    Serial.println(header);
//    server.send(200, "text/html","receiver at esp");
    // Clear the header variable  
    header = "";
    // Close the connection
    //  POST COLLECTED DATA
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
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }


 
//  delay(5*1000);  //Send a request every 10 seconds
    
}
