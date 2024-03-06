#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
#include <JPEGDecoder.h>
#include <Arduino.h>

TFT_eSPI tft = TFT_eSPI();

const int dacPin = 25; // DAC pin
const int buttonPin = 22; // Pin for the push button
volatile bool flag = false; // Flag to be toggled, marked as volatile for use in interrupts

uint16_t counter =0,qs=0,wc=0;
void IRAM_ATTR buttonISR() {
  flag = !flag;
  Serial.println("Interrupt worked.");
  counter=0;
  qs=0;
  wc=0;
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);

  // Initialize TFT screen
  tft.begin();
  tft.setRotation(1); // Portrait orientation

  // Initialize SD card
  if (!SD.begin()) {
    Serial.println("SD Card initialization failed!");
    return;
  }
  Serial.println("SD Card initialized successfully!");
  
    drawSdJpeg("/welcomeLM.jpg", 0, 0);
    playSound("/welcomeLM.wav");
    counter++;
  
}


void loop() {
  // Check for touch input
  uint16_t x, y;
  
  if (tft.getTouch(&x, &y) && flag==0) {
    // Redraw the JPEG image and play the sound
    if(counter==0){
      drawSdJpeg("/welcomeLM.jpg", 0, 0);
      playSound("/welcomeLM.wav");
    }
    counter++;
    if(counter%8==2){
      drawSdJpeg("/480x320/Roster480x320.jpg", 0, 0);
      playSound("/sound/Roster.wav");
      playSound("/LM_record/roster_.wav");
      delay(500); // Delay to avoid repeated touches
    }else if(counter%8==3){
      drawSdJpeg("/480x320/cat480x320.jpg", 0, 0);
      playSound("/sound/cat.wav");
      playSound("/LM_record/cat_.wav");
      delay(500); // Delay to avoid repeated touches
    }
    else if(counter%8==4){
      drawSdJpeg("/480x320/duck480x320.jpg", 0, 0);
      playSound("/sound/duck.wav");
      playSound("/LM_record/duck_.wav");
      delay(500); // Delay to avoid repeated touches
    }
    else if(counter%8==5){
      drawSdJpeg("/480x320/goat480x320.jpg", 0, 0);
      playSound("/sound/goat.wav");
      playSound("/LM_record/goat_.wav");
      delay(500); // Delay to avoid repeated touches
    }
    else if(counter%8==6){
      drawSdJpeg("/480x320/tiger480x320.jpg", 0, 0);
      playSound("/sound/tiger.wav");
      playSound("/LM_record/tiger_.wav");
      delay(500); // Delay to avoid repeated touches
    }
    else if(counter%8==7){
      drawSdJpeg("/480x320/piegon480x320.jpg", 0, 0);
      playSound("/sound/pigeon.wav");
      playSound("/LM_record/crow_.wav");
      delay(500); // Delay to avoid repeated touches
    }
    else if(counter%8==0){
      drawSdJpeg("/480x320/magpie480x320.jpg", 0, 0);
      playSound("/sound/magpie.wav");
      playSound("/LM_record/magpie_.wav");
      delay(500); // Delay to avoid repeated touches
    }   
    else {
      drawSdJpeg("/480x320/cow480x320.jpg", 0, 0);
      playSound("/sound/cow.wav");
      playSound("/LM_record/cow_.wav");
      delay(500); // Delay to avoid repeated touches
    }
  }
  if(flag==1){
  uint16_t ans=0;
  if (tft.getTouch(&x, &y)) {
    if(counter==0 && wc==0){
      drawSdJpeg("/welcomeEM.jpg", 0, 0);
      playSound("/welcomeEM.wav");
      wc=1;
    }
    // Redraw the JPEG image and play the sound
    if(counter%8==0){
      drawSdJpeg("/240x160/Roster240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/cat240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/piegon240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/tiger240x160.jpg", 241, 161);
      
      if(qs==1 ){
        if(x>=241 && y>=161) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/cat.wav");
        playSound("/EM_record/cat_f.wav");
        qs=1;
      }
      delay(100); // Delay to avoid repeated touches
    }
    if(counter%8==1){
      drawSdJpeg("/240x160/piegon240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/cow240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/duck240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/magpie240x160.jpg", 241, 161);

      if(qs==1){
        if(x<=240 && y<=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/duck.wav");
        playSound("/EM_record/duck_f.wav");
        qs=1;
      }
      delay(100); // Delay to avoid repeated touches
    }
    if(counter%8==2){
      drawSdJpeg("/240x160/cow240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/cat240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/roster240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/goat240x160.jpg", 241, 161);
      
      if(qs==1){
        if(x>=240 && y<=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/goat.wav");
        playSound("/EM_record/goat_f.wav");
        qs=1;
      }
      delay(100);
    }
    if(counter%8==3) {
      drawSdJpeg("/240x160/tiger240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/cow240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/magpie240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/cat240x160.jpg", 241, 161);

      if(qs==1){
        if(x<=240 && y>=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/tiger.wav");
        playSound("/EM_record/tiger_f.wav");
        qs=1;
      }
      delay(100);
    }
    if(counter%8==4) {
      drawSdJpeg("/240x160/duck240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/magpie240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/piegon240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/Roster240x160.jpg", 241, 161);

      if(qs==1){
        if(x>=240 && y>=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/magpie.wav");
        playSound("/EM_record/magpie_f.wav");
        qs=1;
      }
      delay(100);
    }
    if(counter%8==5) {
      drawSdJpeg("/240x160/cow240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/tiger240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/piegon240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/goat240x160.jpg", 241, 161);

      if(qs==1){
        if(x<=240 && y<=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/pigeon.wav");
        playSound("/EM_record/crow_f.wav");
        qs=1;
      }
      delay(100);
    }
    if(counter%8==6) {
      drawSdJpeg("/240x160/Roster240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/duck240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/magpie240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/cat240x160.jpg", 241, 161);

      if(qs==1){
        if(x<=240 && y>=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/Roster.wav");
        playSound("/EM_record/roster_f.wav");
        qs=1;
      }
      delay(100);
    }
    if(counter%8==7) {
      drawSdJpeg("/240x160/piegon240x160.jpg", 0, 0);
      drawSdJpeg("/240x160/magpie240x160.jpg", 241, 0);
      drawSdJpeg("/240x160/cat240x160.jpg", 0, 161);
      drawSdJpeg("/240x160/cow240x160.jpg", 241, 161);

      if(qs==1){
        if(x>=240 && y<=160) {
          playSound("/EM_record/correct.wav");
          qs=0;
          counter++;
        }
        else{
          playSound("/EM_record/wrong.wav");
        }
      }
      else {
        playSound("/sound/cow.wav");
        playSound("/EM_record/cow_f.wav");
        qs=1;
      }
      delay(100);
    }
  }
  }
}


void drawSdJpeg(const char *filename, int xpos, int ypos) {
  File jpegFile = SD.open(filename, FILE_READ);
  if (!jpegFile) {
    Serial.print("Error opening JPEG file: ");
    Serial.println(filename);
    return;
  }

  bool decoded = JpegDec.decodeSdFile(jpegFile);
  if (decoded) {
    jpegInfo();
    jpegRender(xpos, ypos);
  } else {
    Serial.println("JPEG file format not supported!");
  }
}

void jpegRender(int xpos, int ypos) {
  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;

  bool swapBytes = tft.getSwapBytes();
  tft.setSwapBytes(true);

  while (JpegDec.read()) {
    pImg = JpegDec.pImage;
    tft.pushImage(xpos + JpegDec.MCUx * mcu_w, ypos + JpegDec.MCUy * mcu_h, mcu_w, mcu_h, pImg);
  }

  tft.setSwapBytes(swapBytes);
}

void jpegInfo() {
  Serial.println("JPEG image info");
  Serial.println("====================");
  Serial.print("Width: ");
  Serial.println(JpegDec.width);
  Serial.print("Height: ");
  Serial.println(JpegDec.height);
  Serial.println("====================");
}

void playSound(const char *filename) {
  // Open the WAV file
  File audioFile = SD.open(filename, FILE_READ);
  if (!audioFile) {
    Serial.println("Error opening audio file!");
    return;
  }

  // Play audio
  while (audioFile.available()) {
    uint16_t val = audioFile.read(); // Read sample
    dacWrite(dacPin, val);           // Output sample to DAC
  }
  audioFile.close();
}
