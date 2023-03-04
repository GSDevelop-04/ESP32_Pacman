#define XCCLDIF 26
#define YCCLDIF 31
#define XCCLMORT 14
#define YCCLMORT 11

void afficheClyde() {
  if ((phClyde == CHASSE) || (phClyde == DIFFUSION)) {
    if (dirClyde == 1) {
      if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, cld1, cld1Width, cld1Height);
      if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, cld2, cld2Width, cld2Height);
    }
    if (dirClyde == 2) {
      if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clg1, clg1Width, clg1Height);
      if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clg2, clg2Width, clg2Height);
    }
    if (dirClyde == 3) {
      if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clb1, clb1Width, clb1Height);
      if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clb2, clb2Width, clb2Height);
    }
    if (dirClyde == 4) {
      if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clh1, clh1Width, clh1Height);
      if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clh2, clh2Width, clh2Height);
    }
  }
  if (phClyde == PEUR) {
    if (tps < peurClyde - TPSCLIGNO) {
      if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, peur1, peur1Width, peur1Height);
      if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, peur2, peur2Width, peur2Height);
    } else {
      if ((tps / 500) % 2 == 0) { // 1/2 secondes paires en bleu
        if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, peur3, peur3Width, peur3Height);
        if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, peur4, peur4Width, peur4Height);
      } else {    // 1/2 secondes impaires en blanc
        if (eClyde / 5 == 0)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, peur1, peur1Width, peur1Height);
        if (eClyde / 5 == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, peur2, peur2Width, peur2Height);
      }
    }
  }
  if (phClyde == MORT) {
    if (dirClyde == 1)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, oeil1, oeil1Width, oeil1Height);
    if (dirClyde == 2)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, oeil2, oeil2Width, oeil2Height);
    if (dirClyde == 3)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, oeil3, oeil3Width, oeil3Height);
    if (dirClyde == 4)  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, oeil4, oeil4Width, oeil4Height);
  }

  anc_xClyde = xClyde;
  anc_yClyde = yClyde;
}


void gestionClyde() {

  // case de pacman
  byte xcPacman = xCase(xPacman);
  byte ycPacman = yCase(yPacman);
  // case de Clyde
  byte xcClyde = xCase(xClyde);
  byte ycClyde = yCase(yClyde);

  int dh, db, dd, dg;
  byte choix;

  int xcPoursuite = xcPacman;
  int ycPoursuite = ycPacman;

  if (((phClyde == CHASSE) || (phClyde == DIFFUSION)) && ((xcClyde == xcPacman) && (ycClyde == ycPacman))) { // c'est la fin !
    Serial.println(phClyde);
    nbVies--;
    affiche_plateau();
    debutJeu();
  }

  if ((tps > peurClyde) && (phClyde != MORT)) {
    phClyde = CHASSE;
    perClyde = PERNORMALE;
  } else {
    if ((xcClyde == xcPacman) && (ycClyde == ycPacman) && (phClyde != MORT)) {
      phClyde = MORT;
      perClyde = PERMORT; // retour rapide;
      score += bonus;
      tft.setCursor((xcClyde - 1)*pasX + DX, ycClyde * pasY + DY);
      tft.println(bonus);
      bonus = bonus * 2;
      delay(700);
      effaceBonus(xcClyde - 1, ycClyde);
      peurClyde = tps;
    }
  }

  if ((phClyde == CHASSE) || (phClyde == DIFFUSION)) {
    if (phase == CHASSE) {
      xcPoursuite = xcPacman;
      ycPoursuite = ycPacman;
    }

    if (phase == DIFFUSION) {
      xcPoursuite = XCCLDIF;
      ycPoursuite = YCCLDIF;

    }
  }
  if (phClyde == MORT) {
    xcPoursuite = XCCLMORT;
    ycPoursuite = YCCLMORT;
    if ((xcClyde == XCCLMORT) && (ycClyde == YCCLMORT)) {
      phClyde  = CHASSE;
      perClyde = PERNORMALE;
    }
  }


  switch (dirClyde) {
    case DROITE:
      if ((phClyde == PEUR) || (abs(xcClyde - xcPacman) + abs(ycClyde - ycPacman)) > 8) {
        choix =       alea(xcClyde, ycClyde - 1, xcClyde + 1, ycClyde, xcClyde, ycClyde + 1, xcPoursuite, ycPoursuite, 0);
      } else choix = plusProche(xcClyde, ycClyde - 1, xcClyde + 1, ycClyde, xcClyde, ycClyde + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xClyde % pasX == pasX - RX)) dirClyde = HAUT;
      if ((choix == 3) && (xClyde % pasX == pasX - RX)) dirClyde = BAS;
      break;

    case GAUCHE:
      if ((phClyde == PEUR) || (abs(xcClyde - xcPacman) + abs(ycClyde - ycPacman)) > 8) {
        choix =       alea(xcClyde, ycClyde - 1, xcClyde - 1, ycClyde, xcClyde, ycClyde + 1, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcClyde, ycClyde - 1, xcClyde - 1, ycClyde, xcClyde, ycClyde + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xClyde % pasX == pasX - RX)) dirClyde = HAUT;
      if ((choix == 3) && (xClyde % pasX == pasX - RX)) dirClyde = BAS;
      break;

    case BAS:
      if ((phClyde == PEUR) || (abs(xcClyde - xcPacman) + abs(ycClyde - ycPacman)) > 8) {
        choix =       alea(xcClyde - 1, ycClyde, xcClyde, ycClyde + 1, xcClyde + 1, ycClyde, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcClyde - 1, ycClyde, xcClyde, ycClyde + 1, xcClyde + 1, ycClyde, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (yClyde % pasY == pasY - RY)) dirClyde = GAUCHE;
      if ((choix == 3) && (yClyde % pasY == pasY - RY)) dirClyde = DROITE;
      break;

    case HAUT:
      if ((phClyde == PEUR) || (abs(xcClyde - xcPacman) + abs(ycClyde - ycPacman)) > 8) {
        choix =       alea(xcClyde - 1, ycClyde, xcClyde, ycClyde - 1, xcClyde + 1, ycClyde, xcPoursuite, ycPoursuite, 1);
      }  else choix = plusProche(xcClyde - 1, ycClyde, xcClyde, ycClyde - 1, xcClyde + 1, ycClyde, xcPoursuite, ycPoursuite, 1);
      if ((choix == 1) && (yClyde % pasY == pasY - RY)) dirClyde = GAUCHE;
      if ((choix == 3) && (yClyde % pasY == pasY - RY)) dirClyde = DROITE;
      break;
  }

  if (dirClyde == DROITE) xClyde++;
  if (dirClyde == GAUCHE) xClyde--;
  if (dirClyde == BAS)    yClyde++;
  if (dirClyde == HAUT)   yClyde--;

  // Le tunnel
  if (xClyde >= 183) xClyde = 1;
  if (xClyde <= 0) xClyde = 182;

  eClyde++;
  if (eClyde == 10) eClyde = 0;

  effaceFantome(anc_xClyde, anc_yClyde);
  afficheClyde();
}
