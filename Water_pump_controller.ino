#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <string.h>

#define l1 8
#define l2 9
#define l3 10

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
SoftwareSerial mySerial(2, 3);
String sLine, Mobno = "+917083593900";
String msg1, lcdstr;
char *data, *msg, *mobno;

int i;

boolean rflag = false;
boolean doflag = 1;
boolean rsflag = false;

void col_data(void);

short int motor = 13, level = 0;

void setup() {
  pinMode(motor, OUTPUT);
  digitalWrite(motor, LOW);

  pinMode(l1, INPUT);
  // digitalWrite(l1, LOW);
  pinMode(l2, INPUT);
  // digitalRead(l1);
  pinMode(l3, INPUT);

  // pinMode(motor, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("*CHARISMA");
  lcd.setCursor(2, 1);
  lcd.print("INNOVATIONS*");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");

  Serial.begin(9600);
  mySerial.begin(9600);

  while (!strstr(data, "OK")) {
    mySerial.println("AT");
    Serial.println("AT");
    delay(500);
    col_data();
  }

  do {
    mySerial.println("ATE0");
    Serial.println("ATE0");
    delay(500);
    col_data();
  } while (!strstr(data, "OK"));

  do {
    mySerial.println("AT+CMGF=1");
    Serial.println("AT+CMGF=1");
    delay(500);
    col_data();
  } while (!strstr(data, "OK"));

  do {
    mySerial.println("AT+CNMI=1,3");
    Serial.println("AT+CNMI=1,3");
    delay(500);
    col_data();
  } while (!strstr(data, "OK"));

  do {
    mySerial.println("AT+CMGDA=\"DEL ALL\"");
    Serial.println("AT+CMGDA=\"DEL ALL\"");
    delay(500);
    col_data();
  } while (!strstr(data, "OK"));

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Initialized");
  //   delay (2000);
}

