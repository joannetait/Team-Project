#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder ENC_1(65, 64);
Encoder ENC_2(65, 64);
Encoder ENC_3(65, 64);
Encoder ENC_4(65, 64);
Encoder ENC_5(65, 64);
Encoder ENC_6(65, 64);
Encoder ENC_7(65, 64);
Encoder ENC_8(65, 64);
Encoder ENC_9(65, 64);
Encoder ENC_10(65, 64);
Encoder ENC_11(65, 64);
Encoder ENC_12(65, 64);
Encoder ENC_13(65, 64);
Encoder ENC_14(65, 64);
Encoder ENC_15(65, 64);
Encoder ENC_16(65, 64);
Encoder ENC_17(63, 62);
Encoder ENC_18(63, 62);
Encoder ENC_19(63, 62);
Encoder ENC_20(63, 62);

// mux adress pins
const int S0=31;
const int S1=29;
const int S2=27;
const int S3=25;

// the input pins (mux's outputs):
const int mux1A_out = 65;
const int mux1B_out = 64;
const int mux2A_out = 63;
const int mux2B_out = 62;

const int mux_enable = 23;


void setup() {
    pinMode(S0, OUTPUT);
`   pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    
    pinMode(mux1A_out, INPUT);
    pinMode(mux1B_out, INPUT);
    pinMode(mux2A_out, INPUT);
    pinMode(mux2B_out, INPUT);

    pinMode(mux_enable, OUTPUT);
    
    digitalWrite(mux_enable,LOW); 
    Serial.begin(9600);
    Serial.println("Multiplexed Encoder Test:");
  }
}

long ENC_1_position  = 0;
long ENC_2_position  = 0;
long ENC_3_position  = 0;
long ENC_4_position  = 0;
long ENC_5_position  = 0;
long ENC_6_position  = 0;
long ENC_7_position  = 0;
long ENC_8_position  = 0;
long ENC_9_position  = 0;
long ENC_10_position  = 0;
long ENC_11_position  = 0;
long ENC_12_position  = 0;
long ENC_13_position  = 0;
long ENC_14_position  = 0;
long ENC_15_position  = 0;
long ENC_16_position  = 0;
long ENC_17_position  = 0;
long ENC_18_position  = 0;
long ENC_19_position  = 0;
long ENC_20_position  = 0;

void loop() {
  long newENC_1_position, newENC_2_position, newENC_3_position, newENC_4_position, newENC_5_position ;
  long newENC_6_position, newENC_7_position, newENC_8_position, newENC_9_position, newENC_10_position ;
  long newENC_11_position, newENC_12_position, newENC_13_position, newENC_14_position, newENC_15_position ;
  long newENC_16_position, newENC_17_position, newENC_18_position, newENC_19_position, newENC_20_position ;

/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  newENC_1_position = ENC_1.read();
  newENC_17_position = ENC_17.read();
  
  if (newENC_1_position != ENC_1_position {
    Serial.print("Enc1 = ");
    Serial.print(newENC_1_position);
    Serial.println();
    ENC_1_position = newENC_1_position;
   }
   
  if (newENC_17_position != ENC_17_position {
    Serial.print("Enc17 = ");
    Serial.print(newENC_17_position);
    Serial.println();
    ENC_17_position = newENC_17_position;
   }
/////////////////////////////////////////////////////////////    
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);

  newENC_2_position = ENC_2.read();
  newENC_18_position = ENC_18.read();

if (newENC_2_position != ENC_2_position {
    Serial.print("Enc2 = ");
    Serial.print(newENC_1_position);
    Serial.println();
    ENC_2_position = newENC_2_position;
   }
   
  if (newENC_18_position != ENC_18_position {
    Serial.print("Enc18 = ");
    Serial.print(newENC_18_position);
    Serial.println();
    ENC_18_position = newENC_18_position;
   }
 
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  newENC_3_position = ENC_3.read();
  newENC_19_position = ENC_19.read();
  
  if (newENC_3_position != ENC_3_position {
    Serial.print("Enc3 = ");
    Serial.print(newENC_3_position);
    Serial.println();
    ENC_3_position = newENC_3_position;
   }
   
  if (newENC_19_position != ENC_19_position {
    Serial.print("Enc19 = ");
    Serial.print(newENC_19_position);
    Serial.println();
    ENC_19_position = newENC_19_position;
   }
///////////////////////////////////////////////////////////// 
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  
  newENC_4_position = ENC_4.read();
  newENC_20_position = ENC_20.read();
  
  if (newENC_4_position != ENC_4_position {
    Serial.print("Enc4 = ");
    Serial.print(newENC_4_position);
    Serial.println();
    ENC_4_position = newENC_4_position;
   }
   
  if (newENC_20_position != ENC_20_position {
    Serial.print("Enc20 = ");
    Serial.print(newENC_20_position);
    Serial.println();
    ENC_20_position = newENC_20_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
  newENC_5_position = ENC_5.read();

  if (newENC_5_position != ENC_5_position {
    Serial.print("Enc5 = ");
    Serial.print(newENC_5_position);
    Serial.println();
    ENC_5_position = newENC_5_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
  newENC_6_position = ENC_6.read();

  if (newENC_6_position != ENC_6_position {
    Serial.print("Enc6 = ");
    Serial.print(newENC_6_position);
    Serial.println();
    ENC_6_position = newENC_6_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
  newENC_7_position = ENC_7.read();

  if (newENC_7_position != ENC_7_position {
    Serial.print("Enc7 = ");
    Serial.print(newENC_7_position);
    Serial.println();
    ENC_7_position = newENC_7_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  
  newENC_8_position = ENC_8.read();

  if (newENC_8_position != ENC_8_position {
    Serial.print("Enc8 = ");
    Serial.print(newENC_8_position);
    Serial.println();
    ENC_8_position = newENC_8_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  newENC_9_position = ENC_9.read();

  if (newENC_9_position != ENC_9_position {
    Serial.print("Enc9 = ");
    Serial.print(newENC_9_position);
    Serial.println();
    ENC_9_position = newENC_9_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  newENC_10_position = ENC_10.read();

  if (newENC_10_position != ENC_10_position {
    Serial.print("Enc10 = ");
    Serial.print(newENC_10_position);
    Serial.println();
    ENC_10_position = newENC_10_position;
   }
//////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  newENC_11_position = ENC_11.read();

  if (newENC_11_position != ENC_11_position {
    Serial.print("Enc11 = ");
    Serial.print(newENC_11_position);
    Serial.println();
    ENC_11_position = newENC_11_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  
  newENC_12_position = ENC_12.read();

  if (newENC_12_position != ENC_12_position {
    Serial.print("Enc12 = ");
    Serial.print(newENC_12_position);
    Serial.println();
    ENC_12_position = newENC_12_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  newENC_13_position = ENC_13.read();

  if (newENC_13_position != ENC_13_position {
    Serial.print("Enc13 = ");
    Serial.print(newENC_13_position);
    Serial.println();
    ENC_13_position = newENC_13_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  newENC_14_position = ENC_14.read();

  if (newENC_14_position != ENC_14_position {
    Serial.print("Enc14 = ");
    Serial.print(newENC_14_position);
    Serial.println();
    ENC_14_position = newENC_14_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  newENC_15_position = ENC_15.read();

  if (newENC_15_position != ENC_15_position {
    Serial.print("Enc15 = ");
    Serial.print(newENC_15_position);
    Serial.println();
    ENC_15_position = newENC_15_position;
   }
/////////////////////////////////////////////////////////////
  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  
  newENC_16_position = ENC_16.read();

  if (newENC_16_position != ENC_16_position {
    Serial.print("Enc16 = ");
    Serial.print(newENC_16_position);
    Serial.println();
    ENC_16_position = newENC_16_position;
   }
/////////////////////////////////////////////////////////////
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  //if (Serial.available()) {
  //  Serial.read();
  //  Serial.println("Reset both knobs to zero");
  //  knobLeft.write(0);
  //  knobRight.write(0);
  //}
}
