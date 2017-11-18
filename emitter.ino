// this code takes the input to the serial termincal
// and converts to binary packets before emitting
// the binary via an attached LED

#define LED_PIN 0

void setup() {
        Serial.begin(9600);
}

void loop() {
        Serial.read();
}
