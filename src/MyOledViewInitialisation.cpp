#include "MyOledViewInitialisation.h"

void MyOledViewInitialisation::setIdDuSysteme(std::string val){
    idDuSysteme = val;
}

void MyOledViewInitialisation::setNomDuSysteme(std::string val){
    nomDuSysteme=val;
}

void MyOledViewInitialisation::display(Adafruit_SSD1306 *adafruit){
    adafruit->clearDisplay();

    adafruit->setTextSize(2);
    adafruit->setCursor(0, 0);
    adafruit->print("SAC System");

    adafruit->setTextSize(1);
    adafruit->setCursor(0, 20);
    adafruit->print("ID : ");
    adafruit->setCursor(24, 20);
    adafruit->print("oui");
    adafruit->setCursor(0, 30);
    adafruit->print("INITIALIZATION....");
    
    
    adafruit->display();
}

void MyOledViewInitialisation::update(Adafruit_SSD1306 *adafruit){
    
}