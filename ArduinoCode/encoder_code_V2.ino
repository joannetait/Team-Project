#include <Bounce2.h>

// mux adress pins
#define S0 31
#define S1 29
#define S2 27
#define S3 25

// the input pins (mux's outputs):
#define mux1A 65
#define mux1B 64
#define mux2A 63
#define mux2B 62
#define mux_enable 23

// define encoder button pins (get pin numbers from arduino due schematic and encoders pcb file). undefined buttons for the screen are on pin 37/35/53

#define VCO_BUTTON_PIN 43
#define FM_BUTTON_PIN 39
#define OCT_LVL_BUTTON_PIN 41
#define LFO_BUTTON_PIN 47
#define LFO_MODE_BUTTON_PIN 49
#define ADSR_BUTTON_PIN 51

// instantiate bounce objects
Bounce2::Button VCOButton = Bounce2::Button();
Bounce2::Button FMButton = Bounce2::Button();
Bounce2::Button VCO_OCT_LEVEL_Button = Bounce2::Button();
Bounce2::Button LFOButton = Bounce2::Button();
Bounce2::Button LFO_MODE_Button = Bounce2::Button();
Bounce2::Button ADSRButton = Bounce2::Button();


// Variables to store button states
bool VCO_select = LOW;
bool FM_select = LOW; 
bool VCO1_OCT_LVL_select = LOW; 
bool VCO2_OCT_LVL_select = LOW; 
bool SYNC_select = LOW; 

bool LFO_select = LOW;
bool LFO1_MODE_select = LOW;
bool LFO2_MODE_select = LOW;

bool ADSR_select = LOW;

// Variables to store physical encoder states for all controls 

bool enc_OCTLVL_A;
bool enc_OCTLVL_B;
bool enc_FM_DETUNE_A;
bool enc_FM_DETUNE_B;
bool enc_VCO_PWM_A;
bool enc_VCO_PWM_B;
bool enc_VCO_SHAPE_A;
bool enc_VCO_SHAPE_B;

bool enc_OCTLVL_A_prev;
bool enc_OCTLVL_B_prev;
bool enc_FM_DETUNE_A_prev;
bool enc_FM_DETUNE_B_prev;
bool enc_VCO_PWM_A_prev;
bool enc_VCO_PWM_B_prev;
bool enc_VCO_SHAPE_A_prev;
bool enc_VCO_SHAPE_B_prev;

bool enc_CUTOFF_A_prev;
bool enc_CUTOFF_B_prev;
bool enc_RES_A_prev;
bool enc_RES_B_prev;
bool enc_DRIVE_A_prev;
bool enc_DRIVE_B_prev;

bool enc_CUTOFF_A;
bool enc_CUTOFF_B;
bool enc_RES_A;
bool enc_RES_B;
bool enc_DRIVE_A;
bool enc_DRIVE_B;

bool enc_LFO_FREQ_A;
bool enc_LFO_FREQ_B;
bool enc_lFO_SHAPE_A;
bool enc_LFO_SHAPE_B;
bool enc_LFO_PWM_A;
bool enc_LFO_PWM_B;
bool enc_LFO_AMPLITUDE_A;
bool enc_LFO_AMPLITUDE_B;
bool enc_LFO_OFFSET_A;
bool enc_LFO_OFFSET_B;

bool enc_LFO_FREQ_A_prev;
bool enc_LFO_FREQ_B_prev;
bool enc_lFO_SHAPE_A_prev;
bool enc_LFO_SHAPE_B_prev;
bool enc_LFO_PWM_A_prev;
bool enc_LFO_PWM_B_prev;
bool enc_LFO_AMPLITUDE_A_prev;
bool enc_LFO_AMPLITUDE_B_prev;
bool enc_LFO_OFFSET_A_prev;
bool enc_LFO_OFFSET_B_prev;

bool enc_ADSR_ATTACK_A;
bool enc_ADSR_ATTACK_B;
bool enc_ADSR_DECAY_A;
bool enc_ADSR_DECAY_B;
bool enc_ADSR_SUSTAIN_A;
bool enc_ADSR_SUSTAIN_B;
bool enc_ADSR_RELEASE_A;
bool enc_ADSR_RELEASE_B;

