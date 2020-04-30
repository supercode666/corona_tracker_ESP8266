/*  
    Authored by : SUPER CODE 
    
    THIS SKETCH DOES : 
    i   ) Connects your own wifi
    ii  ) Pull Corona Virus Status API data
    iii ) Display each of the status data ijn the ESP8266-->LCD Display-->with customized display flow

    COMPONENTS :
    i)  NodeMCU ESP8266        - https://my.cytron.io/p-nodemcu-lua-v3-esp8266-wifi-with-ch340c?search=esp8266&description=1&src=search.list
    ii) i2c Serial LED Display - https://my.cytron.io/p-i2c-1602-serial-lcd-for-arduino-and-rpi?search=i2c&description=1&src=search.list

    !!!!!!!! ATTTENTION !!!!!!!! : EDIT THESE FOR YOUR OWN PROJECTS :
    
            i  ) wifi ssid              - line 39
            ii ) wifi password          - line 40
            iii) country name (region)  - line 43
            
*/

/* LIBRARIES */
#include <ESP8266WiFi.h>          //wifi setup
#include <ESP8266HTTPClient.h>    //http GET request method
#include <ArduinoJson.h>          //to decode the JSON data
#include <LiquidCrystal_I2C.h>    //lcd
/* end -- LIBRARIES */

/* INITIALIZATIONS */
//display delay
int dt = 1500;

//lcd setup
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);
/* end -- INITIALIZATIONS */

/* EDIT HERE */
// WiFi Parameters
const char* ssid = "your_ssid";                                                           //edit - 1
const char* password = "your_password";                                                   //edit - 2

// Region
const char* region = "your_country";   //not case sensitive ex: (INDIA/India/india)       //edit - 3 

/* end -- EDIT HERE */

void setup() {

  //lcd
  lcd.init();        // LCD initialization                     
  lcd.backlight();   // turn on backlight  

  //wifi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    lcd_print("Connecting wifi...","");   //trying to connect wifi
  }  


  //welcome msg
  lcd_print("SuperCode","Corona Tracker");
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://iothost.xyz/api/api.php?region=" + String(region)); //api link
    int httpCode = http.GET();
    
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Parsing
      const size_t bufferSize = 370;      
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      
      // Parameters
      //total
      int total_cases = root["data"]["summary"]["total_cases"];         //total cases
      int active_cases = root["data"]["summary"]["active_cases"];       //total active_cases
      int deaths = root["data"]["summary"]["deaths"];                   //total deaths
      int recovered = root["data"]["summary"]["recovered"];             //total recovered

      //today
      int change_total_cases = root["data"]["change"]["total_cases"];   //today cases
      int change_active_cases = root["data"]["change"]["active_cases"]; //today active_cases
      int change_deaths = root["data"]["change"]["deaths"];             //today deaths
      int change_recovered = root["data"]["change"]["recovered"];       //today recovered
      
      //Display the corona data
      lcd_print(  "TotalCases:"+ String(total_cases)   ,  "Today:"+ String(change_total_cases)  );
      lcd_print(  "ActiveCases:"+ String(active_cases) ,  "Today:"+ String(change_active_cases) );
      lcd_print(  "Deaths:"+ String(deaths)            ,  "Today:"+ String(change_deaths)       );
      lcd_print(  "Recovered:"+ String(recovered)      ,  "Today:"+ String(change_recovered)    );

    }
    
    http.end();   //Close connection
  }
  
  delay(dt);
}

void lcd_print(String top_display,String bottom_display){
  
    lcd.clear();
    delay(300);
    lcd.setCursor(0, 0);
    lcd.print(top_display);
    lcd.setCursor(0, 1);
    lcd.print(bottom_display);
    delay(dt);
  
}
