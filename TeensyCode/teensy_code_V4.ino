// Three bytes interface is used between Arduino Due and Teensy on COM serial port:
// Byte 1: 255 (sync byte)
// Byte 2: <control> - [0:255]
// Byte 3: <value MSB> - [0:255]

// --------------------------------------------------
#include <MCP492X.h> // Include the library
#include <SPI.h>
#include <lfo.h>          // required for function generation
#include <adsr.h>         // required for function generation

#define CHIP_SELECT_A 4 // =SC1 on schematic 
//#define CHIP_SELECT_B 3 // =SC2 on schematic etc
#define CHIP_SELECT_C 10
#define CHIP_SELECT_D 9
#define CHIP_SELECT_E 8
#define CHIP_SELECT_F 7 
#define CHIP_SELECT_G 6
#define CHIP_SELECT_H 5


// DAC init: DAC_A holds DAC1 and 2, DAC_B holds DAC3 and 4 and so on
MCP492X myDacA(CHIP_SELECT_A);
//MCP492X myDacB(CHIP_SELECT_B);
MCP492X myDacC(CHIP_SELECT_C);
MCP492X myDacD(CHIP_SELECT_D);
MCP492X myDacE(CHIP_SELECT_E);
MCP492X myDacF(CHIP_SELECT_F);
MCP492X myDacG(CHIP_SELECT_G);
MCP492X myDacH(CHIP_SELECT_H);

#define DACSIZE 4096             // vertical resolution of the DACs

// NOTE: all ID_xxxx variables below are CONTROL numbers for interfacing with Arduino Due
//       for instance: if Arduino sends over 255 - 210 - 0 - 100 that will mean that the attack of the ADSR is going to be set to 100µs
//       (Because of this definition -> #define ID_ADSR_ATTACK 210)
//NOTE2: you can change these definitions as you like, but dont forget to change the according numbers in the DUE code as well.

#define ID_SONG_BPM 250       // defines the BPM
#define ID_NOTE_PRIORITY 251

#define ID_VCO1_OCT 202
#define ID_VCO1_LVL 203

#define ID_VCO2_OCT 204
#define ID_VCO2_LVL 205

#define ID_CUTOFF_POSITION 206
#define ID_VCF_RES 213
#define ID_DRIVE 214

// for ADSR1
#define ID_ADSR1_ATTACK 10
#define ID_ADSR1_DECAY 11
#define ID_ADSR1_SUSTAIN 12
#define ID_ADSR1_RELEASE 13

// for LFO1
#define ID_LFO1_MODE 100
#define ID_LFO1_MODE0_FREQ 101
#define ID_LFO1_MODE1_RATE 102
#define ID_LFO1_WAVEFORM 103
#define ID_LFO1_AMPL 104
#define ID_LFO1_AMPL_OFFSET 105
#define ID_LFO1_PHASE 106

//Destinations

#define ID_PB1_ADSR1_AMOUNT 30
#define ID_PB1_LFO1_AMOUNT 130

#define ID_SHAPE1_ADSR1_AMOUNT 38
#define ID_SHAPE1_LFO1_AMOUNT 138

#define ID_LVL1_ADSR1_AMOUNT 42
#define ID_LVL1_LFO1_AMOUNT 142
  
#define ID_PB2_ADSR1_AMOUNT 46
#define ID_PB2_LFO1_AMOUNT 146

#define ID_SHAPE2_ADSR1_AMOUNT 54
#define ID_SHAPE2_LFO1_AMOUNT 154

#define ID_LVL2_ADSR1_AMOUNT 58
#define ID_LVL2_LFO1_AMOUNT 158

#define ID_CUTOFF_ADSR1_AMOUNT 66
#define ID_CUTOFF_ADSR2_AMOUNT 67
#define ID_CUTOFF_LFO1_AMOUNT 166
#define ID_CUTOFF_LFO2_AMOUNT 167

#define ID_RES_ADSR1_AMOUNT 70
#define ID_RES_LFO1_AMOUNT 170

#define ID_DRIVE_ADSR1_AMOUNT 74
#define ID_DRIVE_LFO1_AMOUNT 174


