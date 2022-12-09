
/* Copyright (C) 2021 Alain Dube
 * All rights reserved.
 *
 * Projet Sac
 * Ecole du Web
 * Cours Objets connectés (c)2021
 *
    @file     main.cpp
    @author   Alain Dubé
    @version  1.1 21/08/15

    Historique des versions
           Version    Date       Auteur       Description
           1.1        21/08/15  Alain       Première version du logiciel
           1.3        9/12/2022 Florian     Version avec la plus part des fonctionalité

    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps =

            ESPAsyncWebServer-esphome                   (Pour accéder au Wifi)
            AsyncTCP-esphome                            (Pour utiliser les focntionnalités TCP)
            bblanchon/ArduinoJson@^6.17.2               (Pour accéder au fonctionnalités Json)
            adafruit/Adafruit GFX Library@^1.11.3       (                                   )
	          makuna/NeoPixelBus@^2.7.0                   (           Gestion écran           )
	          adafruit/Adafruit SSD1306@^2.5.7            (                                   )

    Autres librairies (à copier dans le répertoire lib)
         WifiManagerDevelopment
            //Remarques
            //Pour trouver le WifiManager (dans la branche development)
            //   https://github.com/tzapu/WiFiManager/tree/development
            //   Ne pas oublier d'appuyez sur l'ampoule et choisir : ajouter Lib

    Fonctions utiles (utilitaires)
        /lib/MYLIB/myFunctions.cpp
            //Pour vérifier plus simplement que deux chaines sont identiques
            bool isEqualString(std::string line1, std::string line2)
            //Pour extraire une partie d'une chaine de caractères avec l'aide d'un index
            std::string getValue(std::string data, char separator, int index)
            //Pour remplacer plus facilement une sous chaine
            bool replaceAll(std::string& source, const std::string& from, const std::string& to)
            //Pour obtenir un chaine aléatoire d'une certaine longeur
            std::string get_random_string(unsigned int len)

    Classes du système

        MyServer                        V1.0    Pour la gestion des routes pour le site WEB
            /data                               Répertoire qui contient les fichiers du site WEB
                index.html              V1.0    Page index du site WEB
                index.css               V1.0    CSS
                script.js               V1.0    JS (fonctions JavaScript)

    Liens gitHub

 * */

#include <iostream>
#include <string>

#include <Arduino.h>
#include <ArduinoJson.h>

#include "myFunctions.cpp" //fonctions utilitaires

using namespace std;

#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
#define WEBSERVER_H

#include "MyDHT.h"
MyDHT *dht;
float temperature = 0;
char strTemperature[64] = "";
char strDrying[64] = "";
#define PinTemp  15
#define dhtType DHT22

// gestion led
#define GPIOLedGreen 2  // GPIO utilisee par la led verte
#define GPIOLedYellow 4 // GPIO utilisee par la led jaune
#define GPIOLedRed 17 //  // GPIO utilisee par la led rouge

// gestion Oled

#include "MyOled.h"
#include "MyOledView.h"
#include "MyOledViewErrorWifiConnexion.h"
#include "MyOledViewInitialisation.h"
#include "MyOledViewWifiAp.h"
#include "MyOledViewWorking.h"
#include "MyOledViewWorkingCOLD.h"
#include "MyOledViewWorkingHEAT.h"
#include "MyOledViewWorkingOFF.h"

MyOled *myOled;
MyOledViewWorking *myOledViewWorking;
MyOledViewErrorWifiConnexion *myOledViewErrorWifiConnexion;
MyOledViewInitialisation *myOledViewInitialisation;
MyOledViewWorkingOFF *myOledViewWorkingOFF;
MyOledViewWorkingCOLD *myOledViewWorkingCOLD;
MyOledViewWorkingHEAT *myOledViewWorkingHEAT;
MyOledViewWifiAp *myOledViewWifiAp;
const unsigned int SCREEN_WIDTH = 128; // OLED display width, in pixels
const unsigned int SCREEN_HEIGHT = 64; // OLED display height, in pixels
const unsigned int OLED_RESET = 4;     // Reset pin # (or -1 if sharing Arduino reset pin)

// Pour la gestion du serveur ESP32
#include "MyServer.h"
MyServer *myServer = NULL;

// Variable pour la connection Wifi
const char *SSID = "SAC_Florian";
const char *PASSWORD = "sac12345";
String ssIDRandom;

// serveur api 
const char* serverName = "http://165.227.37.65:3000/bois";
unsigned long last_time = 0;
unsigned long timer_delay = 10000;

int drying = 0;
int dryingBois = 0;
int tempMin = 0;
int compteur = 0;
bool isDrying = false;

String boisReadings;

