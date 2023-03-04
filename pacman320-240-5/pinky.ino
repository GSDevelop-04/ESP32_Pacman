#define XCPIDIF 1
#define YCPIDIF 1
#define XCPIMORT 14
#define YCPIMORT 11

void affichePinky() {
  if ((phPinky == CHASSE) || (phPinky == DIFFUSION)) {
    if (dirPinky == 1) {
      if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pid1, pid1Width, pid1Height);
      if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pid2, pid2Width, pid2Height);
    }
    if (dirPinky == 2) {
      if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pig1, pig1Width, pig1Height);
      if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pig2, pig2Width, pig2Height);
    }
    if (dirPinky == 3) {
      if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pib1, pib1Width, pib1Height);
      if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pib2, pib2Width, pib2Height);
    }
    if (dirPinky == 4) {
      if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pih1, pih1Width, pih1Height);
      if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pih2, pih2Width, pih2Height);
    }
  }
  if (phPinky == PEUR) {
    if (tps < peurPinky - TPSCLIGNO) {
      if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, peur1, peur1Width, peur1Height);
      if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, peur2, peur2Width, peur2Height);
    } else {
      if ((tps / 500) % 2 == 0) { // 1/2 secondes paires en bleu
        if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, peur3, peur3Width, peur3Height);
        if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, peur4, peur4Width, peur4Height);
      } else {    // 1/2 secondes impaires en blanc
        if (ePinky / 5 == 0)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, peur1, peur1Width, peur1Height);
        if (ePinky / 5 == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, peur2, peur2Width, peur2Height);
      }
    }
  }
  if (phPinky == MORT) {
    if (dirPinky == 1)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, oeil1, oeil1Width, oeil1Height);
    if (dirPinky == 2)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, oeil2, oeil2Width, oeil2Height);
    if (dirPinky == 3)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, oeil3, oeil3Width, oeil3Height);
    if (dirPinky == 4)  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, oeil4, oeil4Width, oeil4Height);
  }

  anc_xPinky = xPinky;
  anc_yPinky = yPinky;
}

void gestionPinky() {
  // case de pacman
  byte xcPacman = xCase(xPacman);
  byte ycPacman = yCase(yPacman);
  // case de Pinky
  byte xcPinky = xCase(xPinky);
  byte ycPinky = yCase(yPinky);

  int dh, db, dd, dg;
  byte choix;

  int xcPoursuite = xcPacman;
  int ycPoursuite = ycPacman;


  if (((phPinky == CHASSE) || (phPinky == DIFFUSION)) && ((xcPinky == xcPacman) && (ycPinky == ycPacman))) { // c'est la fin !
    nbVies--;
    affiche_plateau();
    debutJeu();
  }

  if ((tps > peurPinky) && (phPinky != MORT)) {
    phPinky = CHASSE;
    perBlinky = PERNORMALE;
  } else {
    if ((xcPinky == xcPacman) && (ycPinky == ycPacman) && (phPinky != MORT)) {
      phPinky = MORT;
      perPinky = PERMORT; // retour rapide;
      tft.setCursor((xcPinky - 1)*pasX + DX, ycPinky * pasY + DY);
      tft.println(bonus);
      bonus = bonus * 2;
      delay(700);
      effaceBonus(xcPinky - 1, ycPinky);
      peurPinky = tps;
    }
  }

  if ((phPinky == CHASSE) || (phPinky == DIFFUSION)) {
    if (phase == CHASSE) {
      xcPoursuite = xcPacman;
      ycPoursuite = ycPacman;
      if (dirPacman == 1) xcPoursuite = xcPacman + 4;
      if (dirPacman == 2) xcPoursuite = xcPacman - 4;
      if (dirPacman == 3) ycPoursuite = ycPacman + 4;
      if (dirPacman == 4) ycPoursuite = ycPacman - 4;


    }

    if (phase == DIFFUSION) {
      xcPoursuite = XCPIDIF;
      ycPoursuite = YCPIDIF;

    }
  }
  if (phPinky == MORT) {
    xcPoursuite = XCPIMORT;
    ycPoursuite = YCPIMORT;
    if ((xcPinky == XCPIMORT) && (ycPinky == YCPIMORT)) {
      phPinky  = CHASSE;
      perPinky = PERNORMALE;
    }
  }


  switch (dirPinky) {
    case DROITE:
      if (phPinky == PEUR) {
        choix =       alea(xcPinky, ycPinky - 1, xcPinky + 1, ycPinky, xcPinky, ycPinky + 1, xcPoursuite, ycPoursuite, 0);
      } else choix = plusProche(xcPinky, ycPinky - 1, xcPinky + 1, ycPinky, xcPinky, ycPinky + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xPinky % pasX == pasX - RX)) dirPinky = HAUT;
      if ((choix == 3) && (xPinky % pasX == pasX - RX)) dirPinky = BAS;
      break;

    case GAUCHE:
      if (phPinky == PEUR) {
        choix =       alea(xcPinky, ycPinky - 1, xcPinky - 1, ycPinky, xcPinky, ycPinky + 1, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcPinky, ycPinky - 1, xcPinky - 1, ycPinky, xcPinky, ycPinky + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xPinky % pasX == pasX - RX)) dirPinky = HAUT;
      if ((choix == 3) && (xPinky % pasX == pasX - RX)) dirPinky = BAS;
      break;

    case BAS:
      if (phPinky == PEUR) {
        choix =       alea(xcPinky - 1, ycPinky, xcPinky, ycPinky + 1, xcPinky + 1, ycPinky, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcPinky - 1, ycPinky, xcPinky, ycPinky + 1, xcPinky + 1, ycPinky, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (yPinky % pasY == pasY - RY)) dirPinky = GAUCHE;
      if ((choix == 3) && (yPinky % pasY == pasY - RY)) dirPinky = DROITE;
      break;

    case HAUT:
      if (phPinky == PEUR) {
        choix =       alea(xcPinky - 1, ycPinky, xcPinky, ycPinky - 1, xcPinky + 1, ycPinky, xcPoursuite, ycPoursuite, 1);
      }  else choix = plusProche(xcPinky - 1, ycPinky, xcPinky, ycPinky - 1, xcPinky + 1, ycPinky, xcPoursuite, ycPoursuite, 1);
      if ((choix == 1) && (yPinky % pasY == pasY - RY)) dirPinky = GAUCHE;
      if ((choix == 3) && (yPinky % pasY == pasY - RY)) dirPinky = DROITE;
      break;
  }

  if (dirPinky == DROITE) xPinky++;
  if (dirPinky == GAUCHE) xPinky--;
  if (dirPinky == BAS)    yPinky++;
  if (dirPinky == HAUT)   yPinky--;

  // Le tunnel
  if (xPinky >= 183) xPinky = 1;
  if (xPinky <= 0) xPinky = 182;

  ePinky++;
  if (ePinky == 10) ePinky = 0;

  effaceFantome(anc_xPinky, anc_yPinky);
  affichePinky();

}