// internal variables
int rx_state = 0;
int i=0;
byte cc_sync;
byte cc_control;
byte cc_val1;
byte cc_val2;

uint8_t pitchBendChan;

unsigned long   t = 0;
unsigned long   sync_t0 = 0;
unsigned long   connected_t0 = 0;


float _freqArray[24] = {64, 48, 32, 24, 16, 12, 8, 6, 5.3333, 4, 3.2, 3, 2.667, 2, 1.333, 1, 0.667, 0.5, 0.333, 0.25, 0.167, 0.125, 0.0625, 0.03125}; //array representing the different
                                                                                                                                                      //bpm subdivision for sync lfos
float           bpm = 120;

int             note_priority = 2; // 0 = bottom note 1=top note 2=last note //receive from teensy in note priority menu default is last note 

int             VCO1_OCT = 0;
int             VCO2_OCT =0;
int             adsr1_sample = 0; //current sample from modulation to be multiplied by amounts to relevant DACs
int             lfo1_sample = 0;
int             lfo1_ampl= DACSIZE-1;
int             VCO1_SHAPE=0;
int             VCO2_SHAPE=0;

// internal classes
lfo         lfo1(DACSIZE);
adsr        adsr1(DACSIZE); 

//ints for writing to DACS
int pb;
int mV;
int             PB1=0;  
int             PB2=0;
int             CUTOFF=0;
int             RES=0;
int             VCA1=0;
int             VCA2=0;
int             VCA3=0;
int             VCA4=0;
int             VCA5=0;
int             VCA6=0;
int             VCA7=0;
int             VCA8=0;

//parameter values, range 0/1
float           lvl1_position = 0.;
float           lvl2_position = 0.;
float           drive_position = 0.;
float           cutoff_position = 0.;
float           res_position = 0.;

float           vca1_position = 0.;
float           vca2_position = 0.;
float           vca3_position = 0.;
float           vca4_position = 0.;
float           vca5_position = 0.;
float           vca6_position = 0.;
float           volume_position = 0.; 

//modulation amounts value, range -1/1
float           PB1_ADSR1_AMOUNT = 0.;
float           PB1_LFO1_AMOUNT = 0.;

float           PB2_ADSR1_AMOUNT = 0.;
float           PB2_LFO1_AMOUNT = 0.;

float           LVL1_ADSR1_AMOUNT = 0.;
float           LVL1_LFO1_AMOUNT = 0.;

float           LVL2_ADSR1_AMOUNT = 0.;
float           LVL2_LFO1_AMOUNT = 0.;

float           CUTOFF_ADSR1_AMOUNT = 0.;
float           CUTOFF_LFO1_AMOUNT = 0.;

float           RES_ADSR1_AMOUNT = 0.;
float           RES_LFO1_AMOUNT = 0.;

float           DRIVE_ADSR1_AMOUNT = 0.;
float           DRIVE_LFO1_AMOUNT = 0.;

float           SHAPE1_ADSR1_AMOUNT = 0.;
float           SHAPE1_LFO1_AMOUNT = 0.;

float           SHAPE2_ADSR1_AMOUNT = 0.;
float           SHAPE2_LFO1_AMOUNT = 0.;

float           VCA7_ADSR1_AMOUNT = 0.;
float           VCA7_LFO1_AMOUNT = 0.;

void setup() {
  delay(100);
  lfo1.setAmpl(DACSIZE); // init amplitude

  sync_t0 = t;
  connected_t0 = t;

 // pinMode(LED_BUILTIN, OUTPUT);
 // digitalWrite(LED_BUILTIN, false);
  
  myDacA.begin();
//  myDacB.begin();
  myDacC.begin();
  myDacD.begin();
  myDacE.begin();
  myDacF.begin();
  myDacG.begin();
  myDacH.begin();
  lfo1.setMode(0);
  lfo1.setWaveForm(2); //triangle wave
  lfo1.setMode0Freq(40);

  Serial.begin(9600);

}

