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

// Variables to indicate which lfo/adsr amounts 
bool dest1_select = LOW;
bool dest2_select = LOW;
bool dest3_select = LOW;
bool dest4_select = LOW;
bool dest5_select = LOW;
bool dest6_select = LOW;
bool dest7_select = LOW;
bool dest8_select = LOW;
bool dest9_select = LOW;
bool dest10_select = LOW;
bool dest11_select = LOW;
bool dest12_select = LOW;

// Variables to store physical encoder states for all controls still to add lfo amounts 

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

bool enc_LFO_FREQRATE_A;
bool enc_LFO_FREQRATE_B;
bool enc_LFO_SHAPE_A;
bool enc_LFO_SHAPE_B;
bool enc_LFO_PWM_A;
bool enc_LFO_PWM_B;
bool enc_LFO_AMPLITUDE_A;
bool enc_LFO_AMPLITUDE_B;
bool enc_LFO_OFFSET_A;
bool enc_LFO_OFFSET_B;

bool enc_LFO_FREQRATE_A_prev;
bool enc_LFO_FREQRATE_B_prev;
bool enc_LFO_SHAPE_A_prev;
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

bool enc_TOP_LEFT_A;
bool enc_TOP_LEFT_B;
bool enc_BOTTOM_LEFT_A;
bool enc_BOTTOM_LEFT_B;
bool enc_TOP_RIGHT_A;
bool enc_TOP_RIGHT_B;
bool enc_BOTTOM_RIGHT_A;
bool enc_BOTTOM_RIGHT_B;

bool enc_TOP_LEFT_A_prev;
bool enc_TOP_LEFT_B_prev;
bool enc_BOTTOM_LEFT_A_prev;
bool enc_BOTTOM_LEFT_B_prev;
bool enc_TOP_RIGHT_A_prev;
bool enc_TOP_RIGHT_B_prev;
bool enc_BOTTOM_RIGHT_A_prev;
bool enc_BOTTOM_RIGHT_B_prev;

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

int CUTOFF_position  = 0;
int RES_position  = 0;
int DRIVE_position  = 0;

int CUTOFF_position_prev  = 0;
int RES_position_prev  = 0;
int DRIVE_position_prev  = 0;   

int LFO1_FREQ_position  = 0;
int LFO1_RATE_position =0;
int LFO1_SHAPE_position  = 0;
int LFO1_PWM_position  = 0;
int LFO1_AMPLITUDE_position  = 0;
int LFO1_OFFSET_position  = 0;

int LFO1_FREQ_position_prev  = 0;
int LFO1_RATE_position_prev =0;
int LFO1_SHAPE_position_prev  = 0;
int LFO1_PWM_position_prev  = 0;
int LFO1_AMPLITUDE_position_prev  = 0;
int LFO1_OFFSET_position_prev  = 0;

int LFO2_FREQ_position  = 0;
int LFO2_RATE_position =0;
int LFO2_SHAPE_position  = 0;
int LFO2_PWM_position  = 0;
int LFO2_AMPLITUDE_position  = 0;
int LFO2_OFFSET_position  = 0;

int LFO2_FREQ_position_prev  = 0;
int LFO2_RATE_position_prev =0;
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

int LFO1_DEST1_position =0; 
int LFO2_DEST1_position =0; 
int ADSR1_DEST1_position =0; 
int ADSR2_DEST1_position =0; 

int LFO1_DEST1_position_prev =0; 
int LFO2_DEST1_position_prev =0; 
int ADSR1_DEST1_position_prev =0; 
int ADSR2_DEST1_position_prev =0; 

int LFO1_DEST2_position =0; 
int LFO2_DEST2_position =0; 
int ADSR1_DEST2_position =0; 
int ADSR2_DEST2_position =0; 

int LFO1_DEST2_position_prev =0; 
int LFO2_DEST2_position_prev =0; 
int ADSR1_DEST2_position_prev =0; 
int ADSR2_DEST2_position_prev =0; 

int LFO1_DEST3_position =0; 
int LFO2_DEST3_position =0; 
int ADSR1_DEST3_position =0; 
int ADSR2_DEST3_position =0; 

int LFO1_DEST3_position_prev =0; 
int LFO2_DEST3_position_prev =0; 
int ADSR1_DEST3_position_prev =0; 
int ADSR2_DEST3_position_prev =0; 

int LFO1_DEST4_position =0; 
int LFO2_DEST4_position =0; 
int ADSR1_DEST4_position =0; 
int ADSR2_DEST4_position =0; 

int LFO1_DEST4_position_prev =0; 
int LFO2_DEST4_position_prev =0; 
int ADSR1_DEST4_position_prev =0; 
int ADSR2_DEST4_position_prev =0; 

int LFO1_DEST5_position =0; 
int LFO2_DEST5_position =0; 
int ADSR1_DEST5_position =0; 
int ADSR2_DEST5_position =0; 

int LFO1_DEST5_position_prev =0; 
int LFO2_DEST5_position_prev =0; 
int ADSR1_DEST5_position_prev =0; 
int ADSR2_DEST5_position_prev =0; 

int LFO1_DEST6_position =0; 
int LFO2_DEST6_position =0; 
int ADSR1_DEST6_position =0; 
int ADSR2_DEST6_position =0; 

int LFO1_DEST6_position_prev =0; 
int LFO2_DEST6_position_prev =0; 
int ADSR1_DEST6_position_prev =0; 
int ADSR2_DEST6_position_prev =0; 

int LFO1_DEST7_position =0; 
int LFO2_DEST7_position =0; 
int ADSR1_DEST7_position =0; 
int ADSR2_DEST7_position =0; 

int LFO1_DEST7_position_prev =0; 
int LFO2_DEST7_position_prev =0; 
int ADSR1_DEST7_position_prev =0; 
int ADSR2_DEST7_position_prev =0; 

int LFO1_DEST8_position =0; 
int LFO2_DEST8_position =0; 
int ADSR1_DEST8_position =0; 
int ADSR2_DEST8_position =0; 

int LFO1_DEST8_position_prev =0; 
int LFO2_DEST8_position_prev =0; 
int ADSR1_DEST8_position_prev =0; 
int ADSR2_DEST8_position_prev =0; 

int LFO1_DEST9_position =0; 
int LFO2_DEST9_position =0; 
int ADSR1_DEST9_position =0; 
int ADSR2_DEST9_position =0; 

int LFO1_DEST9_position_prev =0; 
int LFO2_DEST9_position_prev =0; 
int ADSR1_DEST9_position_prev =0; 
int ADSR2_DEST9_position_prev =0; 

int LFO1_DEST10_position =0; 
int LFO2_DEST10_position =0; 
int ADSR1_DEST10_position =0; 
int ADSR2_DEST10_position =0; 

int LFO1_DEST10_position_prev =0; 
int LFO2_DEST10_position_prev =0; 
int ADSR1_DEST10_position_prev =0; 
int ADSR2_DEST10_position_prev =0; 

int LFO1_DEST11_position =0; 
int LFO2_DEST11_position =0; 
int ADSR1_DEST11_position =0; 
int ADSR2_DEST11_position =0; 

int LFO1_DEST11_position_prev =0; 
int LFO2_DEST11_position_prev =0; 
int ADSR1_DEST11_position_prev =0; 
int ADSR2_DEST11_position_prev =0; 

int LFO1_DEST12_position =0; 
int LFO2_DEST12_position =0; 
int ADSR1_DEST12_position =0; 
int ADSR2_DEST12_position =0; 

int LFO1_DEST12_position_prev =0; 
int LFO2_DEST12_position_prev =0; 
int ADSR1_DEST12_position_prev =0; 
int ADSR2_DEST12_position_prev =0; 

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
    Serial3.begin(9600);
    


}

void loop() {
    updateEncoders();
    //add GAMEDUINO code so that updateEncoder function gets called regularly (100Hz or so)
}   //end Main loop


