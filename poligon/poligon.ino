// определение каналов реле
#define BLINK_CH      1 // кана реле для мигалки
#define LED_RED_CH    2 // канал для светодиодной ленты - красного цвет
#define LED_BLUE_CH   3 // канал для светодиодной ленты - голубой цвет
#define LED_GREEN_CH  4 // канал для светодиодной летны - зеленый цвет

#define FIRST_MINE_CH     5   // каналы мин
#define SECOND_MINE_CH    6
#define THIRD_MINE_CH     7
#define RESET_BUTTON_CH   8   // канал кнопки сброса

void relaySetup()   // инициализация реле
{
  pinMode(BLINK_CH, OUTPUT);
  pinMode(LED_RED_CH, OUTPUT);
  pinMode(LED_BLUE_CH, OUTPUT);
  pinMode(LED_GREEN_CH, OUTPUT);
}

void buttonsSetup()   // инициализация кнопок, включая мины
{
  pinMode(FIRST_MINE_CH, INPUT);
  pinMode(SECOND_MINE_CH, INPUT);
  pinMode(THIRD_MINE_CH, INPUT);
  pinMode(RESET_BUTTON_CH, INPUT);  
}

bool isMinesActivated() // активированы ли мины (хотя бы одна)
{
  return ((digitalRead(FIRST_MINE_CH) == HIGH) ||  
          (digitalRead(SECOND_MINE_CH) == HIGH) ||
          (digitalRead(THIRD_MINE_CH) == HIGH));  
}

bool isResetPressed() // нажата ли кнопка reset
{
  return digitalRead(RESET_BUTTON_CH) == HIGH;  
}

void glowRed()  // светись красным
{
  digitalWrite(LED_RED_CH, HIGH);
  digitalWrite(LED_BLUE_CH, LOW);
  digitalWrite(LED_GREEN_CH, LOW);
}

void glowBlue() // светись голубым
{
  digitalWrite(LED_RED_CH, LOW);
  digitalWrite(LED_BLUE_CH, HIGH);
  digitalWrite(LED_GREEN_CH, LOW);
}

void glowGreen()  // светись зеленым
{
  digitalWrite(LED_RED_CH, LOW);
  digitalWrite(LED_BLUE_CH, LOW);
  digitalWrite(LED_GREEN_CH, HIGH);
}

void glowWhite()  // светись белым
{
  digitalWrite(LED_RED_CH, HIGH);
  digitalWrite(LED_BLUE_CH, HIGH);
  digitalWrite(LED_GREEN_CH, HIGH);
}

void blinkActivate()
{
  digitalWrite(BLINK_CH, HIGH);
}

void blinkDeactivate()
{
  digitalWrite(BLINK_CH, LOW);
}

void reset()    // перезапуск системы
{
  
}

void setup() 
{
  relaySetup();
  buttonsSetup();
  reset();
}

void loop() 
{
  
}
