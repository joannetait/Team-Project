# include <EEPROM.h>
# include <SPI.h>
# include <GD2.h>
# include <Bounce2.h>

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

static int param_1 = 69;
static int param_2 = 69;
static int param_3 = 69;
static int param_4 = 69;

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
bool enc_LFO_PHASE_A;
bool enc_LFO_PHASE_B;
bool enc_LFO_AMPLITUDE_A;
bool enc_LFO_AMPLITUDE_B;
bool enc_LFO_OFFSET_A;
bool enc_LFO_OFFSET_B;

bool enc_LFO_FREQRATE_A_prev;
bool enc_LFO_FREQRATE_B_prev;
bool enc_LFO_SHAPE_A_prev;
bool enc_LFO_SHAPE_B_prev;
bool enc_LFO_PHASE_A_prev;
bool enc_LFO_PHASE_B_prev;
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
int LFO1_PHASE_position  = 0;
int LFO1_AMPLITUDE_position  = 0;
int LFO1_OFFSET_position  = 0;

int LFO1_FREQ_position_prev  = 0;
int LFO1_RATE_position_prev =0;
int LFO1_SHAPE_position_prev  = 0;
int LFO1_PHASE_position_prev  = 0;
int LFO1_AMPLITUDE_position_prev  = 0;
int LFO1_OFFSET_position_prev  = 0;

int LFO2_FREQ_position  = 0;
int LFO2_RATE_position =0;
int LFO2_SHAPE_position  = 0;
int LFO2_PHASE_position  = 0;
int LFO2_AMPLITUDE_position  = 0;
int LFO2_OFFSET_position  = 0;

int LFO2_FREQ_position_prev  = 0;
int LFO2_RATE_position_prev =0;
int LFO2_SHAPE_position_prev  = 0;
int LFO2_PHASE_position_prev  = 0;
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

//********************* setup, display startup screen ********************

void setup(){
    GD.begin(); //start the display
    Serial.begin (9600);                    
    GD.ClearColorRGB(0x103000);
    GD.Clear();                         //clear the display
    GD.cmd_text(240, 136, 31, OPT_CENTER, "Team 1"); 
    GD.swap();              //update the display
    delay(1000);            //keep startup screen for 1s

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
    
    Serial.begin(9600);
    Serial3.begin(9600);
    

}

