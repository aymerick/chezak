// serialized payload
struct {
  byte light;     // light sensor: 0..255
  byte lobat :1;  // supply voltage dropped under 3.1V: 0..1
  byte humi  :7;  // humidity: 0..100
  int  temp  :10; // temperature: -500..+500 (tenths)
} payload;


static void serialFlush () {
#if ARDUINO >= 100
  Serial.flush();
#endif

  // make sure tx buf is empty before going back to sleep
  delay(2);
}

void setup() {
 Serial.begin(57600);
 Serial.print("\n[test][conv]");
}

void testTemp(short int value) {
  payload.temp = value;

  Serial.print(value);
  Serial.print(' ');
  Serial.print((int) payload.temp);
  Serial.println();
}

void loop(void) {
  short int temp;

  temp = 50;
  testTemp(temp);

  temp = -50;
  testTemp(temp);

  temp = 200;
  testTemp(temp);

  temp = -200;
  testTemp(temp);

  // -5
  temp = 0xFFFB;
  testTemp(temp);

  temp = 511;
  testTemp(temp);

  temp = 512;
  testTemp(temp);

  temp = 513;
  testTemp(temp);

  temp = -511;
  testTemp(temp);

  temp = -512;
  testTemp(temp);

  temp = -513;
  testTemp(temp);

  delay(10000);
}

