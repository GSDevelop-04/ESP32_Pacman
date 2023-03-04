// 2023 Sylvain Grimal Pac-man pour SI-CIT

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library for ST7735

#include <SPI.h>

#include "sprites.h"
#include "plateau.h"

#define TFT_CS        14
#define TFT_RST       16 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC        27
// NB: hardware SPI pins

// Joystick
#define pinJoyHB 35
#define pinJoyDG 4
#define pinJoyAlim 17
#define pinJoySW 25

// decalage plateau dans ecran
#define DX 22
#define DY 20
// recul du sprite pas rapport à la case
#define RX 3
#define RY 2

// les directions
#define DROITE 1
#define GAUCHE 2
#define BAS 3
#define HAUT 4

// les differents modes des fantomes
#define CHASSE 0
#define DIFFUSION 1
#define PEUR 2
#define MORT 3

#define TPSPEUR 12000  // 12 s pour manger les fantomes
#define TPSCLIGNO 4000 // 4 dernieres secondes en clignotement

// gestion des joueurs
#define PERNORMALE 20 // toutes les 20 ms
#define PERMORT    10 // retour rapide pour les morts
#define PERSUPER   25 // fantome plus lent si superPIL

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// le Pacman
int xPacman ,
    anc_xPacman;
int yPacman,
    anc_yPacman;

int bonus;

#define XDEBUTPA 13
#define YDEBUTPA 23

int ePacman;
int nbVies = 3;
byte dirPacman;
unsigned long tpsPacman;
byte perPacman;
int pil = 0;

// la phase commune à tous les fantomes
byte phase = DIFFUSION;

// Blinky
int xBlinky,
    anc_xBlinky;
int yBlinky,
    anc_yBlinky;

#define XDEBUTBL 14
#define YDEBUTBL 11

int eBlinky;
byte dirBlinky;
byte phBlinky;
unsigned long tpsBlinky;
unsigned long peurBlinky = 0;
byte perBlinky;


// Pinky
int xPinky,
    anc_xPinky;
int yPinky,
    anc_yPinky;

#define XDEBUTPI 13
#define YDEBUTPI 13

int ePinky;
byte dirPinky;
byte phPinky;
unsigned long tpsPinky;
unsigned long peurPinky = 0;
byte perPinky;

// Clyde
int xClyde,
    anc_xClyde;
int yClyde,
    anc_yClyde;

#define XDEBUTCL 15
#define YDEBUTCL 13

int eClyde;
byte dirClyde;
byte phClyde;
unsigned long tpsClyde;
unsigned long peurClyde = 0;
byte perClyde;

// Inky
int xInky,
    anc_xInky;
int yInky,
    anc_yInky;

#define XDEBUTIN 14
#define YDEBUTIN 14

int eInky;
byte dirInky;
byte phInky;
unsigned long tpsInky;
unsigned long peurInky = 0;
byte perInky;



int score;


unsigned long tps;

unsigned long perDiffusion = 5000; // 5  sec de diffusion
unsigned long perChasse = 20000; // 20 sec de chasse



unsigned long tpsDifCha; // alternance des modes poursuite et chasse

uint8_t plateau[28 * 31];

void setup(void) {
  init_io();

  Serial.begin(500000);
  Serial.print("ILI9341 Test!");

  tft.begin();

  Serial.println(F("Initialized"));

  tft.fillScreen(ILI9341_BLACK);

  delay(500);

  score = 0;
  init_plateau();
  affiche_plateau();
  debutJeu();
}

void loop() {
  tps = millis();
  if (tps >= tpsPacman) {
    tpsPacman = tps + perPacman;
    gestionPacman();
  }

  if (tps >= tpsBlinky) {
    tpsBlinky = tps + perBlinky;
    gestionBlinky();
  }

  if (tps >= tpsPinky) {
    tpsPinky = tps + perPinky;
    gestionPinky();
  }

  if (tps >= tpsClyde) {
    tpsClyde = tps + perClyde;
    gestionClyde();
  }

  if (tps >= tpsInky) {
    tpsInky = tps + perInky;
    gestionInky();
  }
  if (tps >= tpsDifCha) {
    dirBlinky = inverseDir(dirBlinky);
    dirPinky = inverseDir(dirPinky);
    if (phase == DIFFUSION) {
      phase = CHASSE;
      tpsDifCha = tps + perChasse;
    } else if (phase == CHASSE) {
      phase = DIFFUSION;
      tpsDifCha = tps + perDiffusion;
    }
  }
  Serial.println(pil);
  if (pil >= 244) {
    pil = 0;
    init_plateau();
    affiche_plateau();
    debutJeu();
  }
}
