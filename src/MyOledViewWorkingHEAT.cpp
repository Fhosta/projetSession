#include <Arduino.h>
#include "MyOledViewWorkingHEAT.h"
using namespace std;

void MyOledViewWorkingHEAT::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);

    adafruit->setCursor(80, 20);
    adafruit->print("Heating");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());

    adafruit->setCursor(80, 30);

    adafruit->display();
}

void MyOledViewWorkingHEAT::update(Adafruit_SSD1306 *adafruit){
    adafruit->setTextColor(WHITE);

    adafruit->clearDisplay();
    adafruit->setTextSize(1);
    adafruit->setCursor(0, 0);
    adafruit->print("WorkingHEAT");

    adafruit->display();
}