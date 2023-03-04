void incScore(int points) {
  score += points;
  String scoreTxt = String(score);
  //tft.setTextSize(1);
  tft.setCursor(50 - scoreTxt.length() * 7, 4);
  tft.fillRect(20, 4, 32, 8, 0);
  tft.println(scoreTxt);
}

void superPil() {
  phBlinky = PEUR;
  peurBlinky = tps + TPSPEUR;
  perBlinky = PERSUPER;
  dirBlinky = inverseDir(dirBlinky);
  
  phPinky = PEUR;
  peurPinky = tps + TPSPEUR;
  perPinky = PERSUPER;
  dirPinky = inverseDir(dirPinky);
  
  phClyde = PEUR;
  peurClyde = tps + TPSPEUR;
  perClyde = PERSUPER;
  dirClyde = inverseDir(dirClyde);
  
  bonus = 200;
  incScore(50);
  pil++;
}

void affichePacman() {
  if (dirPacman <= DROITE) {
    if (ePacman / 3 == 0)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcf, pcfWidth, pcfHeight);
    if ((ePacman / 3 == 1) or (ePacman / 3 == 3)) tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcdm, pcdmWidth, pcdmHeight);
    if (ePacman / 3 == 2)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcdo, pcdoWidth, pcdoHeight);
  }
  if (dirPacman == GAUCHE) {
    if (ePacman / 3 == 0)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcf, pcfWidth, pcfHeight);
    if ((ePacman / 3 == 1) or (ePacman / 3 == 3)) tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcgm, pcgmWidth, pcgmHeight);
    if (ePacman / 3 == 2)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcgo, pcgoWidth, pcgoHeight);
  }

  if (dirPacman == BAS) {
    if (ePacman / 3 == 0)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcf, pcfWidth, pcfHeight);
    if ((ePacman / 3 == 1) or (ePacman / 3 == 3)) tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcbm, pcbmWidth, pcbmHeight);
    if (ePacman / 3 == 2)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcbo, pcboWidth, pcboHeight);
  }

  if (dirPacman == HAUT) {
    if (ePacman / 3 == 0)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcf, pcfWidth, pcfHeight);
    if ((ePacman / 3 == 1) or (ePacman / 3 == 3)) tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pchm, pchmWidth, pchmHeight);
    if (ePacman / 3 == 2)tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcho, pchoWidth, pchoHeight);
  }
}
void gestionPacman() {
  int joyX = analogRead(pinJoyDG);
  int joyY = analogRead(pinJoyHB);
  int joySW = digitalRead(pinJoySW);

  //Serial.print(yPacman % pasY); Serial.print("\t"); if (libre(xcPacman + 1, yPacman,0)) Serial.print("Libre");  Serial.print("\t"); Serial.print(yPacman % pasY); Serial.prin("\t");
  if ((joyX > 3000) && (yPacman % pasY == pasY - RY) && (libre(xCase(xPacman) + 1, yCase(yPacman), 0))) dirPacman = DROITE;
  if ((joyX < 1000) && (yPacman % pasY == pasY - RY) && (libre(xCase(xPacman - 1), yCase(yPacman), 0))) dirPacman = GAUCHE;
  if ((joyY > 3000) && (xPacman % pasX == pasX - RX) && (libre(xCase(xPacman), yCase(yPacman) + 1, 0))) dirPacman = BAS;
  if ((joyY < 1000) && (xPacman % pasX == pasX - RX) && (libre(xCase(xPacman), yCase(yPacman - 1), 0))) dirPacman = HAUT;

  if ((dirPacman == DROITE) && (libre(xCase(xPacman) + 1, yCase(yPacman), 0))) xPacman++;
  if ((dirPacman == GAUCHE) && (libre(xCase(xPacman - 1), yCase(yPacman), 0))) xPacman--;
  if ((dirPacman == BAS)    && (libre(xCase(xPacman), yCase(yPacman ) + 1, 0))) yPacman++;
  if ((dirPacman == HAUT)   && (libre(xCase(xPacman), yCase(yPacman - 1), 0))) yPacman--;

  ePacman++;
  if (xPacman >= 183) xPacman = 1;
  if (xPacman <= 0) xPacman = 182;

  if (ePacman == 12) ePacman = 0;

  tft.drawRGBBitmap(anc_xPacman + DX, anc_yPacman + DY, effac, effacWidth, effacHeight);
  affichePacman();

  if (plateau[mem(xCase(xPacman), yCase(yPacman))] == GUM) {
    plateau[mem(xCase(xPacman), yCase(yPacman))] = 99;
    incScore(10);
    pil++;
  }
  if ((plateau[mem(xCase(xPacman) + 1, yCase(yPacman))] == GUM) && (xPacman % pasX > 2)) {
    plateau[mem(xCase(xPacman) + 1, yCase(yPacman))] = 99;
    incScore(10);
    pil++;
  }
  if ((plateau[mem(xCase(xPacman), yCase(yPacman) + 1)] == GUM) && (yPacman % pasY > 3)) {
    plateau[mem(xCase(xPacman), yCase(yPacman) + 1)] = 99;
    incScore(10);
    pil++;
  }

  if (plateau[mem(xCase(xPacman), yCase(yPacman))] == SUPERGUM) {
    plateau[mem(xCase(xPacman), yCase(yPacman))] = 99;
    superPil();
  }
  if ((plateau[mem(xCase(xPacman) + 1, yCase(yPacman))] == SUPERGUM) && (xPacman % pasX > 2)) {
    plateau[mem(xCase(xPacman) + 1, yCase(yPacman))] = 99;
    superPil();
  }
  if ((plateau[mem(xCase(xPacman), yCase(yPacman) + 1)] == SUPERGUM) && (yPacman % pasY > 3)) {
    plateau[mem(xCase(xPacman), yCase(yPacman) + 1)] = 99;
    superPil();
  }
  anc_xPacman = xPacman;
  anc_yPacman = yPacman;
}
