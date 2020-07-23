
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53//rf
#define RST_PIN 5

#include <Adafruit_Fingerprint.h>
#include <Servo.h>
#include <LiquidCrystal.h> // include the library code
//constants for the number of rows and columns in the LCD
const int numRows = 2;
const int numCols = 16;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 7, 4, 3, 2);

Servo myservo;
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key;
// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
#define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
//#include <SoftwareSerial.h>
//SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  //Serial.println("\n\nAdafruit finger detect test");
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522
  // set the data rate for the sensor serial port
  finger.begin(57600);
  myservo.attach(8);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.print("Fingersensor on");
    delay(1000);
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
     lcd.print("Fingersensor off");
    delay(1000);
    while (1) {
      delay(1);
    }
  }

  finger.getTemplateCount();
  //Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid RFID...");
  lcd.clear();
     lcd.print("Scan card pls");
    delay(1000);
  //Serial.println("scan rfid to begin");
  myservo.write(15);
}


void loop() {
  // put your main code here, to run repeatedly:

  String ab = reuid();
  switch (ab)
  {
    case "33516246" :
     int grace = 0;
    Serial.println("lets scan your finger Nurudeen");
    
    Serial.println("place finger on the scanner");
    delay(1000);
    lcd.clear();
     lcd.print("Scan Finger");
    delay(6000);
    int fing=-1;
    while ((grace < 2)&&(fing==-1)) {
      Serial.println("scanning...");
      lcd.clear();
     lcd.print("scanning...");
    delay(1000);
       fing = getFingerprintIDez();
      if ((fing != -1)) {
        Serial.println("access granted");
        lcd.clear();
     lcd.print("Access Granted");
    delay(1000);
        myservo.write(180);
        grace=5;
        delay(3000);
        Serial.println("Closing door");
        lcd.clear();
     lcd.print("Closing door");
    delay(10000);
        myservo.write(15);
        Serial.println("Waiting for valid RFID");
        lcd.clear();
     lcd.print("Scan Card");
    delay(1000);
       break; 
     case "335420146" :
        int grace = 0;
    Serial.println("lets scan your finger Wale");
    
    Serial.println("place finger on the scanner");
    delay(1000);
    lcd.clear();
     lcd.print("Scan Finger");
    delay(6000);
    int fing=-1;
    while ((grace < 2)&&(fing==-1)) {
      Serial.println("scanning...");
      lcd.clear();
     lcd.print("scanning...");
    delay(1000);
       fing = getFingerprintIDez();
      if ((fing != -1)) {
        Serial.println("access granted");
        lcd.clear();
     lcd.print("Access Granted");
    delay(1000);
        myservo.write(180);
        grace=5;
        delay(3000);
        Serial.println("Closing door");
        lcd.clear();
     lcd.print("Closing door");
    delay(10000);
        myservo.write(15);
        Serial.println("Waiting for valid RFID");
        lcd.clear();
     lcd.print("Scan Card");
    delay(1000);
      break;
   case "313910337" :
       int grace = 0;
    Serial.println("lets scan your finger Bola");
    
    Serial.println("place finger on the scanner");
    delay(1000);
    lcd.clear();
     lcd.print("Scan Finger");
    delay(6000);
    int fing=-1;
    while ((grace < 2)&&(fing==-1)) {
      Serial.println("scanning...");
      lcd.clear();
     lcd.print("scanning...");
    delay(1000);
       fing = getFingerprintIDez(3);
      if ((fing != -1)) {
        Serial.println("access granted");
        lcd.clear();
     lcd.print("Access Granted");
    delay(1000);
        myservo.write(180);
        grace=5;
        delay(3000);
        Serial.println("Closing door");
        lcd.clear();
     lcd.print("Closing door");
    delay(10000);
        myservo.write(15);
        Serial.println("Waiting for valid RFID");
        lcd.clear();
     lcd.print("Scan Card");
    delay(1000);
     break;
    default:
       Serial.println("access denied");
        lcd.clear();
     lcd.print("Access Denied");
    delay(1000);
        grace++; 
  }
     if ((grace < 2)&&(fing=-1)) {
        Serial.println("clean your finger and try again");
       delay(4000);
       lcd.clear();
     lcd.print("Again");
    delay(1000);
        
      }
    }
  }

  else{if(ab!="null"){Serial.println("access denied");}}
  //Serial.println(getFingerprintIDez());
  delay(50);            //don't ned to run this at full speed.
}







uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  //Serial.print("Found ID #"); Serial.print(finger.fingerID);
  //Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}



/////////////////////////////////////////////////////////////////////////////////////////////
String reuid() {
  String res = "null";
  // put your main code here, to run repeatedly:
  if ( ! rfid.PICC_IsNewCardPresent())
    return res;
  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return res;
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);//get the type
  res = printHextxt(rfid.uid.uidByte, rfid.uid.size);
  //Serial.println(res);
  // Halt PICC
  rfid.PICC_HaltA();
  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();
}


String printHextxt(byte *buffer, byte bufferSize) {
  String coa = "";
  for (byte i = 0; i < bufferSize; i++) {
    String a = String(buffer[i], DEC);
    coa = coa + a;
  }
  return coa;
}

