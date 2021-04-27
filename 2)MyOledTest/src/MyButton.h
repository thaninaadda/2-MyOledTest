
/* MyButton.h */
/* Copyright (C) 2020 Alain Dube
 * All rights reserved.
 *
 * Gestion d'un bouton 
 * 
 * */

/**
    Class MyButton : Gestion d'un bouton TOUCH ESP32
    @file MyButton.h (MyButton.cpp)
    @author Alain Dubé
    @version 1.0 17/03/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      17/03/21   Ald          Première version de la classe
                            
    platform = espressif32
    board = esp32doit-devkit-v1
    framework = arduino
    lib_deps = <Aucune>
    Autres librairies (à copier dans le répertoire lib)
        Aucune
    Touchs sensitives pins possibles       
        GPIO04 : T0 (défaut)    GPIO00 : T1     GPIO02 : T2     GPIO15 : T3     GPIO13 : T4
        GPIO12 : T5             GPIO14 : T6     GPIO27 : T7     GPIO32 : T8     GPIO33 : T9
    Sensibilité du bouton = 20 par défaut

    Exemple d'utilisation
        #include "MyButton.h"
        #define PIN_BUTTON_USED T8      //IO32  - Pin utilisée sur le ESP32
        MyButton myButton;
        myButton.init(PIN_BUTTON_USED);
        int NbreDSecondesAppuyes = myButton.checkMyButton();  //En dixième de secondes
        if(NbreDSecondesAppuyes>0) cout << "\nButton pressed";

**/

#include <Arduino.h>

#ifndef MYBUTTON_H
#define MYBUTTON_H

using namespace std;

class MyButton  {
public:
    void init(int GPIONumber = T0, int toucheButtonSensibiliteToUse = 20);
    //Appeler pour vérifier le nombre de dixiemes de secondes le bouton a été appuyé
    int checkMyButton();

private : 
    int buttonGPIO = T0;    //pin GPIO pour le bouton
    int toucheButtonSensibilite = 20;
    
    //Pour calculer le temps qu'il faut pour activer le bouton
    bool toucheButtonActif;
    int toucheButtonActifStart;
    int toucheButtonActifEnd;
};
#endif