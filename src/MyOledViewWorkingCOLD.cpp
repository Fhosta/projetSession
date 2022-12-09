#include <Arduino.h>
#include "MyOledViewWorkingCOLD.h"
using namespace std;

void MyOledViewWorkingCOLD::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);

    adafruit->setCursor(80, 20);
    adafruit->print("Waiting");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());

    adafruit->setCursor(80, 30);
    //displayGifFire(adafruit, 60, 30);

    adafruit->display();
}

void MyOledViewWorkingCOLD::update(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);

    adafruit->setTextSize(1);
    adafruit->setCursor(80, 20);
    adafruit->print("Waiting");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());

    //adafruit->setCursor(80, 30);
    //displayGifFire(adafruit, 60, 30);


    adafruit->display();
}