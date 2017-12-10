// this code will look for blinking lights and synchronize its timing
// then receive a packet constructed from the emitter.ino code
// finally reconstructing the data and sending it back through the terminal

#define PACKET_SIZE 35
#define PAYLOAD_LENGTH 32

int analogPin = 21; //photodiode
int val = 0; 

void setup() 
{
  Serial.begin(9600);
  pinMode(21, INPUT);
  delay(5000);
}

void loop()
{
  char val;
  //char temp_byte = 0b0;

  for(int i=0; i<PACKET_SIZE; i++) //perform 35 times to reconstruct packet
  {
    for(int j=0; j<8; j++) //read LED state 8 times to reconstruct a character
    {
    val = analogRead(analogPin);
    if(val < 60) //below threshold, LED is off
        {
            val=0;
            Serial.print(0);
          }
    else         //above threshold, LED is on
          {
             val=1;
             Serial.print(1); 
          }
    //temp_byte = temp_byte | val; 
    //temp_byte = temp_byte << 1; 
    delay(60);
    }
  }
}