void updateEncoders() { //runs through all the encoders 
    //update all physical buttons and accroding states, still to write to the according LEDs through shift registers 
  
    VCOButton.update(); 
    if ( VCOButton.pressed()) {
        VCO_select = !VCO_select;
    }
  
    FMButton.update();  
    if ( FMButton.pressed()) {
        if (VCO_select = LOW) { // button controls wheter fm is linear or exponential  
            FM_select = !FM_select;
            //send change to teensy to switch CD4066 from exp to lin fm or vice versa
            ///////////////////////////////////////////////////////////
        }
        if (VCO_select = HIGH) { // button controls wether we sync VCO2 to 1
            SYNC_select = !SYNC_select;
            //send change to teensy to switch CD4066 SYNC ON or OFF 
            /////////////////////////////////////////////////////////
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
            transmitVal(100,LFO1_MODE_select,0);
        }
        if ( LFO_select == HIGH ){ //button controls LFO1 mode
            LFO2_MODE_select = !LFO2_MODE_select;   
            //send change to teensy
            transmitVal(110,LFO2_MODE_select,0);
        }
    }
    
    ADSRButton.update(); 
    if ( ADSRButton.pressed()) {
        ADSR_select = !ADSR_select;
    }

    ///////////MULTI ON PIN 0: CONTROLS VCO OCT AND LVL//////////////////////////////////////////////////     
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
                ////////////////////////////////////////////////////////////////
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
                //////////////////////////////////////////////////
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
                //////////////////////////////////////////////////
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
                /////////////////////////////////////////////////////
            }
        }   
    }
    if (dest1_select == HIGH) {
        LFO1_DEST1_position_prev = LFO1_DEST1_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST1_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST1_position > 100 ) { //boundary check
            LFO1_DEST1_position = 100;
            }
        if ( LFO1_DEST1_position < -100 ) {
            LFO1_DEST1_position = -100;
            }
            
        if (LFO1_DEST1_position != LFO1_DEST1_position_prev){
        //send change to teensy (lfo1 amount to vco 1 pitch bend dac) ID_DAC2_LFO1_AMOUNT
            byte LFO1_DEST1_pos = (byte)(LFO1_DEST1_position + 100);
            transmitVal(136, LFO1_DEST1_pos, 0);
               }        
    }
    if (dest2_select == HIGH) {
        LFO1_DEST2_position_prev = LFO1_DEST2_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST2_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST2_position > 100 ) { //boundary check
            LFO1_DEST2_position = 100;
            }
        if ( LFO1_DEST2_position < -100 ) {
            LFO1_DEST2_position = -100;
            }
            
        if (LFO1_DEST2_position != LFO1_DEST2_position_prev){
        //send change to teensy (lfo1 amount to vco 1 PWM dac) ID_DAC5_LFO1_AMOUNT
            byte LFO1_DEST2_pos = (byte)(LFO1_DEST2_position + 100);
            transmitVal(148, LFO1_DEST2_pos, 0);
            }        
    }
    if (dest3_select == HIGH) {
        LFO1_DEST3_position_prev = LFO1_DEST3_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST3_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST3_position > 100 ) { //boundary check
            LFO1_DEST3_position = 100;
            }
        if ( LFO1_DEST3_position < -100 ) {
            LFO1_DEST3_position = -100;
            }
            
        if (LFO1_DEST3_position != LFO1_DEST3_position_prev){
        //send change to teensy (lfo1 amount to vco 1 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer) ID_DAC9_LFO1_AMOUNT??
            byte LFO1_DEST3_pos = (byte)(LFO1_DEST3_position + 100);
            transmitVal(164, LFO1_DEST3_pos, 0); //is this the right DAC?
        }        
    }
    if (dest4_select == HIGH) {
        LFO1_DEST4_position_prev = LFO1_DEST4_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST4_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST4_position > 100 ) { //boundary check
            LFO1_DEST4_position = 100;
            }
        if ( LFO1_DEST4_position < -100 ) {
            LFO1_DEST4_position = -100;
            }
            
        if (LFO1_DEST4_position != LFO1_DEST4_position_prev){
        //send change to teensy (lfo1 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer)
        //////////////////////////////////////////////////////////////////////////
            byte LFO1_DEST4_pos = (byte)(LFO1_DEST4_position + 100);
            transmitVal(ID, LFO1_DEST4_pos, 0); //TODO ID
        }        
    }
    if (dest5_select == HIGH) {
        LFO1_DEST5_position_prev = LFO1_DEST5_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST5_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST5_position > 100 ) { //boundary check
            LFO1_DEST5_position = 100;
            }
        if ( LFO1_DEST5_position < -100 ) {
            LFO1_DEST5_position = -100;
            }
            
        if (LFO1_DEST5_position != LFO1_DEST5_position_prev){
        //send change to teensy (lfo1 amount to vco 2 pitch bend dac) ID_DAC4_LFO1_AMOUNT 
            byte LFO1_DEST5_pos = (byte)(LFO1_DEST5_position + 100);
            transmitVal(144, LFO1_DEST4_pos, 0);
        }        
    }
    if (dest6_select == HIGH) {
        LFO1_DEST6_position_prev = LFO1_DEST6_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST6_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST6_position > 100 ) { //boundary check
            LFO1_DEST6_position = 100;
            }
        if ( LFO1_DEST6_position < -100 ) {
            LFO1_DEST6_position = -100;
            }
            
        if (LFO1_DEST6_position != LFO1_DEST6_position_prev){
        //send change to teensy (lfo1 amount to vco 2 PWM dac) ID_DAC6_LFO1_AMOUNT
            byte LFO1_DEST6_pos = (byte)(LFO1_DEST6_position + 100);
            transmitVal(152, LFO1_DEST6_pos, 0);
        }        
    }
    if (dest7_select == HIGH) {
        LFO1_DEST7_position_prev = LFO1_DEST7_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST7_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST7_position > 100 ) { //boundary check
            LFO1_DEST7_position = 100;
            }
        if ( LFO1_DEST7_position < -100 ) {
            LFO1_DEST7_position = -100;
            }
            
        if (LFO1_DEST7_position != LFO1_DEST7_position_prev){
        //send change to teensy (lfo1 amount to vco 2 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
        ///////////////////////////////////////
            byte LFO1_DEST7_pos = (byte)(LFO1_DEST7_position + 100);
            transmitVal(ID, LFO1_DEST7_pos, 0); //TODO ID
        }        
    }
    if (dest8_select == HIGH) {
        LFO1_DEST8_position_prev = LFO1_DEST8_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST8_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST8_position > 100 ) { //boundary check
            LFO1_DEST8_position = 100;
            }
        if ( LFO1_DEST8_position < -100 ) {
            LFO1_DEST8_position = -100;
            }
            
        if (LFO1_DEST8_position != LFO1_DEST8_position_prev){
        //send change to teensy (lfo1 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer)
        //////////////////////////////////////
            byte LFO1_DEST8_pos = (byte)(LFO1_DEST8_position + 100);
            transmitVal(ID, LFO1_DEST8_pos, 0); //TODO ID
        }        
    }
    if (dest9_select == HIGH) {
        LFO1_DEST9_position_prev = LFO1_DEST9_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST9_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST9_position > 100 ) { //boundary check
            LFO1_DEST9_position = 100;
            }
        if ( LFO1_DEST9_position < -100 ) {
            LFO1_DEST9_position = -100;
            }
            
        if (LFO1_DEST9_position != LFO1_DEST9_position_prev){
        //send change to teensy (lfo1 amount to FM level)
        //////////////////////////////////////////////////////
            byte LFO1_DEST9_pos = (byte)(LFO1_DEST9_position + 100);
            transmitVal(ID, LFO1_DEST9_pos, 0); //TODO ID        
               }        
    }    
    if (dest10_select == HIGH) {
        LFO1_DEST10_position_prev = LFO1_DEST10_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST10_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST10_position > 100 ) { //boundary check
            LFO1_DEST10_position = 100;
            }
        if ( LFO1_DEST10_position < -100 ) {
            LFO1_DEST10_position = -100;
            }
            
        if (LFO1_DEST10_position != LFO1_DEST10_position_prev){
        //send change to teensy (lfo1 amount to cutoff) ID_DAC8_LFO1_AMOUNT 
            byte LFO1_DEST10_pos = (byte)(LFO1_DEST10_position + 100);
            transmitVal(160, LFO1_DEST10_pos, 0); 

        }        
    }
    if (dest11_select == HIGH) {
        LFO1_DEST11_position_prev = LFO1_DEST11_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST11_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST11_position > 100 ) { //boundary check
            LFO1_DEST11_position = 100;
            }
        if ( LFO1_DEST11_position < -100 ) {
            LFO1_DEST11_position = -100;
            }
            
        if (LFO1_DEST11_position != LFO1_DEST11_position_prev){
        //send change to teensy (lfo1 amount to resonance) ID_DAC7_LFO1_AMOUNT 
            byte LFO1_DEST11_pos = (byte)(LFO1_DEST11_position + 100);
            transmitVal(156, LFO1_DEST11_pos, 0);
        }        
    }
    if (dest12_select == HIGH) {
        LFO1_DEST12_position_prev = LFO1_DEST12_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST12_position, mux2A, mux2B); //get new position

        if ( LFO1_DEST12_position > 100 ) { //boundary check
            LFO1_DEST12_position = 100;
            }
        if ( LFO1_DEST12_position < -100 ) {
            LFO1_DEST12_position = -100;
            }
            
        if (LFO1_DEST12_position != LFO1_DEST12_position_prev){
        //send change to teensy (lfo1 amount to drive)
            byte LFO1_DEST12_pos = (byte)(LFO1_DEST12_position + 100);
            transmitVal(ID, LFO1_DEST10_pos, 0); //TODO ID
        }        
    }
    ///////////MULTI ON PIN 1: CONTROLS CUTOFF//////////////////////////////////////////////////    
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW); //Pin 2 is always on VCF cutoff

    CUTOFF_position_prev = CUTOFF_position;      
    getPosition(enc_CUTOFF_A, enc_CUTOFF_B, enc_CUTOFF_A_prev, enc_CUTOFF_B_prev, CUTOFF_position, mux1A, mux1B); //get new position   
    if ( CUTOFF_position > 127 ) { //boundary check
        CUTOFF_position = 127;
        }
    if ( CUTOFF_position < 0 ) {
        VCO1_OCT_position = 0;
        }        
    if (CUTOFF_position != CUTOFF_position_prev){
        //send change to teensy
        byte CUTOFF_pos = (byte)CUTOFF_position;
        transmitVal(ID, CUTOFF_pos, 0); //TODO ID 
    }
    if (dest1_select == HIGH) {
        LFO2_DEST1_position_prev = LFO2_DEST1_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST1_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST1_position > 100 ) { //boundary check
            LFO2_DEST1_position = 100;
            }
        if ( LFO2_DEST1_position < -100 ) {
            LFO2_DEST1_position = -100;
            }
            
        if (LFO2_DEST1_position != LFO2_DEST1_position_prev){
        //send change to teensy (lfo2 amount to vco 1 pitch bend dac) ID_DAC2_LFO2_AMOUNT 
            byte LFO2_DEST1_pos = (byte)(LFO2_DEST1_position + 100);
            transmitVal(137, LFO2_DEST1_pos, 0); 
        }        
    }

    if (dest2_select == HIGH) {
        LFO2_DEST2_position_prev = LFO2_DEST2_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST2_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST2_position > 100 ) { //boundary check
            LFO2_DEST2_position = 100;
            }
        if ( LFO2_DEST2_position < -100 ) {
            LFO2_DEST2_position = -100;
            }
            
        if (LFO2_DEST2_position != LFO2_DEST2_position_prev){
        //send change to teensy (lfo2 amount to vco 1 PWM dac) ID_DAC6_LFO2_AMOUNT 
            byte LFO2_DEST2_pos = (byte)(LFO2_DEST2_position + 100);
            transmitVal(153, LFO2_DEST2_pos, 0); 
        }        
    }
    if (dest3_select == HIGH) {
        LFO2_DEST3_position_prev = LFO2_DEST3_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST3_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST3_position > 100 ) { //boundary check
            LFO2_DEST3_position = 100;
            }
        if ( LFO2_DEST3_position < -100 ) {
            LFO2_DEST3_position = -100;
            }
            
        if (LFO2_DEST3_position != LFO2_DEST3_position_prev){
        //send change to teensy (lfo2 amount to vco 1 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
            byte LFO2_DEST3_pos = (byte)(LFO2_DEST3_position + 100);
            transmitVal(ID, LFO2_DEST3_pos, 0); //TODO ID
        }        
    }

    if (dest4_select == HIGH) {
        LFO2_DEST4_position_prev = LFO2_DEST4_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST4_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST4_position > 100 ) { //boundary check
            LFO2_DEST4_position = 100;
            }
        if ( LFO2_DEST4_position < -100 ) {
            LFO2_DEST4_position = -100;
            }
            
        if (LFO2_DEST4_position != LFO2_DEST4_position_prev){
        //send change to teensy (lfo2 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer)
            byte LFO2_DEST4_pos = (byte)(LFO2_DEST4_position + 100);
            transmitVal(ID, LFO2_DEST4_pos, 0); //TODO ID       
       }        
    }
    if (dest5_select == HIGH) {
        LFO2_DEST5_position_prev = LFO2_DEST5_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST5_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST5_position > 100 ) { //boundary check
            LFO2_DEST5_position = 100;
            }
        if ( LFO2_DEST5_position < -100 ) {
            LFO2_DEST5_position = -100;
            }
            
        if (LFO2_DEST5_position != LFO2_DEST5_position_prev){
        //send change to teensy (lfo2 amount to vco 2 pitch bend dac) ID_DAC4_LFO2_AMOUNT 
            byte LFO2_DEST5_pos = (byte)(LFO2_DEST5_position + 100);
            transmitVal(145, LFO2_DEST5_pos, 0);           

        }        
    }
    if (dest6_select == HIGH) {
        LFO2_DEST6_position_prev = LFO2_DEST6_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST6_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST6_position > 100 ) { //boundary check
            LFO2_DEST6_position = 100;
            }
        if ( LFO2_DEST6_position < -100 ) {
            LFO2_DEST6_position = -100;
            }
            
        if (LFO2_DEST6_position != LFO2_DEST6_position_prev){
        //send change to teensy (lfo2 amount to vco 2 PWM dac) ID_DAC6_LFO2_AMOUNT 
            byte LFO2_DEST6_pos = (byte)(LFO2_DEST6_position + 100);
            transmitVal(153, LFO2_DEST6_pos, 0);           
        }        
    }
    if (dest7_select == HIGH) {
        LFO2_DEST7_position_prev = LFO2_DEST7_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST7_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST7_position > 100 ) { //boundary check
            LFO2_DEST7_position = 100;
            }
        if ( LFO2_DEST7_position < -100 ) {
            LFO2_DEST7_position = -100;
            }
            
        if (LFO2_DEST7_position != LFO2_DEST7_position_prev){
        //send change to teensy (lfo2 amount to vco 2 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
            byte LFO2_DEST7_pos = (byte)(LFO2_DEST7_position + 100);
            transmitVal(ID, LFO2_DEST7_pos, 0); //TODO ID 
        }        
    }
    if (dest8_select == HIGH) {
        LFO2_DEST8_position_prev = LFO2_DEST8_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST8_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST8_position > 100 ) { //boundary check
            LFO2_DEST8_position = 100;
            }
        if ( LFO2_DEST8_position < -100 ) {
            LFO2_DEST8_position = -100;
            }
            
        if (LFO2_DEST8_position != LFO2_DEST8_position_prev){
        //send change to teensy (lfo2 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer)
        }        
    }
    if (dest9_select == HIGH) {
        LFO2_DEST9_position_prev = LFO2_DEST9_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST9_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST9_position > 100 ) { //boundary check
            LFO2_DEST9_position = 100;
            }
        if ( LFO2_DEST9_position < -100 ) {
            LFO2_DEST9_position = -100;
            }
            
        if (LFO2_DEST9_position != LFO2_DEST9_position_prev){
        //send change to teensy (lfo2 amount to FM level)
            byte LFO2_DEST9_pos = (byte)(LFO2_DEST9_position + 100);
            transmitVal(ID, LFO2_DEST9_pos, 0); //TODO ID 
        }        
    }    
    if (dest10_select == HIGH) {
        LFO2_DEST10_position_prev = LFO2_DEST10_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST10_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST10_position > 100 ) { //boundary check
            LFO2_DEST10_position = 100;
            }
        if ( LFO2_DEST10_position < -100 ) {
            LFO2_DEST10_position = -100;
            }
            
        if (LFO2_DEST10_position != LFO2_DEST10_position_prev){
        //send change to teensy (lfo2 amount to cutoff) ID_DAC8_LFO2_AMOUNT 
            byte LFO2_DEST10_pos = (byte)(LFO2_DEST10_position + 100);
            transmitVal(161, LFO2_DEST10_pos, 0);  

        }        
    }
    if (dest11_select == HIGH) {
        LFO2_DEST11_position_prev = LFO2_DEST11_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST11_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST11_position > 100 ) { //boundary check
            LFO2_DEST11_position = 100;
            }
        if ( LFO2_DEST11_position < -100 ) {
            LFO2_DEST11_position = -100;
            }
            
        if (LFO2_DEST11_position != LFO2_DEST11_position_prev){
        //send change to teensy (lfo2 amount to resonance) ID_DAC7_LFO2_AMOUNT 
            byte LFO2_DEST11_pos = (byte)(LFO2_DEST11_position + 100); 
            transmitVal(157, LFO2_DEST11_pos, 0);          
        }        
    }
    if (dest12_select == HIGH) {
        LFO2_DEST12_position_prev = LFO2_DEST12_position;
        getPosition(enc_TOP_RIGHT_A, enc_TOP_RIGHT_B, enc_TOP_RIGHT_A_prev, enc_TOP_RIGHT_B_prev, LFO2_DEST12_position, mux2A, mux2B); //get new position

        if ( LFO2_DEST12_position > 100 ) { //boundary check
            LFO2_DEST12_position = 100;
            }
        if ( LFO2_DEST12_position < -100 ) {
            LFO2_DEST12_position = -100;
            }
            
        if (LFO2_DEST12_position != LFO2_DEST12_position_prev){
        //send change to teensy (lfo2 amount to drive)
            byte LFO2_DEST12_pos = (byte)(LFO2_DEST12_position + 100); 
            transmitVal(ID, LFO2_DEST12_pos, 0); //TODO ID  
        }        
    }

    ///////////MULTI ON PIN 2: CONTROLS LFO PWMs//////////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW); 
    if (LFO_select == LOW) { //encoder controls LFO1 PWM
        LFO1_PWM_position_prev = LFO1_PWM_position;
        getPosition(enc_LFO_PWM_A, enc_LFO_PWM_B, enc_LFO_PWM_A_prev, enc_LFO_PWM_B_prev,LFO1_PWM_position, mux1A, mux1B); //get new position

        if ( LFO1_PWM_position > 127 ) { //boundary check
            LFO1_PWM_position = 127;
            }
        if ( LFO1_PWM_position < 0 ) {
            LFO1_PWM_position = 0;
            }
            
        if (LFO1_PWM_position != LFO1_PWM_position_prev){
        //send change to teensy 
        //what VCO's do these go to?
            byte LFO1_PWM_pos = (byte)LFO1_PWM_position;
            transmitVal(ID, LFO1_PWM_pos, 0); //TODO ID
        }
    }
    if (LFO_select == HIGH) { //encoder controls LFO2 PWM
    
        LFO2_PWM_position_prev = LFO2_PWM_position;
        
        getPosition(enc_LFO_PWM_A, enc_LFO_PWM_B, enc_LFO_PWM_A_prev, enc_LFO_PWM_B_prev, LFO2_PWM_position, mux1A, mux1B); //get new position
        
        if ( LFO2_PWM_position > 127 ) { //boundary check
        LFO2_PWM_position = 127;
        }
        if ( LFO2_PWM_position < 0 ) {
        LFO2_PWM_position = 0;
        }
        
        if (LFO2_PWM_position != LFO2_PWM_position_prev){
        //send change to teensy  
            byte LFO2_PWM_pos = (byte)LFO2_PWM_position;
            transmitVal(ID, LFO2_PWM_pos, 0); //TODO ID
        }   
    }
    if (dest1_select == HIGH) {
        ADSR1_DEST1_position_prev = ADSR1_DEST1_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST1_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST1_position > 100 ) { //boundary check
            ADSR1_DEST1_position = 100;
            }
        if ( ADSR1_DEST1_position < -100 ) {
            ADSR1_DEST1_position = -100;
            }
            
        if (ADSR1_DEST1_position != ADSR1_DEST1_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 pitch bend dac) ID_DAC2_ADSR1_AMOUNT 
            byte ADSR1_DEST1_pos = (byte)(ADSR1_DEST1_position + 100); 
            transmitVal(036, ADSR1_DEST1_pos, 0);  
        }        
    }
    if (dest2_select == HIGH) {
        ADSR1_DEST2_position_prev = ADSR1_DEST2_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST2_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST2_position > 100 ) { //boundary check
            ADSR1_DEST2_position = 100;
            }
        if ( ADSR1_DEST2_position < -100 ) {
            ADSR1_DEST2_position = -100;
            }
            
        if (ADSR1_DEST2_position != ADSR1_DEST2_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 PWM dac) ID_DAC5_ADSR1_AMOUNT 
            byte ADSR1_DEST2_pos = (byte)(ADSR1_DEST2_position + 100); 
            transmitVal(048, ADSR1_DEST2_pos, 0);             
        }        
    }
    if (dest3_select == HIGH) {
        ADSR1_DEST3_position_prev = ADSR1_DEST3_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST3_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST3_position > 100 ) { //boundary check
            ADSR1_DEST3_position = 100;
            }
        if ( ADSR1_DEST3_position < -100 ) {
            ADSR1_DEST3_position = -100;
            }
            
        if (ADSR1_DEST3_position != ADSR1_DEST3_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
            byte ADSR1_DEST3_pos = (byte)(ADSR1_DEST3_position + 100); 
            transmitVal(ID, ADSR1_DEST3_pos, 0); //TODO ID
        }        
    }
    if (dest4_select == HIGH) {
        ADSR1_DEST4_position_prev = ADSR1_DEST4_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST4_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST4_position > 100 ) { //boundary check
            ADSR1_DEST4_position = 100;
            }
        if ( ADSR1_DEST4_position < -100 ) {
            ADSR1_DEST4_position = -100;
            }
            
        if (ADSR1_DEST4_position != ADSR1_DEST4_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer)
            byte ADSR1_DEST4_pos = (byte)(ADSR1_DEST4_position + 100); 
            transmitVal(ID, ADSR1_DEST4_pos, 0); //TODO ID
        }        
    }
    if (dest5_select == HIGH) {
        ADSR1_DEST5_position_prev = ADSR1_DEST5_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST5_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST5_position > 100 ) { //boundary check
            ADSR1_DEST5_position = 100;
            }
        if ( ADSR1_DEST5_position < -100 ) {
            ADSR1_DEST5_position = -100;
            }
            
        if (ADSR1_DEST5_position != ADSR1_DEST5_position_prev){
        //send change to teensy (ADSR1 amount to vco 2 pitch bend dac) ID_DAC4_ADSR1_AMOUNT 
            byte ADSR1_DEST5_pos = (byte)(ADSR1_DEST5_position + 100); 
            transmitVal(044, ADSR1_DEST5_pos, 0);         
        }        
    }
    if (dest6_select == HIGH) {
        ADSR1_DEST6_position_prev = ADSR1_DEST6_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST6_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST6_position > 100 ) { //boundary check
            ADSR1_DEST6_position = 100;
            }
        if ( ADSR1_DEST6_position < -100 ) {
            ADSR1_DEST6_position = -100;
            }
            
        if (ADSR1_DEST6_position != ADSR1_DEST6_position_prev){
        //send change to teensy (ADSR1 amount to vco 2 PWM dac) ID_DAC6_ADSR1_AMOUNT 
            byte ADSR1_DEST6_pos = (byte)(ADSR1_DEST6_position + 100); 
            transmitVal(052, ADSR1_DEST6_pos, 0);   
        }        
    }
    if (dest7_select == HIGH) {
        ADSR1_DEST7_position_prev = ADSR1_DEST7_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST7_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST7_position > 100 ) { //boundary check
            ADSR1_DEST7_position = 100;
            }
        if ( ADSR1_DEST7_position < -100 ) {
            ADSR1_DEST7_position = -100;
            }
            
        if (ADSR1_DEST7_position != ADSR1_DEST7_position_prev){
        //send change to teensy (ADSR1 amount to vco 2 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
            byte ADSR1_DEST7_pos = (byte)(ADSR1_DEST7_position + 100); 
            transmitVal(ID, ADSR1_DEST7_pos, 0); //TODO ID   
        }        
    }
    if (dest8_select == HIGH) {
        ADSR1_DEST8_position_prev = ADSR1_DEST8_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST8_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST8_position > 100 ) { //boundary check
            ADSR1_DEST8_position = 100;
            }
        if ( ADSR1_DEST8_position < -100 ) {
            ADSR1_DEST8_position = -100;
            }
            
        if (ADSR1_DEST8_position != ADSR1_DEST8_position_prev){
        //send change to teensy (lADSR1 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer)
            byte ADSR1_DEST8_pos = (byte)(ADSR1_DEST8_position + 100); 
            transmitVal(ID, ADSR1_DEST8_pos, 0); //TODO ID  
        }        
    }
    if (dest9_select == HIGH) {
        ADSR1_DEST9_position_prev = ADSR1_DEST9_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST9_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST9_position > 100 ) { //boundary check
            ADSR1_DEST9_position = 100;
            }
        if ( ADSR1_DEST9_position < -100 ) {
            ADSR1_DEST9_position = -100;
            }
            
        if (ADSR1_DEST9_position != ADSR1_DEST9_position_prev){
        //send change to teensy (ADSR1 amount to FM level)
            byte ADSR1_DEST9_pos = (byte)(ADSR1_DEST9_position + 100); 
            transmitVal(ID, ADSR1_DEST9_pos, 0); //TODO ID  
        }        
    }    
    if (dest10_select == HIGH) {
        ADSR1_DEST10_position_prev = ADSR1_DEST10_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST10_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST10_position > 100 ) { //boundary check
            ADSR1_DEST10_position = 100;
            }
        if ( ADSR1_DEST10_position < -100 ) {
            ADSR1_DEST10_position = -100;
            }
            
        if (ADSR1_DEST10_position != ADSR1_DEST10_position_prev){
        //send change to teensy (ADSR1 amount to cutoff) ID_DAC8_ADSR1_AMOUNT 
            byte ADSR1_DEST10_pos = (byte)(ADSR1_DEST10_position + 100); 
            transmitVal(060, ADSR1_DEST10_pos, 0);   

        }        
    }
    if (dest11_select == HIGH) {
        ADSR1_DEST11_position_prev = ADSR1_DEST11_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST11_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST11_position > 100 ) { //boundary check
            ADSR1_DEST11_position = 100;
            }
        if ( ADSR1_DEST11_position < -100 ) {
            ADSR1_DEST11_position = -100;
            }
            
        if (ADSR1_DEST11_position != ADSR1_DEST11_position_prev){
        //send change to teensy (ADSR1 amount to resonance) ID_DAC7_ADSR1_AMOUNT 
            byte ADSR1_DEST11_pos = (byte)(ADSR1_DEST11_position + 100); 
            transmitVal(056, ADSR1_DEST11_pos, 0);  
        }        
    }
    if (dest12_select == HIGH) {
        ADSR1_DEST12_position_prev = ADSR1_DEST12_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST12_position, mux2A, mux2B); //get new position

        if ( ADSR1_DEST12_position > 100 ) { //boundary check
            ADSR1_DEST12_position = 100;
            }
        if ( ADSR1_DEST12_position < -100 ) {
            ADSR1_DEST12_position = -100;
            }
            
        if (ADSR1_DEST12_position != ADSR1_DEST12_position_prev){
        //send change to teensy (ADSR1 amount to drive)
            byte ADSR1_DEST12_pos = (byte)(ADSR1_DEST12_position + 100); 
            transmitVal(ID, ADSR1_DEST12_pos, 0); //TODO ID          
        }        
    }
  


    ///////////MULTI ON PIN 3: CONTROLS FM AND DETUNE////////////////////////////////////////////////// 
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    if (VCO_select == LOW) { //encoder controls FM AMOUNT
        VCO1_FM_AMOUNT_position_prev = VCO1_FM_AMOUNT_position;
        getPosition(enc_FM_DETUNE_A, enc_FM_DETUNE_B, enc_FM_DETUNE_A_prev, enc_FM_DETUNE_B_prev, VCO1_FM_AMOUNT_position, mux1A, mux1B); //get new position

        if ( VCO1_FM_AMOUNT_position > 127 ) { //boundary check
            VCO1_FM_AMOUNT_position = 127;
        }
        if ( VCO1_FM_AMOUNT_position < 0 ) {
            VCO1_FM_AMOUNT_position = 0;
        }
            
        if (VCO1_FM_AMOUNT_position != VCO1_FM_AMOUNT_position_prev){
        //send change to teensy
            VCO1_FM_AMOUNT_pos = (byte)VCO1_FM_AMOUNT_position;
            transmitVal(ID,VCO1_FM_AMOUNT_pos,0); //TODO ID

        }
    }
    if (VCO_select == HIGH) { //encoder controls VCO2 detune amount
    
        VCO2_DETUNE_position_prev = VCO2_DETUNE_position;
        
        getPosition(enc_FM_DETUNE_A, enc_FM_DETUNE_B, enc_FM_DETUNE_A_prev, enc_FM_DETUNE_B_prev, VCO2_DETUNE_position, mux1A, mux1B); //get new position
        
        if ( VCO2_DETUNE_position > 127 ) { //boundary check
        VCO2_DETUNE_position = 127;
        }
        if ( VCO2_DETUNE_position < 0 ) {
        VCO2_DETUNE_position = 0;
        }
        
        if (VCO2_DETUNE_position != VCO2_DETUNE_position_prev){
        //send change to teensy 
            VCO2_DETUNE_pos = (byte)VCO2_DETUNE_position_prev;
            transmitVal(ID,VCO2_DETUNE_pos,0); //TODO ID
        }   
    }
    if (dest1_select == HIGH) {
        ADSR2_DEST1_position_prev = ADSR2_DEST1_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST1_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST1_position > 100 ) { //boundary check
            ADSR2_DEST1_position = 100;
            }
        if ( ADSR2_DEST1_position < -100 ) {
            ADSR2_DEST1_position = -100;
            }
            
        if (ADSR2_DEST1_position != ADSR2_DEST1_position_prev){
        //send change to teensy (ADSR2 amount to vco 1 pitch bend dac) ID_DAC2_ADSR2_AMOUNT 
            byte ADSR2_DEST1_pos = (byte)(ADSR2_DEST1_position + 100); 
            transmitVal(037, ADSR2_DEST11_pos, 0);         

        }        
    }
    if (dest2_select == HIGH) {
        ADSR2_DEST2_position_prev = ADSR2_DEST2_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST2_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST2_position > 100 ) { //boundary check
            ADSR2_DEST2_position = 100;
            }
        if ( ADSR2_DEST2_position < -100 ) {
            ADSR2_DEST2_position = -100;
            }
            
        if (ADSR2_DEST2_position != ADSR2_DEST2_position_prev){
        //send change to teensy (ADSR2 amount to vco 1 PWM dac) ID_DAC5_ADSR2_AMOUNT
            byte ADSR2_DEST2_pos = (byte)(ADSR2_DEST2_position + 100); 
            transmitVal(049, ADSR2_DEST2_pos, 0); 
        }        
    }
    if (dest3_select == HIGH) {
        ADSR2_DEST3_position_prev = ADSR2_DEST3_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST3_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST3_position > 100 ) { //boundary check
            ADSR2_DEST3_position = 100;
            }
        if ( ADSR2_DEST3_position < -100 ) {
            ADSR2_DEST3_position = -100;
            }
            
        if (ADSR2_DEST3_position != ADSR2_DEST3_position_prev){
        //send change to teensy (ADSR2 amount to vco 1 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
            byte ADSR2_DEST3_pos = (byte)(ADSR2_DEST3_position + 100); 
            transmitVal(ID, ADSR2_DEST3_pos, 0); //TODO ID 

        }        
    }
    if (dest4_select == HIGH) {
        ADSR2_DEST4_position_prev = ADSR2_DEST4_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST4_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST4_position > 100 ) { //boundary check
            ADSR2_DEST4_position = 100;
            }
        if ( ADSR2_DEST4_position < -100 ) {
            ADSR2_DEST4_position = -100;
            }
            
        if (ADSR2_DEST4_position != ADSR2_DEST4_position_prev){
        //send change to teensy (ADSR2 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer)
            byte ADSR2_DEST4_pos = (byte)(ADSR2_DEST4_position + 100); 
            transmitVal(ID, ADSR2_DEST4_pos, 0); //TODO ID 
        }        
    }
    if (dest5_select == HIGH) {
        ADSR2_DEST5_position_prev = ADSR2_DEST5_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST5_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST5_position > 100 ) { //boundary check
            ADSR2_DEST5_position = 100;
            }
        if ( ADSR2_DEST5_position < -100 ) {
            ADSR2_DEST5_position = -100;
            }
            
        if (ADSR2_DEST5_position != ADSR2_DEST5_position_prev){ 
        //send change to teensy (ADSR2 amount to vco 2 pitch bend dac) ID_DAC4_ADSR2_AMOUNT 
            byte ADSR2_DEST5_pos = (byte)(ADSR2_DEST5_position + 100); 
            transmitVal(045, ADSR2_DEST5_pos, 0); 
        }        
    }
    if (dest6_select == HIGH) {
        ADSR2_DEST6_position_prev = ADSR2_DEST6_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST6_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST6_position > 100 ) { //boundary check
            ADSR2_DEST6_position = 100;
            }
        if ( ADSR2_DEST6_position < -100 ) {
            ADSR2_DEST6_position = -100;
            }
            
        if (ADSR2_DEST6_position != ADSR2_DEST6_position_prev){
        //send change to teensy (ADSR2 amount to vco 2 PWM dac) ID_DAC6_ADSR2_AMOUNT 
            byte ADSR2_DEST6_pos = (byte)(ADSR2_DEST6_position + 100); 
            transmitVal(053, ADSR2_DEST6_pos, 0); 
        }        
    }
    if (dest7_select == HIGH) {
        ADSR2_DEST7_position_prev = ADSR2_DEST7_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST7_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST7_position > 100 ) { //boundary check
            ADSR2_DEST7_position = 100;
            }
        if ( ADSR2_DEST7_position < -100 ) {
            ADSR2_DEST7_position = -100;
            }
            
        if (ADSR2_DEST7_position != ADSR2_DEST7_position_prev){
        //send change to teensy (ADSR2 amount to vco 2 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer)
            byte ADSR2_DEST7_pos = (byte)(ADSR2_DEST7_position + 100); 
            transmitVal(ID, ADSR2_DEST7_pos, 0); //TODO ID 
        }        
    }
    if (dest8_select == HIGH) {
        ADSR2_DEST8_position_prev = ADSR2_DEST8_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST8_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST8_position > 100 ) { //boundary check
            ADSR2_DEST8_position = 100;
            }
        if ( ADSR2_DEST8_position < -100 ) {
            ADSR2_DEST8_position = -100;
            }
            
        if (ADSR2_DEST8_position != ADSR2_DEST8_position_prev){
        //send change to teensy (ADSR2 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer)
            byte ADSR2_DEST8_pos = (byte)(ADSR2_DEST8_position + 100); 
            transmitVal(ID, ADSR2_DEST8_pos, 0); //TODO ID 
        }        
    }
    if (dest9_select == HIGH) {
        ADSR2_DEST9_position_prev = ADSR2_DEST9_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST9_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST9_position > 100 ) { //boundary check
            ADSR2_DEST9_position = 100;
            }
        if ( ADSR2_DEST9_position < -100 ) {
            ADSR2_DEST9_position = -100;
            }
            
        if (ADSR2_DEST9_position != ADSR2_DEST9_position_prev){
        //send change to teensy (ADSR2 amount to FM level)
            byte ADSR2_DEST9_pos = (byte)(ADSR2_DEST9_position + 100); 
            transmitVal(ID, ADSR2_DEST9_pos, 0); //TODO ID 
        }        
    }    
    if (dest10_select == HIGH) {
        ADSR2_DEST10_position_prev = ADSR2_DEST10_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST10_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST10_position > 100 ) { //boundary check
            ADSR2_DEST10_position = 100;
            }
        if ( ADSR2_DEST10_position < -100 ) {
            ADSR2_DEST10_position = -100;
            }
            
        if (ADSR2_DEST10_position != ADSR2_DEST10_position_prev){
        //send change to teensy (ADSR2 amount to cutoff) ID_DAC8_ADSR2_AMOUNT 061
            byte ADSR2_DEST10_pos = (byte)(ADSR2_DEST10_position + 100); 
            transmitVal(061, ADSR2_DEST10_pos, 0); 
        }        
    }
    if (dest11_select == HIGH) {
        ADSR2_DEST11_position_prev = ADSR2_DEST11_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST11_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST11_position > 100 ) { //boundary check
            ADSR2_DEST11_position = 100;
            }
        if ( ADSR2_DEST11_position < -100 ) {
            ADSR2_DEST11_position = -100;
            }
            
        if (ADSR2_DEST11_position != ADSR2_DEST11_position_prev){
        //send change to teensy (ADSR2 amount to resonance) ID_DAC7_ADSR2_AMOUNT 057
            byte ADSR2_DEST11_pos = (byte)(ADSR2_DEST11_position + 100); 
            transmitVal(057, ADSR2_DEST11_pos, 0); 
        }        
    }
    if (dest12_select == HIGH) {
        ADSR2_DEST12_position_prev = ADSR2_DEST12_position;
        getPosition(enc_BOTTOM_RIGHT_A, enc_BOTTOM_RIGHT_B, enc_BOTTOM_RIGHT_A_prev, enc_BOTTOM_RIGHT_B_prev, ADSR2_DEST12_position, mux2A, mux2B); //get new position

        if ( ADSR2_DEST12_position > 100 ) { //boundary check
            ADSR2_DEST12_position = 100;
            }
        if ( ADSR2_DEST12_position < -100 ) {
            ADSR2_DEST12_position = -100;
            }
            
        if (ADSR2_DEST12_position != ADSR2_DEST12_position_prev){
        //send change to teensy (ADSR2 amount to drive)
            byte ADSR2_DEST12_pos = (byte)(ADSR2_DEST12_position + 100); 
            transmitVal(ID, ADSR2_DEST12_pos, 0); //TODO ID
        }        
    }
  

    ///////////MULTI ON PIN 4: CONTROLS ADSR RELEASE//////////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    if (ADSR_select == LOW) { //encoder controls ADSR1 RELEASE
        ADSR1_RELEASE_position_prev =ADSR1_RELEASE_position;
        getPosition(enc_ADSR_RELEASE_A, enc_ADSR_RELEASE_B, enc_ADSR_RELEASE_A_prev, enc_ADSR_RELEASE_B_prev, ADSR1_RELEASE_position, mux1A, mux1B); //get new position

        if ( ADSR1_RELEASE_position > 127 ) { //boundary check
            ADSR1_RELEASE_position = 127;
        }
        if ( ADSR1_RELEASE_position < 0 ) {
            ADSR1_RELEASE_position = 0;
        }
            
        if (ADSR1_RELEASE_position != ADSR1_RELEASE_position_prev){
        //send change to teensy ID_ADSR1_RELEASE 013
            byte ADSR1_RELEASE_pos = (byte)ADSR1_RELEASE_position;
            transmitVal(013,ADSR1_RELEASE_pos,0);

        }
    }
    if (ADSR_select == HIGH) { //encoder controls ADSR2 RELEASE
    
        ADSR2_RELEASE_position_prev = ADSR2_RELEASE_position;
        
        getPosition(enc_ADSR_RELEASE_A, enc_ADSR_RELEASE_B, enc_ADSR_RELEASE_A_prev, enc_ADSR_RELEASE_B_prev, ADSR2_RELEASE_position, mux1A, mux1B); //get new position
        
        if ( ADSR2_RELEASE_position > 127 ) { //boundary check
        ADSR2_RELEASE_position = 127;
        }
        if ( ADSR2_RELEASE_position < 0 ) {
        ADSR2_RELEASE_position = 0;
        }
        
        if (ADSR2_RELEASE_position != ADSR2_RELEASE_position_prev){
        //send change to teensy ID_ADSR2_RELEASE 023
            byte ADSR2_RELEASE_pos = (byte)ADSR2_RELEASE_position;
            transmitVal(023,ADSR1_RELEASE_pos,0);
        }   
    }

    ///////////MULTI ON PIN 5: CONTROLS ADSR DECAY//////////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    if (ADSR_select == LOW) { //encoder controls ADSR1 DECAY
        ADSR1_DECAY_position_prev =ADSR1_DECAY_position;
        getPosition(enc_ADSR_DECAY_A, enc_ADSR_DECAY_B, enc_ADSR_DECAY_A_prev, enc_ADSR_DECAY_B_prev, ADSR1_DECAY_position, mux1A, mux1B); //get new position

        if ( ADSR1_DECAY_position > 127 ) { //boundary check
            ADSR1_DECAY_position = 127;
        }
        if ( ADSR1_DECAY_position < 0 ) {
            ADSR1_DECAY_position = 0;
        }
            
        if (ADSR1_DECAY_position != ADSR1_DECAY_position_prev){
        //send change to teensy ID_ADSR1_DECAY 011
            byte ADSR1_DECAY_pos = (byte)ADSR1_DECAY_position;
            transmitVal(011,ADSR1_DECAY_pos,0);
        }
    }
    if (ADSR_select == HIGH) { //encoder controls ADSR2 DECAY
    
        ADSR2_DECAY_position_prev = ADSR2_DECAY_position;
        
        getPosition(enc_ADSR_DECAY_A, enc_ADSR_DECAY_B, enc_ADSR_DECAY_A_prev, enc_ADSR_DECAY_B_prev, ADSR2_DECAY_position, mux1A, mux1B); //get new position
        
        if ( ADSR2_DECAY_position > 127 ) { //boundary check
        ADSR2_DECAY_position = 127;
        }
        if ( ADSR2_DECAY_position < 0 ) {
        ADSR2_DECAY_position = 0;
        }
        
        if (ADSR2_DECAY_position != ADSR2_DECAY_position_prev){
        //send change to teensy ID_ADSR2_DECAY 021 
            byte ADSR2_DECAY_pos = (byte)ADSR2_DECAY_position;
            transmitVal(021,ADSR2_DECAY_pos,0);        
        }   
    }
  
    ///////////MULTI ON PIN 6: CONTROLS VCO PWMs//////////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    if (VCO_select == LOW) { //encoder controls VCO1 PWM
        VCO1_PWM_position_prev = VCO1_PWM_position;
        getPosition(enc_VCO_PWM_A, enc_VCO_PWM_B, enc_VCO_PWM_A_prev, enc_VCO_PWM_B_prev, VCO1_PWM_position, mux1A, mux1B); //get new position

        if ( VCO1_PWM_position > 127 ) { //boundary check
            VCO1_PWM_position = 127;
            }
        if ( VCO1_PWM_position < 0 ) {
            VCO1_PWM_position = 0;
            }
            
        if (VCO1_PWM_position != VCO1_PWM_position_prev){
        //send change to teensy
        }
    }
    if (VCO_select == HIGH) { //encoder controls VCO2 PWM

    
        VCO2_PWM_position_prev = VCO2_PWM_position;
        
        getPosition(enc_VCO_PWM_A, enc_VCO_PWM_B, enc_VCO_PWM_A_prev, enc_VCO_PWM_B_prev, VCO2_PWM_position, mux1A, mux1B); //get new position
        
        if ( VCO2_PWM_position > 127 ) { //boundary check
        VCO2_PWM_position = 127;
        }
        if ( VCO2_PWM_position < 0 ) {
        VCO2_PWM_position = 0;
        }
        
        if (VCO2_PWM_position != VCO2_PWM_position_prev){
        //send change to teensy  
        }   
    }
   
    ///////////////MULTI ON PIN 7: CONTROLS LFO FREQ AND TIME DIVISION//////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, LOW);
    if (LFO_select == LOW) { //encoders control LFO1 FREQ/RATE
        if (LFO1_MODE_select == LOW) { //encoder controls LFO1 FREQUENCY
            LFO1_FREQ_position_prev = LFO1_FREQ_position;  
        
            getPosition(enc_LFO_FREQRATE_A, enc_LFO_FREQRATE_B, enc_LFO_FREQRATE_A_prev, enc_LFO_FREQRATE_B_prev, LFO1_FREQ_position, mux1A, mux1B); //get new position
        
            if ( LFO1_FREQ_position > 100 ) { //boundary check
                LFO1_FREQ_position = 100;
            }
            if ( LFO1_FREQ_position < 1 ) {
                LFO1_FREQ_position = 1;
            }
        
            if (LFO1_FREQ_position != LFO1_FREQ_position_prev){
                //send change to teensy
            }
        }

        if (LFO1_MODE_select == HIGH) { //encoder controls LFO1 sync rate (0:24 ==> 48:1/64)
            LFO1_RATE_position_prev = LFO1_RATE_position;
        
            getPosition(enc_LFO_FREQRATE_A, enc_LFO_FREQRATE_B, enc_LFO_FREQRATE_A_prev, enc_LFO_FREQRATE_B_prev, LFO1_RATE_position, mux1A, mux1B); //get new position
        
            if ( LFO1_RATE_position > 24 ) { //boundary check
                LFO1_RATE_position = 24;
            }
            if ( LFO1_RATE_position < 0 ) {
                LFO1_RATE_position = 0;
            }
        
            if (LFO1_RATE_position != LFO1_RATE_position_prev){
                //send change to teensy
            }
        }
    }
    if (LFO_select == HIGH) { //encoders control LFO2 FREQ/RATE
        if (LFO2_MODE_select == LOW) { //encoder controls LFO2 FREQUENCY
            LFO2_FREQ_position_prev = LFO2_FREQ_position;
        
            getPosition(enc_LFO_FREQRATE_A, enc_LFO_FREQRATE_B, enc_LFO_FREQRATE_A_prev, enc_LFO_FREQRATE_B_prev, LFO2_FREQ_position, mux1A, mux1B); //get new position
        
            if ( LFO2_FREQ_position > 100 ) { //boundary check
                LFO2_FREQ_position = 100;
            }
            if ( LFO2_FREQ_position < 1 ) {
                LFO2_FREQ_position = 1;
            }
        
            if (LFO2_FREQ_position != LFO2_FREQ_position_prev){
                //send change to teensy
            }
        }

        if (LFO2_MODE_select == HIGH) { //encoder controls LFO2 sync rate (0:24 ==> 48:1/64)
            LFO2_RATE_position_prev = LFO2_RATE_position;
        
            getPosition(enc_LFO_FREQRATE_A, enc_LFO_FREQRATE_B, enc_LFO_FREQRATE_A_prev, enc_LFO_FREQRATE_B_prev, LFO2_RATE_position, mux1A, mux1B); //get new position
        
            if ( LFO2_RATE_position > 24 ) { //boundary check
                LFO2_RATE_position = 24;
            }
            if ( LFO2_RATE_position < 0 ) {
                LFO2_RATE_position = 0;
            }
        
            if (LFO2_RATE_position != LFO2_RATE_position_prev){
                //send change to teensy
            }
        }   
    }
  
    ///////////////MULTI ON PIN 8: CONTROLS ADSR SUSTAIN//////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    if (ADSR_select == LOW) { //encoder controls ADSR1 SUSTAIN
        ADSR1_SUSTAIN_position_prev =ADSR1_SUSTAIN_position;
        getPosition(enc_ADSR_SUSTAIN_A, enc_ADSR_SUSTAIN_B, enc_ADSR_SUSTAIN_A_prev, enc_ADSR_SUSTAIN_B_prev, ADSR1_SUSTAIN_position, mux1A, mux1B); //get new position

        if ( ADSR1_SUSTAIN_position > 127 ) { //boundary check
            ADSR1_SUSTAIN_position = 127;
        }
        if ( ADSR1_SUSTAIN_position < 0 ) {
            ADSR1_SUSTAIN_position = 0;
        }
            
        if (ADSR1_SUSTAIN_position != ADSR1_SUSTAIN_position_prev){
        //send change to teensy
        }
    }
    if (ADSR_select == HIGH) { //encoder controls ADSR2 SUSTAIN
    
        ADSR2_SUSTAIN_position_prev = ADSR2_SUSTAIN_position;
        
        getPosition(enc_ADSR_SUSTAIN_A, enc_ADSR_SUSTAIN_B, enc_ADSR_SUSTAIN_A_prev, enc_ADSR_SUSTAIN_B_prev, ADSR2_SUSTAIN_position, mux1A, mux1B); //get new position
        
        if ( ADSR2_SUSTAIN_position > 127 ) { //boundary check
        ADSR2_SUSTAIN_position = 127;
        }
        if ( ADSR2_SUSTAIN_position < 0 ) {
        ADSR2_SUSTAIN_position = 0;
        }
        
        if (ADSR2_SUSTAIN_position != ADSR2_SUSTAIN_position_prev){
        //send change to teensy  
        }   
    }
    
    ///////////////MULTI ON PIN 9: CONTROLS LFO OFFSET//////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    if (LFO_select == LOW) { //encoder controls LFO1 OFFSET
        LFO1_OFFSET_position_prev = LFO1_OFFSET_position;
        getPosition(enc_LFO_OFFSET_A, enc_LFO_OFFSET_B, enc_LFO_OFFSET_A_prev, enc_LFO_OFFSET_B_prev, LFO1_OFFSET_position, mux1A, mux1B); //get new position

        if ( LFO1_AMPLITUDE_position > 127 ) { //boundary check
            LFO1_AMPLITUDE_position = 127;
            }
        if ( LFO1_AMPLITUDE_position < 0 ) {
            LFO1_AMPLITUDE_position = 0;
            }
            
        if (LFO1_AMPLITUDE_position != LFO1_AMPLITUDE_position_prev){
        //send change to teensy
        }
    }
    if (LFO_select == HIGH) { //encoder controls LFO2 OFFSET
        LFO2_OFFSET_position_prev = LFO2_OFFSET_position;
        getPosition(enc_LFO_OFFSET_A, enc_LFO_OFFSET_B, enc_LFO_OFFSET_A_prev, enc_LFO_OFFSET_B_prev, LFO1_OFFSET_position, mux1A, mux1B); //get new position

        if ( LFO2_OFFSET_position > 127 ) { //boundary check
            LFO2_OFFSET_position = 127;
            }
        if ( LFO2_OFFSET_position < 0 ) {
            LFO2_OFFSET_position = 0;
            }
            
        if (LFO2_OFFSET_position != LFO2_OFFSET_position_prev){
        //send change to teensy
        }
    }

    ///////////////MULTI ON PIN 10: CONTROLS LFO MAX AMPLITUDE///////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    if (LFO_select == LOW) { //encoder controls LFO1 AMPLITUDE
        LFO1_AMPLITUDE_position_prev = LFO1_AMPLITUDE_position;
        getPosition(enc_LFO_AMPLITUDE_A, enc_LFO_AMPLITUDE_B, enc_LFO_AMPLITUDE_A_prev, enc_LFO_AMPLITUDE_B_prev, LFO1_AMPLITUDE_position, mux1A, mux1B); //get new position

        if ( LFO1_AMPLITUDE_position > 127 ) { //boundary check
            LFO1_AMPLITUDE_position = 127;
            }
        if ( LFO1_AMPLITUDE_position < 0 ) {
            LFO1_AMPLITUDE_position = 0;
            }
            
        if (LFO1_AMPLITUDE_position != LFO1_AMPLITUDE_position_prev){
        //send change to teensy
        }
    }
    if (LFO_select == HIGH) { //encoder controls LFO2 AMPLITUDE
        LFO2_AMPLITUDE_position_prev = LFO2_AMPLITUDE_position;
        getPosition(enc_LFO_AMPLITUDE_A, enc_LFO_AMPLITUDE_B, enc_LFO_AMPLITUDE_A_prev, enc_LFO_AMPLITUDE_B_prev, LFO1_AMPLITUDE_position, mux1A, mux1B); //get new position

        if ( LFO2_AMPLITUDE_position > 127 ) { //boundary check
            LFO2_AMPLITUDE_position = 127;
            }
        if ( LFO2_AMPLITUDE_position < 0 ) {
            LFO2_AMPLITUDE_position = 0;
            }
            
        if (LFO2_AMPLITUDE_position != LFO2_AMPLITUDE_position_prev){
        //send change to teensy
        }
    }

    ///////////////MULTI ON PIN 11: CONTROLS VCO SHAPE//////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    if (VCO_select == LOW) { //encoder controls VCO1 SHAPE
        VCO1_SHAPE_position_prev = VCO1_SHAPE_position;
        getPosition(enc_VCO_SHAPE_A, enc_VCO_SHAPE_B, enc_VCO_SHAPE_A_prev, enc_VCO_SHAPE_B_prev, VCO1_SHAPE_position, mux1A, mux1B); //get new position

        if ( VCO1_SHAPE_position > 127 ) { //boundary check
            VCO1_SHAPE_position = 127;
            }
        if ( VCO1_SHAPE_position < 0 ) {
            VCO1_SHAPE_position = 0;
            }
            
        if (VCO1_SHAPE_position != VCO1_SHAPE_position_prev){
        //send change to teensy
        }
    }
    if (VCO_select == HIGH) { //encoder controls VCO2 SHAPE
    
    
        VCO2_SHAPE_position_prev = VCO2_SHAPE_position;
        
        getPosition(enc_VCO_SHAPE_A, enc_VCO_SHAPE_B, enc_VCO_SHAPE_A_prev, enc_VCO_SHAPE_B_prev, VCO2_SHAPE_position, mux1A, mux1B); //get new position
        
        if ( VCO2_SHAPE_position > 127 ) { //boundary check
        VCO2_SHAPE_position = 127;
        }
        if ( VCO2_PWM_position < 0 ) {
        VCO2_SHAPE_position = 0;
        }
        
        if (VCO2_SHAPE_position != VCO2_SHAPE_position_prev){
        //send change to teensy  
        }   
    }
    
    ///////////////MULTI ON PIN 12: CONTROLS DRIVE//////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    DRIVE_position_prev = DRIVE_position;  
        
    getPosition(enc_DRIVE_A, enc_DRIVE_B, enc_DRIVE_A_prev, enc_DRIVE_B_prev, DRIVE_position, mux1A, mux1B); //get new position
        
    if ( DRIVE_position > 127 ) { //boundary check
        DRIVE_position = 127;
    }
    if ( DRIVE_position < 0 ) {
        DRIVE_position = 0;
    }        
    if (DRIVE_position != DRIVE_position_prev){
        //send change to teensy
    }  
    
    ///////////////MULTI ON PIN 13: CONTROLS ADSR ATTACK//////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    if (ADSR_select == LOW) { //encoder controls ADSR1 ATTACK
        ADSR1_ATTACK_position_prev =ADSR1_ATTACK_position;
        getPosition(enc_ADSR_ATTACK_A, enc_ADSR_ATTACK_B, enc_ADSR_ATTACK_A_prev, enc_ADSR_ATTACK_B_prev, ADSR1_ATTACK_position, mux1A, mux1B); //get new position

        if ( ADSR1_SUSTAIN_position > 127 ) { //boundary check
            ADSR1_SUSTAIN_position = 127;
        }
        if ( ADSR1_SUSTAIN_position < 0 ) {
            ADSR1_SUSTAIN_position = 0;
        }
            
        if (ADSR1_SUSTAIN_position != ADSR1_SUSTAIN_position_prev){
        //send change to teensy
        }
    }
    if (ADSR_select == HIGH) { //encoder controls ADSR2 SUSTAIN ATTACK
        ADSR1_ATTACK_position_prev =ADSR1_ATTACK_position;
        getPosition(enc_ADSR_ATTACK_A, enc_ADSR_ATTACK_B, enc_ADSR_ATTACK_A_prev, enc_ADSR_ATTACK_B_prev, ADSR1_ATTACK_position, mux1A, mux1B); //get new position

        if ( ADSR1_SUSTAIN_position > 127 ) { //boundary check
            ADSR1_SUSTAIN_position = 127;
        }
        if ( ADSR1_SUSTAIN_position < 0 ) {
            ADSR1_SUSTAIN_position = 0;
        }
            
        if (ADSR1_SUSTAIN_position != ADSR1_SUSTAIN_position_prev){
        //send change to teensy
        }
    }

    ///////////////MULTI ON PIN 14: CONTROLS VCF RES//////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    RES_position_prev = RES_position;  
        
    getPosition(enc_RES_A, enc_RES_B, enc_RES_A_prev, enc_RES_B_prev, RES_position, mux1A, mux1B); //get new position
        
    if ( RES_position > 127 ) { //boundary check
        RES_position = 127;
    }
    if ( RES_position < 0 ) {
        RES_position = 0;
    }        
    if (RES_position != RES_position_prev){
        //send change to teensy
    }    
    
    ///////////////MULTI ON PIN 15: CONTROLS LFO SHAPE//////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    if (LFO_select == LOW) { //encoder controls LFO1 SHAPE
        LFO1_SHAPE_position_prev = LFO1_SHAPE_position;
        getPosition(enc_LFO_SHAPE_A, enc_LFO_SHAPE_B, enc_LFO_SHAPE_A_prev, enc_LFO_SHAPE_B_prev,LFO1_SHAPE_position, mux1A, mux1B); //get new position

        if ( LFO1_SHAPE_position > 4) { //boundary check
            LFO1_SHAPE_position = 4;
            }
        if ( LFO1_SHAPE_position < 0 ) {
            LFO1_SHAPE_position = 0;
            }
            
        if (LFO1_SHAPE_position != LFO1_SHAPE_position_prev){
        //send change to teensy
        }
    }
    if (LFO_select == HIGH) { //encoder controls LFO2 SHAPE
    
        LFO2_SHAPE_position_prev = LFO2_SHAPE_position;
        
        getPosition(enc_LFO_SHAPE_A, enc_LFO_SHAPE_B, enc_LFO_SHAPE_A_prev, enc_LFO_SHAPE_B_prev, LFO2_SHAPE_position, mux1A, mux1B); //get new position
        
        if ( LFO2_SHAPE_position > 4 ) { //boundary check
        LFO2_SHAPE_position = 4;
        }
        if ( LFO2_SHAPE_position < 0 ) {
        LFO2_SHAPE_position = 0;
        }
        
        if (LFO2_SHAPE_position != LFO2_SHAPE_position_prev){
        //send change to teensy  
        }   
    }
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

void transmitVal(byte ID, byte val){
        byte msg[3];
        msg[0] = 255;
        msg[1] = ID;
        msg[2] = val;
        Serial3.write(msg,3);
     }
