// this code takes the input to the serial termincal
// and converts to binary packets before emitting
// the binary via an attached LED

#define LED_PIN 0
#define PACKET_SIZE 35
#define PAYLOAD_LENGTH 32
#define PREAMBLE 0b10101010
#define CRC16 0x8005

unsigned short gen_crc16(const unsigned char*, unsigned short);

void setup() {
        Serial.begin(2400);
}

void loop() {
        if (Serial.available() > 0) {

        unsigned char payload[PACKET_SIZE];
        unsigned int crc;

        payload[0] = PREAMBLE;

        for (int i = 0; i < PAYLOAD_LENGTH ; i++) {
                    payload[i + 1] = Serial.read();
        }

        crc=65535

        payload[PAYLOAD_LENGTH + 1] = crc >> 8;
        payload[PAYLOAD_LENGTH + 2] = (unsigned char) crc;

        Serial.print("test");
        }
        delay(1000);
}



// not our code - taken from tested CRC16 implementation on github
// unsigned short gen_crc16(const unsigned char *data, unsigned short size)
// {
// 	unsigned short out = 0;
// 	int bits_read = 0, bit_flag;
//
// 	/* Sanity check: */
// 	if (data == 0)
// 		return 0;
//
// 	while (size > 0)
// 	{
// 		bit_flag = out >> 15;
// 		/* Get next bit: */
// 		out <<= 1;
// 		out |= (*data >> bits_read) & 1;
//                 // item a) work from the least significant bits
// 		bits_read++;
// 		if (bits_read > 7)
// 		{
// 			bits_read = 0;
// 			data++;
// 			size--;
// 		}
// 		/* Cycle check: */
// 		if (bit_flag)
// 			out ^= CRC16;
// 	}
// 	// item b) "push out" the last 16 bits
// 	int i;
// 	for (i = 0; i < 16; ++i) {
// 		bit_flag = out >> 15;
// 		out <<= 1;
// 		if (bit_flag)
// 			out ^= CRC16;
// 	}
// 	// item c) reverse the bits
// 	unsigned short crc = 0;
// 	i = 0x8000;
// 	int j = 0x0001;
// 	for (; i != 0; i >>= 1, j <<= 1) {
// 		if (i & out) crc |= j;
// 	}
//
// 	return crc;
// }
