void init_io() {
  pinMode(pinJoyAlim, OUTPUT);
  pinMode(pinJoyHB, INPUT);
  pinMode(pinJoyDG, INPUT);
  pinMode(pinJoySW, INPUT_PULLUP);
  digitalWrite(pinJoyAlim, HIGH);
}

void afficheVie() {
  tft.fillRect(10, 31 * HHeight + DY, 4 * 1.2 * pcdoWidth, pcdoHeight, 0);
  for (int n = 0; n < nbVies; n++) tft.drawRGBBitmap(DX + 1.2 * n * pcdoWidth, 31 * VHeight + DY, pcdo, pcdoWidth, pcdoHeight);

}

void debutJeu() {
  afficheVie();
  // le Pacman
  xPacman = XDEBUTPA * pasX - RX,
  anc_xPacman = xPacman;
  yPacman = YDEBUTPA * pasY - RY,
  anc_yPacman = yPacman;
  ePacman = 0;
  dirPacman = 0;
  perPacman = PERNORMALE;
  tft.drawRGBBitmap(xPacman + DX, yPacman + DY, pcdm, pcdmWidth, pcdmHeight);

  // la phase commune à tous les fantomes
  phase = DIFFUSION;

  // Blinky
  xBlinky = XDEBUTBL * pasX - RX,
  anc_xBlinky = xBlinky;
  yBlinky = YDEBUTBL * pasY - RY,
  anc_yBlinky = yBlinky;
  eBlinky = 0;
  dirBlinky = 4;
  phBlinky = DIFFUSION;
  perBlinky = PERNORMALE;
  tft.drawRGBBitmap(xBlinky + DX, yBlinky + DY, bld1, bld1Width, bld1Height);
  
  // Pinky
  xPinky = XDEBUTPI * pasX - RX,
  anc_xPinky = xPinky;
  yPinky = YDEBUTPI * pasY - RY,
  anc_yPinky = yPinky;
  ePinky = 0;
  dirPinky = 4;
  phPinky = DIFFUSION;
  perPinky = PERNORMALE;
  tft.drawRGBBitmap(xPinky + DX, yPinky + DY, pih1, pih1Width, pih1Height);

  // Clyde
  xClyde = XDEBUTCL * pasX - RX,
  anc_xClyde = xClyde;
  yClyde = YDEBUTCL * pasY - RY,
  anc_yClyde = yClyde;
  eClyde = 0;
  dirClyde = 4;
  phClyde = DIFFUSION;
  perClyde = PERNORMALE;
  tft.drawRGBBitmap(xClyde + DX, yClyde + DY, clh1, clh1Width, clh1Height);


  // INKY
  xInky = XDEBUTIN * pasX - RX,
  anc_xInky = xInky;
  yInky = YDEBUTIN * pasY - RY,
  anc_yInky = yInky;
  eInky = 0;
  dirInky = 4;
  phInky = DIFFUSION;
  perInky = PERNORMALE;
  tft.drawRGBBitmap(xInky + DX, yInky + DY, inh1, inh1Width, inh1Height);
  
  
  tft.setCursor(12 * pasX + DX, 17 * pasY + DY);
  tft.println("Ready !");




  while (digitalRead(pinJoySW)) {
  }
  tft.fillRect(12 * pasX + DX, 17 * pasY + DY, 5 * 8, 8, 0);


  tpsPacman = millis() + perPacman;
  tpsBlinky = millis() + perBlinky;
  tpsPinky = millis() + perPinky;
  tpsDifCha = millis() + perDiffusion;
}
void afficheCase(int x, int y) {
  switch (plateau[x + y * 28]) {

    case 1:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, H, HWidth, HHeight);
      break;

    case 2:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, HR, HRWidth, HRHeight);
      break;

    case 3:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, V, VWidth, VHeight);
      break;

    case 7:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, BD, BDWidth, BDHeight);
      break;

    case 8:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, GB, GBWidth, GBHeight);
      break;

    case 9:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, HD, HDWidth, HDHeight);
      break;

    case 10:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, HG, HGWidth, HGHeight);
      break;

    case 16:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, PT, PTWidth, PTHeight);
      break;

    case 17:
      tft.drawRGBBitmap(x * pasX + DX, y * pasY + DY, PIL, PILWidth, PILHeight);
      break;
  }
}
void init_plateau() {
  tft.fillRect(DX, DY , HWidth * 28, HHeight * 31, 0);
  for (byte x = 0; x < 14; x++) {
    for (byte y = 0; y < 31; y++) {

      switch (demiPlateau[x + y * 14]) {
        case 0:
          plateau[x + y * 28] = 15;
          plateau[27 - x + y * 28] = 15;
          break;

        case 1:
          plateau[x + y * 28] = 1;
          plateau[27 - x + y * 28] = 1;
          break;

        case 2:
          plateau[x + y * 28] = 2;
          plateau[27 - x + y * 28] = 2;
          break;


        case 3:
          plateau[x + y * 28] = 3;
          plateau[27 - x + y * 28] = 3;
          break;

        case 7:
          plateau[x + y * 28] = 7;
          plateau[27 - x + y * 28] = 8;
          break;

        case 8:
          plateau[x + y * 28] = 8;
          plateau[27 - x + y * 28] = 7;
          break;

        case 9:
          plateau[x + y * 28] = 9;
          plateau[27 - x + y * 28] = 10;
          break;

        case 10:
          plateau[x + y * 28] = 10;
          plateau[27 - x + y * 28] = 9;
          break;

        case 16:
          plateau[x + y * 28] = 16;
          plateau[27 - x + y * 28] = 16;
          break;

        case 17:
          plateau[x + y * 28] = 17;
          plateau[27 - x + y * 28] = 17;
          break;
      }

    }
  }
}
void affiche_plateau() {
  tft.fillRect(DX, DY , HWidth * 28, HHeight * 31, 0);
  for (byte x = 0; x < 28; x++) {
    for (byte y = 0; y < 31; y++) {

      afficheCase(x,y);

    }
  }
}