void loop() {
  delay(2000);
  check_level();
  lcd.clear();
  lcdstr = "Tank=";
  lcdstr.concat(level);
  lcdstr = lcdstr + "% filled";
  lcd.setCursor(3, 0);
  lcd.print("*CHARISMA*");
  lcd.setCursor(0, 1);
  lcd.print(lcdstr);

  if (level >= 99 && digitalRead(motor)) {
    // delay(2000);
    digitalWrite(motor, LOW);
    // Mobno=Mobno.concat(defno);
    msg1 = "AT+CMGS=\"" + Mobno + "\"";
    mySerial.println(msg1);
    Serial.println("sent:" + msg1);

    delay(200);

    mySerial.println("Charisma says: MOTOR IS TURNED OFF");
    Serial.println("MOTOR IS OFF");
    delay(200);

    Serial.println((char)26);
    mySerial.println((char)26);
    delay(1000);
  }

  // delay (2000);
  // autoScroll();

  if (mySerial.available()) {

    mySerial.println("AT+CMGR=1");
    Serial.println("AT+CMGR=1");
    rflag = true;
    col_data();
    rsflag = true;

    if (strstr(msg, "READ")) {

      if (strstr(msg, "CHARISMA SWITCH MOTOR ON")) {
        if (!digitalRead(motor)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MESSAGE REVIEVED");
          lcd.setCursor(0, 1);
          lcd.print("Motor is ON");
          // autoScroll();
          // delay(1000);
          digitalWrite(motor, HIGH);

          msg1 = "AT+CMGS=\"" + Mobno + "\"";
          mySerial.println(msg1);
          Serial.println("sent:" + msg1);

          delay(200);
          mySerial.println("Charisma says: MOTOR IS ON");
          Serial.println("MOTOR IS ON");
          delay(500);

          Serial.println((char)26);
          mySerial.println((char)26);
          col_data();
          delay(100);

          delay(1000);
        }

        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MESSAGE REVIEVED");
          lcd.setCursor(0, 1);
          lcd.print("Motor is ON");
          // autoScroll();

          msg1 = "AT+CMGS=\"" + Mobno + "\"";
          mySerial.println(msg1);
          Serial.println("sent:" + msg1);

          delay(200);
          // delay(500);
          mySerial.println("Charisma says: MOTOR IS ALREADY ON");
          Serial.println("MOTOR IS ALREADY ON");
          delay(200);

          Serial.println((char)26);
          mySerial.println((char)26);
          delay(1000);
        }

      }

      else if (strstr(msg, "CHARISMA SWITCH MOTOR OFF")) {
        if (digitalRead(motor)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MESSAGE REVIEVED");
          lcd.setCursor(0, 1);
          lcd.print("Motor is OFF");

          digitalWrite(motor, LOW);
          msg1 = "AT+CMGS=\"" + Mobno + "\"";
          mySerial.println(msg1);
          Serial.println("sent:" + msg1);

          delay(200);

          mySerial.println("Charisma says: MOTOR IS TURNED OFF");
          Serial.println("MOTOR IS OFF");
          delay(200);

          Serial.println((char)26);
          mySerial.println((char)26);
          delay(1000);

        }

        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MESSAGE REVIEVED");
          lcd.setCursor(0, 1);
          lcd.print("Motor is OFF");
          // autoScroll();
          msg1 = "AT+CMGS=\"" + Mobno + "\"";
          mySerial.println(msg1);
          Serial.println("sent:" + msg1);

          delay(200);

          mySerial.println("Charisma Says: MOTOR IS ALREADY OFF");
          Serial.println("MOTOR IS ALREADY OFF");
          delay(200);

          mySerial.println((char)26);
          Serial.println((char)26);
          delay(1000);
        }

      }

      else if (strstr(msg, "CHARISMA TELL MOTOR STATUS")) {
        if (digitalRead(motor)) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MESSAGE REVIEVED");
          lcd.setCursor(0, 1);
          lcd.print("Motor is ON");
          // autoScroll();

          msg1 = "AT+CMGS=\"" + Mobno + "\"";
          mySerial.println(msg1);
          Serial.println("sent:" + msg1);

          delay(200);

          mySerial.println("Charisma says: MOTOR IS ON and " + lcdstr);
          Serial.println("MOTOR IS ON and " + lcdstr);
          delay(200);

          mySerial.println((char)26);
          Serial.println((char)26);
          delay(1000);
        }

        else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("MESSAGE REVIEVED");
          lcd.setCursor(0, 1);
          lcd.print("Motor is OFF");
          // autoScroll();

          msg1 = "AT+CMGS=\"" + Mobno + "\"";
          mySerial.println(msg1);
          Serial.println("sent:" + msg1);

          delay(200);

          mySerial.println("Charisma says: MOTOR IS OFF and " + lcdstr);
          Serial.println("MOTOR IS OFF and " + lcdstr);
          delay(200);

          mySerial.println((char)26);
          Serial.println((char)26);

          delay(1000);
        }
      }
    }
    delay(2000);
  }
  if (rsflag == true) {
    do {

      mySerial.println("AT+CMGDA=\"DEL ALL\"");
      Serial.println("AT+CMGDA=\"DEL ALL\"");
      col_data();
    } while (!strstr(data, "OK"));
    rsflag = false;
    delay(2000);
  }

  free(msg);
  msg = NULL;
}
//

void col_data(void) {

  while (!mySerial.available())
    ;
  sLine = mySerial.readString();
  data = (char *)realloc(data, sLine.length() + 1);
  Serial.println("Recieved data:");
  sLine.toCharArray(data, sLine.length());
  Serial.println(data);
  delay(1000);
  if (rflag == true) {
    msg = (char *)realloc(msg, sLine.length() + 1);
    Serial.println("Recieved message:");
    sLine.toCharArray(msg, sLine.length());
    Serial.println(msg);
    extractno();
    delay(1000);
    rflag = false;
  }
}
void extractno(void) {
  char *no;
  no = realloc(no, strlen(msg));

  no = strstr(msg, "AD\",\"") + 5;
  Mobno = "";
  Mobno.concat(no);
  Mobno = Mobno.substring(0, 13);
}

// return data;

void check_level(void) {
  if (digitalRead(l1) == LOW && digitalRead(l2) == LOW &&
      digitalRead(l3) == LOW)
    level = 0;
  else if (digitalRead(l1) == HIGH && digitalRead(l2) == LOW &&
           digitalRead(l3) == LOW)
    level = 33;
  else if (digitalRead(l1) == HIGH && digitalRead(l2) == HIGH &&
           digitalRead(l3) == LOW)
    level = 66;
  else if (digitalRead(l1) == HIGH && digitalRead(l2) == HIGH &&
           digitalRead(l3) == HIGH)
    level = 99;
  else
    level = 101;
}
void autoScroll(void) {
  for (i = 0; i <= 7; i++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }
}
