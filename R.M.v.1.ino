#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD //address to 0x27 for a 16 chars and 2 line display

//ENCODER KY-040

const int clkPin= 4; //the clk attach to pin2
const int dtPin= 5; //the dt attach to pin3
const int swPin= 6 ;//the number of the button


// RELAY SWITCH

const int relayPin = 8;// Connected to relay (LED)
int val = 0; // push value from pin 4
int MotorON = 0;//light status
int pushed = 0;//push status

//EN500 ENCODER

#define  Z_CHANNEL 2
unsigned int channel_Z = 0;  //Assign a value to the token bit

int encoderVal = 0;
void setup()
{
 
    //ENCODER KY-040
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);

     //EN500 ENCODER  
  pinMode(Z_CHANNEL, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(Z_CHANNEL), interrupt, CHANGE); //Interrupt trigger mode: RISING
 
 //Serial.begin(9600); // initialize serial communications at 9600 bps  
  lcd.begin();  // initialize the lcd
  lcd.backlight();
  lcd.print("DOORNBOS EQUIP.");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set Length :");
  
}


void loop() 
{  
   int change = getEncoderTurn();
    encoderVal = encoderVal + change;

     val = digitalRead(swPin);// read the push button value

  if(val == HIGH && MotorON == LOW)
  {
    pushed = 1-pushed;
    delay(100);
  }    

     MotorON = val;

      if(pushed == HIGH)
      {
        digitalWrite(relayPin, LOW); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set Length :");
       // Serial.println(encoderVal); //print the encoderVal on the serial monitor
        lcd.setCursor(5,1);
        lcd.print(encoderVal);    
      }
      
 else
      {
        digitalWrite(relayPin, HIGH);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("MOTOR ON :");
      }     
    
 if  (channel_Z == encoderVal*2)  
      {
        digitalWrite(relayPin, LOW); 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Set Length :");
       // Serial.println(encoderVal); //print the encoderVal on the serial monitor
        lcd.setCursor(5,1);
        lcd.print(encoderVal);    
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
{ 
 int i = 0;
  i = digitalRead(Z_CHANNEL);
  if (i == 0)
    channel_Z += 1;

}


