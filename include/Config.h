#ifndef CONFIG_H
#define CONFIG_H

// ---------------- //
//     Commandes    //
// ---------------- //

// Pin de commande de la pompe à vide
#define VOID_PUMP_PIN 28

// Pin de commande de la pompe à lait
#define MILK_PUMP_PIN 30

// Pin de commande de l'eau froide
#define COLD_WATER_PIN 34

// Pin de commande de l'eau chaude
#define HOT_WATER_PIN 32

// Pin de commande de la vanne 3 voies
#define THREE_WAY_VALVE_PIN 40

// Bouton de navigation pour les menus
#define NAV_MENU_BTN_PIN 8

// Bouton de confirmation pour les menus
#define CONFIRM_MENU_BTN_PIN 9

// ---------------- //
//     Capteurs     //
// ---------------- //

// Pin utilisé pour le capteur de niveau d'eau (tout ou rien) dans le bac de lavage
#define WATER_SENSOR_PIN A7

// ---------------- //
//       Ecran      //
// ---------------- //

// Adresse de l'écran pour l'affichage visuel des menus et des statuts
#define LCD_I2C_ADDRESS 0x3F

// Nombre de caractères de l'écran par ligne
#define LCD_MAX_LENGTH 16


#endif