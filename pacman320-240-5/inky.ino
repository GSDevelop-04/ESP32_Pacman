#define XCINDIF 1
#define YCINDIF 1
#define XCINMORT 14
#define YCINMORT 11

void afficheInky() {
  if ((phInky == CHASSE) || (phInky == DIFFUSION)) {
    if (dirInky == 1) {
      if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, ind1, ind1Width, ind1Height);
      if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, ind2, ind2Width, ind2Height);
    }
    if (dirInky == 2) {
      if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, ing1, ing1Width, ing1Height);
      if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, ing2, ing2Width, ing2Height);
    }
    if (dirInky == 3) {
      if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, inb1, inb1Width, inb1Height);
      if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, inb2, inb2Width, inb2Height);
    }
    if (dirInky == 4) {
      if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, inh1, inh1Width, inh1Height);
      if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, inh2, inh2Width, inh2Height);
    }
  }
  if (phInky == PEUR) {
    if (tps < peurInky - TPSCLIGNO) {
      if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, peur1, peur1Width, peur1Height);
      if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, peur2, peur2Width, peur2Height);
    } else {
      if ((tps / 500) % 2 == 0) { // 1/2 secondes paires en bleu
        if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, peur3, peur3Width, peur3Height);
        if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, peur4, peur4Width, peur4Height);
      } else {    // 1/2 secondes impaires en blanc
        if (eInky / 5 == 0)  tft.drawRGBBitmap(xInky + DX, yInky + DY, peur1, peur1Width, peur1Height);
        if (eInky / 5 == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, peur2, peur2Width, peur2Height);
      }
    }
  }
  if (phInky == MORT) {
    if (dirInky == 1)  tft.drawRGBBitmap(xInky + DX, yInky + DY, oeil1, oeil1Width, oeil1Height);
    if (dirInky == 2)  tft.drawRGBBitmap(xInky + DX, yInky + DY, oeil2, oeil2Width, oeil2Height);
    if (dirInky == 3)  tft.drawRGBBitmap(xInky + DX, yInky + DY, oeil3, oeil3Width, oeil3Height);
    if (dirInky == 4)  tft.drawRGBBitmap(xInky + DX, yInky + DY, oeil4, oeil4Width, oeil4Height);
  }

  anc_xInky = xInky;
  anc_yInky = yInky;
}

void gestionInky() {
  // case de pacman
  byte xcPacman = xCase(xPacman);
  byte ycPacman = yCase(yPacman);
  // case de Inky
  byte xcInky = xCase(xInky);
  byte ycInky = yCase(yInky);

  int dh, db, dd, dg;
  byte choix;

  int xcPoursuite = xcPacman;
  int ycPoursuite = ycPacman;


  if (((phInky == CHASSE) || (phInky == DIFFUSION)) && ((xcInky == xcPacman) && (ycInky == ycPacman))) { // c'est la fin !
    nbVies--;
    affiche_plateau();
    debutJeu();
  }

  if ((tps > peurInky) && (phInky != MORT)) {
    phInky = CHASSE;
    perBlinky = PERNORMALE;
  } else {
    if ((xcInky == xcPacman) && (ycInky == ycPacman) && (phInky != MORT)) {
      phInky = MORT;
      perInky = PERMORT; // retour rapide;
      tft.setCursor((xcInky - 1)*pasX + DX, ycInky * pasY + DY);
      tft.println(bonus);
      bonus = bonus * 2;
      delay(700);
      effaceBonus(xcInky - 1, ycInky);
      peurInky = tps;
    }
  }

  if ((phInky == CHASSE) || (phInky == DIFFUSION)) {
    if (phase == CHASSE) {
      xcPoursuite = xcPacman;
      ycPoursuite = ycPacman;
      if (dirPacman == 1) xcPoursuite = xcPacman + 4;
      if (dirPacman == 2) xcPoursuite = xcPacman - 4;
      if (dirPacman == 3) ycPoursuite = ycPacman + 4;
      if (dirPacman == 4) ycPoursuite = ycPacman - 4;


    }

    if (phase == DIFFUSION) {
      xcPoursuite = XCINDIF;
      ycPoursuite = YCINDIF;

    }
  }
  if (phInky == MORT) {
    xcPoursuite = XCINMORT;
    ycPoursuite = YCINMORT;
    if ((xcInky == XCINMORT) && (ycInky == YCINMORT)) {
      phInky  = CHASSE;
      perInky = PERNORMALE;
    }
  }


  switch (dirInky) {
    case DROITE:
      if (phInky == PEUR) {
        choix =       alea(xcInky, ycInky - 1, xcInky + 1, ycInky, xcInky, ycInky + 1, xcPoursuite, ycPoursuite, 0);
      } else choix = plusProche(xcInky, ycInky - 1, xcInky + 1, ycInky, xcInky, ycInky + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xInky % pasX == pasX - RX)) dirInky = HAUT;
      if ((choix == 3) && (xInky % pasX == pasX - RX)) dirInky = BAS;
      break;

    case GAUCHE:
      if (phInky == PEUR) {
        choix =       alea(xcInky, ycInky - 1, xcInky - 1, ycInky, xcInky, ycInky + 1, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcInky, ycInky - 1, xcInky - 1, ycInky, xcInky, ycInky + 1, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (xInky % pasX == pasX - RX)) dirInky = HAUT;
      if ((choix == 3) && (xInky % pasX == pasX - RX)) dirInky = BAS;
      break;

    case BAS:
      if (phInky == PEUR) {
        choix =       alea(xcInky - 1, ycInky, xcInky, ycInky + 1, xcInky + 1, ycInky, xcPoursuite, ycPoursuite, 0);
      }  else choix = plusProche(xcInky - 1, ycInky, xcInky, ycInky + 1, xcInky + 1, ycInky, xcPoursuite, ycPoursuite, 0);
      if ((choix == 1) && (yInky % pasY == pasY - RY)) dirInky = GAUCHE;
      if ((choix == 3) && (yInky % pasY == pasY - RY)) dirInky = DROITE;
      break;

    case HAUT:
      if (phInky == PEUR) {
        choix =       alea(xcInky - 1, ycInky, xcInky, ycInky - 1, xcInky + 1, ycInky, xcPoursuite, ycPoursuite, 1);
      }  else choix = plusProche(xcInky - 1, ycInky, xcInky, ycInky - 1, xcInky + 1, ycInky, xcPoursuite, ycPoursuite, 1);
      if ((choix == 1) && (yInky % pasY == pasY - RY)) dirInky = GAUCHE;
      if ((choix == 3) && (yInky % pasY == pasY - RY)) dirInky = DROITE;
      break;
  }

  if (dirInky == DROITE) xInky++;
  if (dirInky == GAUCHE) xInky--;
  if (dirInky == BAS)    yInky++;
  if (dirInky == HAUT)   yInky--;

  // Le tunnel
  if (xInky >= 183) xInky = 1;
  if (xInky <= 0) xInky = 182;

  eInky++;
  if (eInky == 10) eInky = 0;

  effaceFantome(anc_xInky, anc_yInky);
  afficheInky();

}
