// определение каналов реле
#define BLINK_CH      4 // кана реле для мигалки
#define LED_RED_CH    5 // канал для светодиодной ленты - красного цвет
#define LED_BLUE_CH   2 // канал для светодиодной ленты - голубой цвет
#define LED_GREEN_CH  3 // канал для светодиодной летны - зеленый цвет

#define FIRST_MINE_CH     8   // каналы мин
#define SECOND_MINE_CH    9
#define THIRD_MINE_CH     10
#define RED_BUTTON        11  // каналы красной и зеленой кнопки
#define GREEN_BUTTON      12
#define RESET_BUTTON_CH   13   // канал кнопки сброса

#define BLINK_TIME  3000  // время работы мигалки

bool firstMineActive = true;    // флаги активности мин - не дезактивированы ли они
bool secondMineActive = true;
bool thirdMineActive = true;

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

bool isFirstMineActivated() // активирована ли первая мина 
{
  return digitalRead(FIRST_MINE_CH) == HIGH;
}

bool isSecondMineActivated() // активирована ли вторая мина 
{
  return digitalRead(SECOND_MINE_CH) == HIGH;
}

bool isThirdMineActivated() // активирована ли третья мина 
{
  return digitalRead(THIRD_MINE_CH) == HIGH;
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
  glowBlue();
  digitalWrite(BLINK_CH, LOW);
  firstMineActive = true;    
  secondMineActive = true;
  thirdMineActive = true;
}

void lowAll()
{
  digitalWrite(LED_RED_CH, LOW);
  digitalWrite(LED_BLUE_CH, LOW);
  digitalWrite(LED_GREEN_CH, LOW);
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
  static bool blinkActivator = false; // флаг активирующий мигалку
  static unsigned long timer = 0; 
  
  if(isRedPressed())  //  если нажата красная кнопка
  {
    glowRed();
    delay(100);    
  }
  
  if(isGreenPressed())  // если нажата зеленая кнопка
  {
    glowGreen();
    delay(100);  
  }
  
  if(isResetPressed())  // нажата кнопка сброса
  {
    reset();   // просто моргаем синим цветам
    delay(300); 
    lowAll();
    blinkActivator = false;
    delay(300); 
    glowBlue();
    delay(300);
    digitalWrite(LED_BLUE_CH, LOW);
    delay(300);
    glowBlue();
    delay(100);
  }  
  
  if(isFirstMineActivated() && firstMineActive)   // если нажата первая мина и она активна
  {
    blinkActivator = true;  // ставим флаг, что нужно включить мигалку
    firstMineActive = false;  // деактивируем мину
    timer = millis();   
  }
  
  if(isSecondMineActivated() && secondMineActive) // если нажата вторая мина и она активна
  {
    blinkActivator = true;  // ставим флаг, что нужно включить мигалку
    secondMineActive = false; // деактивируем мину
    timer = millis();     
  }
  
  if(isThirdMineActivated() && thirdMineActive) // если нажата третья мина и она активна
  {
    blinkActivator = true;  // ставим флаг, что нужно включить мигалку
    thirdMineActive = false;  // деактивируем мину
    timer = millis();   
  }
  
  if(blinkActivator && ((millis() - timer) < BLINK_TIME))
  {
    blinkActivate();
    delay(100);
  }
  else
  {
    blinkDeactivate();
    blinkActivator = false;
    delay(100);
  }
  delay(10);
}
