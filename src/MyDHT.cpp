/*
 * MyTemp.cpp
 *
 *  Created on : 04/05/22
 *  @Author: Florian Hostachy
 */
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "MyDHT.h"

MyDHT::MyDHT(uint8_t DHTPIN, uint8_t DHTTYPE) // constructeur
{
    MyDHT::dht = new DHT_Unified(DHTPIN, DHTTYPE);
    dht->begin();
    dht->temperature().getSensor(&sensor);
    dht->humidity().getSensor(&sensor);
};

// pour voir les details des senseurs temperature et humidité
void MyDHT::printSensorDetails()
{
    dht->temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    dht->humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
};

// obtenir la valeur de la temperature
// return : 0 en cas d`erreur sinon la valeur de la temperature en float
float MyDHT::getTemp()
{
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        // Serial.println(F("Error reading temperature!"));
        return 0;
    }
    else {
        return event.temperature;
    }
};

// obtenir la valeur de l`humidité
// return : 0 en cas d`erreur sinon la valeur de l`humidité en float
float MyDHT::getHumidity()
{
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
        return 0;
    }
    else {
        return event.relative_humidity;
    }
};

// afficher la temparature dans le terminal
void MyDHT::printTemp()
{
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
    }
    else {
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));
    }
};

// afficher l`humidité dans le terminal
void MyDHT::printHumidity()
{
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
    }
    else {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
    }
};