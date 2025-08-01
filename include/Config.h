#ifndef CONFIG_H
#define CONFIG_H

// ---------------- //
//     Commandes    //
// ---------------- //

// Pin de commande de la pompe à vide
#define VOID_PUMP_PIN 26

// Pin de commande de la pompe à lait
#define MILK_PUMP_PIN 28

// Pin de commande de l'eau froide
#define COLD_WATER_PIN 30

// Pin de commande de l'eau chaude
#define HOT_WATER_PIN 32

// Pin de commande de la vanne 3 voies
#define THREE_WAY_VALVE_PIN 38

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

// Adresse de l'écran pour l'affichage visuel des menus et des statuts Soit  0x3F soit 0x27 pour les tests
// A déterminer avec un programme de recherche de périphériques I2C disponible sur internet
#define LCD_I2C_ADDRESS 0x3F

// Nombre de caractères de l'écran par ligne
#define LCD_MAX_LENGTH 16

// Nombre de lignes de l'écran
#define LCD_MAX_LINES 2

// ---------------- //
//  Temps de lavage //
// ---------------- //

#define PRE_HEAT_HOT_WATER_PIPE_MS 1uL * 20uL * 1000uL
#define CLEAN_COLD_WATER_DURATION_MS 2uL * 60uL * 1000uL
#define CLEAN_AND_DRY_COLD_WATER_DURATION_MS  12uL * 60uL * 1000uL
#define CLEAN_HOT_WATER_DURATION_MS 8uL * 60uL * 1000uL

#define EVACUATION_DURATION_MS 2uL * 60uL * 1000uL
#define PURGE_DURATION_MS 7uL * 1000uL
#define DELAY_BETWEEN_TWO_COMMAND_MS 2uL * 1000uL

#define DELAY_HOT_WATER_MILK_PUMP_START 15uL * 1000uL

// ---------------- //
//       Leds       //
// ---------------- //

#define PIN_RGB_LED_RED 2

#endif