bool enc_ADSR_ATTACK_A_prev;
bool enc_ADSR_ATTACK_B_prev;
bool enc_ADSR_DECAY_A_prev;
bool enc_ADSR_DECAY_B_prev;
bool enc_ADSR_SUSTAIN_A_prev;
bool enc_ADSR_SUSTAIN_B_prev;
bool enc_ADSR_RELEASE_A_prev;
bool enc_ADSR_RELEASE_B_prev;

//initialise parameter positions and previous positions
    
int VCO1_OCT_position  = 0;
int VCO1_LVL_position  = 0;
int VCO1_FM_AMOUNT_position  = 0;
int VCO1_SHAPE_position  = 0;
int VCO1_PWM_position  = 0;
    
int VCO1_OCT_position_prev  = 0;
int VCO1_LVL_position_prev  = 0;
int VCO1_FM_AMOUNT_position_prev  = 0;
int VCO1_SHAPE_position_prev  = 0;
int VCO1_PWM_position_prev  = 0;

int VCO2_OCT_position  = 0;
int VCO2_LVL_position  = 0;
int VCO2_DETUNE_position  = 0;
int VCO2_SHAPE_position  = 0;
int VCO2_PWM_position  = 0;

int VCO2_OCT_position_prev = 0;
int VCO2_LVL_position_prev  = 0;
int VCO2_DETUNE_position_prev  = 0;
int VCO2_SHAPE_position_prev  = 0;
int VCO2_PWM_position_prev  = 0;

int VCF_CUTOFF_position  = 0;
int VCF_Q_position  = 0;
int VCF_DRIVE_position  = 0;

int VCF_CUTOFF_position_prev  = 0;
int VCF_Q_position_prev  = 0;
int VCF_DRIVE_position_prev  = 0;   

int LFO1_FREQ_position  = 0;
int LFO1_SHAPE_position  = 0;
int LFO1_PWM_position  = 0;
int LFO1_AMPLITUDE_position  = 0;
int LFO1_OFFSET_position  = 0;

int LFO1_FREQ_position_prev  = 0;
int LFO1_SHAPE_position_prev  = 0;
int LFO1_PWM_position_prev  = 0;
int LFO1_AMPLITUDE_position_prev  = 0;
int LFO1_OFFSET_position_prev  = 0;

int LFO2_FREQ_position  = 0;
int LFO2_SHAPE_position  = 0;
int LFO2_PWM_position  = 0;
int LFO2_AMPLITUDE_position  = 0;
int LFO2_OFFSET_position  = 0;

int LFO2_FREQ_position_prev  = 0;
int LFO2_SHAPE_position_prev  = 0;
int LFO2_PWM_position_prev  = 0;
int LFO2_AMPLITUDE_position_prev  = 0;
int LFO2_OFFSET_position_prev  = 0;

int ADSR1_ATTACK_position  = 0;
int ADSR1_DECAY_position  = 0;
int ADSR1_SUSTAIN_position  = 0;
int ADSR1_RELEASE_position  = 0;

int ADSR1_ATTACK_position_prev  = 0;
int ADSR1_DECAY_position_prev  = 0;
int ADSR1_SUSTAIN_position_prev = 0;
int ADSR1_RELEASE_position_prev  = 0;

int ADSR2_ATTACK_position  = 0;
int ADSR2_DECAY_position  = 0;
int ADSR2_SUSTAIN_position  = 0;
int ADSR2_RELEASE_position  = 0;

