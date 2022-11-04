/* Copyright (C) 2022 Samy Bennabi
 * All rights reserved.
 * Projet d'intégration 2
 * 
 * Ecole du Web
 * Cours Systèmes embarqués (c)2022
 *  
    @file           : MyDHT.h
    @author         : Samy Bennabi
    @version        : 1.0   04/05/22
    @description    : Classe permettant d'utiliser le senseur DHT

    platform = ESP32
    OS = Arduino
    Langage : C++

    Historique des versions
        Version    Date       Auteur       Description
        1.0        04/05/22   Samy       Première version du logiciel
        1.1        26/05/22   Samy       Ajout des fonctions pour humidité

**/
#ifndef MYDHT_H
#define MYDHT_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

class MyDHT
{
    private :
    sensor_t sensor;
    DHT_Unified *dht;
    sensors_event_t event;

    public :

    MyDHT(uint8_t DHTPIN, uint8_t DHTTYPE); // constructeur
    ~MyDHT(){}; // destructeur

    // pour voir les informations de senseur dans le terminal
    void printSensorDetails();

    // obtenir les valeurs
    float getTemp();    // de la temperature
    float getHumidity();// de l`humidite

    // afficher les valeurs temperature et humidite dans le terminal
    void printTemp();
    void printHumidity();
};

#endif