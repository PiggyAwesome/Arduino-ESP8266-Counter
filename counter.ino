#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define buzzerPin D6
#define buttonPin D5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define whiteLED D8
#define greenLED D7
#define yellowLED1 D4
#define yellowLED2 D3
#define redLED D0
#define DEBOUNCE_TIME 200

int counter = 0;
volatile int prev_micros = 0 ;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED1, OUTPUT);
  pinMode(yellowLED2, OUTPUT);
  pinMode(redLED, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), plusone, HIGH);
  
  if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  oled.clearDisplay();

  oled.setTextSize(2);
  oled.setTextColor(WHITE);

}

ICACHE_RAM_ATTR void plusone() {
   if((micros() - prev_micros) >= DEBOUNCE_TIME * 1000) {
    counter += 1;
    prev_micros = micros();
  }
    
}

void loop() {
  oled.clearDisplay();
  oled.setCursor(0, 10);

  oled.print("Count: ");
  oled.println(counter);

  if (counter >= 100 && counter < 101) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(whiteLED, HIGH);
  }
  else {
    digitalWrite(buzzerPin, LOW);
  }
  if (counter >= 80) {
    digitalWrite(greenLED, HIGH);
  }
  else if (counter >= 60) {
    digitalWrite(yellowLED1, HIGH);
  }
  else if (counter >= 40) {
    digitalWrite(yellowLED2, HIGH);
  }
  else if (counter >= 20) {
    digitalWrite(redLED, HIGH);
  }
  oled.display();
}
