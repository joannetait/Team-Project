
https://uofglasgow.zoom.us/j/6288081878 sent Today at 10:47
# include <EEPROM.h>
# include <SPI.h>
# include <GD2.h>
void setup()
{


    GD.begin();
    Serial.begin (9600);                    
    GD.ClearColorRGB(0x103000);
    GD.Clear();
    GD.cmd_text(240, 136, 31, OPT_CENTER, "Team 1");
    GD.swap();
    delay(1000);
}

void loop()
{
    int xtouch;
    int ytouch;
    int brntag;
    GD.Clear(); 
    GD.Begin(RECTS); 
    GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
    GD.Tag(1);
    GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155); 
    GD.Tag(2);
    GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155);
    GD.Tag(3);
    GD.Vertex2ii(300, 200); GD.Vertex2ii(450, 240);
    GD.TagMask(0);
    
    GD.ColorRGB(0x103000);
    GD.cmd_text(30, 136, 25, OPT_CENTERY, "Settings");
    GD.cmd_text(250, 136, 25, OPT_CENTERY, "Performance");
    
    GD.swap();
    int retval;
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
    while((xtouch >= 0) && (brntag >0))
    {
        GD.get_inputs();
        xtouch = GD.inputs.x;
        ytouch = GD.inputs.y;
        brntag = GD.inputs.tag;
        //wait for button to be released
    }
    Serial.println(retval); //print pres value to serial monitor

    if(retval == 1) //"settings"
    {
        do
        {
            Serial.println("we are in setrttings");
            GD.Clear(); 
            GD.Begin(RECTS); 
            GD.LineWidth(5 * 5); // corner radius 5.0 pixels 
            GD.Tag(3);
            GD.Vertex2ii(30, 115); GD.Vertex2ii(220, 155); 
            GD.Tag(4);
            GD.Vertex2ii(250, 115); GD.Vertex2ii(450, 155); 
            GD.TagMask(0);
            
            GD.ColorRGB(0x103000);
            GD.cmd_text(30, 136, 25, OPT_CENTERY, "S");
            GD.cmd_text(250, 136, 25, OPT_CENTERY, "P");
            
            GD.swap();
        } while (retbutt == 0)
    }
    if(retval == 2)
    {
        
    }*/

}
