/** MyButton.cpp 
 Gestion d'un bouton 
 Copyright (C) 2021 Alain Dube
 All rights reserved.
 @file MyButton.cpp
 @author Alain Dubé
 @version 1.1 21/01/19
 **/

#include "MyButton.h"

/**
 * init Initialisation de l'objet
 *
 * La classe nécessite une initialisation préalable après l'instanciation
 * 
 * @param toucheButtonSensibiliteToUse Sensibilité du bouton à utiliser (par defaut : 20)
 * @param GPIONumber Le GPIO utilisé pour le bouton T0:pin24(default)  T1:Pin23     T2:Pin22   T3:Pin21
 */
void MyButton::init(int GPIONumber, int toucheButtonSensibiliteToUse) {
    buttonGPIO = GPIONumber;
    pinMode(buttonGPIO, INPUT);
    toucheButtonSensibilite = toucheButtonSensibiliteToUse;
}

/**
 * checkMyButton Teste si le bouton est activé et retourne le nombre de dixiemes de secondes 
 *
 * 
  * @return int 0 : Si rien   NbreSec : Nbre de secondes que le bouton est appuye et relaché   Négatif:si le bouton est appuyé mais non relaché
 */
int MyButton::checkMyButton() {
    //Vérification si l'usager a appuyé sur le bouton 
    if (touchRead(buttonGPIO) < toucheButtonSensibilite) {
        if (!toucheButtonActif) {
            toucheButtonActif = true;
            toucheButtonActifStart = (unsigned long)(esp_timer_get_time()) / 100000;
            toucheButtonActifEnd = 0;
            return (0);
        }
        toucheButtonActifEnd = (unsigned long)(esp_timer_get_time()) / 100000;
        toucheButtonActifEnd -= toucheButtonActifStart;
        return (-toucheButtonActifEnd);
    }
    else {
        if(toucheButtonActif) {
            toucheButtonActif = false;
            return (toucheButtonActifEnd);
        }
    }
    return (0);
}
