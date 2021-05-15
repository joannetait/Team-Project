# include <SPI.h>
# include <GD2.h>
static int param_1 = 69;
static int param_2 = 69;
static int param_3 = 69;
static int param_4 = 69;

//********************* setup, display startup screen ********************

void setup(){
    GD.begin(); //start the display
    Serial.begin (9600);                    
    GD.ClearColorRGB(0x103000);
    GD.Clear();                         //clear the display
    GD.cmd_text(240, 136, 31, OPT_CENTER, "Team 1"); 
    GD.swap();              //update the display
    delay(1000);            //keep startup screen for 1s
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


/*
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
*/


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
