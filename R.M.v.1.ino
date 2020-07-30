#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//  LCD
LiquidCrystal_I2C lcd(0x27,16,2);  

// Rotary Encoder Control
const int clk= 2; 
const int dt= 3; 
const int sw= 4 ;
   int encoderVal = 0;

// RELAY
const int relay = 7;// Connected to relay (LED)
   int val = 0; // push value from pin 4
   int MotorON = 0;//light status
   int pushed = 0;//push status

// Rotary Encoder Measure

#define  A_channel 9
#define  B_channel 10
   unsigned int channel_A = 0;  //Assign a value 
   unsigned int channel_B = 0;  //Assign a value 


void setup() {
 
 Serial.begin(9600);   
 lcd.begin();  // initialize the lcd
  lcd.backlight();
  lcd.print("Hello world");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Value :");
  pinMode(clk, INPUT);
  pinMode(dt, INPUT);
  pinMode(sw, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);// 
  pinMode(A_channel, INPUT_PULLUP);
  pinMode(B_channel, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt( A_channel), interrupt, RISING); 
}

void loop() 
{  int change = getEncoderTurn();
  encoderVal = encoderVal + change;

  val = digitalRead(sw);
    if(val == HIGH && MotorON == LOW){

    pushed = 1-pushed;
    delay(100);
  }    

  MotorON = val;

      if(pushed == HIGH){
        digitalWrite(relay, LOW); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set Length :");
        Serial.println(encoderVal); //print the encoderVal on the serial monitor
        lcd.setCursor(5,1);
        lcd.print(encoderVal);    
  }
       
      else{
        digitalWrite(relay, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MOTOR ON :");
      }     

  delay(100);
}

int getEncoderTurn(void)
{
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(dt);//read the value of clk to newA
  int newB = digitalRead(clk);//read the value of dt to newB
  if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
  {
    // something has changed
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}

void interrupt()
{ char i;
  i = digitalRead( B_channel);
  if (i == 1)
    channel_A += 1;
  else
    channel_B += 1;

if (channel_A == encoderVal*2048)  {
digitalWrite(relay, HIGH);
delay(1000); 
}
}

