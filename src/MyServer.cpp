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

    // Route index.css
    this->on("/index.css", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/index.css", "text/css"); });

    //Route image
    this->on("/sac", HTTP_GET, [](AsyncWebServerRequest *request)
             { request->send(SPIFFS, "/sac.png", "img/png"); });

    this->onNotFound([](AsyncWebServerRequest *request)
                     { request->send(404, "text/plain", "Page Not Found"); });

    //Route pour avoir la température
    this->on("/getTemp", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
    std::string repString = "";
    if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askTempFour");
    String lireTempDuFour =String(repString.c_str());
    request->send(200, "text/plain", lireTempDuFour );
    });

    //Route pour avoir le compteur
     this->on("/getTempsCompteur", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
    std::string repString = "";
    if (ptrToCallBackFunction) repString = (*ptrToCallBackFunction)("askTempsCompteur");
    String lireTempsCompteur =String(repString.c_str());
    request->send(200, "text/plain", lireTempsCompteur );
    });

    //Route pour l'obtension des bois
    this->on("/getAllWood", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        HTTPClient http;
        String apiRestAddress = "http://165.227.37.65:3000/woods";
        http.begin(apiRestAddress);
        http.GET();
        String response = http.getString();
        String tempToSend;
        StaticJsonDocument<5000> doc;
        request->send(200, "text/plain", response );

    });

    //Route pour l'obtemsion des détail
    this->on("/getAllWoodDetail", HTTP_GET, [](AsyncWebServerRequest *request) {
        if(request->hasParam("name"))
        {

            AsyncWebParameter* p = request->getParam("name");
            HTTPClient http;
            String apiRestAddress = "http://165.227.37.65:3000/woodinfo/" + p->value();
            String response = "Error";
            bool beginResult = http.begin(apiRestAddress);
            if(!beginResult){
                Serial.println("Erreur lors de la connection au serveur");
            }
            else{
                Serial.println("Connection au serveur réussie");
                http.GET();
                response = http.getString();
                http.end();
            }

            request->send(200, "text/plain", response);
        }
        else{
            request->send(400, "text/plain", "Erreur : Paramètres manquant");
        };
    });

    //Route qui retourne les informations des bois
    this->on("/envoyerInfo", HTTP_GET, [](AsyncWebServerRequest *request)
    {
        AsyncResponseStream *response = request->beginResponseStream("text/html"); //Reception de la réponse
        AsyncWebParameter* drying = request->getParam(0); // Récupération de la valeur du premier paramètre de notre requête GET
        AsyncWebParameter* tempMin = request->getParam(1); // Récupération de la valeur du premier paramètre de notre requête GET
        String sendTo = "button envoyerInfo ";
        String actionToSend = String(sendTo + drying->value() + " " + tempMin->value());
        if (ptrToCallBackFunction) (*ptrToCallBackFunction)(actionToSend.c_str());
        request->send(200, "text/plain", "envoyerInfo");
    });
        this->begin();
};

