#include <LiquidCrystal.h>

LiquidCrystal lcd(9, 8, 5, 4, 3, 2); // Fill out pin declarations according to board pins the LCD is connected to

byte DINO_STAND_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001};
byte DINO_STAND_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte DINO_RIGHT_FOOT_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00001};
byte DINO_RIGHT_FOOT_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B00000};
byte DINO_LEFT_FOOT_PART_1[8] = {B00000, B00000, B00010, B00010, B00011, B00011, B00001, B00000};
byte DINO_LEFT_FOOT_PART_2[8] = {B00111, B00111, B00111, B00100, B11100, B11100, B11000, B01000};
byte TWO_BRANCHES_PART_1[8] = {B00000, B00100, B00100, B10100, B10100, B11100, B00100, B00100};
byte TWO_BRANCHES_PART_2[8] = {B00100, B00101, B00101, B10101, B11111, B00100, B00100, B00100};
byte BIRD_WINGS_PART1[8] = {B00001, B00001, B00001, B00001, B01001, B11111, B00000, B00000};
byte BIRD_WINGS_PART2[8] = {B00000, B10000, B11000, B11100, B11110, B11111, B00000, B00000};

// ... (previous code)

// Define variables
int dinoColumn1 = 1;
int dinoColumn2 = 2;
int dinoRow = 1;
unsigned long gameClock = 0; // Use the millis function instead of delay
int period = 100; // Period in milliseconds
int flag = 1;
int branchRow = 0;
int branchColumn = 13;
int period2 = 100;
unsigned long gameClock2 = 0;
int a = 0;
int b = 1;
int c = 2;
int d = 0;
unsigned long gameClock3 = 0;
int period3 = 100;
int points = 0;
int point2 = 0;
int randomNumber = 0;
int birdColumn = 13;
int e = 0;
int birdRow = 1;
int currentSignal = 0;
int previousSignal = 0;
int f = 13;
int acceleration = 1;
unsigned long gameClock4 = 0;
int period4 = 800;
int button = 11; // Pushbutton pin - for making the Dinosaur jump
int buzzer = 10; // Passive Buzzer pin - for sound effects

void setup() {
  // ... (previous setup code)
}

void loop() {
  if (millis() > gameClock + period) { // Delay for the dinosaur's feet
    gameClock = millis();
    if (flag == 1) {
      flag = 2;
    }
    else if (flag == 2) {
      flag = 1;
    }
  }

  if (millis() > gameClock2 + period2) { // Delay for the speed of branches
    gameClock2 = millis();

    branchColumn = branchColumn - 1;
    if (branchColumn < 0) {
      branchColumn = 13;
      period2 = period2 - acceleration; // Acceleration
      randomNumber = random(0, 3); // Randomly select the branch type each time it returns to column 13
    }

    f = branchColumn + 1;
    lcd.setCursor(f, 1);          // Clean below
    lcd.print(" ");

    f = branchColumn + 1;
    lcd.setCursor(f, 0);          // Clean above
    lcd.print(" ");

    lcd.setCursor(0, 1);           // Clean above
    lcd.print(" ");

    lcd.setCursor(0, 0);
    lcd.print(" ");

    a = 1;
  }

  if (d == 0) {
    if (flag == 1) {
      lcd.setCursor(dinoColumn1, dinoRow);
      lcd.write(byte(2));
      lcd.setCursor(dinoColumn2, dinoRow);
      lcd.write(byte(3));
    }
    if (flag == 2) {
      lcd.setCursor(dinoColumn1, dinoRow);
      lcd.write(byte(4));
      lcd.setCursor(dinoColumn2, dinoRow);
      lcd.write(byte(5));
    }
  }

  if (a == 1) {
    // ... (previous code)
    a = 0;
  }

  if (digitalRead(button) == HIGH && (branchColumn == 1 || branchColumn == 2 || birdColumn == 1 || birdColumn == 2) && branchRow == 0) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("GAME OVER");
    delay(2000);
    lcd.clear();
    branchColumn = 15;
    period2 = 100;
    points = 0;
    point2 = 0;
    period2 = 100;
  }

  if ((branchColumn == b || branchColumn == c) && branchRow == 1) {
    // ... (previous code)
  }

  if (digitalRead(button) == HIGH) {
    // ... (previous code)
  }
  else {
    // ... (previous code)
  }

  if (millis() > gameClock3 + period3) { // Delay for accumulated points
    gameClock3 = millis();
    // ... (previous code)
    currentSignal = digitalRead(button);
    if (currentSignal != previousSignal) {
      lcd.setCursor(1, 0);
      lcd.print("  ");
    }
    previousSignal = currentSignal;
  }
}
