// определение каналов реле
#define BLINK_CH      5 // кана реле для мигалки
#define LED_RED_CH    2 // канал для светодиодной ленты - красного цвет
#define LED_BLUE_CH   3 // канал для светодиодной ленты - голубой цвет
#define LED_GREEN_CH  4 // канал для светодиодной летны - зеленый цвет

#define FIRST_MINE_CH     8   // каналы мин
#define SECOND_MINE_CH    9
#define THIRD_MINE_CH     10
#define RED_BUTTON        11  // каналы красной и зеленой кнопки
#define GREEN_BUTTON      12
#define RESET_BUTTON_CH   13   // канал кнопки сброса


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
  pinMode(RED_BUTTON, INPUT);
  pinMode(GREEN_BUTTON, INPUT);
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

bool isGreenPressed() // нажата ли зеленая кнопка
{
  return digitalRead(GREEN_BUTTON) == HIGH; 
}

bool isRedPressed() // нажата ли красная кнопка
{
  return digitalRead(RED_BUTTON) == HIGH; 
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
  digitalWrite(LED_RED_CH, LOW);
  digitalWrite(LED_BLUE_CH, LOW);
  digitalWrite(LED_GREEN_CH, LOW);
  digitalWrite(BLINK_CH, LOW);
}

void setup() 
{
  relaySetup();
  buttonsSetup();
  reset();
  Serial.begin(9600);
}

void loop() 
{
  if(isRedPressed())
  {
    Serial.println("red");
    glowRed();
    delay(100);    
  }
  if(isGreenPressed())
  {
    Serial.println("green");
    glowGreen();
    delay(100);  
  }
  if(isMinesActivated())
  {
    Serial.println("mines");
    blinkActivate();
  }
  if(isResetPressed())
  {
    Serial.println("reset");
    reset();
  }  
  delay(10);
}