int ADSR2_ATTACK_position_prev  = 0;
int ADSR2_DECAY_position_prev  = 0;
int ADSR2_SUSTAIN_position_prev  = 0;
int ADSR2_RELEASE_position_prev  = 0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
    // initialise all the encoder buttons to their physical pins, check every 10ms, eventually try to make that 10ms as big as possible without responsitivity loss. 
    
    VCOButton.attach(VCO_BUTTON_PIN,INPUT_PULLUP);
    VCOButton.interval(10);

    FMButton.attach(FM_BUTTON_PIN,INPUT_PULLUP);
    FMButton.interval(10);

    VCO_OCT_LEVEL_Button.attach(OCT_LVL_BUTTON_PIN,INPUT_PULLUP);
    VCO_OCT_LEVEL_Button.interval(10);
    
    LFOButton.attach(LFO_BUTTON_PIN,INPUT_PULLUP);
    LFOButton.interval(10);

    LFO_MODE_Button.attach(LFO_MODE_BUTTON_PIN,INPUT_PULLUP);
    LFO_MODE_Button.interval(10);
    
    ADSRButton.attach(ADSR_BUTTON_PIN,INPUT_PULLUP);
    ADSRButton.interval(10);

    // Buttons are pressed when pin reads LOW voltage
    VCOButton.setPressedState(LOW); 
    FMButton.setPressedState(LOW); 
    VCO_OCT_LEVEL_Button.setPressedState(LOW); 
    LFOButton.setPressedState(LOW); 
    LFO_MODE_Button.setPressedState(LOW); 
    ADSRButton.setPressedState(LOW); 

    // set multiplexer pins modes. mux_enable always stays low, initialise muxs to their 1st position.
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    digitalWrite(S0,LOW); 
    digitalWrite(S1,LOW); 
    digitalWrite(S2,LOW); 
    digitalWrite(S3,LOW); 
    
    pinMode(mux1A, INPUT); //all encoders that directly control the synth are on mux1, encoders used with the screen are on mux2 
    pinMode(mux1B, INPUT);
    pinMode(mux2A, INPUT);
    pinMode(mux2B, INPUT);

    pinMode(mux_enable, OUTPUT);
    digitalWrite( mux_enable, LOW ); 
    
    // initialise debug serial coms
    Serial.begin(9600);
    Serial.println("Multiplexed Encoder Test:");
    


}

void loop() {
    //update all buttons and accroding states, still to write to the according LEDs through shift registers 
  
  VCOButton.update(); 
  if ( VCOButton.pressed()) {
    VCO_select = !VCO_select;
  }
  
  FMButton.update();  
  if ( FMButton.pressed()) {
    if (VCO_select = LOW) { // button controls wheter fm is linear or exponential  
      FM_select = !FM_select;
      //send change to teensy to switch CD4066 from exp to lin fm or vice versa
      }
    if (VCO_select = HIGH) { // button controls wether we sync VCO2 to 1
      SYNC_select = !SYNC_select;
      //send change to teensy to switch CD4066 SYNC ON or OFF 
      }
  }
  VCO_OCT_LEVEL_Button.update(); 
  if ( VCO_OCT_LEVEL_Button.pressed()) {
    VCO1_OCT_LVL_select = !VCO1_OCT_LVL_select;
  }
  
  LFOButton.update(); 
  if ( LFOButton.pressed()) {
    LFO_select = !LFO_select;
  }
  
  LFO_MODE_Button.update(); 
  if ( LFO_MODE_Button.pressed()) {
    if ( LFO_select == LOW){ //button controls LFO1 mode
      LFO1_MODE_select = !LFO1_MODE_select;
      //send change to teensy
    }
    if ( LFO_select == HIGH ){ //button controls LFO1 mode
      LFO2_MODE_select = !LFO2_MODE_select;   
      //send change to teensy
    }
  }
  ADSRButton.update(); 
  if ( ADSRButton.pressed()) {
    ADSR_select = !ADSR_select;
  }
  
  updateEncoders();
  
  //add GAMEDUINO code so that updateEncoder function gets called regularly (100Hz or so), buttons need to be updated before calling the updateEncoder function.

} //end Main loop


