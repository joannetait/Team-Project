#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>
#include <Bounce2.h>

static int param_1 = 69;
static int param_2 = 69;
static int param_3 = 69;
static int param_4 = 69;

// Variables to indicate which lfo/adsr amounts 
bool dest1_select = LOW;
bool dest2_select = LOW;
bool dest3_select = LOW;
bool dest4_select = LOW;
bool dest5_select = LOW;
bool dest6_select = LOW;

#define LED_data 14               // the data pin
#define LED_shiftclk 16           // the serial clock pin
#define LED_displayclk 15         // the register clock pin

// Test pin

#define TestPin 62

// mux adress pins
#define S0 31
#define S1 29
#define S2 27
#define S3 25

// the input pins (mux's outputs):
#define mux1A 69
#define mux1B 68
#define mux2A 67
#define mux2B 66
#define mux_enable 23

// define encoder button pins (get pin numbers from arduino due schematic and encoders pcb file). undefined buttons for the screen are on pin 37/35/53

#define VCO_BUTTON_PIN 43
#define FM_BUTTON_PIN 39
#define OCT_LVL_BUTTON_PIN 41
#define LFO_BUTTON_PIN 47
#define LFO_MODE_BUTTON_PIN 49
#define ADSR_BUTTON_PIN 33

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
//ENCODER 0 X 2    
int VCO1_OCT_position  = 0;
int VCO1_LVL_position  = 0;

//ENCODER 3
int VCO1_SHAPE_position  = 0;

// ENCODER 12
int CUTOFF_position  = 0;

// ENCODER 14
int RES_position  = 0;

//ENCODER 2 X 2
int LFO1_FREQ_position  = 0;
int LFO1_RATE_position =0;

//ENCODER 15
int LFO1_SHAPE_position  = 0;

//ENCODER 1
int LFO1_PHASE_position  = 0;

//ENCODER 10
int LFO1_AMPLITUDE_position  = 0;

//ENCODER 9
int LFO1_OFFSET_position  = 0;

//ENCODER 13
int ADSR1_ATTACK_position  = 0;

//ENCODER 5
int ADSR1_DECAY_position  = 0;

//ENCODER 8
int ADSR1_SUSTAIN_position  = 0;

//ENCODER 4
int ADSR1_RELEASE_position  = 0;

int VCO1_OCT_position_prev  = 0;
int VCO1_LVL_position_prev  = 0;
int VCO1_FM_AMOUNT_position_prev  = 0;
int VCO1_SHAPE_position_prev  = 0;

int CUTOFF_position_prev  = 0;
int RES_position_prev  = 0;

int LFO1_FREQ_position_prev  = 0;
int LFO1_RATE_position_prev =0;
int LFO1_SHAPE_position_prev  = 0;
int LFO1_PHASE_position_prev  = 0;
int LFO1_AMPLITUDE_position_prev  = 0;
int LFO1_OFFSET_position_prev  = 0;

int ADSR1_ATTACK_position_prev  = 0;
int ADSR1_DECAY_position_prev  = 0;
int ADSR1_SUSTAIN_position_prev = 0;
int ADSR1_RELEASE_position_prev  = 0;

//--------------multiplexer 2-----------//
//LFO1 on encoder 1
//ADSR1 on encoder 2
int LFO1_DEST1_position =0; 
int ADSR1_DEST1_position =0; 

int LFO1_DEST1_position_prev =0; 
int ADSR1_DEST1_position_prev =0; 

int LFO1_DEST2_position =0; 
int ADSR1_DEST2_position =0; 

int LFO1_DEST2_position_prev =0; 
int ADSR1_DEST2_position_prev =0; 

int LFO1_DEST3_position =0; 
int ADSR1_DEST3_position =0; 

int LFO1_DEST3_position_prev =0; 
int ADSR1_DEST3_position_prev =0; 

int LFO1_DEST4_position =0; 
int ADSR1_DEST4_position =0; 

int LFO1_DEST4_position_prev =0; 
int ADSR1_DEST4_position_prev =0; 

int LFO1_DEST5_position =0; 
int ADSR1_DEST5_position =0; 

int LFO1_DEST5_position_prev =0; 
int ADSR1_DEST5_position_prev =0; 

int LFO1_DEST6_position =0; 
int ADSR1_DEST6_position =0; 

int LFO1_DEST6_position_prev =0; 
int ADSR1_DEST6_position_prev =0; 

// Test variables
unsigned long Time = 0;
unsigned long TimePrev = 0;
bool indicator = LOW;

int retval = 0;

const char *ParamName = "Parameter:";
int ParamVal = 0;
int ParamValPrev = 0;

int DestValLFO = 0;
int DestValLFOPrev = 0;

int DestValADSR = 0;
int DestValADSRPrev = 0;

//********************* setup, display startup screen ********************

void setup(){
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

    GD.begin(); //start the display                    
    GD.ClearColorRGB(0x103000);
    GD.Clear();                         //clear the display
    GD.cmd_text(240, 136, 31, OPT_CENTER, "Team 1"); 
    GD.swap();              //update the display
    delay(1000);            //keep startup screen for 1s
    Serial.print("Starting Gameduino Skeleton 8.7");
}