unsigned long trigTimer[3] = {0}; //from elkayem code, don't kno why it's in between setup and main and not in init stage
bool notes[3][88] = {0}, initial_loop = 1; 
int8_t noteOrder[3][10] = {0}, orderIndx[3] = {0};
uint8_t         pitchBendChan;   

void loop() {

    t = micros();           // take timestamp
    int8_t noteMsg, velocity, channel, d2;

    if (usbMIDI.read()) {                    
    byte type = usbMIDI.getType();
    switch (type) {
        
    case usbMIDI.NoteOff:
    case usbMIDI.NoteOn:
        noteMsg = usbMIDI.getData1() - 21; // A0 = 21, Top Note = 108
        channel = usbMIDI.getChannel()-1;
        
        if (channel > 2) return;  // Only channel 0,1,2 supported
        if ((noteMsg < 0) || (noteMsg > 87)) break;  // Only 88 notes of keyboard are supported
        if (type == usbMIDI.NoteOn) velocity = usbMIDI.getData2();
        else velocity  = 0;  
        if (velocity == 0)  {
        notes[channel][noteMsg] = false;
        adsr1.noteOff(t);
        }
        else {
        notes[channel][noteMsg] = true;
        adsr1.noteOn(t);
        }
        if (note_priority == 1){ // Top note priority
          mV=commandTopNote(channel);
          myDacC.analogWrite(0,mV);

        }
        else if (note_priority == 0){ // Bottom note priority
          mV= commandBottomNote(channel);
          myDacC.analogWrite(0,mV);
        }
        else { // Last note priority  
          if (notes[channel][noteMsg]) {  // If note is on and using last note priority, add to ordered list
              orderIndx[channel] = (orderIndx[channel]+1) % 10;
              noteOrder[channel][orderIndx[channel]] = noteMsg;                 
          }
         mV = commandLastNote(channel);
         myDacC.analogWrite(0,mV);
        }
            
        break;
        case usbMIDI.PitchBend:
        if (usbMIDI.getChannel() == pitchBendChan) {
        // Pitch bend output from 0 to 1023 mV.  Left shift d2 by 4 to scale from 0 to 2047.
        // With DAC gain = 1X, this will yield a range from 0 to 1023 mV.  Additional amplification
        // after DAC will rescale to -1 to +1V.
        d2 = usbMIDI.getData2(); // d2 from 0 to 127, mid point = 64
        pb= d2<<4;  
        myDacC.analogWrite(1,pb);
        }
         
        break;
    }
}

    adsr1_sample = adsr1.getWave(t) -2048; //current sample from modulation (0 centered) to be multiplied by amounts to relevant DACs
    lfo1_sample = lfo1.getWave(t) -2048;

    //-------------------------------write to CUTOFF---------------------------------//
    CUTOFF=int(cutoff_position*(adsr1_sample*CUTOFF_ADSR1_AMOUNT + adsr2_sample*CUTOFF_ADSR2_AMOUNT + lfo1_sample*CUTOFF_LFO1_AMOUNT + lfo2_sample*CUTOFF_LFO2_AMOUNT) + 2048); //all modulations weighted and added together 
    if (CUTOFF > 4095){
        CUTOFF=4095;
    }
    myDacD.analogWrite(0,CUTOFF); 

    //-------------------------------write to RES---------------------------------//
    RES=int(res_position*(adsr1_sample*RES_ADSR1_AMOUNT + adsr2_sample*RES_ADSR2_AMOUNT + lfo1_sample*RES_LFO1_AMOUNT + lfo2_sample*RES_LFO2_AMOUNT) + 2048); //all modulations weighted and added together 
    if (RES > 4095){
        RES=4095;
    }
    myDacD.analogWrite(1,RES); 

     //-------------------------------write to wavemixer vca5---------------------------------//
    VCA5=int(drive_position*vca5_position + 2048); 
    if (VCA5 > 4095){
        VCA5=4095;
    }
    myDacG.analogWrite(0,VCA5); 
    
    //-------------------------------write to wavemixer vca6---------------------------------//
    VCA6=int(drive_position*vca6_position + 2048); 
    if (VCA6 > 4095){
        VCA6=4095;
    }
    myDacG.analogWrite(1,VCA1); 

    //-------------------------------write to OUTPUT VCA---------------------------------//
    VCA8=int(volume_position*(adsr1_sample+2048)); //hard coded adsr1 to control volume enveloppe at all time, no volume mod coded for this iteration
    if (VCA8 > 4095){
        VCA8=4095;
    }
    myDacH.analogWrite(1,VCA8);    

//----------Check if control commands have been received from Arduino------------//
  if (Serial.available()) {
    connected_t0 = t;
    if (digitalRead(LED_BUILTIN) == 0)
      digitalWrite(LED_BUILTIN, 1);
      
    rx_state++;
    switch (rx_state) {
      case 1:                     // first byte is always 255 for sync
        cc_sync = Serial.read();
        if(cc_sync != 255) {     // reset if first is not 255 sync byte
          rx_state = 0;
        }
        break;
      case 2:                     // second is the control byte / ID byte
        cc_control = Serial.read();
        break;        
      case 3:                     // third is the most significant byte of the value
        cc_val1 = Serial.read();     
        break;
      case 4:                     // fourth is the least significant byte of the value
        cc_val2 = Serial.read();
        rx_state = 0;

        // re-compile value from its two bytes (cc_val1 is the MSB and cc_val2 the LSB)
        int value = getInt(cc_val1, cc_val2);

        // Track specific IDs
        if (cc_control == ID_SONG_BPM) {
            bpm = ((float)value)/10;
            lfo1.setMode1Bpm(bpm);
            lfo2.setMode1Bpm(bpm);
        }
        if (cc_control == ID_NOTE_PRIORITY){
            note_priority = value;
        }
              
         // LFO1
        else if (cc_control == ID_LFO1_MODE){
            lfo1.setMode(value);
        }
        else if (cc_control == ID_LFO1_MODE0_FREQ){
            lfo1.setMode0Freq(((float)value)/100, t);
        }
        else if (cc_control == ID_LFO1_MODE1_RATE){
            lfo1.setMode1Rate(_freqArray[(int)value]);
        }
        else if(cc_control == ID_LFO1_AMPL) {
            lfo1_ampl = value;
            lfo1.setAmpl(lfo1_ampl);
        }
        else if(cc_control == ID_LFO1_AMPL_OFFSET){
            lfo1.setAmplOffset(value);
        }
        else if(cc_control == ID_LFO1_WAVEFORM){
            lfo1.setWaveForm(value);
        }
        else if(cc_control == ID_LFO1_PHASE){
            lfo1.setMode1Phase((360 - (float)value) / 360); 
        }

        // ADSR1
        else if (cc_control == ID_ADSR1_ATTACK)
            adsr1.setAttack(1000*value);                                          // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR1_DECAY)
            adsr1.setDecay(1000*value);                                           // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR1_SUSTAIN)
            adsr1.setSustain(pow(10, -1*(float)value/1000)*(DACSIZE - 1));        // parameter is logarithmic from 0 to -70dB -> in MaxForLive it is multiplied with -100 for transportation to the Arduino. The value sent to the Arduino is thus an INT between 0 and 7000. To convert back -> time -1 and divide by 100. Then we need to convet from log to lin, which is done with 10^x/10 -> therefore we divide by 1000 here.
        else if (cc_control == ID_ADSR1_RELEASE)
            adsr1.setRelease(1000*value);                                         // times 1000 -> conversion from ms to µs  

        // modulation amounts to pitch bend 1
        else if (cc_control == ID_PB1_ADSR1_AMOUNT){
            PB1_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB1_LFO1_AMOUNT){
            PB1_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco1 shape
        else if (cc_control == ID_SHAPE1_ADSR1_AMOUNT){
            SHAPE1_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE1_LFO1_AMOUNT){
            SHAPE1_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 volume
        else if (cc_control == ID_LVL1_ADSR1_AMOUNT){
            LVL1_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL1_LFO1_AMOUNT){
            LVL1_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to pitch bend 2
        else if (cc_control == ID_PB2_ADSR1_AMOUNT){
            PB2_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB2_LFO1_AMOUNT){
            PB2_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 shape
        else if (cc_control == ID_SHAPE2_ADSR1_AMOUNT){
            SHAPE1_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE2_LFO1_AMOUNT){
            SHAPE2_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 volume
        else if (cc_control == ID_LVL2_ADSR1_AMOUNT){
            LVL2_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL2_LFO1_AMOUNT){
            LVL2_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vcf cutoff
        else if (cc_control == ID_CUTOFF_ADSR1_AMOUNT){
            CUTOFF_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_CUTOFF_LFO1_AMOUNT){
            CUTOFF_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vcf RESONANCE
        else if (cc_control == ID_RES_ADSR1_AMOUNT){
            RES_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_RES_LFO1_AMOUNT){
            RES_LFO1_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to DRIVE
        else if (cc_control == ID_DRIVE_ADSR1_AMOUNT){
            DRIVE_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_DRIVE_LFO1_AMOUNT){
            DRIVE_LFO1_AMOUNT = (value -100)/100 ;
        }
        // parameter positions 
        else if (cc_control == ID_VCO1_OCT){
            VCO1_OCT=value -1 ;
        }
        else if (cc_control == ID_VCO2_OCT){
            VCO2_OCT=value -1 ;
        }
        else if (cc_control == ID_VCO1_LVL){
            lvl1_position = value/100 ;
        }
        else if (cc_control == ID_VCO2_LVL){
            lvl2_position = value/100 ;
        }
        else if (cc_control == ID_CUTOFF_POSITION ){
            cutoff_position = value/100 ;
        }
        else if (cc_control == ID_VCF_RES){
            res_position = value/100 ;
        }
        else if (cc_control == ID_DRIVE){
            drive_position = value/100 ;
        }

        break;
    }
  }
}

int getInt(int l_highByte, int l_lowByte) {
  return ((unsigned int)l_highByte << 8) + l_lowByte;
}

int commandTopNote(int channel){
  int topNote = 0;
  bool noteActive = false;
 
  for (int i=0; i<88; i++){
    if (notes[channel][i]) {
      topNote = i;
      noteActive = true;
    }
  }

  if (noteActive){
    return note2mV(topNote);
      }
  else{ // All notes are off, turn off gate
  // turn adsrs off
   adsr1.noteOff(t);
   adsr2.noteOff(t);
  }
}
int commandBottomNote(int channel){

  int bottomNote = 0;
  bool noteActive = false;
 
  for (int i=87; i>=0; i--){
    if (notes[channel][i]) {
      bottomNote = i;
      noteActive = true;
    }
  }

  if (noteActive){
    return note2mV(bottomNote);
   // myDacA.analogWrite(0,note2mV(bottomNote));
  }
  else{ // All notes are off, turn off gate
   // turn adsrs off
   adsr1.noteOff(t);
   adsr2.noteOff(t);
  }
}
int commandLastNote(int channel){

  int8_t noteIndx;
  
  for (int i=0; i<10; i++) {
    noteIndx = noteOrder[channel][ mod(orderIndx[channel]-i, 10) ];
    if (notes[channel][noteIndx]) {

    //  myDacA.analogWrite(0,note2mV(noteIndx));
      
      return note2mV(noteIndx);
    }
  }
  // turn adsrs off
  adsr1.noteOff(t);
  adsr2.noteOff(t);
}

// Rescale 88 notes to 4096 mV:
//    noteMsg = 0 -> 0 mV 
//    noteMsg = 87 -> 4096 mV
// DAC output will be (4095/87) = 47.069 mV per note, and 564.9655 mV per octave
// Note that DAC output will need to be amplified by 1.77X for the standard 1V/octave 
#define NOTE_SF 47.069f 

int note2mV(int noteMsg) {
  //turn ADSRs ON
  unsigned int mV = (unsigned int) ((float) noteMsg * NOTE_SF * 1.15 + 0.5);
  Serial.print("inside func");
  Serial.print(mV);
  return mV;   
 
}

int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}