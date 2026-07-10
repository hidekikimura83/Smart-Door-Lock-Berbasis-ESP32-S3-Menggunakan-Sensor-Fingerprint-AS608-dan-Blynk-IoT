/*************************************************************
  ESP32-S3 + AS608 + Blynk + Door Lock
 *************************************************************/

#define BLYNK_TEMPLATE_ID   "ID"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN    "TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Fingerprint.h>


char ssid[] = "Wifi";
char pass[] = "Pass";


#define FP_RX 17
#define FP_TX 18
#define RELAY_PIN 15

HardwareSerial FingerSerial(2);
Adafruit_Fingerprint finger(&FingerSerial);
BlynkTimer timer;


bool fingerReady = false;
bool enrollRequest = false;
uint8_t nextEnrollID = 1;


void unlockDoor();
void enrollFingerprint(uint8_t id);
void scanFingerprint();
void checkConnection();


BLYNK_WRITE(V2) {   
  if (param.asInt()) {
    enrollRequest = true;
  }
}

BLYNK_WRITE(V3) { 
  if (param.asInt()) {
    unlockDoor();
  }
}


void checkConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    return;
  }
  if (!Blynk.connected()) {
    Blynk.connect(3000);
  }
}


void unlockDoor() {
  Serial.println("PINTU TERBUKA 🔓");
  Blynk.virtualWrite(V1, "Akses diterima");

  digitalWrite(RELAY_PIN, HIGH);

  timer.setTimeout(3000L, []() {
    digitalWrite(RELAY_PIN, LOW);
    Blynk.virtualWrite(V1, "Scan Fingerprint");
    Serial.println("PINTU TERKUNCI 🔒");
  });
}


void enrollFingerprint(uint8_t id) {
  Serial.println("Tempelkan jari...");
  Blynk.virtualWrite(V1, "Tempelkan jari");

  while (finger.getImage() != FINGERPRINT_OK) {
    Blynk.run(); timer.run();
  }

  if (finger.image2Tz(1) != FINGERPRINT_OK) {
    Blynk.virtualWrite(V1, "Gagal konversi");
    return;
  }

  Serial.println("Angkat jari");
  Blynk.virtualWrite(V1, "Angkat jari");
  delay(2000);

  while (finger.getImage() != FINGERPRINT_NOFINGER) {
    Blynk.run(); timer.run();
  }

  Serial.println("Tempelkan jari yang sama");
  Blynk.virtualWrite(V1, "Tempelkan jari lagi");

  while (finger.getImage() != FINGERPRINT_OK) {
    Blynk.run(); timer.run();
  }

  if (finger.image2Tz(2) != FINGERPRINT_OK) {
    Blynk.virtualWrite(V1, "Gagal konversi");
    return;
  }

  if (finger.createModel() != FINGERPRINT_OK) {
    Blynk.virtualWrite(V1, "Sidik jari tidak cocok");
    return;
  }

  if (finger.storeModel(id) == FINGERPRINT_OK) {
    Serial.println("Fingerprint berhasil disimpan");
    Blynk.virtualWrite(V1, "Berhasil");
    nextEnrollID++;
  } else {
    Blynk.virtualWrite(V1, "Gagal simpan");
  }

  delay(2000);
  Blynk.virtualWrite(V1, "Scan Fingerprint");
}


void scanFingerprint() {
  if (!fingerReady) return;

  if (enrollRequest) {
    enrollRequest = false;
    enrollFingerprint(nextEnrollID);
    return;
  }

  if (finger.getImage() != FINGERPRINT_OK) return;
  if (finger.image2Tz() != FINGERPRINT_OK) return;

  if (finger.fingerFastSearch() == FINGERPRINT_OK) {
    Serial.print("Fingerprint dikenali ID=");
    Serial.println(finger.fingerID);
    unlockDoor();
  } else {
    Blynk.virtualWrite(V1, "Akses ditolak");
    delay(1500);
    Blynk.virtualWrite(V1, "Scan Fingerprint");
  }
}


void setup() {
  Serial.begin(115200);
  delay(3000);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  
  FingerSerial.begin(57600, SERIAL_8N1, FP_RX, FP_TX);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Sensor fingerprint terdeteksi");
    fingerReady = true;
  } else {
    Serial.println("Fingerprint tidak terdeteksi");
  }

  finger.getTemplateCount();
  nextEnrollID = finger.templateCount + 1;

  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Blynk.config(BLYNK_AUTH_TOKEN);

  Blynk.virtualWrite(V1, "Scan Fingerprint");

  timer.setInterval(2000L, checkConnection);
  timer.setInterval(800L, scanFingerprint);
}



void loop() {
  Blynk.run();
  timer.run();
}
