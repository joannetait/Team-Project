# include <EEPROM.h>
# include <SPI.h>
# include <GD2.h>

//********************* setup, display startup screen ********************

void setup()
{
    GD.begin(); //start the display
    Serial.begin (9600);                    
    GD.ClearColorRGB(0x103000);
    GD.Clear();                         //clear the display
    GD.cmd_text(240, 136, 31, OPT_CENTER, "Team 1"); 
    GD.swap();              //update the display
    delay(1000);            //keep startup screen for 1s
}

void loop()
{
    int xtouch;
    int ytouch;
    int brntag;
    /******************* initial menu ******************/
    GD.Clear();                 //clear the screen (posibly not vital?)
    GD.Begin(RECTS);            //start drawing rectangles
    GD.LineWidth(5 * 5);        // corner radius 5.0 pixels 
    /* Now create a tagmask including all the rectangles. The whole rectangle carries the mask */
    GD.Tag(1);                  //create tag for rectangle 1
    GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155);      //define rectangle 1, top left + bottom right corners
    GD.Tag(2);
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

    while(xtouch >= 0)          //debounce menu select from previous
    {
        GD.get_inputs();
        xtouch = GD.inputs.x;       //x coordinates of screen press
        ytouch = GD.inputs.y;       //y coordintaes of screen press
        brntag = GD.inputs.tag;     //which tag has been pressed
    }
    int buttonpress = 0;            //assume screen is not pressed initialy
    
    while(buttonpress == 0)         //only one button can be pressed at a time
    {
        // Determine if a button has been pressed
        GD.get_inputs();
        xtouch = GD.inputs.x;
        ytouch = GD.inputs.y;
        brntag = GD.inputs.tag;
        //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
        if ((xtouch >= 0) && (brntag >0))          //has screen been pressed?
        {       //key decode loop
            //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
            buttonpress = 1;           //screen is being pressed now
           
            /*  the following is an ugly, but functioning method for checking our tagmask */
            if (brntag == 1)
            {
                retval = 1;
            }
            else if (brntag == 2)
            {
                retval = 2;
            }
            else retval = 0;
        }
     }
    while((xtouch >= 0) && (brntag >0)) //keep checking the screen for press until button is released
    {
        GD.get_inputs();
        xtouch = GD.inputs.x;
        ytouch = GD.inputs.y;
        brntag = GD.inputs.tag;
        //wait for button to be released
    }
    Serial.println(retval); //print pres value to serial monitor


    //**************** the SETTINGS screen is defined below in a similar fashion *****************//
    //********************************************************************************************//
    if(retval == 1) //if the settings button has been pressed
    {
        do
        {
            //print seetings screen and create appropriate tagmasks
            GD.Clear(); 
            GD.Begin(RECTS); 
            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
            GD.Tag(3);
            GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155); 
            GD.Tag(4);
            GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155); 
            GD.Tag(5);
            GD.Vertex2ii(30, 70); GD.Vertex2ii(220, 110); 
            GD.Tag(6);
            GD.Vertex2ii(250, 70); GD.Vertex2ii(450, 110); 
            GD.Tag(7);                      
            GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
            GD.TagMask(0);
            
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 72, 25, 0, "MIDI channel");
            GD.cmd_text(250, 72, 25, 0, "Clock");
            GD.cmd_text(30, 136, 25, OPT_CENTERY, "Brightness");
            GD.cmd_text(250, 136, 25, OPT_CENTERY, "Save");
            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
            
            GD.swap();
            //int retval;
            GD.get_inputs();
            xtouch = GD.inputs.x;
            ytouch = GD.inputs.y;
            brntag = GD.inputs.tag;

            while(xtouch >= 0)          //debounce menu select from previous
            {
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
            }
            int buttonpress = 0;
            //Draws the main menu for dual probe
            while(buttonpress == 0)
            {
            // Determine if a button has been pressed
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
                if ((xtouch >= 0) && (brntag >0))
                {       //key decode loop
                //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
                    buttonpress = 1;
                
                    if (brntag == 3)
                    {
                        retval = 3;
                    }
                    else if (brntag == 4)
                    {
                        retval = 4;
                    }
                    else if (brntag == 5)
                    {
                        retval = 5;
                    }
                    else if (brntag == 6)
                    {
                        retval = 6;
                    }
                    else if (brntag == 7)
                    {
                        retval = 7;
                    }
                    else retval = 0;
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
        } while (retval != 7);      //stay in loop until the return button is pressed
    }

    //**************** the PERFORMANCE screen is defined below *****************//
    //**************************************************************************//
    else if(retval == 2) //"performance"
    {
        do
        { //creating performance menu
            GD.Clear(); 
            GD.Begin(RECTS); 
            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
            GD.Tag(8);
            GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155); //mod matrix 
            GD.Tag(9);
            GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155); //param visuals
            GD.Tag(10);                      
            GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);  //return button position 
            GD.TagMask(0);
            
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 117, 25, 0, "Mod Matrix");
            GD.cmd_text(250, 117, 25, 0, "LIVE!");
            GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
            
            GD.swap();
            //int retval;
            GD.get_inputs();
            xtouch = GD.inputs.x;
            ytouch = GD.inputs.y;
            brntag = GD.inputs.tag;

            while(xtouch >= 0)          //debounce menu select from previous
            {
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
            }
            int buttonpress = 0;
            //Draws the main menu for dual probe
            while(buttonpress == 0)
            {
            // Determine if a button has been pressed
                GD.get_inputs();
                xtouch = GD.inputs.x;
                ytouch = GD.inputs.y;
                brntag = GD.inputs.tag;
                //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
                if ((xtouch >= 0) && (brntag >0))
                {       //key decode loop
                //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
                    buttonpress = 1;
                
                    if (brntag == 8)
                    {
                        retval = 8;
                    }
                    else if (brntag == 9)
                    {
                        retval = 9;
                    }
                    else if (brntag == 10)
                    {
                        retval = 10;
                    }
                    else retval = 0;
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
            Serial.println(retval); //print pres value to serial monitor

            //**************** the MOD MATRIX screen is defined below *****************//
            //*************************************************************************//
            if(retval == 8) //"Mod matrix"
            {
                do
                {
                    GD.Clear(); 
                    GD.Begin(RECTS); 
                    GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
                    GD.Tag(11);
                    GD.Vertex2ii(22, 22); GD.Vertex2ii(128, 58); 
                    GD.Tag(12);
                    GD.Vertex2ii(132, 22); GD.Vertex2ii(238, 58); 
                    GD.Tag(13);                      
                    GD.Vertex2ii(242, 22); GD.Vertex2ii(348, 58);
                    GD.Tag(12);
                    GD.Vertex2ii(352, 22); GD.Vertex2ii(458, 58);

                    GD.Tag(13);
                    GD.Vertex2ii(22, 62); GD.Vertex2ii(128, 98); 
                    GD.Tag(14);
                    GD.Vertex2ii(132, 62); GD.Vertex2ii(238, 98);
                    GD.Tag(15);
                    GD.Vertex2ii(242, 62); GD.Vertex2ii(348, 98); 
                    GD.Tag(16);
                    GD.Vertex2ii(352, 62); GD.Vertex2ii(458, 98);

                    GD.Tag(17);
                    GD.Vertex2ii(22, 102); GD.Vertex2ii(128, 138); 
                    GD.Tag(18);
                    GD.Vertex2ii(132, 102); GD.Vertex2ii(238, 138);
                    GD.Tag(19);
                    GD.Vertex2ii(242, 102); GD.Vertex2ii(348, 138); 
                    GD.Tag(20);
                    GD.Vertex2ii(352, 102); GD.Vertex2ii(458, 138);

                    GD.Tag(21);
                    GD.Vertex2ii(22, 142); GD.Vertex2ii(128, 178); 
                    GD.Tag(22);
                    GD.Vertex2ii(132, 142); GD.Vertex2ii(238, 178);
                    GD.Tag(23);
                    GD.Vertex2ii(242, 142); GD.Vertex2ii(348, 178); 
                    GD.Tag(24);
                    GD.Vertex2ii(352, 142); GD.Vertex2ii(458, 178);  

                    GD.Tag(25);
                    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240); //return buton as usual  

                    GD.TagMask(0);
                    
                    GD.ColorRGB(0x103000);
                    GD.cmd_text(30, 136, 25, OPT_CENTER, "MIDI channel");
                    GD.cmd_text(300, 220, 25, OPT_CENTERY, "Return"); //return button as usual
                    
                    GD.swap();
                    //int retval;
                    GD.get_inputs();
                    xtouch = GD.inputs.x;
                    ytouch = GD.inputs.y;
                    brntag = GD.inputs.tag;

                    while(xtouch >= 0)          //debounce menu select from previous
                    {
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                    }
                    int buttonpress = 0;
                    //Draws the main menu for dual probe
                    while(buttonpress == 0)
                    {
                    // Determine if a button has been pressed
                        GD.get_inputs();
                        xtouch = GD.inputs.x;
                        ytouch = GD.inputs.y;
                        brntag = GD.inputs.tag;
                        //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
                        if ((xtouch >= 0) && (brntag >0))
                        {       //key decode loop
                        //Serial.println("x %i y %i Button pressed %i \n \r ",xtouch, ytouch, brntag);
                            buttonpress = 1;
                        
                            if (brntag == 11)
                            {
                                retval = 11;
                            }
                            else if (brntag == 12)
                            {
                                retval = 12;
                            }
                            else if (brntag == 13)
                            {
                                retval = 13;
                            }
                            else if (brntag == 14)
                            {
                                retval = 14;
                            }
                            else if (brntag == 15)
                            {
                                retval = 15;
                            }
                            else if (brntag == 16)
                            {
                                retval = 16;
                            }
                            else if (brntag == 17)
                            {
                                retval = 17;
                            }
                            else if (brntag == 18)
                            {
                                retval = 18;
                            }
                            else if (brntag == 19)
                            {
                                retval = 19;
                            }
                            else if (brntag == 20)
                            {
                                retval = 20;
                            }
                            else if (brntag == 21)
                            {
                                retval = 21;
                            }
                            else if (brntag == 22)
                            {
                                retval = 22;
                            }
                            else if (brntag == 23)
                            {
                                retval = 23;
                            }
                            else if (brntag == 24)
                            {
                                retval = 24;
                            }
                            else if (brntag == 25)
                            {
                                retval = 25;
                            }
                            else retval = 0;
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
                    Serial.println(retval); //print pres value to serial monitor
                } while (retval != 25);     //stay in loop until return button is pressed
            }
        } while (retval != 10);     // stay in loop until return button is pressed
    }
}       //end of main loop
