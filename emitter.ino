// this code takes the input to the serial termincal
// and converts to binary packets before emitting
// the binary via an attached LED

#define LED_PIN 0
#define PACKET_SIZE 35
#define PAYLOAD_LENGTH 32
#define PREAMBLE 0b10101010
#define POLY 0x8408


unsigned short crc16(char*, unsigned short);

void setup() {
        Serial.begin(9600);
}

void loop() {
        char payload[PACKET_SIZE];
        unsigned int crc;

        payload[0] = PREAMBLE;

        for (int i = 1; i < PAYLOAD_LENGTH; i++) {
                if (Serial.available() > 0) {
                    payload[i] = Serial.read();
            } else {
                    payload[i] = 0;
            }
        }

        crc=crc16(payload + 1, 32);

        Serial.write(crc);

        payload[PAYLOAD_LENGTH + 1] = crc >> 8;
        payload[PAYLOAD_LENGTH + 2] = (unsigned char) crc;
}

/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/

unsigned short crc16(char *data_p, unsigned short length)
{
      unsigned char i;
      unsigned int data;
      unsigned int crc = 0xffff;

      if (length == 0)
            return (~crc);

      do
      {
            for (i=0, data=(unsigned int)0xff & *data_p++;
                 i < 8;
                 i++, data >>= 1)
            {
                  if ((crc & 0x0001) ^ (data & 0x0001))
                        crc = (crc >> 1) ^ POLY;
                  else  crc >>= 1;
            }
      } while (--length);

      crc = ~crc;
      data = crc;
      crc = (crc << 8) | (data >> 8 & 0xff);

      return (crc);
}
