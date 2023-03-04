int mem(int xc, int yc) {
  return (yc * 28 + xc);
}

bool libre(int xc, int yc, byte dir) {
  if ((plateau[mem(xc,yc)]==2)&&(dir==1)||(plateau[mem(xc, yc)] > 10)) return true; else return false;
}

int xCase(int x) {
  return (x + RX) / pasX;
}

int yCase(int y) {
  return (y + RY) / pasY;
}

byte inverseDir(byte dir) {
    if (dir == 1) return 2;
    if (dir == 2) return 1;
    if (dir == 3) return 4;
    if (dir == 4) return 3;
}

void effaceFantome(int x, int y) {
  tft.drawRGBBitmap(x + DX, y + DY, effac, effacWidth, effacHeight);
  int xc=xCase(x);
  int yc=yCase(y);
  if (plateau[mem(xc, yc)] == 16) tft.drawRGBBitmap(pasX * xc + DX, pasY * yc + DY, PT, PTWidth, PTHeight);
  if (plateau[mem(xc + 1, yc)] == 16) tft.drawRGBBitmap(pasX * (xc+1) + DX, pasY * yc + DY, PT, PTWidth, PTHeight);   
  if (plateau[mem(xc, yc + 1)] == 16) tft.drawRGBBitmap(pasX * xc + DX, pasY * (yc+1) + DY, PT, PTWidth, PTHeight);

  if (plateau[mem(xc, yc)] == 17) tft.drawRGBBitmap(pasX * xc + DX, pasY * yc + DY, PIL, PILWidth, PILHeight);
  if (plateau[mem(xc+1, yc)] == 17) tft.drawRGBBitmap(pasX * (xc+1) + DX, pasY * yc + DY, PIL, PILWidth, PILHeight);   
  if (plateau[mem(xc, yc+1)] == 17) tft.drawRGBBitmap(pasX * xc + DX, pasY * (yc+1) + DY, PIL, PILWidth, PILHeight);

  // porte
  if (plateau[mem(xc, yc+1)] == 2) {
   Serial.println("La porte !");
   afficheCase(12,12);
   afficheCase(13,12);
   afficheCase(14,12);
   afficheCase(15,12);

  }
}

void effaceBonus(int xc, int yc){ 
   afficheCase(xc,yc);
   afficheCase(xc+1,yc);
   afficheCase(xc+2,yc);
}


byte alea(int x1, int y1, int x2, int y2, int x3, int y3, int xref, int yref,byte dir) {
  byte choix = 0; //pas de choix initial
  if (!libre(x1, y1, dir)) { // le choix se fait entre 2 ou 3
    if (!libre(x2, y2, dir)) choix = 3; //pas de cul de sac donc si 1 et 2 pas libres 3 est libre
    if (!libre(x3, y3, dir)) choix = 2; //idem
    if (libre(x2, y2, dir) && libre(x3, y3, dir)) {
      if (random(2)== 0) choix = 2; else choix = 3;
    }
  }
  if (!libre(x2, y2, dir)) { // le choix se fait entre 1 ou 3
    if (!libre(x1, y1, dir)) choix = 3;
    if (!libre(x3, y3, dir)) choix = 1;
    if (libre(x1, y1, dir) && libre(x3, y3, dir)) {
      if (random(2) == 0) choix = 1; else choix = 3;
    }
  }
  if (!libre(x3, y3, dir)) { // le choix se fait entre 1 ou 2
    if (!libre(x1, y1, dir)) choix = 2;
    if (!libre(x2, y2, dir)) choix = 1;
    if (libre(x1, y1, dir) && libre(x2, y2, dir)) {
      if (random(2) == 0) choix = 1; else choix = 2;
    }
  }
  if (libre(x1, y1, dir) && libre(x2, y2, dir) && libre(x3, y3, dir)) {
    choix=random(1,4);
  }
  return choix;
}

byte plusProche(int x1, int y1, int x2, int y2, int x3, int y3, int xref, int yref, byte dir) {
  byte choix = 0; //pas de choix initial
  // calcul des trois normes

  int l1 = pow(x1 - xref, 2) + pow(y1 - yref, 2);
  int l2 = pow(x2 - xref, 2) + pow(y2 - yref, 2);
  int l3 = pow(x3 - xref, 2) + pow(y3 - yref, 2);

  // choix
  if (!libre(x1, y1, dir)) { // le choix se fait entre 2 ou 3
    if (!libre(x2, y2, dir)) choix = 3; //pas de cul de sac donc si 1 et 2 pas libres 3 est libre
    if (!libre(x3, y3, dir)) choix = 2; //idem
    if (libre(x2, y2, dir) && libre(x3, y3, dir)) {
      if (l2 < l3) choix = 2; else choix = 3;
    }
  }
  if (!libre(x2, y2, dir)) { // le choix se fait entre 1 ou 3
    if (!libre(x1, y1, dir)) choix = 3;
    if (!libre(x3, y3, dir)) choix = 1;
    if (libre(x1, y1, dir) && libre(x3, y3, dir)) {
      if (l1 < l3) choix = 1; else choix = 3;
    }
  }
  if (!libre(x3, y3, dir)) { // le choix se fait entre 1 ou 2
    if (!libre(x1, y1, dir)) choix = 2;
    if (!libre(x2, y2, dir)) choix = 1;
    if (libre(x1, y1, dir) && libre(x2, y2, dir)) {
      if (l1 < l2) choix = 1; else choix = 2;
    }
  }
  if (libre(x1, y1, dir) && libre(x2, y2, dir) && libre(x3, y3, dir)) {
    if ((l1 <= l2) && (l1 <= l3)) choix = 1;
    if ((l2 <= l1) && (l2 <= l3)) choix = 2;
    if ((l3 <= l1) && (l3 <= l2)) choix = 3;
  }
  return choix;
}
