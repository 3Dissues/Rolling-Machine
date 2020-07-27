#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD 

//address to 0x27 for a 16 chars and 2 line display

// Rotary Encoder Control

const int clkPin= 2; //the clk attach to pin2

const int dtPin= 3; //the dt attach to pin3

const int swPin= 4 ;//the number of the button

int encoderVal = 0;

const int relayPin = 7;// Connected to relay (LED)
int val = 0; // push value from pin 4
int MotorON = 0;//light status
int pushed = 0;//push status

// Rotary Encoder Measure

#define  A_PHASE 2
#define  B_PHASE 3
unsigned int flag_A = 0;  //Assign a value to the token bit
unsigned int flag_B = 0;  //Assign a value to the token bit


void setup() {
//Serial.begin(9600); // initialize serial communications at 9600 bps  
 lcd.begin();  // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
  lcd.print("DOORNBOS EQUIP.");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Length :");
  //set clkPin,dePin,swPin as INPUT
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);// keep the load OFF at the begining. If you wanted to be ON, change the HIGH to LOW

 // ENCODER MEASURE 

  pinMode(A_PHASE, INPUT_PULLUP);
  pinMode(B_PHASE, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt( A_PHASE), interrupt, RISING); //Interrupt trigger mode: RISING
}

void loop() 
{  int change = getEncoderTurn();
  encoderVal = encoderVal + change;

  val = digitalRead(swPin);// read the push button value

  if(val == HIGH && MotorON == LOW){

    pushed = 1-pushed;
    delay(100);
  }    

  MotorON = val;

      if(pushed == HIGH){
        digitalWrite(relayPin, LOW); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set Length :");
        Serial.println(encoderVal); //print the encoderVal on the serial monitor
        lcd.setCursor(5,1);
        lcd.print(encoderVal);    
  }
       
      else{
        digitalWrite(relayPin, HIGH);
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
  int newA = digitalRead(dtPin);//read the value of clkPin to newA
  int newB = digitalRead(clkPin);//read the value of dtPin to newB
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

void interrupt()// Interrupt function
{ char i;
  i = digitalRead( B_PHASE);
  if (i == 1)
    flag_A += 1;
  else
    flag_B += 1;

}

for flag_A = encoderVal*0; flag_A < encoderVal*2048; flag_A++) { 
digitalWrite(relayPin, HIGH);
delay(1000);  
}