void loop(){
    

    int xtouch;
    int ytouch;
    int brntag;
    /******************* initial menu ******************/
    GD.Clear();                 //clear the screen (posibly not vital?)
    GD.Begin(RECTS);            //start drawing rectangles
    GD.LineWidth(5 * 5);        // corner radius 5.0 pixels 
    /* Now create a tagmask including all the rectangles. The whole rectangle carries the mask */
    GD.Tag(1);      //settings
    GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155);      //define rectangle 1, top left + bottom right corners
    GD.Tag(2);      //perfomrnace
    GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155);
    GD.TagMask(0);              //end tagmask creation
    
    GD.ColorRGB(0x103000);
    GD.cmd_text(30, 136, 25, OPT_CENTERY, "Settings");         
    GD.cmd_text(250, 136, 25, OPT_CENTERY, "Performance");
    
    GD.swap();                   //update screen with initial menu
    
    int retval;                  //define throwaway int for storing screen press info
    updateEncoders();
    GD.get_inputs();             //check for screen press
    xtouch = GD.inputs.x;
    ytouch = GD.inputs.y;
    brntag = GD.inputs.tag;

    while(xtouch >= 0){          //debounce menu select from previous
        updateEncoders();
        GD.get_inputs();
        xtouch = GD.inputs.x;       //x coordinates of screen press
        ytouch = GD.inputs.y;       //y coordintaes of screen press
        brntag = GD.inputs.tag;     //which tag has been pressed
    }
    int buttonpress = 0;            //assume screen is not pressed initialy
    
    while(buttonpress == 0){         //only one button can be pressed at a time
        // Determine if a button has been pressed
        updateEncoders();
        GD.get_inputs();
        xtouch = GD.inputs.x;
        ytouch = GD.inputs.y;
        brntag = GD.inputs.tag;
        if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
        {       //key decode loop
            buttonpress = 1;           //screen is being pressed now
           
            //-----------this used to be a series of if statemnts, now a for loop----------//          
            for (int i = 1; i < 3; i++){
                if (int(brntag) == i){
                    retval = i;
                    break;
                }
                else retval = 0;
            }
        }
     }
    while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
        updateEncoders();
        GD.get_inputs();
        xtouch = GD.inputs.x;
        ytouch = GD.inputs.y;
        brntag = GD.inputs.tag;
        //wait for button to be released
    }
    Serial.println(retval); //print pres value to serial monitor


    //**************** the SETTINGS screen is defined below in a similar fashion *****************//
    //********************************************************************************************//
    if(retval == 1){ //if the settings button has been pressed
        do{
            //print seetings screen and create appropriate tagmasks
            GD.Clear(); 
            GD.Begin(RECTS); 
            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
            GD.Tag(3);  //note priority
            GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155); 
            GD.Tag(4);  //save
            GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155); 
            GD.Tag(5);  //midi channel
            GD.Vertex2ii(30, 70); GD.Vertex2ii(220, 110); 
            GD.Tag(6);  //clock
            GD.Vertex2ii(250, 70); GD.Vertex2ii(450, 110); 
            GD.Tag(7);  //return button                      
            GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
            GD.TagMask(0);
            
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 72, 25, 0, "MIDI channel");
            GD.cmd_text(250, 72, 25, 0, "Clock");
            GD.cmd_text(30, 136, 25, OPT_CENTERY, "Note priority");
            GD.cmd_text(250, 136, 25, OPT_CENTERY, "Save");
            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
            
            GD.swap();
            //int retval;
            updateEncoders();
            GD.get_inputs();
            xtouch = GD.inputs.x;
            ytouch = GD.inputs.y;
            brntag = GD.inputs.tag;

            while(xtouch >= 0){          //debounce menu select from previous
                updateEncoders();
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
            }
            int buttonpress = 0;

            while(buttonpress == 0){
            // Determine if a button has been pressed
                updateEncoders();
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                if ((xtouch >= 0) && (brntag >0))
                {       //key decode loop
                    buttonpress = 1;
                    for (int i = 3; i < 8; i++){
                        if (int(brntag) == i){
                            retval = i;
                            break;
                        }
                        else retval = 0;
                    }
                }
            }  
            while((xtouch >= 0) && (brntag >0))
            {
                updateEncoders();
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //wait for button to be released
            }
            Serial.println(retval); //print press value to serial monitor

            //-------------------- different settings here ------------------------//


            //--------------------------NOTE PRIORITY---------------------------//
            //------------------------!CHANGE TAGS HERE!-----------------------//
            if(retval == 3){  
                do{
                    //print note priority screen and create appropriate tagmasks
                    GD.Clear(); 
                    GD.Begin(RECTS); 
                    GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                    GD.Tag(26);  //Top note
                    GD.Vertex2ii(30, 50); GD.Vertex2ii(220, 90); 
                    GD.Tag(27);  //bottom note
                    GD.Vertex2ii(30, 100); GD.Vertex2ii(220, 140); 
                    GD.Tag(28);  //last note
                    GD.Vertex2ii(30,150); GD.Vertex2ii(220, 190); 
                    GD.Tag(29);  //return button                      
                    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                    GD.TagMask(0);
                    
                    GD.ColorRGB(0x103000);
                    GD.cmd_text(30, 70, 25, OPT_CENTERY, "Top note");
                    GD.cmd_text(30, 120, 25, OPT_CENTERY, "Bottom note");
                    GD.cmd_text(30, 160, 25, OPT_CENTERY, "Last note");
                    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                    
                    GD.swap();
                    //int retval;
                    updateEncoders();
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;

                    while(xtouch >= 0){          //debounce menu select from previous
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                    }
                    int buttonpress = 0;

                    while(buttonpress == 0){
                    // Determine if a button has been pressed
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        if ((xtouch >= 0) && (brntag >0))
                        {       //key decode loop
                            buttonpress = 1;
                            for (int i = 26; i < 30; i++){
                                if (int(brntag) == i){
                                    retval = i;
                                    break;
                                }
                                else retval = 0;
                            }
                        }
                    }  
                    while((xtouch >= 0) && (brntag >0))
                    {
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        //wait for button to be released
                    }
                    Serial.println(retval); //print press value to serial monitor
                }while(retval != 29);           //return from note priority
            }



            //--------------------------- CLOCK ------------------------//
            if(retval == 6){
                static uint16_t clock_value = 0;
                //---------------Draw the return button-------------//
                GD.Clear(); 
                GD.Begin(RECTS); 
                GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                GD.Tag(26);                      
                GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                GD.TagMask(0);
                GD.ColorRGB(0x103000);
                GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                GD.swap();
                do
                { 
                    //------------------check previous presses released------------//
                    updateEncoders();
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;
                    
                    while(xtouch >= 0){          //debounce menu select from previous

                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                    }
                    int buttonpress = 0;

                    //---------------------Loop which checks the buttons----------------------//
                    while(buttonpress == 0){                        //loop while button is not being pressed
                    
                        // Determine if a button has been pressed
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        
                        //--------------Track the dial---------------//
                        switch (GD.inputs.track_tag & 0xff){   //' track{
                            case 27:
                            clock_value = GD.inputs.track_val;
                            Serial.print(clock_value / 516);
                            int brntag = GD.inputs.tag;
                            //-------------------send clock value to teensy----------------//
                        } //' }track
                        GD.Clear(); 
                        //-------------Redraw the display---------------//
                        GD.Tag(27); //' dial{
                        GD.cmd_dial(130, 135, 70, OPT_FLAT, clock_value);
                        GD.cmd_track(130, 135, 1, 1, 27);   //' }dial
                        GD.Begin(RECTS); 
                        GD.LineWidth(5 * 5);                                  // corner radius 5.0 pixels 
                        GD.cmd_text(240, 31, 30, OPT_CENTER, "clock");
                        GD.cmd_number(220, 135, 25, OPT_CENTERY, clock_value / 516);
                        GD.Tag(26);                      
                        GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);         //return button position 
                        GD.TagMask(0);
                        GD.ColorRGB(0x103000);
                        GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                        GD.swap();
                                               
                        //---------------Decode which button is pressed---------------//
                        if ((xtouch >= 0) && (brntag >0))
                        {       
                            buttonpress = 1;
                        
                            for (int i = 26; i < 27; i++){
                                if (int(brntag) == i){
                                    retval = i;
                                    break;
                                }
                                else retval = 0;
                            }
                        }
                    }  
                    //-----------------Wait until button is released-------------------//
                    while((xtouch >= 0) && (brntag >0)){
                        updateEncoders();                         
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        
                        //--------------Track the dial---------------//
                        switch (GD.inputs.track_tag & 0xff){   //' track{
                            case 27:
                            clock_value = GD.inputs.track_val;
                            Serial.print(clock_value / 516);
                            int brntag = GD.inputs.tag;
                            //--------------send clock value to
                        } //' }track

                        //-------------------Redraw the display--------------------//
                        GD.Clear(); 
                        GD.Tag(27); //' dial{
                        GD.cmd_dial(130, 135, 70, OPT_FLAT, clock_value);
                        GD.cmd_track(130, 135, 1, 1, 27);   //' }dial
                        GD.Begin(RECTS); 
                        GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                        GD.cmd_text(240, 31, 30, OPT_CENTER, "clock");
                        GD.cmd_number(220, 135, 25, OPT_CENTERY, clock_value / 516);
                        GD.Tag(26);                      
                        GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                        GD.TagMask(0);
                        GD.ColorRGB(0x103000);
                        GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                        GD.swap();
                    }
                    Serial.println(retval); //print pres value to serial monitor

                } while (retval != 26);
            }
        } while (retval != 7);      //stay in loop until the return button is pressed
    }

    //**************** the PERFORMANCE screen is defined below *****************//
    //**************************************************************************//
    else if(retval == 2){ //"performance"
        do{ //creating performance menu
            GD.Clear(); 
            GD.Begin(RECTS); 
            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
            GD.Tag(8);      //mode matrix
            GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155); //mod matrix 
            GD.Tag(9);      //LIVE
            GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155); //param visuals
            GD.Tag(10);     //return           
            GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
            GD.TagMask(0);
            
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 117, 25, 0, "Mod Matrix");
            GD.cmd_text(250, 117, 25, 0, "LIVE!");  //------replace this with a VOLUME dial
            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
            
            GD.swap();
            //int retval;
            updateEncoders();
            GD.get_inputs();
            xtouch = GD.inputs.x;
            ytouch = GD.inputs.y;
            brntag = GD.inputs.tag;

            while(xtouch >= 0){          //debounce menu select from previous
                updateEncoders();
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
            }
            int buttonpress = 0;
            while(buttonpress == 0){
            // Determine if a button has been pressed
                updateEncoders();
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;

                if ((xtouch >= 0) && (brntag >0)){
                    buttonpress = 1;
                    for (int i = 8; i < 11; i++){
                        if (int(brntag) == i){
                            retval = i;
                            break;
                        }
                        else retval = 0;
                    }
                }
            }  
            while((xtouch >= 0) && (brntag >0)){
                updateEncoders();
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //wait for button to be released
            }
            Serial.println(retval); //print pres value to serial monitor

            //**************** the MOD MATRIX screen is defined below *****************//
            //*************************************************************************//
            if(retval == 8){ //"Mod matrix"
                do{
                    GD.Clear(); 
                    GD.Begin(RECTS); 
                    GD.LineWidth(5 * 5); // corner radius 5.0 pixels 

                    //-----------------create mod matrix rectangles--------------------//
                    GD.Tag(11);
                    GD.Vertex2ii(22, 22); GD.Vertex2ii(164, 58); 
                    GD.Tag(12);
                    GD.Vertex2ii(22, 62); GD.Vertex2ii(164, 98);
                    GD.Tag(13);
                    GD.Vertex2ii(22, 102); GD.Vertex2ii(164, 138); 
                    GD.Tag(14);
                    GD.Vertex2ii(22, 142); GD.Vertex2ii(164, 178);

                    GD.Tag(15);
                    GD.Vertex2ii(168, 22); GD.Vertex2ii(310, 58);
                    GD.Tag(16);
                    GD.Vertex2ii(168, 62); GD.Vertex2ii(310, 98);
                    GD.Tag(17);
                    GD.Vertex2ii(168, 102); GD.Vertex2ii(310, 138);
                    GD.Tag(18);
                    GD.Vertex2ii(168, 142); GD.Vertex2ii(310, 178);

                    GD.Tag(19);                      
                    GD.Vertex2ii(314, 22); GD.Vertex2ii(456, 58);
                    GD.Tag(20);
                    GD.Vertex2ii(314, 62); GD.Vertex2ii(456, 98);
                    GD.Tag(21);
                    GD.Vertex2ii(314, 102); GD.Vertex2ii(456, 138);
                    GD.Tag(22);
                    GD.Vertex2ii(314, 142); GD.Vertex2ii(456, 178); 

                    GD.Tag(25);
                    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240); //return button as usual  

                    GD.TagMask(0);
                    
                    GD.ColorRGB(0x103000);
                    GD.cmd_text(22, 40, 25, OPT_CENTERY, "PB1");
                    GD.cmd_text(22, 80, 25, OPT_CENTERY, "PWM1");
                    GD.cmd_text(22, 120, 25, OPT_CENTERY, "LVL1");
                    GD.cmd_text(22, 160, 25, OPT_CENTERY, "SHAPE1");

                    GD.cmd_text(168, 40, 25, OPT_CENTERY, "PB2");
                    GD.cmd_text(168, 80, 25, OPT_CENTERY, "PWM2");
                    GD.cmd_text(168, 120, 25, OPT_CENTERY, "SHAPE2");
                    GD.cmd_text(168, 160, 25, OPT_CENTERY, "LVL2");

                    GD.cmd_text(314, 40, 25, OPT_CENTERY, "FM");
                    GD.cmd_text(314, 80, 25, OPT_CENTERY, "CUTOFF");
                    GD.cmd_text(314, 120, 25, OPT_CENTERY, "RES");
                    GD.cmd_text(314, 160, 25, OPT_CENTERY, "DRIVE");
                    
                    
                    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                    
                    GD.swap();
                    //int retval;
                    updateEncoders();
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;

                    while(xtouch >= 0){          //debounce menu select from previous
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                    }
                    int buttonpress = 0;
                    //Draws the main menu for dual probe
                    while(buttonpress == 0){
                    // Determine if a button has been pressed
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;

                        if ((xtouch >= 0) && (brntag >0)){       //key decode loop
                            buttonpress = 1;
                            for (int i = 11; i < 26; i++){
                                if (int(brntag) == i){
                                    retval = i;
                                    break;
                                }
                                else retval = 0;
                            }
                        }
                    }  
                    while((xtouch >= 0) && (brntag >0)){
                        updateEncoders();
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        //wait for button to be released
                    }
                    
                    Serial.println(retval); //print pres value to serial monitor

                    //---------------put mod matrix menu here---------------//

                    if (retval == 11){
                        while(1){
                            //------------PB1 select to HIGH-------------//
                            ctrlpanel("PB1", param_1, param_2, param_3, param_4);
                        }    
                    }

                } while (retval != 25);     //stay in loop until return button is pressed
            }
        } while (retval != 10);     // stay in loop until return button is pressed
    }
}       //end of main loop

