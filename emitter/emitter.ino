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
        Serial.begin(9600);
}

void loop() {
        if (Serial.available() > 0) {
        unsigned char payload[PACKET_SIZE];
        unsigned int crc;

        payload[0] = PREAMBLE;

        for (int i = 1; i < PAYLOAD_LENGTH; i++) {
                if (Serial.available() > 0) {
                    payload[i] = Serial.read();
            } else {
                    payload[i] = 0;
            }
        }

        crc=gen_crc16(payload + 1, 32);

        payload[PAYLOAD_LENGTH + 1] = crc >> 8;
        payload[PAYLOAD_LENGTH + 2] = (unsigned char) crc;

        Serial.write(payload);
}
}

/*
//                                      16   12   5
// this is the CCITT CRC 16 polynomial X  + X  + X  + 1.
// This works out to be 0x1021, but the way the algorithm works
// lets us use 0x8408 (the reverse of the bit pattern).  The high
// bit is always assumed to be set, thus we only use 16 bits to
// represent the 17 bit value.
*/

unsigned short gen_crc16(const unsigned char *data, unsigned short size)
{
	unsigned short out = 0;
	int bits_read = 0, bit_flag;

	/* Sanity check: */
	if (data == 0)
		return 0;

	while (size > 0)
	{
		bit_flag = out >> 15;

		/* Get next bit: */
		out <<= 1;
		out |= (*data >> bits_read) & 1; // item a) work from the least significant bits

										 /* Increment bit counter: */
		bits_read++;
		if (bits_read > 7)
		{
			bits_read = 0;
			data++;
			size--;
		}

		/* Cycle check: */
		if (bit_flag)
			out ^= CRC16;

	}

	// item b) "push out" the last 16 bits
	int i;
	for (i = 0; i < 16; ++i) {
		bit_flag = out >> 15;
		out <<= 1;
		if (bit_flag)
			out ^= CRC16;
	}

	// item c) reverse the bits
	unsigned short crc = 0;
	i = 0x8000;
	int j = 0x0001;
	for (; i != 0; i >>= 1, j <<= 1) {
		if (i & out) crc |= j;
	}

	return crc;
}
