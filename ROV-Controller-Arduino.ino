//Data Flow
int dataIN[7];
int MotorD[6];
int Relay[8];
int Micro[8];

//Dagu pulse //dhp = Driver Horizontal Pulse
int dvp1 = 4;
int dvp2 = 5;
int dhp1 = 6;
int dhp2 = 7;
int dhp3 = 8;
int dhp4 = 9;

//Dagu direction //dvd = Driver Vertical Direction
int dvd1 = 47;
int dvd2 = 49;
int dhd1 = 39;
int dhd2 = 41;
int dhd3 = 43;
int dhd4 = 45;

//Main Relay pins
int r1 = 38;
int ARM = 40;
int r3 = 42;
int r4 = 44;
int T1 = 46;
int T2 = 48;
int r7 = 50;
int r8 = 52;

//Micro pins
int m1 = 30;
int RM1 = 22;
int RM2 = 24;
int LM1 = 26;
int LM2 = 28;
int MLED = 34;
int m7 = 32;
int m8 = 36;

//Metal Sensor Pin
int Metsen = 33;
int x;

//pH Sensor Pin
int ph = A0;

//Temp. Sensor Pin
const int analogInPin = A7; 
const int SensorValueLow = 201; 
const int SensorValueDiff = 24; // differance between high and low sensor value
const int TempValueDiff = 60; // differance between high and low Temp value
const int TempValueLow = 37;
int sensorValue = 0;
double Temp = 0;

//States pins
int leak = 37;
int power = 21;
int serial = 35;

void setup() {

  Serial.begin(2000000);

  //Driver pulse
  pinMode(dvp1, OUTPUT);
  pinMode(dvp2, OUTPUT);
  pinMode(dhp1, OUTPUT);
  pinMode(dhp2, OUTPUT);
  pinMode(dhp3, OUTPUT);
  pinMode(dhp4, OUTPUT);

  //Driver directions
  pinMode(dvd1, OUTPUT);
  pinMode(dvd2, OUTPUT);
  pinMode(dhd1, OUTPUT);
  pinMode(dhd2, OUTPUT);
  pinMode(dhd3, OUTPUT);
  pinMode(dhd4, OUTPUT);

  //Relay
  pinMode(r1, OUTPUT);
  pinMode(ARM, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(T1, OUTPUT);
  pinMode(T2, OUTPUT);
  pinMode(r7, OUTPUT);
  pinMode(r8, OUTPUT);


  //Micro
  pinMode(m1, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(MLED, OUTPUT);
  pinMode(m7, OUTPUT);
  pinMode(m8, OUTPUT);

  //States LEDs
  pinMode(serial, OUTPUT);
  pinMode(leak, INPUT);
  pinMode(power , INPUT);

  //Sensors
  pinMode(Metsen, INPUT);

  //PWM for vertical
  analogWrite(dvp1, 0);
  analogWrite(dvp2, 0);

  //PWM for horizontal
  analogWrite(dhp1, 0);
  analogWrite(dhp2, 0);
  analogWrite(dhp3, 0);
  analogWrite(dhp4, 0);

  //Relays
  digitalWrite(r1, 1);
  digitalWrite(ARM, 1);
  digitalWrite(r3, 1);
  digitalWrite(r4, 1);
  digitalWrite(T1, 1);
  digitalWrite(T2, 1);
  digitalWrite(r7, 1);
  digitalWrite(r8, 1);

  //Micro
  digitalWrite(m1, 1);
  digitalWrite(RM1, 1);
  digitalWrite(RM2, 1);
  digitalWrite(LM1, 1);
  digitalWrite(LM2, 1);
  digitalWrite(MLED, 1);
  digitalWrite(m7, 1);
  digitalWrite(m8, 1);
}

void loop() {

  if (Serial.available() == 0)
  {
    digitalWrite(serial, LOW);                         //Serial led goes low if there isn't serial data
  }

  int i = 0;
  while (Serial.available() > 0)                        //Reciving and decoding
  {
    digitalWrite(serial, HIGH);                         //Serial led goes high if there is serial data
    
    dataIN[i] = Serial.parseInt();
    if (Serial.read() == '\n') break;
    i++;
  }

  for (int i = 5; i >= 0; i--)
    MotorD[i] = bitRead(dataIN[3], i);

  for (int i = 7; i >= 0; i--)
    Relay[i] = bitRead(dataIN[4], i);

  for (int i = 7; i >= 0; i--)
    Micro[i] = bitRead(dataIN[5], i);
   


  //PWM for vertical
  analogWrite(dvp1, dataIN[0]);
  analogWrite(dvp2, dataIN[0]);

  //PWM for horizontal
  analogWrite(dhp1, dataIN[2]); //Front Left
  analogWrite(dhp2, dataIN[1]); //Front Right
  analogWrite(dhp3, dataIN[2]); //Back Right
  analogWrite(dhp4, dataIN[1]); //Back Left

  //Driver directions
  digitalWrite(dhd1, MotorD[0]);
  digitalWrite(dhd2, MotorD[1]);
  digitalWrite(dhd3, MotorD[2]);
  digitalWrite(dhd4, MotorD[3]);
  digitalWrite(dvd1, MotorD[4]);
  digitalWrite(dvd2, MotorD[5]);

  //Relays direction
  digitalWrite(r1, 1);
  digitalWrite(ARM, Relay[1]);
  digitalWrite(r3, 1);
  digitalWrite(r4, 1);
  digitalWrite(T1, Relay[4]);
  digitalWrite(T2, Relay[5]);
  digitalWrite(r7, 1);
  digitalWrite(r8, 1);

  //Micro  //m4 hnst8fmhas
  digitalWrite(m1, 1);
  digitalWrite(RM1, 1);
  digitalWrite(RM2, 1);
  digitalWrite(LM1, 1);
  digitalWrite(LM2, 1);
  digitalWrite(MLED, 1);
  digitalWrite(m7, 1);
  digitalWrite(m8, 1);

  //metal sensor
  x = digitalRead(Metsen);

  //Temp. sensor
  sensorValue = analogRead(analogInPin);
  Temp = sensorValue-SensorValueLow;
  Temp = Temp/SensorValueDiff;
  Temp = Temp*TempValueDiff;
  Temp = Temp+TempValueLow;
  Temp = Temp /1.2;
  //LEDs output
  if (dataIN[6] == 1)
  {
    Serial.println ( x );
  }
  if (dataIN[6] == 4)
  {
    Serial.print ( Temp ) ;
    Serial.print ('-');
    Serial.println ( sensorValue ) ;    
  }
  else 
  {
    Serial.println ( '0' );
  }
}