// fonction statique qui permet aux objets d'envoyer des messages (callBack)
std::string CallBackMessageListener(string message)
{
  while (replaceAll(message, std::string("  "), std::string(" ")));

    string actionToDo = getValue(message, ' ', 0);
    string arg1 = getValue(message, ' ', 1);
    string arg2 = getValue(message, ' ', 2);
    string arg3 = getValue(message, ' ', 3);
    string arg4 = getValue(message, ' ', 4);
    string arg5 = getValue(message, ' ', 5);
    string arg6 = getValue(message, ' ', 6);
    string arg7 = getValue(message, ' ', 7);
    string arg8 = getValue(message, ' ', 8);
    string arg9 = getValue(message, ' ', 9);
    string arg10 = getValue(message, ' ', 10);
 
  std::string tempDuFour = strTemperature; //Lire le senseur de température
  if (string(actionToDo.c_str()).compare(string("askTempFour")) == 0) {
  return(tempDuFour.c_str()); }

  std::string tempsCompteur = strDrying; //Lire le compteur
  if (string(actionToDo.c_str()).compare(string("askTempsCompteur")) == 0) {
  return(tempsCompteur.c_str()); }

  if (string(actionToDo.c_str()).compare(string("button")) == 0) 
  {
        if(string(arg1.c_str()).compare(string("envoyerInfo")) == 0) 
        {
            drying = atoi(arg2.c_str());
            Serial.println(drying);
            dryingBois = atoi(arg2.c_str());
            tempMin = atoi(arg3.c_str());
            Serial.println(tempMin);
            isDrying = true;
            return(String("Ok").c_str());
        }
  }
}

void displayViewAP()
{
  myOledViewErrorWifiConnexion = new MyOledViewErrorWifiConnexion();
  myOledViewErrorWifiConnexion->setNomDuSysteme(SSID);
  myOled->displayView(myOledViewErrorWifiConnexion);
}

void displayViewOFF()
{
  myOledViewWorkingOFF->setParams("nomSystem", "SAC System");
  myOledViewWorkingOFF->setParams("idSystem", "01436");
  myOledViewWorkingOFF->setParams("ipSystem", "165.227.37.65");
  myOledViewWorkingOFF->setParams("temp", strTemperature);
  myOled->displayView(myOledViewWorkingOFF);
  digitalWrite(GPIOLedGreen, LOW);
  digitalWrite(GPIOLedYellow, HIGH);
  digitalWrite(GPIOLedRed, LOW);
}

void displayViewCOLD()
{
  myOledViewWorkingCOLD->setParams("nomSystem", "SAC System");
  myOledViewWorkingCOLD->setParams("idSystem", "01436");
  myOledViewWorkingCOLD->setParams("ipSystem", "165.227.37.65");
  myOledViewWorkingCOLD->setParams("temp", strTemperature);
  myOled->displayView(myOledViewWorkingCOLD);
  digitalWrite(GPIOLedGreen, HIGH);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedRed, LOW);
}

void displayViewHEAT()
{
  myOledViewWorkingHEAT->setParams("nomSystem", "SAC System");
  myOledViewWorkingHEAT->setParams("idSystem", "01436");
  myOledViewWorkingHEAT->setParams("ipSystem", "165.227.37.65");
  myOledViewWorkingHEAT->setParams("temp", strTemperature);
  myOled->displayView(myOledViewWorkingHEAT);
  digitalWrite(GPIOLedGreen, LOW);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedRed, HIGH);
}

void setup()
{
  Serial.begin(9600);
  delay(100);

  dht = new MyDHT(PinTemp, dhtType);
  // Connection au WifiManager
  String ssIDRandom, PASSRandom;
  String stringRandom;
  stringRandom = get_random_string(4).c_str();
  ssIDRandom = SSID;
  ssIDRandom = ssIDRandom + stringRandom;
  stringRandom = get_random_string(4).c_str();
  PASSRandom = PASSWORD;
  PASSRandom = PASSRandom ;

  //Gestion des led
  pinMode(GPIOLedYellow, OUTPUT);
  pinMode(GPIOLedRed, OUTPUT);
  digitalWrite(GPIOLedGreen, LOW);
  digitalWrite(GPIOLedYellow, LOW);
  digitalWrite(GPIOLedRed, LOW);

  char strToPrint[128];
  sprintf(strToPrint, "Identification : %s   MotDePasse: %s", ssIDRandom, PASSRandom);
  Serial.println(strToPrint);

  if (!wm.autoConnect(ssIDRandom.c_str(), PASSRandom.c_str()))
  {
    Serial.println("Erreur de connexion.");
  }
  else
  {
    Serial.println("Connexion Établie.");
  }

  // ----------- Routes du serveur ----------------
  myServer = new MyServer(80);
  myServer->initAllRoutes();
  myServer->initCallback(&CallBackMessageListener);

  // Oled
  myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
  myOled->init();
  myOled->veilleDelay(30); // En secondes

  myOledViewWorking = new MyOledViewWorking();
  myOledViewInitialisation = new MyOledViewInitialisation();
  myOled->displayView(myOledViewInitialisation);

  delay(3000);

  myOledViewWifiAp = new MyOledViewWifiAp();
  myOledViewWifiAp->setNomDuSysteme("Bonjour");
  myOledViewWifiAp->setSsIDDuSysteme(SSID);
  myOledViewWifiAp->setPassDuSysteme(PASSWORD);
  
  myOledViewWorkingOFF = new MyOledViewWorkingOFF();
  myOledViewWorkingCOLD = new MyOledViewWorkingCOLD();
  myOledViewWorkingHEAT = new MyOledViewWorkingHEAT();
}

void loop()
{
  delay(3000);
  temperature = dht->getTemp();
  sprintf(strTemperature, "%g", temperature);

  myOledViewWorking->setParams("temp", strTemperature);

  if(dryingBois== 0){ isDrying = false; }

  if (isDrying)
  {
    if(temperature >= tempMin){
    displayViewHEAT();
    dryingBois --;
    sprintf(strDrying,"%g",dryingBois);
    Serial.println(dryingBois);
    }else{
    displayViewCOLD();
    }
  }
  else
  {
    displayViewOFF();
  }

  delay(1000); // reduct
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}