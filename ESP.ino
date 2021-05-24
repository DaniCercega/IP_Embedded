/*void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}*/

#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

const char *ssid =  "DIGI-24-E1B8";     // replace with your wifi ssid and wpa2 key
const char *pass =  "qH4UThaf5G";


WiFiClient client;
IPAddress server_addr(35,157,16,43);  // IP of the MySQL *server* here

char user[] = "sql11414385";              // MySQL user login username
char password[] = "rJu85hQjtS"; 
String input;

MySQL_Connection conn((Client *)&client);


 
void setup() 
{
       Serial.begin(115200);
       delay(10);
               
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
       WiFi.begin(ssid, pass); 
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 

      
}
 

void loop() { // run over and over
  if (Serial.available()) {
    
    delay(100);
    if (conn.connected()) {
    // do something
    input= Serial.readString();
    delay(100);
    Serial.println(input);
    char INSERT_SQL[input.length()+1];
    input.toCharArray(INSERT_SQL,input.length()+1);
    delay(100);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute(INSERT_SQL);
    delay(100);
    delete cur_mem;
    }
    else {
      conn.close();
    Serial.println("Connecting...");
    if (conn.connect(server_addr, 3306, user, password)) {
      delay(500);
      Serial.println("Successful reconnect!");
    }
    else {
      Serial.println("Cannot reconnect! Drat.");
    }
    }
  }
 
  

  
  /**/
  
  
}
