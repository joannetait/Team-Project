

GD.Clear();              //clear the display
/////create display layout here/////
GD.swap();               //update the display


GD.Begin(RECTS);            //start drawing rectangles
GD.LineWidth(5 * 5);        //corner radius 5.0 pixels 
GD.Tag(1);                  //assign tag 1 to the following button                                 
GD.Vertex2ii(30, 115);      //top left corner coordinates
GD.Vertex2ii(220, 155);     //bottom right corner coordinates  


GD.get_inputs();             //check for screen press
xtouch = GD.inputs.x;        //get x coordinates
ytouch = GD.inputs.y;        //get y coordinates
brntag = GD.inputs.tag;      //get tag of button pressed (0 if nothing pressed)


if (retval == /*menu button tag*/){         //enter new menu
    do{                                     //loop with new menu

        ////create new display and scan for touch////

//---stay in loop until return button is pressed---//
} while (retval != /*return button tag*/);     


if (retval == /*destination tag*/){          //destination selected selected
    //------------Destination select to HIGH-------------//
    dest_select = HIGH;

    ////destination menu loop here

    //------------Destination select to LOW--------------//
    dest_select = LOW;
}





