#include <Arduino.h>
#include "MyOledViewWorkingOFF.h"
using namespace std;

void MyOledViewWorkingOFF::display(Adafruit_SSD1306 *adafruit){
    MyOledViewWorking::display(adafruit);

    adafruit->setTextSize(1);
    adafruit->setCursor(80, 20);
    adafruit->print("Ready");

    adafruit->setTextSize(2);
    adafruit->setCursor(20, 30);
    adafruit->print(getTag("temp").c_str());


    adafruit->display();
}