void updateEncoders() { //runs through all the encoders 

  digitalWrite(S0, LOW);  // adress 0000 is the octave/oscillator level encoder (get that from cheking encoder schematic and pcb file 
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
 
  if (VCO_select == LOW) { //encoders control VCO1
    if (VCO1_OCT_LVL_select == LOW) { //encoder controls octave number
      VCO1_OCT_position_prev = VCO1_OCT_position;  
      
      getPosition(enc_OCTLVL_A, enc_OCTLVL_B, enc_OCTLVL_A_prev, enc_OCTLVL_B_prev, VCO1_OCT_position, mux1A, mux1B); //get new position
      
      if ( VCO1_OCT_position > 5 ) { //boundary check
        VCO1_OCT_position = 5;
      }
      if ( VCO1_OCT_position < 0 ) {
        VCO1_OCT_position = 0;
      }
      
      if (VCO1_OCT_position != VCO1_OCT_position_prev){
        //send change to teensy
      }
    }

    if (VCO1_OCT_LVL_select == HIGH) { //encoder controls VCO1 volume
      VCO1_LVL_position_prev = VCO1_LVL_position;
      
      getPosition(enc_OCTLVL_A, enc_OCTLVL_B, enc_OCTLVL_A_prev, enc_OCTLVL_B_prev,VCO1_LVL_position, mux1A, mux1B); //get new position
      
      if ( VCO1_LVL_position > 127 ) { //boundary check
        VCO1_LVL_position = 127;
      }
      if ( VCO1_LVL_position < 0 ) {
        VCO1_LVL_position = 0;
      }
      
      if (VCO1_LVL_position != VCO1_LVL_position_prev){
        //send change to teensy
      }
    }
  }
  if (VCO_select == HIGH) { //encoders control VCO2
    if (VCO2_OCT_LVL_select == LOW) { //encoder controls octave number
      VCO2_OCT_position_prev = VCO2_OCT_position;
      
      getPosition(enc_OCTLVL_A, enc_OCTLVL_B, enc_OCTLVL_A_prev, enc_OCTLVL_B_prev, VCO2_OCT_position, mux1A, mux1B); //get new position
      
      if ( VCO2_OCT_position > 5 ) { //boundary check
        VCO2_OCT_position = 5;
      }
      if ( VCO2_OCT_position < 0 ) {
        VCO2_OCT_position = 0;
      }
      
      if (VCO2_OCT_position != VCO2_OCT_position_prev){
        //send change to teensy
      }
    }

    if (VCO2_OCT_LVL_select == HIGH) { //encoder controls VCO1 volume
      VCO2_LVL_position_prev = VCO2_LVL_position;
      
      getPosition(enc_OCTLVL_A, enc_OCTLVL_B, enc_OCTLVL_A_prev, enc_OCTLVL_B_prev, VCO2_LVL_position, mux1A, mux1B); //get new position
      
      if ( VCO2_LVL_position > 127 ) { //boundary check
        VCO2_LVL_position = 127;
      }
      if ( VCO2_LVL_position < 0 ) {
        VCO2_LVL_position = 0;
      }
      
      if (VCO2_LVL_position != VCO2_LVL_position_prev){
        //send change to teensy
      }
    }   
 }


/////////////////////////////////////////////////////////////    
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

///////////////////////////////////////////////////////////// 
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  

/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);

/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

//////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);

/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);

/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
   
}

void getPosition(bool encA,bool encB,bool encA_prev,bool encB_prev, int param_position,int muxA,int muxB) {  //send the parameter virtual pin names, their previous position, the parameter current value and
                                                                                   //the multiplexer pins on which the physical encoder is, "returns" the new parameter position.
                                                                                    
      encA = digitalRead(muxA); //reads encoder physical position, make sure the multiplexer is set accordingly before calling function.
      encB = digitalRead(muxB); 
                                                                                       
      if (encA != encA_prev && encB == encB_prev){      //state machine begin
        if (encB == encA) {                             //test changes when pinA has changed
          param_position++;
        }
        else{
          param_position--;  
        }
      }
    
    if (encB != encB_prev && encA == encA_prev){
      if (encA == encB) {                    //test changes when pinB has changed
        param_position--;
      }
      else{
        param_position++;  
      }
    }                                                  //state machine end
    encA_prev = encA;                                  //update virtual encoder pin previous positions
    encB_prev = encB; 
}
