#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
Servo gateServo;

const int trigPin = 9;
const int echoPin = 10;
const int gatePin = 11;

long duration;
int distanceCm;

void setup()
{
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  gateServo.attach(gatePin);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;

  UpdateLCDMessage(distanceCm);

  if (distanceCm < 15)
  {
    OpenGate();
  }
  else
  {
    CloseGate();
  }

  delay(10);
}

void UpdateLCDMessage(int distance)
{
  if (distance < 15) {
    lcd.setCursor(0, 0);
    lcd.print("Portao Fechado    "); // Mensagem quando o portão estiver fechado
  } else {
    lcd.setCursor(0, 0);
    lcd.print("Portao Aberto   "); // Mensagem quando o portão estiver aberto
  }

  lcd.setCursor(0, 1);
  lcd.print("Distancia: ");
  lcd.print(distance);
  lcd.print(" cm");
}

void OpenGate()
{
  gateServo.write(180); // Abre o portão
  delay(1000);
}

void CloseGate()
{
  gateServo.write(0); // Fecha o portão
  delay(1000);
}
