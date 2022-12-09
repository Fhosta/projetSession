#include "MyOledViewErrorWifiConnexion.h"

void MyOledViewErrorWifiConnexion::setNomDuSysteme(std::string val){
    nomDuSysteme = val;
}

void MyOledViewErrorWifiConnexion::display(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("Nom: ");
    adafruit->setCursor(40, 0);
    adafruit->print(nomDuSysteme.c_str());
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 20);
    adafruit->print("ERROR");

    adafruit->display();
}


void MyOledViewErrorWifiConnexion::update(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("Nom: ");
    adafruit->setCursor(40, 0);
    adafruit->print(nomDuSysteme.c_str());
    adafruit->setTextSize(2);
    adafruit->setCursor(0, 20);
    adafruit->print("ERROR");

    adafruit->display();
}