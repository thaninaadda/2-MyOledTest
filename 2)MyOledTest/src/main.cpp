/**
    OledProjet
    Expérimentations sur l'utilisation des classes et d'un écran Oled (avec un bouton) sur un ESP32
    @file main.cpp
    @author Alain Dubé
    @version 1.0 17/03/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      17/03/21   Ald          Première version qui démontre l'utilisation de classes
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = 
            adafruit/Adafruit GFX Library @ ^1.10.1     (Pour la classe MyOled)
            adafruit/Adafruit SSD1306 @ ^2.4.0          (Pour la classe MyOled)
            adafruit/Adafruit NeoPixel @ ^1.7.0         (Pour la classe MyOled)

    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Classes du système
        MyButton    V1.0    Pour la gestion du bouton
            GPIO32 : Toutch 8

        MyOled      V1.0    Pour interfacer le Oled
            Résolution 128 x 64
            Protocole I2C, Adresse : 0x3C 
            GPIO21 : SDA
            GPIO22 : SCL
**/

#include <Arduino.h>
#include <sstream>

//Classe MyButton 
#include "MyButton.h"
#define PIN_BUTTON_USED T8      //IO32  - Pin utilisée sur le ESP32
MyButton myButton;

//Classe MyOled 
#include <wire.h>
#define SCREEN_WIDTH 128        // OLED display width, in pixels
#define SCREEN_HEIGHT 64        // OLED display height, in pixels
#define OLED_RESET 4            // Reset pin # (or -1 if sharing Arduino reset pin)
#define OLED_I2C_ADDRESS 0x3C   // Adresse I2C de l'écran Oled
#include "MyOled.h"
MyOled *myOled = NULL;

//Il semble que ::to_string n'est pas fonctionnel
//to_string is not a member of std, says g++ (mingw)
//Référence : https://stackoverflow.com/questions/12975341/to-string-is-not-a-member-of-std-says-g-mingw
namespace patch {
    template < typename T > std::string to_string( const T& n ) {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}


void setup() {

    Serial.begin(9600);
    delay(100);
    Serial.println("\nOled project system\n");

    myOled = new MyOled(&Wire, OLED_RESET, SCREEN_HEIGHT, SCREEN_WIDTH);
    myOled->init(OLED_I2C_ADDRESS);
    myOled->veilleDelay(30); //En secondes
    myOled->DisplayInitialisationSystem("My Oled");

    //T0:pin24(default)  T1:Pin23     T2:Pin22   T3:Pin21 ,...   T8:Pin32
    myButton.init(PIN_BUTTON_USED);
}

void loop() {

    myOled->veilleCheck();

    int NbreDSecondes = myButton.checkMyButton(); //En dixiemes de secondes (retourne 0 si le bouton n'est pas appuyé)
    if (NbreDSecondes < -100) { //10 secondes = HardReset 
        ESP.restart(); //Suppression des réglages et redemarrage...
        }
        else if (NbreDSecondes > 0) { //Entre 0.1 et 10 secondes = Bouton est appuyé
            string messageToSend;
            if (myOled->veilleCheck())
                    messageToSend = "Exit sleep mode....";
                else
                    messageToSend = "Button pressed";
            myOled->DisplayWorkingScreen("System", messageToSend);
            delay(3000);
            myOled->DisplayWorkingScreen("System", "Working mode");
         }
}