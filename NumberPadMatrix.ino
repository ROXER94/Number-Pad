#define PORTB (GPIOB->ODR)
#define PINB (GPIOB->IDR)
#define PINC (GPIOB->IDR)

const int16_t portB_message_mask = 0b0000000011111000;
const int16_t char_patterns[13][7] = {
  {~0b0000000001110000, //0
   ~0b0000000010001000,
   ~0b0000000010011000,
   ~0b0000000010101000,
   ~0b0000000011001000,
   ~0b0000000010001000,
   ~0b0000000001110000},
  {~0b0000000000100000, //1
   ~0b0000000001100000,
   ~0b0000000000100000,
   ~0b0000000000100000,
   ~0b0000000000100000,
   ~0b0000000000100000,
   ~0b0000000001110000},
  {~0b0000000001110000, //2
   ~0b0000000010001000,
   ~0b0000000000001000,
   ~0b0000000000110000,
   ~0b0000000001000000,
   ~0b0000000010000000,
   ~0b0000000011111000},
  {~0b0000000011111000, //3
   ~0b0000000000001000,
   ~0b0000000000010000,
   ~0b0000000000110000,
   ~0b0000000000001000,
   ~0b0000000010001000,
   ~0b0000000001110000},
  {~0b0000000000010000, //4
   ~0b0000000000110000,
   ~0b0000000001010000,
   ~0b0000000010010000,
   ~0b0000000011111000,
   ~0b0000000000010000,
   ~0b0000000000010000},
  {~0b0000000011111000, //5
   ~0b0000000010000000,
   ~0b0000000011110000,
   ~0b0000000000001000,
   ~0b0000000000001000,
   ~0b0000000010001000,
   ~0b0000000001110000},
  {~0b0000000000111000, //6
   ~0b0000000001000000,
   ~0b0000000010000000,
   ~0b0000000011110000,
   ~0b0000000010001000,
   ~0b0000000010001000,
   ~0b0000000001110000},
  {~0b0000000011111000, //7
   ~0b0000000000001000,
   ~0b0000000000010000,
   ~0b0000000000100000,
   ~0b0000000001000000,
   ~0b0000000001000000,
   ~0b0000000001000000},
  {~0b0000000001110000, //8
   ~0b0000000010001000,
   ~0b0000000010001000,
   ~0b0000000001110000,
   ~0b0000000010001000,
   ~0b0000000010001000,
   ~0b0000000001110000},
  {~0b0000000001110000, //9
   ~0b0000000010001000,
   ~0b0000000010001000,
   ~0b0000000001111000,
   ~0b0000000000001000,
   ~0b0000000000010000,
   ~0b0000000011100000},
  {~0b0000000000100000, //!
   ~0b0000000000100000,
   ~0b0000000000100000,
   ~0b0000000000100000,
   ~0b0000000000100000,
   ~0b0000000000000000,
   ~0b0000000000100000},
  {~0b0000000000100000,
   ~0b0000000010101000, //*
   ~0b0000000001110000,
   ~0b0000000011111000,
   ~0b0000000001110000,
   ~0b0000000010101000,
   ~0b0000000000100000},
  {~0b0000000001010000, //#
   ~0b0000000001010000,
   ~0b0000000011111000,
   ~0b0000000001010000,
   ~0b0000000011111000,
   ~0b0000000001010000,
   ~0b0000000001010000}
 };

const int row_count = 7;
const int rows[7] = {A3, A4, A5, DAC, WKP, RX, TX};

const char conversion_table[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

const char conversion_table_2[7][3] =
{{'!', '!', '!'},
{'!', '!', '!'},
{'!', '!', '!'},
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'},
{'*', '0', '#'}};

const byte character_patterns_table[7][3] =
{{10, 10, 10},
{10, 10, 10},
{10, 10, 10},
{ 1, 2, 3},
{ 4, 5, 6},
{ 7, 8, 9},
{11, 0, 12}};

int number = 0;
int i;
int row;
int16_t pattern_read;

inline void clean_update(__IO uint32_t &target_register, int mask, int value_to_update) {
  target_register = (target_register & ~mask) | (value_to_update & mask);
}


void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(D4, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D0, OUTPUT);
}

void pinHigh(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
}

void pinLow(int pin) {
  delay(1);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
}


void loop() {
int time_delay = 1500;
i = 0;
while (i <= row_count) {
  row = rows[i];
  pinMode(row, OUTPUT);
  digitalWrite(row, HIGH);

  pattern_read = (PINC) & pmask;

  if (pattern_read & col1) {
   number = conversion_table_2[i][0];
   }
  if (pattern_read & col2) {
   number = conversion_table_2[i][1];
   }
  if (pattern_read & col3) {
   number = conversion_table_2[i][2];
   }
   clean_update(PORTB, mask, conversion_table_2[i][2]);
   delayMicroseconds(50);
   digitalWrite(row, LOW);
   pinMode(row, LOW);
 }
 /*for (int num=0; num<11; num++) {
   for (int i=0; i<69; i++) {
     for(int row=0; row<row_count; row++) {
       clean_update(PORTB, portB_message_mask, char_patterns[num][row]);
       pinHigh(ledRows[row]);
       delay(1);
       pinLow(ledRows[row]);
     }
   }
 }
 delay(5000);*/

}


}
