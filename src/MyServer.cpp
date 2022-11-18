/**
    Gestion d'un serveur WEB
    @file MyServer.cpp
    @author Alain Dubé
    @version 1.1 20/11/20
*/
#include <Arduino.h>
#include "MyServer.h"
using namespace std;

typedef std::string (*CallbackType)(std::string);
CallbackType MyServer::ptrToCallBackFunction = NULL;

// Exemple pour appeler une fonction CallBack
// if (ptrToCallBackFunction) (*ptrToCallBackFunction)(stringToSend);
void MyServer::initCallback(CallbackType callback)
{
    ptrToCallBackFunction = callback;
}

void MyServer::initAllRoutes()
{
    currentTemperature = 3.3f;

    // Initialisation du SPIFF.
    if (!SPIFFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

    // Route initiale (page html)
    this->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/index.html", "text/html"); });

    // Route du script JavaScript
    this->on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/script.js", "text/javascript"); });

    this->on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/index.css", "text/css"); });

    this->on("/sac", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/sac.png", "img/png"); });

    this->onNotFound([](AsyncWebServerRequest *request)
                     { request->send(404, "text/plain", "Page Not Found"); });


    // this->on("/getNomEsp", HTTP_GET, [](AsyncWebServerRequest *request) {
    // std::string repString = "";
    // if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askNomFour");
    // String lireNomDuFour =String(repString.c_str());
    // request->send(200, "text/plain", lireNomDuFour );
    // });
    this->on("/lireTemp", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
    std::string repString = "";
    if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askTempFour");
    String lireTempDuFour =String(repString.c_str());
    request->send(200, "text/plain", lireTempDuFour );
    });


this->on("/getAllWood", HTTP_GET, [](AsyncWebServerRequest *request) 
{
    HTTPClient http;
    String apiRestAddress = "http://165.227.37.65:3000/woods";
    http.begin(apiRestAddress);
    http.GET();
    String response = http.getString();
    Serial.print(response);
    String tempToSend;
    StaticJsonDocument<5000> doc;

    // response = "";
    // if(response[response.length()-1]==']') response[response.length()-1] = ' ';
    // if(response[0]=='[') response[0] = ' ';

    // deserializeJson(doc, response);
    // JsonObject obj1 = doc.as<JsonObject>();
    // std::string woodId;
    // String woodName;

    // for (JsonPair kv1 : obj1) 
    // {
    // woodId = kv1.key().c_str();
    // Serial.print("Element : ");Serial.println(woodId.c_str());

    // JsonObject elem = obj1[woodId];
    // woodName = elem["name"].as<String>();
    // if(tempToSend!="") tempToSend += "&";
    // tempToSend += String(woodId.c_str()) + String("&") + String(woodName.c_str());
    // Serial.print(woodName);Serial.print(" ");
    // //Pour parcourir les éléments de l'objet
    // for (JsonPair kv2 : elem)
    //     {
    //         Serial.print(" Sous element : ");Serial.print(kv2.key().c_str());
    //         Serial.print(" : ");Serial.println(kv2.value().as<char*>());
    //     }
    // }
    request->send(200, "text/plain", response );

});
    this->begin();
};