void ctrlpanel(const char *ctrlparam, int param_1, int param_2, int param_3, int param_4){
    GD.Clear();
    GD.Begin(RECTS);                //start drawing rectangles
    GD.LineWidth(5 * 5);            // corner radius 5.0 pixels 
    GD.Tag(28);
    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position
    GD.TagMask(0);
    //------------------titles on the left side-----------------//
    GD.cmd_text(40, 80, 25, OPT_CENTERY, "LFO1");
    GD.cmd_text(40, 120, 25, OPT_CENTERY, "LFO2");

    //------------------titles on the right side-----------------//
    GD.cmd_text(260, 80, 25, OPT_CENTERY, "ADSR1");
    GD.cmd_text(260, 120, 25, OPT_CENTERY, "ADSR2");

    //------------------------title on top------------------------//
    GD.cmd_text(240, 31, 30, OPT_CENTER, ctrlparam);

    //------------------left column parameter values--------------//
    GD.cmd_number(140, 80, 25, OPT_CENTERY, param_1);
    GD.cmd_number(140, 120, 25, OPT_CENTERY, param_2);

    //-------------------right column parameter values------------//
    GD.cmd_number(380, 80, 25, OPT_CENTERY, param_3);
    GD.cmd_number(380, 120, 25, OPT_CENTERY, param_4);

    GD.ColorRGB(0x103000);
    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
    GD.swap();
}

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
            //send change to teensy to switch CD4066 from exp to lin fm or vice versa ID_FM_SELECT 200 
            byte FM_sel = (byte)FM_select;
            transmitVal(200,FM_sel);
        }
        if (VCO_select = HIGH) { // button controls wether we sync VCO2 to 1
            SYNC_select = !SYNC_select;
            //send change to teensy to switch CD4066 SYNC ON or OFF 
            byte SYNC_sel = (byte)SYNC_select;
            transmitVal(201,SYNC_sel);
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
            LFO1_MODE_sel = (byte)LFO1_MODE_select;
            transmitVal(100,LFO1_MODE_sel);
        }
        if ( LFO_select == HIGH ){ //button controls LFO1 mode
            LFO2_MODE_select = !LFO2_MODE_select;   
            //send change to teensy
            LFO2_MODE_sel = (byte)LFO2_MODE_select;
            transmitVal(110,LFO2_MODE_sel);
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
                //send change to teensy ID_VCO1_OCT 202
                byte VCO1_OCT_pos=(byte)VCO1_OCT_position;
                transmitVal(202,VCO1_OCT_pos);               
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
                //send change to teensy ID_VCO1_LVL 203
                byte VCO1_LVL_pos = (byte)VCO1_LVL_position;
                transmitVal(203,VCO1_LVL_pos); 
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
                byte VCO2_OCT_pos = (byte)VCO2_OCT_position;
                transmitVal(204,VCO2_OCT_pos); 
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
                //send change to teensy ID_VCO2_LVL 205
                byte VCO2_LVL_pos = (byte)VCO2_LVL_position;
                transmitVal(205, VCO2_LVL_pos); 
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
        //send change to teensy (lfo1 amount to vco 1 pitch bend dac) ID_PB1_LFO1_AMOUNT 130
            byte LFO1_DEST1_pos = (byte)(LFO1_DEST1_position + 100);
            transmitVal(130, LFO1_DEST1_pos);
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
        //send change to teensy (lfo1 amount to vco 1 PWM dac) ID_PWM1_LFO1_AMOUNT 134
            byte LFO1_DEST2_pos = (byte)(LFO1_DEST2_position + 100);
            transmitVal(134, LFO1_DEST2_pos);
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
        //the different vca level in the wavemixer) ID_SHAPE1_LFO1_AMOUNT 138
            byte LFO1_DEST3_pos = (byte)(LFO1_DEST3_position + 100);
            transmitVal(138, LFO1_DEST3_pos); 
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
        //ID_LVL1_LFO1_AMOUNT 142
            byte LFO1_DEST4_pos = (byte)(LFO1_DEST4_position + 100);
            transmitVal(142, LFO1_DEST4_pos);
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
        //send change to teensy (lfo1 amount to vco 2 pitch bend dac) ID_PB2_LFO1_AMOUNT 146 
            byte LFO1_DEST5_pos = (byte)(LFO1_DEST5_position + 100);
            transmitVal(146, LFO1_DEST5_pos);
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
        //send change to teensy (lfo1 amount to vco 2 PWM dac) ID_PWM2_LFO1_AMOUNT 150
            byte LFO1_DEST6_pos = (byte)(LFO1_DEST6_position + 100);
            transmitVal(150, LFO1_DEST6_pos);
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
        //the different vca level in the wavemixer) ID_SHAPE2_LFO1_AMOUNT 154
            byte LFO1_DEST7_pos = (byte)(LFO1_DEST7_position + 100);
            transmitVal(154, LFO1_DEST7_pos); 
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
        //ID_LVL2_LFO1_AMOUNT 158
            byte LFO1_DEST8_pos = (byte)(LFO1_DEST8_position + 100);
            transmitVal(158, LFO1_DEST8_pos);
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
        //send change to teensy (lfo1 amount to FM level) ID_FM_LFO1_AMOUNT 162
            byte LFO1_DEST9_pos = (byte)(LFO1_DEST9_position + 100);
            transmitVal(162, LFO1_DEST9_pos);       
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
        //send change to teensy (lfo1 amount to cutoff) ID_CUTOFF_LFO1_AMOUNT 166
            byte LFO1_DEST10_pos = (byte)(LFO1_DEST10_position + 100);
            transmitVal(166, LFO1_DEST10_pos); 

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
        //send change to teensy (lfo1 amount to resonance) ID_RES_LFO1_AMOUNT 
            byte LFO1_DEST11_pos = (byte)(LFO1_DEST11_position + 100);
            transmitVal(170, LFO1_DEST11_pos);
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
        //send change to teensy (lfo1 amount to drive) ID_DRIVE_LFO1_AMOUNT 174
            byte LFO1_DEST12_pos = (byte)(LFO1_DEST12_position + 100);
            transmitVal(174, LFO1_DEST12_pos); 
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
        //send change to teensy ID_CUTOFF 206 
        byte CUTOFF_pos = (byte) CUTOFF_position;
        transmitVal(206, CUTOFF_pos); 
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
        //send change to teensy (lfo2 amount to vco 1 pitch bend dac) ID_PB1_LFO2_AMOUNT 131
            byte LFO2_DEST1_pos = (byte)(LFO2_DEST1_position + 100);
            transmitVal(131, LFO2_DEST1_pos); 
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
        //send change to teensy (lfo2 amount to vco 1 PWM dac) ID_PWM1_LFO2_AMOUNT 135 
            byte LFO2_DEST2_pos = (byte)(LFO2_DEST2_position + 100);
            transmitVal(135, LFO2_DEST2_pos); 
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
        //the different vca level in the wavemixer) ID_SHAPE1_LFO2_AMOUNT 139 
            byte LFO2_DEST3_pos = (byte)(LFO2_DEST3_position + 100);
            transmitVal(139, LFO2_DEST3_pos); //TODO ID
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
        //ID_LVL1_LFO2_AMOUNT 143
            byte LFO2_DEST4_pos = (byte)(LFO2_DEST4_position + 100);
            transmitVal(143, LFO2_DEST4_pos); //TODO ID       
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
        //send change to teensy (lfo2 amount to vco 2 pitch bend dac) ID_PB2_LFO2_AMOUNT 147
            byte LFO2_DEST5_pos = (byte)(LFO2_DEST5_position + 100);
            transmitVal(147, LFO2_DEST5_pos);           

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
        //send change to teensy (lfo2 amount to vco 2 PWM dac) ID_PWM2_LFO2_AMOUNT 151 
            byte LFO2_DEST6_pos = (byte)(LFO2_DEST6_position + 100);
            transmitVal(151, LFO2_DEST6_pos);           
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
        //the different vca level in the wavemixer) ID_SHAPE2_LFO2_AMOUNT 155
            byte LFO2_DEST7_pos = (byte)(LFO2_DEST7_position + 100);
            transmitVal(155, LFO2_DEST7_pos); 
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
        //send change to teensy (lfo2 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer) ID_LVL2_LFO2_AMOUNT 159
                byte LFO2_DEST8_pos = (byte)(LFO2_DEST8_position+100);
                transmitVal(159,LFO2_DEST8_pos);
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
        //send change to teensy (lfo2 amount to FM level) ID_FM_LFO2_AMOUNT 163
            byte LFO2_DEST9_pos = (byte)(LFO2_DEST9_position + 100);
            transmitVal(163, LFO2_DEST9_pos); 
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
        //send change to teensy (lfo2 amount to cutoff) ID_CUTOFF_LFO2_AMOUNT 167
            byte LFO2_DEST10_pos = (byte)(LFO2_DEST10_position + 100);
            transmitVal(167, LFO2_DEST10_pos);  

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
        //send change to teensy (lfo2 amount to resonance) ID_RES_LFO2_AMOUNT 171 
            byte LFO2_DEST11_pos = (byte)(LFO2_DEST11_position + 100); 
            transmitVal(171,LFO2_DEST11_pos);          
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
        //send change to teensy (lfo2 amount to drive) ID_DRIVE_LFO2_AMOUNT 175
            byte LFO2_DEST12_pos = (byte)(LFO2_DEST12_position + 100); 
            transmitVal(175, LFO2_DEST12_pos);   
        }        
    }

    ///////////MULTI ON PIN 2: CONTROLS LFO PWMs//////////////////////////////////////////////////
    digitalWrite(S0, LOW);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW); 
    if (LFO_select == LOW) { //encoder controls LFO1 PWM
        LFO1_PHASE_position_prev = LFO1_PHASE_position;
        getPosition(enc_LFO_PHASE_A, enc_LFO_PHASE_B, enc_LFO_PHASE_A_prev, enc_LFO_PHASE_B_prev,LFO1_PHASE_position, mux1A, mux1B); //get new position

        if ( LFO1_PHASE_position > 127 ) { //boundary check
            LFO1_PHASE_position = 127;
            }
        if ( LFO1_PHASE_position < 0 ) {
            LFO1_PHASE_position = 0;
            }
            
        if (LFO1_PHASE_position != LFO1_PHASE_position_prev){
        //send change to teensy ID_LFO1_PHASE 106
            byte LFO1_PHASE_pos = (byte)LFO1_PHASE_position;
            transmitVal(106, LFO1_PHASE_pos); 
        }
    }
    if (LFO_select == HIGH) { //encoder controls LFO2 PWM
    
        LFO2_PHASE_position_prev = LFO2_PHASE_position;
        
        getPosition(enc_LFO_PHASE_A, enc_LFO_PHASE_B, enc_LFO_PHASE_A_prev, enc_LFO_PHASE_B_prev, LFO2_PHASE_position, mux1A, mux1B); //get new position
        
        if ( LFO2_PHASE_position > 127 ) { //boundary check
        LFO2_PHASE_position = 127;
        }
        if ( LFO2_PHASE_position < 0 ) {
        LFO2_PHASE_position = 0;
        }
        
        if (LFO2_PHASE_position != LFO2_PHASE_position_prev){
        //send change to teensy ID_LFO2_PHASE 116
            byte LFO2_PHASE_pos = (byte)LFO2_PHASE_position;
            transmitVal(116, LFO2_PHASE_pos); 
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
        //send change to teensy (ADSR1 amount to vco 1 pitch bend dac) ID_PB1_ADSR1_AMOUNT 030
            byte ADSR1_DEST1_pos = (byte)(ADSR1_DEST1_position + 100); 
            transmitVal(30, ADSR1_DEST1_pos);  
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
        //send change to teensy (ADSR1 amount to vco 1 PWM dac) ID_PWM1_ADSR1_AMOUNT 034
            byte ADSR1_DEST2_pos = (byte)(ADSR1_DEST2_position + 100); 
            transmitVal(34, ADSR1_DEST2_pos);             
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
        //the different vca level in the wavemixer) ID_SHAPE1_ADSR1_AMOUNT 038
            byte ADSR1_DEST3_pos = (byte)(ADSR1_DEST3_position + 100); 
            transmitVal(38, ADSR1_DEST3_pos); 
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
        //send change to teensy (ADSR1 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer) ID_LVL1_ADSR1_AMOUNT 042
            byte ADSR1_DEST4_pos = (byte)(ADSR1_DEST4_position + 100); 
            transmitVal(42, ADSR1_DEST4_pos, 0); 
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
        //send change to teensy (ADSR1 amount to vco 2 pitch bend dac) ID_PB2_ADSR1_AMOUNT 046
            byte ADSR1_DEST5_pos = (byte)(ADSR1_DEST5_position + 100); 
            transmitVal(46, ADSR1_DEST5_pos);         
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
        //send change to teensy (ADSR1 amount to vco 2 PWM dac) ID_PWM2_ADSR1_AMOUNT 050 
            byte ADSR1_DEST6_pos = (byte)(ADSR1_DEST6_position + 100); 
            transmitVal(50 , ADSR1_DEST6_pos);   
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
        //the different vca level in the wavemixer) ID_SHAPE2_ADSR1_AMOUNT 054
            byte ADSR1_DEST7_pos = (byte)(ADSR1_DEST7_position + 100); 
            transmitVal(54, ADSR1_DEST7_pos);   
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
        //send change to teensy (lADSR1 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer) ID_LVL2_ADSR1_AMOUNT 058
            byte ADSR1_DEST8_pos = (byte)(ADSR1_DEST8_position + 100); 
            transmitVal(58, ADSR1_DEST8_pos); 
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
        //send change to teensy (ADSR1 amount to FM level) ID_FM_ADSR1_AMOUNT 062
            byte ADSR1_DEST9_pos = (byte)(ADSR1_DEST9_position + 100); 
            transmitVal(62, ADSR1_DEST9_pos);  
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
        //send change to teensy (ADSR1 amount to cutoff) ID_CUTOFF_ADSR1_AMOUNT 066
            byte ADSR1_DEST10_pos = (byte)(ADSR1_DEST10_position + 100); 
            transmitVal(66, ADSR1_DEST10_pos);   

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
        //send change to teensy (ADSR1 amount to resonance) ID_RES_ADSR1_AMOUNT 070
            byte ADSR1_DEST11_pos = (byte)(ADSR1_DEST11_position + 100); 
            transmitVal(70, ADSR1_DEST11_pos);  
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
        //send change to teensy (ADSR1 amount to drive) ID_DRIVE_ADSR1_AMOUNT 074
            byte ADSR1_DEST12_pos = (byte)(ADSR1_DEST12_position + 100); 
            transmitVal(74, ADSR1_DEST12_pos); //TODO ID          
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
            byte VCO1_FM_AMOUNT_pos = (byte)VCO1_FM_AMOUNT_position;
            transmitVal(207,VCO1_FM_AMOUNT_pos); 

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
            byte VCO2_DETUNE_pos = (byte)VCO2_DETUNE_position_prev;
            transmitVal(208,VCO2_DETUNE_pos); 
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
        //send change to teensy (ADSR2 amount to vco 1 pitch bend dac) ID_PB1_ADSR2_AMOUNT 031 
            byte ADSR2_DEST1_pos = (byte)(ADSR2_DEST1_position + 100); 
            transmitVal(31, ADSR2_DEST11_pos);         

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
        //send change to teensy (ADSR2 amount to vco 1 PWM dac) ID_PWM1_ADSR2_AMOUNT 035
            byte ADSR2_DEST2_pos = (byte)(ADSR2_DEST2_position + 100); 
            transmitVal(35, ADSR2_DEST2_pos); 
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
        //the different vca level in the wavemixer) ID_SHAPE1_ADSR2_AMOUNT 039
            byte ADSR2_DEST3_pos = (byte)(ADSR2_DEST3_position + 100); 
            transmitVal(39, ADSR2_DEST3_pos); //TODO ID 

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
        //send change to teensy (ADSR2 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer) ID_LVL1_ADSR2_AMOUNT 043
            byte ADSR2_DEST4_pos = (byte)(ADSR2_DEST4_position + 100); 
            transmitVal(43, ADSR2_DEST4_pos); 
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
        //send change to teensy (ADSR2 amount to vco 2 pitch bend dac) ID_PB2_ADSR2_AMOUNT 047
            byte ADSR2_DEST5_pos = (byte)(ADSR2_DEST5_position + 100); 
            transmitVal(47, ADSR2_DEST5_pos); 
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
        //send change to teensy (ADSR2 amount to vco 2 PWM dac) ID_PWM2_ADSR2_AMOUNT 051 
            byte ADSR2_DEST6_pos = (byte)(ADSR2_DEST6_position + 100); 
            transmitVal(51, ADSR2_DEST6_pos); 
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
        //the different vca level in the wavemixer) ID_SHAPE2_ADSR2_AMOUNT 055
            byte ADSR2_DEST7_pos = (byte)(ADSR2_DEST7_position + 100); 
            transmitVal(55, ADSR2_DEST7_pos); 
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
        //send change to teensy (ADSR2 amount to vco 2 level, basically sets the max value of the 3 first VCAs in the wavemixer) ID_LVL2_ADSR2_AMOUNT 059
            byte ADSR2_DEST8_pos = (byte)(ADSR2_DEST8_position + 100); 
            transmitVal(59, ADSR2_DEST8_pos); 
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
        //send change to teensy (ADSR2 amount to FM level) ID_FM_ADSR2_AMOUNT 063
            byte ADSR2_DEST9_pos = (byte)(ADSR2_DEST9_position + 100); 
            transmitVal(63, ADSR2_DEST9_pos); 
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
        //send change to teensy (ADSR2 amount to cutoff) ID_CUTOFF_ADSR2_AMOUNT 067
            byte ADSR2_DEST10_pos = (byte)(ADSR2_DEST10_position + 100); 
            transmitVal(67, ADSR2_DEST10_pos); 
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
        //send change to teensy (ADSR2 amount to resonance) ID_RES_ADSR2_AMOUNT 071
            byte ADSR2_DEST11_pos = (byte)(ADSR2_DEST11_position + 100); 
            transmitVal(71, ADSR2_DEST11_pos); 
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
        //send change to teensy (ADSR2 amount to drive) ID_DRIVE_ADSR2_AMOUNT 075
            byte ADSR2_DEST12_pos = (byte)(ADSR2_DEST12_position + 100); 
            transmitVal(75, ADSR2_DEST12_pos); 
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
            transmitVal(13,ADSR1_RELEASE_pos);
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
            transmitVal(23,ADSR1_RELEASE_pos);
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
            transmitVal(11,ADSR1_DECAY_pos);
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
            transmitVal(21,ADSR2_DECAY_pos);        
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
        //send change to teensy ID_VCO1_PWM 211
            byte VCO1_PWM_pos = (byte)VCO1_PWM_position;
            transmitVal(211,VCO1_PWM_pos);
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
            byte VCO2_PWM_pos = (byte)VCO2_PWM_position;
            transmitVal(212,VCO2_PWM_pos);
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
                //send change to teensy ID_LFO1_MODE0_FREQ 101
                byte LFO1_FREQ_pos = (byte)LFO1_FREQ_position;
                transmitVal(101,LFO1_FREQ_pos);
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
                //send change to teensy ID_LFO1_MODE1_RATE 102
                byte LFO1_RATE_pos = (byte)LFO1_RATE_position;
                transmitVal(102,LFO1_RATE_pos);

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
                //send change to teensy ID_LFO2_MODE0_FREQ 111
                byte LFO2_FREQ_pos = (byte)LFO2_FREQ_position;
                transmitVal(111,LFO2_FREQ_pos);
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
                //send change to teensy ID_LFO2_MODE1_RATE 112
                byte LFO2_RATE_pos = (byte)LFO2_RATE_position;
                transmitVal(112,LFO2_RATE_pos);
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
        //send change to teensy ID_ADSR1_SUSTAIN 012
            byte ADSR1_SUSTAIN_pos = (byte)ADSR1_SUSTAIN_position;
            transmitVal(12,ADSR1_SUSTAIN_pos);
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
        //send change to teensy ID_ADSR2_SUSTAIN 022
            byte ADSR2_SUSTAIN_pos = (byte)ADSR2_SUSTAIN_position;
            transmitVal(22,ADSR2_SUSTAIN_pos);          
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

        if ( LFO1_OFFSET_position > 127 ) { //boundary check
            LFO1_OFFSET_position = 127;
            }
        if ( LFO1_OFFSET_position < 0 ) {
            LFO1_OFFSET_position = 0;
            }
            
        if (LFO1_OFFSET_position != LFO1_OFFSET_position_prev){
        //send change to teensy ID_LFO1_AMPL_OFFSET 105
            byte LFO1_OFFSET_pos = (byte)LFO1_OFFSET_position;
            transmitVal(105,LFO1_OFFSET_pos); 
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
        //send change to teensy ID_LFO2_AMPL_OFFSET 115
            byte LFO2_OFFSET_pos = (byte)LFO2_OFFSET_position;
            transmitVal(115,LFO2_OFFSET_pos);         
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
        //send change to teensy ID_LFO1_AMPL 104
            byte LFO1_AMPLITUDE_pos = (byte)LFO1_AMPLITUDE_position;
            transmitVal(104,LFO1_AMPLITUDE_pos);
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
        //send change to teensy ID_LFO2_AMPL 114
            byte LFO2_AMPLITUDE_pos = (byte)LFO2_AMPLITUDE_position;
            transmitVal(114,LFO2_AMPLITUDE_pos);
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

        if ( VCO1_SHAPE_position > 180 ) { //boundary check
            VCO1_SHAPE_position = 180;
            }
        if ( VCO1_SHAPE_position < 0 ) {
            VCO1_SHAPE_position = 0;
            }
            
        if (VCO1_SHAPE_position != VCO1_SHAPE_position_prev){
        //send change to teensy ID_VCO1_SHAPE 209
            byte VCO1_SHAPE_pos = (byte)VCO1_SHAPE_position;
            transmitVal(209, VCO1_SHAPE_pos);
        }
    }
    if (VCO_select == HIGH) { //encoder controls VCO2 SHAPE
    
    
        VCO2_SHAPE_position_prev = VCO2_SHAPE_position;
        
        getPosition(enc_VCO_SHAPE_A, enc_VCO_SHAPE_B, enc_VCO_SHAPE_A_prev, enc_VCO_SHAPE_B_prev, VCO2_SHAPE_position, mux1A, mux1B); //get new position
        
        if ( VCO2_SHAPE_position > 180 ) { //boundary check
        VCO2_SHAPE_position = 180;
        }
        if ( VCO2_SHAPE_position < 0 ) {
        VCO2_SHAPE_position = 0;
        }
        
        if (VCO2_SHAPE_position != VCO2_SHAPE_position_prev){
        //send change to teensy  
            byte VCO2_SHAPE_pos = (byte)VCO1_SHAPE_position;
            transmitVal(210, VCO2_SHAPE_pos);
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
        //send change to teensy ID_DRIVE 214
        byte DRIVE_pos = (byte)DRIVE_position;
        transmitVal(214,DRIVE_pos);
    }  
    
    ///////////////MULTI ON PIN 13: CONTROLS ADSR ATTACK//////////////////////////////////////////////
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    if (ADSR_select == LOW) { //encoder controls ADSR1 ATTACK
        ADSR1_ATTACK_position_prev =ADSR1_ATTACK_position;
        getPosition(enc_ADSR_ATTACK_A, enc_ADSR_ATTACK_B, enc_ADSR_ATTACK_A_prev, enc_ADSR_ATTACK_B_prev, ADSR1_ATTACK_position, mux1A, mux1B); //get new position

        if ( ADSR1_ATTACK_position > 127 ) { //boundary check
            ADSR1_ATTACK_position = 127;
        }
        if ( ADSR1_ATTACK_position < 0 ) {
            ADSR1_ATTACK_position = 0;
        }
            
        if (ADSR1_ATTACK_position != ADSR1_ATTACK_position_prev){
        //send change to teensy ID_ADSR1_ATTACK 010
            byte ADSR1_ATTACK_pos = (byte)ADSR1_ATTACK_position;
            transmitVal(10, ADSR1_ATTACK_pos);
        }
    }
    if (ADSR_select == HIGH) { //encoder controls ADSR2  ATTACK
        ADSR2_ATTACK_position_prev =ADSR2_ATTACK_position;
        getPosition(enc_ADSR_ATTACK_A, enc_ADSR_ATTACK_B, enc_ADSR_ATTACK_A_prev, enc_ADSR_ATTACK_B_prev, ADSR1_ATTACK_position, mux1A, mux1B); //get new position

        if ( ADSR2_ATTACK_position > 127 ) { //boundary check
            ADSR2_ATTACK_position = 127;
        }
        if ( ADSR2_ATTACK_position < 0 ) {
            ADSR2_ATTACK_position = 0;
        }
            
        if (ADSR2_ATTACK_position != ADSR1_SUSTAIN_position_prev){
        //send change to teensy ID_ADSR2_ATTACK 020
            byte ADSR2_ATTACK_pos = (byte)ADSR2_ATTACK_position;
            transmitVal(20, ADSR2_ATTACK_pos);
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
        //send change to teensy ID_VCF_RES 213
        byte RES_pos = (byte)RES_position;
        transmitVal(213,RES_pos);
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
        //send change to teensy ID_LFO1_WAVEFORM 103
            byte LFO1_SHAPE_pos = (byte)LFO1_SHAPE_position;
            transmitVal(103,LFO1_SHAPE_pos);
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
        //send change to teensy ID_LFO2_WAVEFORM 113
            byte LFO2_SHAPE_pos = (byte)LFO2_SHAPE_position;
            transmitVal(113,LFO2_SHAPE_pos);       
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
