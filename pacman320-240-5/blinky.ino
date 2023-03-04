#define XCBLDIF 26
#define YCBLDIF 1
#define XCBLMORT 14
#define YCBLMORT 11

void afficheBlinky() {
  if ((phBlinky == CHASSE) || (phBlinky == DIFFUSION)) {
    if (dirBlinky == 1) {
      if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, bld1, bld1Width, bld1Height);
      if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, bld2, bld2Width, bld2Height);
    }
    if (dirBlinky == 2) {
      if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, blg1, blg1Width, blg1Height);
      if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, blg2, blg2Width, blg2Height);
    }
    if (dirBlinky == 3) {
      if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, blb1, blb1Width, blb1Height);
      if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, blb2, blb2Width, blb2Height);
    }
    if (dirBlinky == 4) {
      if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, blh1, blh1Width, blh1Height);
      if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, blh2, blh2Width, blh2Height);
    }
  }
  if (phBlinky == PEUR) {
    if (tps < peurBlinky - TPSCLIGNO) {
      if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, peur1, peur1Width, peur1Height);
      if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, peur2, peur2Width, peur2Height);
    } else {
      if ((tps / 500) % 2 == 0) { // 1/2 secondes paires en bleu
        if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, peur3, peur3Width, peur3Height);
        if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, peur4, peur4Width, peur4Height);
      } else {    // 1/2 secondes impaires en blanc
        if (eBlinky / 5 == 0)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, peur1, peur1Width, peur1Height);
        if (eBlinky / 5 == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, peur2, peur2Width, peur2Height);
      }
    }
  }
  if (phBlinky == MORT) {
    if (dirBlinky == 1)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, oeil1, oeil1Width, oeil1Height);
    if (dirBlinky == 2)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, oeil2, oeil2Width, oeil2Height);
    if (dirBlinky == 3)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, oeil3, oeil3Width, oeil3Height);
    if (dirBlinky == 4)  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, oeil4, oeil4Width, oeil4Height);
  }

  anc_xBlinky = xBlinky;
  anc_yBlinky = yBlinky;
}

void gestionBlinky() {
  // case de pacman
  byte xcPacman = xCase(xPacman);
  byte ycPacman = yCase(yPacman);
  // case de blinky
  byte xcBlinky = xCase(xBlinky);
  byte ycBlinky = yCase(yBlinky);

  int dh, db, dd, dg;
  byte choix;

  int xcPoursuite = xcPacman;
  int ycPoursuite = ycPacman;

  if (((phBlinky == CHASSE) || (phBlinky == DIFFUSION)) && ((xcBlinky == xcPacman) && (ycBlinky == ycPacman))) { // c'est la fin !
    Serial.println(phBlinky);
    nbVies--;
    affiche_plateau();
    debutJeu();
  }

  if ((tps > peurBlinky) && (phBlinky != MORT)) {
    phBlinky = CHASSE;
    perBlinky=PERNORMALE;
  } else {
    if ((xcBlinky == xcPacman) && (ycBlinky == ycPacman) && (phBlinky != MORT)) {
      phBlinky = MORT;
      perBlinky = PERMORT; // retour rapide;
      score += bonus;
      tft.setCursor((xcBlinky - 1)*pasX + DX, ycBlinky * pasY + DY);
      tft.println(bonus);
      bonus = bonus * 2;      
      delay(700);
      effaceBonus(xcBlinky - 1, ycBlinky);      
      peurBlinky = tps;
    }
  }

  if ((phBlinky == CHASSE) || (phBlinky == DIFFUSION)) {
    if (phase == CHASSE) {
      xcPoursuite = xcPacman;
      ycPoursuite = ycPacman;
    }

    if (phase == DIFFUSION) {
      xcPoursuite = XCBLDIF;
      ycPoursuite = YCBLDIF;

    }
  }
  if (phBlinky == MORT) {
    xcPoursuite = XCBLMORT;
    ycPoursuite = YCBLMORT;
    if ((xcBlinky == XCBLMORT) && (ycBlinky == YCBLMORT)) {
      phBlinky  = CHASSE;
      perBlinky = PERNORMALE;
    }
  }


  switch (dirBlinky) {
    case DROITE:
      if (phBlinky == PEUR) {
        choix =       alea(xcBlinky, ycBlinky - 1, xcBlinky + 1, ycBlinky, xcBlinky, ycBlinky + 1, xcPoursuite, ycPoursuite, 0);
      } else choix = plusProche(xcBlinky, ycBlinky - 1, xcBlinky + 1, ycBlinky, xcBlinky, ycBlinky + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xBlinky % pasX == pasX - RX)) dirBlinky = HAUT;
      if ((choix == 3) && (xBlinky % pasX == pasX - RX)) dirBlinky = BAS;
      break;

    case GAUCHE:
      if (phBlinky == PEUR) {
        choix =       alea(xcBlinky, ycBlinky - 1, xcBlinky - 1, ycBlinky, xcBlinky, ycBlinky + 1, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcBlinky, ycBlinky - 1, xcBlinky - 1, ycBlinky, xcBlinky, ycBlinky + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xBlinky % pasX == pasX - RX)) dirBlinky = HAUT;
      if ((choix == 3) && (xBlinky % pasX == pasX - RX)) dirBlinky = BAS;
      break;

    case BAS:
      if (phBlinky == PEUR) {
        choix =       alea(xcBlinky - 1, ycBlinky, xcBlinky, ycBlinky + 1, xcBlinky + 1, ycBlinky, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcBlinky - 1, ycBlinky, xcBlinky, ycBlinky + 1, xcBlinky + 1, ycBlinky, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (yBlinky % pasY == pasY - RY)) dirBlinky = GAUCHE;
      if ((choix == 3) && (yBlinky % pasY == pasY - RY)) dirBlinky = DROITE;
      break;

    case HAUT:
      if (phBlinky == PEUR) {
        choix =       alea(xcBlinky - 1, ycBlinky, xcBlinky, ycBlinky - 1, xcBlinky + 1, ycBlinky, xcPoursuite, ycPoursuite, 1);
      }  else choix = plusProche(xcBlinky - 1, ycBlinky, xcBlinky, ycBlinky - 1, xcBlinky + 1, ycBlinky, xcPoursuite, ycPoursuite, 1);
      if ((choix == 1) && (yBlinky % pasY == pasY - RY)) dirBlinky = GAUCHE;
      if ((choix == 3) && (yBlinky % pasY == pasY - RY)) dirBlinky = DROITE;
      break;
  }

  if (dirBlinky == DROITE) xBlinky++;
  if (dirBlinky == GAUCHE) xBlinky--;
  if (dirBlinky == BAS)    yBlinky++;
  if (dirBlinky == HAUT)   yBlinky--;

  // Le tunnel
  if (xBlinky >= 183) xBlinky = 1;
  if (xBlinky <= 0) xBlinky = 182;

  eBlinky++;
  if (eBlinky == 10) eBlinky = 0;
  
  effaceFantome(anc_xBlinky,anc_yBlinky);
  afficheBlinky();
}
