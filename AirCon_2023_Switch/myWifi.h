#ifndef myWifi_h
#define myWifi_h

#include "Arduino.h"

#include <WiFi.h>
#include "time.h"


#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "novashin2";
const char* password = "0311shin";
//const char* serverUrl = "http://geo.pionman.com:5000/airCon/setAirValues";
const char* serverUrl = "http://192.168.0.19:5000/airCon/setAirValues";

class myWifi {
  public:
    myWifi() {
    };

    void begin() {
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
      }
      Serial.println("WiFi connected.");
    } 

    bool sendAirConditionData(char* device, int temp, int mois, int illu, int co2, int tvoc, int dust1, int dust5, int dust10) {
      if (WiFi.status() != WL_CONNECTED) 
        return false;

      HTTPClient http;
      http.begin(serverUrl);
      http.addHeader("Content-Type", "application/json");

      String device_id(device);
      DynamicJsonDocument doc(1024);
      doc["deviceId"] = device_id;
      doc["temp"] = temp;
      doc["mois"] = mois;
      doc["illu"] = illu;
      doc["co2"] = co2;
      doc["tvoc"] = tvoc;
      doc["dust1"] = dust1;
      doc["dust5"] = dust5;
      doc["dust10"] = dust10;

      String jsonString;
      serializeJson(doc, jsonString);
      Serial.println(jsonString);

      int httpResponseCode = http.POST(jsonString);

      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        // String response = http.getString();
        // Serial.println(response);
      } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      http.end();
      delay(1000);
      return true;
    }

    void printLocalTime()
    {
      struct tm timeinfo;
      if(!getLocalTime(&timeinfo)){
        Serial.println("Failed to obtain time");
        return;
      }
      Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
    }

    void stopWifi() {
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
    }

  private:


};

#endif