void loop(){
    
    int xtouch;
    int ytouch;
    int brntag;
    //******************* initial menu ******************//
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
        updateEncoders();
        // Determine if a button has been pressed
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

            GD.cmd_text(240, 31, 30, OPT_CENTER, "Settings");
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 72, 25, 0, "MIDI channel");
            GD.cmd_text(250, 72, 25, 0, "Clock");
            GD.cmd_text(30, 136, 25, OPT_CENTERY, "Note priority");
            GD.cmd_text(250, 136, 25, OPT_CENTERY, "Save");
            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
            
            GD.swap();
            //int retval;
            GD.get_inputs();
            xtouch = GD.inputs.x;
            ytouch = GD.inputs.y;
            brntag = GD.inputs.tag;

            while(xtouch >= 0){          //debounce menu select from previous
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
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //wait for button to be released
            }
            Serial.println(retval); //print press value to serial monitor

            //-------------------- different settings here ------------------------//


            //--------------------------NOTE PRIORITY---------------------------//
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

                    GD.cmd_text(240, 31, 30, OPT_CENTER, "Note priority");
                    GD.ColorRGB(0x103000);
                    GD.cmd_text(30, 70, 25, OPT_CENTERY, "Top note");
                    GD.cmd_text(30, 120, 25, OPT_CENTERY, "Bottom note");
                    GD.cmd_text(30, 160, 25, OPT_CENTERY, "Last note");
                    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                    
                    GD.swap();
                    //int retval;
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;

                    while(xtouch >= 0){          //debounce menu select from previous
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
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;
                    
                    while(xtouch >= 0){          //debounce menu select from previous
                    
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                    }
                    int buttonpress = 0;

                    //---------------------Loop which checks the buttons----------------------//
                    while(buttonpress == 0){                        //loop while button is not being pressed
                        updateEncoders();
                        // Determine if a button has been pressed
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
                        GD.cmd_text(240, 31, 30, OPT_CENTER, "Clock");
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
                        GD.cmd_text(240, 31, 30, OPT_CENTER, "Clock");
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
        static uint16_t volume = 0;
        do{ //creating performance menu
            GD.Clear(); 
            GD.Begin(RECTS); 
            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
            GD.Tag(8);      //mode matrix
            GD.Vertex2ii(30, 160); GD.Vertex2ii(220, 200); //mod matrix 
            GD.Tag(31);
            GD.Vertex2ii(30, 60); GD.Vertex2ii(220, 100);// param 
            
            GD.Tag(10);     //return           
            GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
            GD.TagMask(0);
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 160, 25, 0, "Mod Matrix");
            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
            GD.cmd_text(30, 60, 25, 0, "Param Vis");
            GD.swap();
            //int retval;
            GD.get_inputs();
            xtouch = GD.inputs.x;
            ytouch = GD.inputs.y;
            brntag = GD.inputs.tag;

            while(xtouch >= 0){          //debounce menu select from previous
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
            }
            int buttonpress = 0;
            while(buttonpress == 0){
                updateEncoders();
                // Determine if a button has been pressed
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //--------------Track the dial---------------//
                switch (GD.inputs.track_tag & 0xff){   //' track{
                    case 9:
                    volume = GD.inputs.track_val;
                    Serial.print(volume / 516);
                    int brntag = GD.inputs.tag;
                    //-------------------send clock value to teensy----------------//
                } //' }track
                GD.Clear(); 
                //-------------Redraw the display---------------//
                GD.Tag(9); //' dial{
                GD.cmd_dial(350, 120, 65, OPT_FLAT, volume);
                GD.cmd_track(350, 120, 1, 1, 9);   //' }dial

                GD.Begin(RECTS); 
                GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                GD.Tag(8);      //mode matrix
                GD.Vertex2ii(30, 160); GD.Vertex2ii(220, 200); //mod matrix 
                GD.Tag(31);//param
                GD.Vertex2ii(30, 60); GD.Vertex2ii(220, 100);// param 
                GD.Tag(10);     //return           
                GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                GD.TagMask(0);
                GD.cmd_text(350, 31, 30, OPT_CENTER, "Volume");
                GD.ColorRGB(0x103000);
                GD.cmd_text(30, 160, 25, 0, "Mod Matrix");
                GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                GD.cmd_text(30, 60, 25, 0, "Param Vis");
                GD.swap();


                if ((xtouch >= 0) && (brntag >0)){
                    buttonpress = 1;
                    for (int i = 8; i < 32; i++){
                        if (int(brntag) == i){
                            retval = i;
                            break;
                        }
                        else retval = 0;
                    }
                }
            }  
            while((xtouch >= 0) && (brntag >0)){
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //wait for button to be released
                //--------------Track the dial---------------//
                switch (GD.inputs.track_tag & 0xff){   //' track{
                    case 9:
                    volume = GD.inputs.track_val;
                    Serial.print(volume / 516);
                    int brntag = GD.inputs.tag;
                    //-------------------send clock value to teensy----------------//
                } //' }track
                GD.Clear(); 
                //-------------Redraw the display---------------//
                GD.Tag(27); //' dial{
                GD.cmd_dial(350, 120, 65, OPT_FLAT, volume);
                GD.cmd_track(350, 120, 1, 1, 9);   //' }dial

                GD.Begin(RECTS); 
                GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                GD.Tag(8);      //mode matrix
                GD.Vertex2ii(30, 160); GD.Vertex2ii(220, 200); //mod matrix 
                GD.Tag(31);// param
                GD.Vertex2ii(30, 60); GD.Vertex2ii(220, 100);// param 
           
                GD.Tag(10);     //return           
                GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                GD.TagMask(0);
                GD.cmd_text(350, 31, 30, OPT_CENTER, "Volume");
                GD.ColorRGB(0x103000);
                GD.cmd_text(30, 160, 25, 0, "Mod Matrix");
                GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                GD.cmd_text(30, 60, 25, 0, "Param Vis");
                GD.swap();
            }
            Serial.println(retval); //print pres value to serial monitor

            //---------PARAM VISUAL MENU HERE:
             if(retval == 31){  
                do{
                    GD.Clear(); 
                    GD.Begin(RECTS); 
                    GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                    GD.Tag(32);  //return button                      
                    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                    GD.TagMask(0);
                    GD.cmd_text(30, 125, 25, OPT_CENTERY, ParamName); 
                    GD.cmd_number(40, 145, 25, OPT_SIGNED, ParamVal);;
                    GD.ColorRGB(0x103000);
                    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                    
                    GD.swap();
                
                    //int retval;
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;
                    
                    while(xtouch >= 0){          //debounce menu select from previous
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                    }
                    int buttonpress = 0;

                    while(buttonpress == 0){
                        updateEncoders();
                        if(ParamVal != ParamValPrev){
                            GD.Clear();
                            GD.Begin(RECTS); 
                            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                            GD.Tag(32);  //return button                      
                            GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
                            GD.TagMask(0);
                            //updateEncoders();
                            GD.cmd_text(40, 115, 25, OPT_CENTERY, ParamName); 
                            GD.cmd_number(40, 145, 25, OPT_SIGNED, ParamVal);
                            GD.ColorRGB(0x103000);
                            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                            GD.swap();
                            ParamValPrev = ParamVal;
                        }

                        // Determine if a button has been pressed
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        if ((xtouch >= 0) && (brntag >0))
                        {       //key decode loop
                            buttonpress = 1;
                            for (int i = 32; i < 33; i++){
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
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        //wait for button to be released
                    }
                    Serial.println(retval); //print press value to serial monitor
                }while(retval != 32);           
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
                    GD.Vertex2ii(168, 22); GD.Vertex2ii(310, 58);
                    GD.Tag(15);
                    GD.Vertex2ii(168, 62); GD.Vertex2ii(310, 98);
                    GD.Tag(16);
                    GD.Vertex2ii(168, 102); GD.Vertex2ii(310, 138);
                
                    GD.Tag(25);
                    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240); //return button as usual  

                    GD.TagMask(0);
                    
                    GD.ColorRGB(0x103000);
                    GD.cmd_text(22, 40, 25, OPT_CENTERY, "PB1");
                    GD.cmd_text(22, 80, 25, OPT_CENTERY, "LVL1");
                    GD.cmd_text(22, 120, 25, OPT_CENTERY, "SHAPE1");

                    GD.cmd_text(168, 40, 25, OPT_CENTERY, "CUTOFF");
                    GD.cmd_text(168, 80, 25, OPT_CENTERY, "RES");
                    GD.cmd_text(168, 120, 25, OPT_CENTERY, "DRIVE");
                    
                    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                    
                    GD.swap();
                    //int retval;
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;

                    while(xtouch >= 0){          //debounce menu select from previous
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
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        //wait for button to be released
                    }
                    
                    Serial.println(retval); //print pres value to serial monitor

                    if (retval == 11){          //PB1 selected
                        //------------PB1 select to HIGH-------------//
                        dest1_select = HIGH;
                        do{
                            ctrlpanel("PB1", LFO1_DEST1_position, ADSR1_DEST1_position);
                            GD.get_inputs();             //check for screen press
                            xtouch = GD.inputs.x;
                            ytouch = GD.inputs.y;
                            brntag = GD.inputs.tag;

                            while(xtouch >= 0){          //debounce menu select from previous
                                GD.get_inputs();
                                xtouch = GD.inputs.x;       //x coordinates of screen press
                                ytouch = GD.inputs.y;       //y coordintaes of screen press
                                brntag = GD.inputs.tag;     //which tag has been pressed
                            }
                            int buttonpress = 0;            //assume screen is not pressed initialy
                            
                            while(buttonpress == 0){         //only one button can be pressed at a time
                                updateEncoders();
                                if(LFO1_DEST1_position != LFO1_DEST1_position_prev || ADSR1_DEST1_position != ADSR1_DEST1_position_prev){
                                    ctrlpanel("PB1", LFO1_DEST1_position, ADSR1_DEST1_position);
                                }
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
                                {       //key decode loop
                                    buttonpress = 1;           //screen is being pressed now
                                
                                    //-----------this used to be a series of if statemnts, now a for loop----------//          
                                    for (int i = 30; i < 31; i++){
                                        if (int(brntag) == i){
                                            retval = i;
                                            break;
                                        }
                                        else retval = 0;
                                    }
                                }
                            }
                            while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                //wait for button to be released
                            }
                            Serial.println(retval); //print pres value to serial monitor
                        } while (retval != 30);     //stay in loop until return button is pressed
                        //------------PB1 select to LOW--------------//
                        dest1_select = LOW;
                    }
                    if (retval == 12){          //LVL1 selected
                        //------------LVL1 select to HIGH-------------//
                        dest2_select = HIGH;
                        do{
                            ctrlpanel("LVL1", LFO1_DEST2_position, ADSR1_DEST2_position);
                            GD.get_inputs();             //check for screen press
                            xtouch = GD.inputs.x;
                            ytouch = GD.inputs.y;
                            brntag = GD.inputs.tag;

                            while(xtouch >= 0){          //debounce menu select from previous
                                GD.get_inputs();
                                xtouch = GD.inputs.x;       //x coordinates of screen press
                                ytouch = GD.inputs.y;       //y coordintaes of screen press
                                brntag = GD.inputs.tag;     //which tag has been pressed
                            }
                            int buttonpress = 0;            //assume screen is not pressed initialy
                            
                            while(buttonpress == 0){         //only one button can be pressed at a time
                                updateEncoders();
                                if(LFO1_DEST2_position != LFO1_DEST2_position_prev || ADSR1_DEST2_position != ADSR1_DEST2_position_prev){
                                    ctrlpanel("LVL1", LFO1_DEST2_position, ADSR1_DEST2_position);
                                }
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
                                {       //key decode loop
                                    buttonpress = 1;           //screen is being pressed now
                                
                                    //-----------this used to be a series of if statemnts, now a for loop----------//          
                                    for (int i = 30; i < 31; i++){
                                        if (int(brntag) == i){
                                            retval = i;
                                            break;
                                        }
                                        else retval = 0;
                                    }
                                }
                            }
                            while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                //wait for button to be released
                            }
                            Serial.println(retval); //print pres value to serial monitor
                        } while (retval != 30);     //stay in loop until return button is pressed
                        //------------LVL1 select to LOW--------------//
                        dest2_select = LOW;
                    }
                    if (retval == 13){          //SHAPE1 selected
                        //------------SHAPE1 select to HIGH-------------//
                        dest3_select = HIGH;
                        do{
                            ctrlpanel("SHAPE1", LFO1_DEST3_position, ADSR1_DEST3_position);
                            GD.get_inputs();             //check for screen press
                            xtouch = GD.inputs.x;
                            ytouch = GD.inputs.y;
                            brntag = GD.inputs.tag;

                            while(xtouch >= 0){          //debounce menu select from previous
                                GD.get_inputs();
                                xtouch = GD.inputs.x;       //x coordinates of screen press
                                ytouch = GD.inputs.y;       //y coordintaes of screen press
                                brntag = GD.inputs.tag;     //which tag has been pressed
                            }
                            int buttonpress = 0;            //assume screen is not pressed initialy
                            
                            while(buttonpress == 0){         //only one button can be pressed at a time
                                updateEncoders();
                                if(LFO1_DEST3_position != LFO1_DEST3_position_prev || ADSR1_DEST3_position != ADSR1_DEST3_position_prev){
                                    ctrlpanel("SHAPE1", LFO1_DEST3_position, ADSR1_DEST3_position);
                                }
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
                                {       //key decode loop
                                    buttonpress = 1;           //screen is being pressed now
                                
                                    //-----------this used to be a series of if statemnts, now a for loop----------//          
                                    for (int i = 30; i < 31; i++){
                                        if (int(brntag) == i){
                                            retval = i;
                                            break;
                                        }
                                        else retval = 0;
                                    }
                                }
                            }
                            while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                //wait for button to be released
                            }
                            Serial.println(retval); //print pres value to serial monitor
                        } while (retval != 30);     //stay in loop until return button is pressed
                        //------------SHAPE1 select to LOW--------------//
                        dest3_select = LOW;
                    }
                    if (retval == 14){          //CUTOFF selected
                        //------------CUTOFF select to HIGH-------------//
                        dest4_select = HIGH;
                        do{
                            ctrlpanel("CUTOFF", LFO1_DEST4_position, ADSR1_DEST4_position);
                            GD.get_inputs();             //check for screen press
                            xtouch = GD.inputs.x;
                            ytouch = GD.inputs.y;
                            brntag = GD.inputs.tag;

                            while(xtouch >= 0){          //debounce menu select from previous
                                GD.get_inputs();
                                xtouch = GD.inputs.x;       //x coordinates of screen press
                                ytouch = GD.inputs.y;       //y coordintaes of screen press
                                brntag = GD.inputs.tag;     //which tag has been pressed
                            }
                            int buttonpress = 0;            //assume screen is not pressed initialy
                            
                            while(buttonpress == 0){         //only one button can be pressed at a time
                                updateEncoders();
                                if(LFO1_DEST4_position != LFO1_DEST4_position_prev || ADSR1_DEST4_position != ADSR1_DEST4_position_prev){
                                    ctrlpanel("CUTOFF", LFO1_DEST4_position, ADSR1_DEST4_position);
                                }
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
                                {       //key decode loop
                                    buttonpress = 1;           //screen is being pressed now
                                
                                    //-----------this used to be a series of if statemnts, now a for loop----------//          
                                    for (int i = 30; i < 31; i++){
                                        if (int(brntag) == i){
                                            retval = i;
                                            break;
                                        }
                                        else retval = 0;
                                    }
                                }
                            }
                            while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                //wait for button to be released
                            }
                            Serial.println(retval); //print pres value to serial monitor
                        } while (retval != 30);     //stay in loop until return button is pressed
                        //------------CUTOFF select to LOW--------------//
                        dest4_select = LOW;
                    }
                    if (retval == 15){          //RES selected
                        //------------RES select to HIGH-------------//
                        dest5_select = HIGH;
                        do{
                            ctrlpanel("RES", LFO1_DEST5_position, ADSR1_DEST5_position);
                            GD.get_inputs();             //check for screen press
                            xtouch = GD.inputs.x;
                            ytouch = GD.inputs.y;
                            brntag = GD.inputs.tag;

                            while(xtouch >= 0){          //debounce menu select from previous
                                GD.get_inputs();
                                xtouch = GD.inputs.x;       //x coordinates of screen press
                                ytouch = GD.inputs.y;       //y coordintaes of screen press
                                brntag = GD.inputs.tag;     //which tag has been pressed
                            }
                            int buttonpress = 0;            //assume screen is not pressed initialy
                            
                            while(buttonpress == 0){         //only one button can be pressed at a time
                                updateEncoders();
                                if(LFO1_DEST5_position != LFO1_DEST5_position_prev || ADSR1_DEST5_position != ADSR1_DEST5_position_prev){
                                    ctrlpanel("RES", LFO1_DEST5_position, ADSR1_DEST5_position);
                                }
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
                                {       //key decode loop
                                    buttonpress = 1;           //screen is being pressed now
                                
                                    //-----------this used to be a series of if statemnts, now a for loop----------//          
                                    for (int i = 30; i < 31; i++){
                                        if (int(brntag) == i){
                                            retval = i;
                                            break;
                                        }
                                        else retval = 0;
                                    }
                                }
                            }
                            while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                //wait for button to be released
                            }
                            Serial.println(retval); //print pres value to serial monitor
                        } while (retval != 30);     //stay in loop until return button is pressed
                        //------------RES select to LOW--------------//
                        dest5_select = LOW;
                    }
                    if (retval == 16){          //DRIVE selected
                        //------------DRIVE select to HIGH-------------//
                        dest6_select = HIGH;
                        do{
                            ctrlpanel("DRIVE", LFO1_DEST6_position, ADSR1_DEST6_position);
                            GD.get_inputs();             //check for screen press
                            xtouch = GD.inputs.x;
                            ytouch = GD.inputs.y;
                            brntag = GD.inputs.tag;

                            while(xtouch >= 0){          //debounce menu select from previous
                                GD.get_inputs();
                                xtouch = GD.inputs.x;       //x coordinates of screen press
                                ytouch = GD.inputs.y;       //y coordintaes of screen press
                                brntag = GD.inputs.tag;     //which tag has been pressed
                            }
                            int buttonpress = 0;            //assume screen is not pressed initialy
                            
                            while(buttonpress == 0){         //only one button can be pressed at a time
                                updateEncoders();
                                if(LFO1_DEST6_position != LFO1_DEST6_position_prev || ADSR1_DEST6_position != ADSR1_DEST6_position_prev){
                                    ctrlpanel("DRIVE", LFO1_DEST6_position, ADSR1_DEST6_position);
                                }
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
                                {       //key decode loop
                                    buttonpress = 1;           //screen is being pressed now
                                
                                    //-----------this used to be a series of if statemnts, now a for loop----------//          
                                    for (int i = 30; i < 31; i++){
                                        if (int(brntag) == i){
                                            retval = i;
                                            break;
                                        }
                                        else retval = 0;
                                    }
                                }
                            }
                            while((xtouch >= 0) && (brntag >0)){ //keep checking the screen for press until button is released
                                GD.get_inputs();
                                xtouch = GD.inputs.x;
                                ytouch = GD.inputs.y;
                                brntag = GD.inputs.tag;
                                //wait for button to be released
                            }
                            Serial.println(retval); //print pres value to serial monitor
                        } while (retval != 30);     //stay in loop until return button is pressed
                        //------------DRIVE select to LOW--------------//
                        dest6_select = LOW;
                    }
                } while (retval != 25);     //stay in loop until return button is pressed
            }
        } while (retval != 10);     // stay in loop until return button is pressed
    }
}       //end of main loop





