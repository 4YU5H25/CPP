#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include <NewPing.h>

#define BlynkPrint Serial1
#define ssidwifi "Rg"
#define passwifi "ayush@25"
#define DHTY DHT11
#define LED 2
#define led 21
#define tempId "TMPL36TMCHa46"
#define tempName "Room Monitoring System"
#define auth "UMoIqDB2imdww76ycR_dtQIMdqJGbJRR"
#define max_dist 100
#define trigpin 18
#define echopin 19


int currentState1 = 0,
    previousState1 = 0,
    currentState2 = 0,
    previousState2 = 0;

DHT dht(14, DHTY);
NewPing io(trigpin, echopin, max_dist);

int distance = 0, dist = INT32_MAX;
int In = 0,
    Out = 0,
    Total = 0;

BLYNK_WRITE(V4) {
  int pin = param.asInt();
  digitalWrite(13,pin);
}

void setup() {
  Serial.begin(115200);
  delay(30);

  Blynk.begin(auth, ssidwifi, passwifi, "blynk.cloud", 80);

  pinMode(13,OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(led, OUTPUT);

  dht.begin();
}

void loop() {
  distance = io.ping_cm();
  Blynk.run();
  if (abs(dist - distance) < 15) {
    return;
  } else {
    if (distance <= 15) {
      currentState1 = 1;
      digitalWrite(LED, HIGH);
      delay(69);
      digitalWrite(LED, LOW);
    }

    else {
      currentState1 = 0;
    }

    if (currentState1 != previousState1) {
      if (currentState1 == 1) {
        Total = Total + 1;
      }
      In += 1;
    }
    delay(100);
    if (distance > 15 && distance <= 30) {
      currentState2 = 1;
      digitalWrite(LED, HIGH);
      delay(69);
      digitalWrite(LED, LOW);
    } else {
      currentState2 = 0;
    }

    if (currentState2 != previousState2) {
      if (currentState2 == 1) {
        Total = Total - 1;
      }
      Out += 1;
    }

    float h = 0;
    float t = 0;
    if (touchRead(4) < 25) {
      In += 1;
      digitalWrite(LED, HIGH);
      delay(69);
      digitalWrite(LED, LOW);
    }
    if (touchRead(15) < 25) {
      Out += 1;
      digitalWrite(LED, HIGH);
      delay(69);
      digitalWrite(LED, LOW);
    }

    Total = In - Out;

    if (Total < 0) {
      Total = 0;
    }

    h = dht.readHumidity();
    t = dht.readTemperature();

    if (Total > 0) {
      digitalWrite(led, HIGH);
    }
    else if(Total == 0) {
      digitalWrite(led,LOW);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    }

    int dist = io.ping_cm();
    Serial.print("\nTemperature is: ");
    Serial.print(t);
    Serial.print("*C\tHumidity is: ");
    Serial.print(h);
    Serial.print("%\nPeople Entered: ");
    Serial.print(In);
    Serial.print("\tPeople Left: ");
    Serial.print(Out);
    Serial.print("\nTotal People in the Room: ");
    Serial.print(Total);

    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V3, Total);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    Blynk.virtualWrite(V1, In);
    Blynk.virtualWrite(V2, Out);
  }

  dist = distance;

  delay(1000);
}
