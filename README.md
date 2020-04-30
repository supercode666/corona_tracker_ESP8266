# Corana Virus Tracker with NodeMCU ESP8266
Version : V1.0

This is a version 1 of the Corona Virus Tracker for Specific country that will automtically update itself when there is a new data coming in on the ESP8266 or the API.

---

### Installation of NodeMCU ESP8266

* Enter https://arduino.esp8266.com/stable/package_esp8266com_index.json into the Additional Board Manager URLs field.

---

### Modication
#### 1. WiFi SSID and Password

* Change the ssid and password to your wifi or hotspots ssid and password :
```c
const char* ssid = "your_ssid";                                                         
const char* password = "your_password";                                             
```

#### 2. Country Name
* Change the country to your desire country
* Example : India, INDIA, india
* Not case-sensitive



```c
const char* region = "your_country";                                             
```