void ctrlpanel(const char *ctrlparam, int param_1, int param_2){
    GD.Clear();
    GD.Begin(RECTS);                //start drawing rectangles
    GD.LineWidth(5 * 5);            // corner radius 5.0 pixels 
    GD.Tag(30);
    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position
    GD.TagMask(0);
    //------------------titles on the left side-----------------//
    GD.cmd_text(40, 120, 25, OPT_CENTERY, "LFO1");


    //------------------titles on the right side-----------------//
    GD.cmd_text(260, 120, 25, OPT_CENTERY, "ADSR1");


    //------------------------title on top------------------------//
    GD.cmd_text(240, 31, 30, OPT_CENTER, ctrlparam);

    //------------------left column parameter values--------------//
    GD.cmd_number(140, 120, 25, OPT_CENTERY, param_1);

    //-------------------right column parameter values------------//
    GD.cmd_number(380, 120, 25, OPT_CENTERY, param_2);


    GD.ColorRGB(0x103000);
    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
    GD.swap();

}

void updateEncoders(){
    /*
    TimePrev = Time;
    Time = millis();
    Serial.print(1000/(Time - TimePrev));
    Serial.print("Hz ");
    */

    //------------BUTTONS-----------//
    VCOButton.update(); 
    if ( VCOButton.pressed()) {
        VCO1_OCT_position--;
        if(VCO1_OCT_position < -1){
            VCO1_OCT_position = -1;
        }
        ParamName = "VCO_OCT_LEVEL:";
        ParamVal = VCO1_OCT_position;
        byte VCO1_OCT_pos=(byte)(VCO1_OCT_position + 1);
        transmitVal(202,VCO1_OCT_pos); 
        //-----------------code to light up led------------------//
    }

    VCO_OCT_LEVEL_Button.update(); 
    if ( VCO_OCT_LEVEL_Button.pressed()) {
        VCO1_OCT_position++;
        if(VCO1_OCT_position > 2){
            VCO1_OCT_position = 2;
        }
        ParamName = "VCO_OCT_LEVEL:";
        ParamVal = VCO1_OCT_position;
        byte VCO1_OCT_pos=(byte)(VCO1_OCT_position + 1);
        transmitVal(202,VCO1_OCT_pos); 
        //-----------------code to light up led------------------//
    }

    //-------------ENCODERS-----------//
    LFO_MODE_Button.update();
    if ( LFO_MODE_Button.pressed()) {
        LFO1_MODE_select = !LFO1_MODE_select;
        if(LFO1_MODE_select){
            ParamName = "LFO1_FREQ:";
            ParamVal = LFO1_FREQ_position;
        } else {
            ParamName = "LFO1_RATE:";
            ParamVal = LFO1_RATE_position;
        }
    }

    VCO1_LVL_position_prev = VCO1_LVL_position;
    SetMuxAdd(LOW, LOW, LOW, LOW);  //ENCODER 0
    getPosition(enc_OCTLVL_A, enc_OCTLVL_B, enc_OCTLVL_A_prev, enc_OCTLVL_B_prev,VCO1_LVL_position, mux1A, mux1B); //get new position
    if (VCO1_LVL_position != VCO1_LVL_position_prev){
        ParamName = "VCO1_LVL:";
        ParamVal = VCO1_LVL_position;
        byte VCO1_LVL_pos = (byte)VCO1_LVL_position;
        transmitVal(203,VCO1_LVL_pos); 
    }
        
    VCO1_SHAPE_position_prev = VCO1_SHAPE_position;
    SetMuxAdd(LOW, LOW, HIGH, HIGH);    //ENCODER 3
    getPosition(enc_VCO_SHAPE_A, enc_VCO_SHAPE_B, enc_VCO_SHAPE_A_prev, enc_VCO_SHAPE_B_prev, VCO1_SHAPE_position, mux1A, mux1B); //get new position    
    if (VCO1_SHAPE_position != VCO1_SHAPE_position_prev){
        ParamName = "VCO1_SHAPE:";
        ParamVal = VCO1_SHAPE_position;
        //send change to teensy ID_VCO1_SHAPE 209
        byte VCO1_SHAPE_pos = (byte)VCO1_SHAPE_position;
        transmitVal(209, VCO1_SHAPE_pos);
    }

    CUTOFF_position_prev = CUTOFF_position;
    SetMuxAdd(HIGH, HIGH, LOW, LOW);    //ENCODER 12
    getPosition(enc_CUTOFF_A, enc_CUTOFF_B, enc_CUTOFF_A_prev, enc_CUTOFF_B_prev, CUTOFF_position, mux1A, mux1B); //get new position   
    if (CUTOFF_position != CUTOFF_position_prev){
        ParamName = "CUTOFF:";
        ParamVal = CUTOFF_position;
        //Serial.print(CUTOFF_position);
        //send change to teensy ID_CUTOFF 206 
        byte CUTOFF_pos = (byte)CUTOFF_position;
        transmitVal(206, CUTOFF_pos); 
    }

    RES_position_prev = RES_position;
    SetMuxAdd(HIGH, HIGH, HIGH, LOW);    //ENCODER 14
    getPosition(enc_RES_A, enc_RES_B, enc_RES_A_prev, enc_RES_B_prev, RES_position, mux1A, mux1B); //get new position
    if (RES_position != RES_position_prev){
        ParamName = "RES:";
        ParamVal = RES_position;
        //Serial.print(RES_position);
        //send change to teensy ID_VCF_RES 213
        byte RES_pos = (byte)RES_position;
        transmitVal(213,RES_pos);
    } 

    SetMuxAdd(LOW, LOW, HIGH, LOW);    //ENCODER 2
    if(LFO1_MODE_select){
        LFO1_FREQ_position_prev = LFO1_FREQ_position;
        getPosition(enc_LFO_FREQRATE_A, enc_LFO_FREQRATE_B, enc_LFO_FREQRATE_A_prev, enc_LFO_FREQRATE_B_prev, LFO1_FREQ_position, mux1A, mux1B); //get new position
        if (LFO1_FREQ_position != LFO1_FREQ_position_prev){
            ParamName = "LFO1_FREQ:";
            ParamVal = LFO1_FREQ_position;
            //Serial.print(LFO1_FREQ_position);
            //send change to teensy ID_LFO1_MODE0_FREQ 101
            byte LFO1_FREQ_pos = (byte)LFO1_FREQ_position;
            transmitVal(101,LFO1_FREQ_pos);
        }
    }else{
        LFO1_RATE_position_prev = LFO1_RATE_position;
        getPosition(enc_LFO_FREQRATE_A, enc_LFO_FREQRATE_B, enc_LFO_FREQRATE_A_prev, enc_LFO_FREQRATE_B_prev, LFO1_RATE_position, mux1A, mux1B); //get new position
        if (LFO1_RATE_position != LFO1_RATE_position_prev){
            ParamName = "LFO1_RATE:";
            ParamVal = LFO1_RATE_position;
            //send change to teensy ID_LFO1_MODE1_RATE 102
            byte LFO1_RATE_pos = (byte)LFO1_RATE_position;
            transmitVal(102,LFO1_RATE_pos);
        }
    } 
    
    LFO1_SHAPE_position_prev = LFO1_SHAPE_position;
    SetMuxAdd(HIGH, HIGH, HIGH, HIGH);    //ENCODER 15
    getPosition(enc_LFO_SHAPE_A, enc_LFO_SHAPE_B, enc_LFO_SHAPE_A_prev, enc_LFO_SHAPE_B_prev, LFO1_SHAPE_position, mux1A, mux1B); //get new position
    if (LFO1_SHAPE_position != LFO1_SHAPE_position_prev){
        ParamName = "LFO1_SHAPE:";
        ParamVal = LFO1_SHAPE_position;
        //Serial.print(LFO1_SHAPE_position);
        //send change to teensy ID_LFO1_WAVEFORM 103
        byte LFO1_SHAPE_pos = (byte)LFO1_SHAPE_position;
        transmitVal(103,LFO1_SHAPE_pos);
    }
            
    LFO1_PHASE_position_prev = LFO1_PHASE_position;
    SetMuxAdd(LOW, LOW, LOW, HIGH);    //ENCODER 1
    getPosition(enc_LFO_PHASE_A, enc_LFO_PHASE_B, enc_LFO_PHASE_A_prev, enc_LFO_PHASE_B_prev,LFO1_PHASE_position, mux1A, mux1B); //get new position    
    if (LFO1_PHASE_position != LFO1_PHASE_position_prev){
        ParamName = "LFO1_PHASE:";
        ParamVal = LFO1_PHASE_position;
        //Serial.print(LFO1_PHASE_position);
        //send change to teensy ID_LFO1_PHASE 106
        byte LFO1_PHASE_pos = (byte)LFO1_PHASE_position;
        transmitVal(106, LFO1_PHASE_pos); 
    }

    LFO1_AMPLITUDE_position_prev = LFO1_AMPLITUDE_position;
    SetMuxAdd(HIGH, LOW, HIGH, LOW);    //ENCODER 10
    getPosition(enc_LFO_AMPLITUDE_A, enc_LFO_AMPLITUDE_B, enc_LFO_AMPLITUDE_A_prev, enc_LFO_AMPLITUDE_B_prev, LFO1_AMPLITUDE_position, mux1A, mux1B); //get new position    
    if (LFO1_AMPLITUDE_position != LFO1_AMPLITUDE_position_prev){
        ParamName = "LFO1_AMPLITUDE:";
        ParamVal = LFO1_AMPLITUDE_position;
        //Serial.print(LFO1_AMPLITUDE_position);
        //send change to teensy ID_LFO1_AMPL 104
        byte LFO1_AMPLITUDE_pos = (byte)LFO1_AMPLITUDE_position;
        transmitVal(104,LFO1_AMPLITUDE_pos);
    }

    LFO1_OFFSET_position_prev = LFO1_OFFSET_position;
    SetMuxAdd(HIGH, LOW, LOW, HIGH);    //ENCODER 9
    getPosition(enc_LFO_OFFSET_A, enc_LFO_OFFSET_B, enc_LFO_OFFSET_A_prev, enc_LFO_OFFSET_B_prev, LFO1_OFFSET_position, mux1A, mux1B); //get new position
    if (LFO1_OFFSET_position_prev != LFO1_OFFSET_position){
        ParamName = "LFO1_OFFSET:";
        ParamVal = LFO1_OFFSET_position;
        //Serial.print(LFO1_OFFSET_position);
        //send change to teensy ID_LFO1_AMPL_OFFSET 105
        byte LFO1_OFFSET_pos = (byte)LFO1_OFFSET_position;
        transmitVal(105,LFO1_OFFSET_pos); 
    }
     
    ADSR1_ATTACK_position_prev =ADSR1_ATTACK_position;
    SetMuxAdd(HIGH, HIGH, LOW, HIGH);    //ENCODER 13
    getPosition(enc_ADSR_ATTACK_A, enc_ADSR_ATTACK_B, enc_ADSR_ATTACK_A_prev, enc_ADSR_ATTACK_B_prev, ADSR1_ATTACK_position, mux1A, mux1B); //get new position
    if (ADSR1_ATTACK_position != ADSR1_ATTACK_position_prev){
        ParamName = "ADSR1_ATTACK:";
        ParamVal = ADSR1_ATTACK_position;
        //Serial.print(ADSR1_ATTACK_position);
        //send change to teensy ID_ADSR1_ATTACK 010
        byte ADSR1_ATTACK_pos = (byte)ADSR1_ATTACK_position;
        transmitVal(10, ADSR1_ATTACK_pos);
    }

    ADSR1_DECAY_position_prev =ADSR1_DECAY_position;
    SetMuxAdd(LOW, HIGH, LOW, HIGH);    //ENCODER 5
    getPosition(enc_ADSR_DECAY_A, enc_ADSR_DECAY_B, enc_ADSR_DECAY_A_prev, enc_ADSR_DECAY_B_prev, ADSR1_DECAY_position, mux1A, mux1B); //get new position
     if (ADSR1_DECAY_position != ADSR1_DECAY_position_prev){
        ParamName = "ADSR1_DECAY:";
        ParamVal = ADSR1_DECAY_position;
        //Serial.print(ADSR1_DECAY_position);
        //send change to teensy ID_ADSR1_DECAY 011
        byte ADSR1_DECAY_pos = (byte)ADSR1_DECAY_position;
        transmitVal(11,ADSR1_DECAY_pos);
    }

    ADSR1_SUSTAIN_position_prev =ADSR1_SUSTAIN_position;
    SetMuxAdd(HIGH, LOW, LOW, LOW);    //ENCODER 8
    getPosition(enc_ADSR_SUSTAIN_A, enc_ADSR_SUSTAIN_B, enc_ADSR_SUSTAIN_A_prev, enc_ADSR_SUSTAIN_B_prev, ADSR1_SUSTAIN_position, mux1A, mux1B); //get new position
    if (ADSR1_SUSTAIN_position != ADSR1_SUSTAIN_position_prev){
        ParamName = "ASDR1_SUSTAIN:";
        ParamVal = ADSR1_SUSTAIN_position;
        //Serial.print(ADSR1_SUSTAIN_position);
        //send change to teensy ID_ADSR1_SUSTAIN 012
        byte ADSR1_SUSTAIN_pos = (byte)ADSR1_SUSTAIN_position;
        transmitVal(12,ADSR1_SUSTAIN_pos);
    }

    ADSR1_RELEASE_position_prev =ADSR1_RELEASE_position;
    SetMuxAdd(LOW, HIGH, LOW, LOW);    //ENCODER 4
    getPosition(enc_ADSR_RELEASE_A, enc_ADSR_RELEASE_B, enc_ADSR_RELEASE_A_prev, enc_ADSR_RELEASE_B_prev, ADSR1_RELEASE_position, mux1A, mux1B); //get new position
    if (ADSR1_RELEASE_position != ADSR1_RELEASE_position_prev){
        ParamName = "ADSR1_RELEASE";
        ParamVal = ADSR1_RELEASE_position;
        //Serial.print(ADSR1_RELEASE_position);
        //send change to teensy ID_ADSR1_RELEASE 013
        byte ADSR1_RELEASE_pos = (byte)ADSR1_RELEASE_position;
        transmitVal(13,ADSR1_RELEASE_pos);
    }
    
    //------------sending to LFO1--------------//
    //------------ENCODER 1 (MUX2)--------------//
    SetMuxAdd(LOW, LOW, LOW, HIGH);
    if (dest1_select == HIGH) {
        LFO1_DEST1_position_prev = LFO1_DEST1_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST1_position, mux2A, mux2B); //get new position
        if (LFO1_DEST1_position != LFO1_DEST1_position_prev){
            byte LFO1_DEST1_pos = (byte)LFO1_DEST1_position;
            transmitVal(130, LFO1_DEST1_pos);
        }        
    }
    if (dest2_select == HIGH) {
        LFO1_DEST2_position_prev = LFO1_DEST2_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST2_position, mux2A, mux2B); //get new position         
        if (LFO1_DEST2_position != LFO1_DEST2_position_prev){
        //send change to teensy (lfo1 amount to vco 1 PWM dac) ID_PWM1_LFO1_AMOUNT 134
            byte LFO1_DEST2_pos = (byte)LFO1_DEST2_position;
            transmitVal(134, LFO1_DEST2_pos);
            }        
    }
    if (dest3_select == HIGH) {
        LFO1_DEST3_position_prev = LFO1_DEST3_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST3_position, mux2A, mux2B); //get new position
        if (LFO1_DEST3_position != LFO1_DEST3_position_prev){
        //send change to teensy (lfo1 amount to vco 1 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer) ID_SHAPE1_LFO1_AMOUNT 138
            byte LFO1_DEST3_pos = (byte)LFO1_DEST3_position;
            transmitVal(138, LFO1_DEST3_pos); 
        }        
    }
    if (dest4_select == HIGH) {
        LFO1_DEST4_position_prev = LFO1_DEST4_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST4_position, mux2A, mux2B); //get new position
        if (LFO1_DEST4_position != LFO1_DEST4_position_prev){
        //send change to teensy (lfo1 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer)
        //ID_LVL1_LFO1_AMOUNT 142
            byte LFO1_DEST4_pos = (byte)LFO1_DEST4_position;
            transmitVal(142, LFO1_DEST4_pos);
        }        
    }
    if (dest5_select == HIGH) {
        LFO1_DEST5_position_prev = LFO1_DEST5_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST5_position, mux2A, mux2B); //get new position
        if (LFO1_DEST5_position != LFO1_DEST5_position_prev){
        //send change to teensy (lfo1 amount to vco 2 pitch bend dac) ID_PB2_LFO1_AMOUNT 146 
            byte LFO1_DEST5_pos = (byte)LFO1_DEST5_position;
            transmitVal(146, LFO1_DEST5_pos);
        }        
    }
    if (dest6_select == HIGH) {
        LFO1_DEST6_position_prev = LFO1_DEST6_position;
        getPosition(enc_TOP_LEFT_A, enc_TOP_LEFT_B, enc_TOP_LEFT_A_prev, enc_TOP_LEFT_B_prev, LFO1_DEST6_position, mux2A, mux2B); //get new position
        if (LFO1_DEST6_position != LFO1_DEST6_position_prev){
        //send change to teensy (lfo1 amount to vco 2 PWM dac) ID_PWM2_LFO1_AMOUNT 150
            byte LFO1_DEST6_pos = (byte)LFO1_DEST6_position;
            transmitVal(150, LFO1_DEST6_pos);
        }        
    }

    //-----------sending to ADSR1---------------//
    //------------ENCODER 2 (MUX2)--------------//
    SetMuxAdd(LOW, LOW, HIGH, LOW);
    if (dest1_select == HIGH) {
        ADSR1_DEST1_position_prev = ADSR1_DEST1_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST1_position, mux2A, mux2B); //get new position
        if (ADSR1_DEST1_position != ADSR1_DEST1_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 pitch bend dac) ID_PB1_ADSR1_AMOUNT 030
            byte ADSR1_DEST1_pos = (byte)ADSR1_DEST1_position;
            transmitVal(30, ADSR1_DEST1_pos);  
        }        
    }
    if (dest2_select == HIGH) {
        ADSR1_DEST2_position_prev = ADSR1_DEST2_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST2_position, mux2A, mux2B); //get new position
        if (ADSR1_DEST2_position != ADSR1_DEST2_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 PWM dac) ID_PWM1_ADSR1_AMOUNT 034
            byte ADSR1_DEST2_pos = (byte)ADSR1_DEST2_position;
            transmitVal(34, ADSR1_DEST2_pos);             
        }        
    }
    if (dest3_select == HIGH) {
        ADSR1_DEST3_position_prev = ADSR1_DEST3_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST3_position, mux2A, mux2B); //get new position
        if (ADSR1_DEST3_position != ADSR1_DEST3_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 SHAPE control, more logic to be written in between to drive
        //the different vca level in the wavemixer) ID_SHAPE1_ADSR1_AMOUNT 038
            byte ADSR1_DEST3_pos = (byte)ADSR1_DEST3_position;
            transmitVal(38, ADSR1_DEST3_pos); 
        }        
    }
    if (dest4_select == HIGH) {
        ADSR1_DEST4_position_prev = ADSR1_DEST4_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST4_position, mux2A, mux2B); //get new position
        if (ADSR1_DEST4_position != ADSR1_DEST4_position_prev){
        //send change to teensy (ADSR1 amount to vco 1 level, basically sets the max value of the 3 first VCAs in the wavemixer) ID_LVL1_ADSR1_AMOUNT 042
            byte ADSR1_DEST4_pos = (byte)ADSR1_DEST4_position;
            transmitVal(42, ADSR1_DEST4_pos); 
        }        
    }
    if (dest5_select == HIGH) {
        ADSR1_DEST5_position_prev = ADSR1_DEST5_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST5_position, mux2A, mux2B); //get new position
        if (ADSR1_DEST5_position != ADSR1_DEST5_position_prev){
        //send change to teensy (ADSR1 amount to vco 2 pitch bend dac) ID_PB2_ADSR1_AMOUNT 046
            byte ADSR1_DEST5_pos = (byte)ADSR1_DEST5_position;
            transmitVal(46, ADSR1_DEST5_pos);         
        }        
    }
    if (dest6_select == HIGH) {
        ADSR1_DEST6_position_prev = ADSR1_DEST6_position;
        getPosition(enc_BOTTOM_LEFT_A, enc_BOTTOM_LEFT_B, enc_BOTTOM_LEFT_A_prev, enc_BOTTOM_LEFT_B_prev, ADSR1_DEST6_position, mux2A, mux2B); //get new position
        if (ADSR1_DEST6_position != ADSR1_DEST6_position_prev){
        //send change to teensy (ADSR1 amount to vco 2 PWM dac) ID_PWM2_ADSR1_AMOUNT 050 
            byte ADSR1_DEST6_pos = (byte)ADSR1_DEST6_position;
            transmitVal(50 , ADSR1_DEST6_pos);   
        }        
    }
}

void SetMuxAdd(bool Sthree, bool Stwo, bool Sone, bool Snaught){
    digitalWrite(S0,Snaught); 
    digitalWrite(S1,Sone); 
    digitalWrite(S2,Stwo); 
    digitalWrite(S3,Sthree);
}

void getPosition(bool &encA,bool &encB,bool &encA_prev,bool &encB_prev, int &param_position,int muxA,int muxB) {  //send the parameter virtual pin names, their previous position, the parameter current value and
                                                                                  //the multiplexer pins on which the physical encoder is, "returns" the new parameter position.
    encA = digitalRead(muxA); //reads encoder physical position, make sure the multiplexer is set accordingly before calling function.
    encB = digitalRead(muxB);

    if (encA != encA_prev && encB == encB_prev){      //state machine begin
        if (encB == encA) {                             //test changes when pinA has changed
            param_position--;
        }
        else{
            param_position++; 
        }
    }
    
     if (encB != encB_prev && encA == encA_prev){
        if (encA == encB) {                    //test changes when pinB has changed
            param_position++;
        }
        else{
            param_position--;
        }
    }                                             //state machine end 
    
    if(param_position > 100){
        param_position = 100;
    }
    if(param_position < 0){
        param_position = 0;
    }
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