const unsigned short servoR = 9;
const unsigned short servoL = 10;

const unsigned short OPT0 = A5; //far left
const unsigned short OPT1 = A4; //left
const unsigned short OPT2 = A3; //mid
const unsigned short OPT3 = A1; //right
const unsigned short OPT4 = A0; //far right


short tabOPT[5] = {0, 0, 0, 0, 0};

short left = 0;


short isBlack(unsigned short OPT)
{
  int OPTvalue;

  OPTvalue = analogRead(OPT);   

  if(OPTvalue > 750)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


short readAndCalculate()
{
  short sum = 0;   
  short count = 0;  

  
  tabOPT[0] = isBlack(OPT0);
  tabOPT[1] = isBlack(OPT1);
  tabOPT[2] = isBlack(OPT2);
  tabOPT[3] = isBlack(OPT3);
  tabOPT[4] = isBlack(OPT4);

  
  if(tabOPT[0] == 0)
  {
    sum = sum - 30;
    count++;
  }
  
  if(tabOPT[1] == 0)
  {
    sum = sum - 20;
    count++;
  }
  
  if(tabOPT[2] == 0)
  {
    sum = sum + 0;
    count++;
  }
   if(tabOPT[3] == 0)
  {
    sum = sum + 20;
    count++;
  }
   if(tabOPT[4] == 0)
  {
    sum = sum + 30;
    count++;
  }

  
  if(sum > 0)
  {
    left = 1;
  }

  if(sum < 0)
  {
    left = 0;
  }

  if(count > 0)
  {
    sum = sum / count;
    sum = sum * 10;
    return sum; 
  }
  else
  {
    return 10000;
  }
  
}


void setup() 
{
  pinMode(servoL, OUTPUT);
  pinMode(servoR, OUTPUT);
} 


void loop() 
{ 
  short speed;
  short brakingPulse;
  short remainerRunPuls;

  speed = readAndCalculate();

  if(speed != 10000)
  {
    if(speed > 0)
    {
      brakingPulse = speed;
    }
    else
    {
      brakingPulse = -speed;
    }

    digitalWrite(servoL, HIGH);
    digitalWrite(servoR, HIGH);

    if(speed > 0)
    {
      delayMicroseconds(1300);
      digitalWrite(servoR, LOW);
      delayMicroseconds(400 - brakingPulse);
      digitalWrite(servoL, LOW);
      delayMicroseconds(2300 - 1700 + brakingPulse);
    }
    else
    {
      delayMicroseconds(1300 + brakingPulse);
      digitalWrite(servoR, LOW);
      delayMicroseconds(400 - brakingPulse);
      digitalWrite(servoL, LOW);
      delayMicroseconds(2300 - 1700);
    }
    delayMicroseconds(700);
    delay(17);
  }
  else
  {
    if(left)
    {
      digitalWrite(servoL, HIGH);
      digitalWrite(servoR, HIGH);
      delayMicroseconds(1400);//delayMicroseconds(1200);
      digitalWrite(servoR, LOW);
      digitalWrite(servoL, LOW);
      delayMicroseconds(1600);//delayMicroseconds(1800);
    }
    else
    {
      digitalWrite(servoL, HIGH);
      digitalWrite(servoR, HIGH);
      delayMicroseconds(1600);//delayMicroseconds(1800);
      digitalWrite(servoL, LOW);
      digitalWrite(servoR, LOW);
      delayMicroseconds(1400);//delayMicroseconds(1200);
    }
    delay(17);
  }
}
