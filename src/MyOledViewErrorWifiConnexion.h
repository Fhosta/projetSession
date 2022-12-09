/**
    Class MyOled : Gestion d'un écran Oled Utilisant un GPIO d'un contrôleur ESP32
    @file MyOled.h (Héritage : Adafruit_SSD1306)
    @author Florian Hostachy
    @version 1.0 17/03/21  
    
    Historique des versions   
                            Versions    Date      Auteur      Description
                            1.0         24/11/22  Florian        Première version de la classe
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
        adafruit/Adafruit GFX Library @ ^1.10.1
        adafruit/Adafruit SSD1306 @ ^2.4.0
        adafruit/Adafruit NeoPixel @ ^1.7.0
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Résolution 128 x 64
            Protocole I2C, Adresse : 0x3C (défaut)
            GPIO21 : SDA
            GPIO22 : SCL

**/
#ifndef MYOLEDVIEWERRORWIFICONNEXION_H
#define MYOLEDVIEWERRORWIFICONNEXION_H
#include "MyOledView.h"

class MyOledViewErrorWifiConnexion : public MyOledView{
    public:
        void setNomDuSysteme(std::string val);

    private:
        std::string nomDuSysteme;

        void display( Adafruit_SSD1306 *adafruit);
        void update(Adafruit_SSD1306 *adafruit);
};

#endif