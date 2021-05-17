// The following code can be used to test the LEDs
// It will work with only one shift register
// The result should be that the LEDs flash at a rate of 0.5Hz

//#include <EEPROM.h>
#include <SPI.h>
//#include <GD2.h>

// LED state array
int LEDS_OFF[8] = {0,0,0,0,0,0,0,0};
int LEDS_ON[8] = {1,1,1,1,1,1,1,1};

// Shift register address pins
// The first set is for the DUE and I'm very confident is correct
// The second one is for the UNO breadboard setup and has to be checked 
// in case the wires have been moved

//#define LED_data 57
//#define LED_shiftclk 58
//#define LED_displayclk 59

#define LED_data 13               // the data pin
#define LED_shiftclk 12           // the serial clock pin
#define LED_displayclk 11         // the register clock pin


void setup(){
    Serial.begin(9600);
    Serial.print("starting LEDs test");
}

//---------MAIN LOOP------------//
void loop(){
    UpdateLeds(LEDS_OFF);         // Set all LEDs to off
    delay(1000);
    UpdateLeds(LEDS_ON);          // Set all LEDs to on
    delay(1000);
}
//----------END OF MAIN LOOP-------------//

// Function to update the LEDs
// The function takes an array of the desired LED values and sends them to the shift register
void UpdateLeds(int data[]){
  
    int i=0;
    int pinState;       //this is the value that is being sent to the shift register
    
    //clear everything out just in case to
    //prepare shift register for bit shifting
    digitalWrite(LED_data, 0);
    digitalWrite(LED_shiftclk, 0);
    
    // The following for loop sweeps through the array of LED states and 
    // sends the apprpriate value to the shift register
    
    for (i=7; i>=0; i--)  {
        digitalWrite(LED_shiftclk, 0);      //set the shift clock to zero

        // Check value inside array and set pinState to corect value
        if (data[i]) {
            pinState= 1;
        }else {
            pinState= 0;
        }
        
        // Sets the pin to HIGH or LOW depending on pinState
        digitalWrite(LED_data, pinState);
        // register shifts bits on upstroke of clock pin
        digitalWrite(LED_shiftclk, 1);
        // zero the data pin after shift to prevent bleed through
        digitalWrite(LED_data, 0);
    }
    //stop shifting
    digitalWrite(LED_shiftclk, 0);
}
