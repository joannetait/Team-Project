// Three bytes interface is used between Arduino Due and Teensy on serial 1 port:
// Byte 1: 255 (sync byte)
// Byte 2: <control> - [0:255]
// Byte 3: <value> - [0:255]

// --------------------------------------------------
#include <MCP492X.h>      // library for DACs
#include <SPI.h>          // required for MCP492X.h
#include <lfo.h>          // required for lfo function generation
#include <adsr.h>         // required for adsr function generation

#define CHIP_SELECT_A 8 
#define CHIP_SELECT_B 9 
#define CHIP_SELECT_C 10
#define CHIP_SELECT_D 12


// DAC initialisation: DAC_A holds DAC1 and 2, DAC_B holds DAC3 and 4 and so on
MCP492X myDacA(CHIP_SELECT_A);
MCP492X myDacB(CHIP_SELECT_B);
MCP492X myDacC(CHIP_SELECT_C);
MCP492X myDacD(CHIP_SELECT_D);


#define DACSIZE 4096             // vertical resolution of the DACs

//       ID_xxxx variables below are CONTROL numbers for interfacing with Arduino Due
//       for instance: if Arduino sends over 255 - 210 - 0 - 100 that will mean that the attack of the ADSR is going to be set to 100µs
//       (Because of this definition -> #define ID_ADSR_ATTACK 210)


#define ID_SONG_BPM 250       
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
#define ID_LFO1_MODE0_FREQ  101
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
int i = 0;
byte cc_sync;
byte cc_control;
byte cc_val1;

uint8_t pitchBendChan;

unsigned long   t = 0;
unsigned long   sync_t0 = 0;
unsigned long   connected_t0 = 0;


float _freqArray[24] = {64, 48, 32, 24, 16, 12, 8, 6, 5.3333, 4, 3.2, 3, 2.667, 2, 1.333, 1, 0.667, 0.5, 0.333, 0.25, 0.167, 0.125, 0.0625, 0.03125}; //array representing the different
//bpm subdivision for sync lfos
float           bpm = 120;

int             note_priority = 2; // 0 = bottom note 1=top note 2=last note. Receive from teensy in note priority menu. Default is last note

int             VCO1_OCT = 0;
int             lfo1_ampl = DACSIZE - 1;

int             VCO1_SHAPE = 0;
int             VCO2_SHAPE = 0;

// internal classes for modulations
lfo         lfo1(DACSIZE);
adsr        adsr1(DACSIZE);

//ints for writing to DACS
int pb;
int mV;
unsigned int             PB1 = 0;
unsigned int             CUTOFF = 0;
unsigned int             RES = 0;

unsigned int             VCA4 = 0;
unsigned int             VCA5 = 0;

unsigned int             VCA8 = 0;

//parameter values, range 0/1
float           lvl1_position = 0.;
int             cutoff_position = 3000;
int             res_position = 2000;

int           vca4_position = 2000;
int           vca5_position = 3000;

float           volume_position = 0.5;

//modulation amounts value, range -1/1
float           PB1_ADSR1_AMOUNT = 0.;
float           PB1_LFO1_AMOUNT = 0.;


float           LVL1_ADSR1_AMOUNT = 0.3;
float           LVL1_LFO1_AMOUNT = 0.5;

float           CUTOFF_ADSR1_AMOUNT = 0.2;
float           CUTOFF_LFO1_AMOUNT = -0.25;

float           RES_ADSR1_AMOUNT = 0.9;
float           RES_LFO1_AMOUNT = -1;

float           DRIVE_ADSR1_AMOUNT = 0.;
float           DRIVE_LFO1_AMOUNT = 0.;

float           SHAPE1_ADSR1_AMOUNT = 0.;
float           SHAPE1_LFO1_AMOUNT = 0.;

float           SHAPE2_ADSR1_AMOUNT = 0.;
float           SHAPE2_LFO1_AMOUNT = 0.;

float           VCA7_ADSR1_AMOUNT = 0.;
float           VCA7_LFO1_AMOUNT = 0.;

int8_t          velocity;

//innitial ADSR paramaters

unsigned long   adsr_attack = 100000;               // time in µs
unsigned long   adsr_decay = 100000;                // time in µs
int             adsr_sustain = 3500;                // sustain level -> from 0 to DACSIZE-1
unsigned long   adsr_release = 1000000;  

void setup() {
  delay(100);
  
  lfo1.setAmpl(DACSIZE); // init amplitude

  sync_t0 = t;
  connected_t0 = t;

  myDacA.begin();
  myDacB.begin();
  myDacC.begin();
  myDacD.begin();

  lfo1.setMode(0);
  lfo1.setWaveForm(2); //triangle wave
  lfo1.setMode0Freq(1);

  Serial1.begin(9600); //recieve comms from UI on Serial1 RX
  
  adsr1.setAttack(adsr_attack);                // initialize attack
  adsr1.setDecay(adsr_decay);                  // initialize decay
  adsr1.setSustain(adsr_sustain);              // initialize sustain
  adsr1.setRelease(adsr_release);              // initialize release
}


//initialise arrays for MIDI input
bool notes[3][88] = {0}, initial_loop = 1;
int8_t noteOrder[3][10] = {0}, orderIndx[3] = {0};

void loop() {

  t = micros();           // take timestamp
  int8_t noteMsg, channel, d2; //re initialise before MIDI is read

  

  if (usbMIDI.read()) {
    byte type = usbMIDI.getType();
    if (type == 224) {
      // Pitch bend output from 0 to 1023 mV.  Left shift d2 by 4 to scale from 0 to 2047.
      // With DAC gain = 1X, this will yield a range from 0 to 1023 mV.  
      d2 = usbMIDI.getData2(); // d2 from 0 to 127, mid point = 64
      pb = d2 << 4;
      myDacA.analogWrite(0, pb);
    }


    switch (type) {

      case usbMIDI.NoteOff:

        adsr1.noteOff(t); //turn ADSR off

      case usbMIDI.NoteOn:

        noteMsg = usbMIDI.getData1() -18 ; // Get note number. A0 = 21, Top Note = 108
        channel = usbMIDI.getChannel() - 1; //Get channel number

        if (channel > 2) return;  // Channel 0,1,2 supported
        if ((noteMsg < 0) || (noteMsg > 49)) break;  // 49 notes of keyboard are supported = 4 octaves 
        if (type == usbMIDI.NoteOn){

          velocity = usbMIDI.getData2(); //Get velocity value
        
        }
        else velocity  = 0;
        if (velocity == 0)  {
          notes[channel][noteMsg] = false;
        }
        else {
          notes[channel][noteMsg] = true;
          adsr1.noteOn(t); //turn ADSR on
        }
        if (note_priority == 1) { // Top note priority
          mV = commandTopNote(channel); //get mV value to write to DAC
          myDacA.analogWrite(1, mV);    //write to DAC

        }
        else if (note_priority == 0) { // Bottom note priority
          mV = commandBottomNote(channel); //get mV value to write to DAC
          myDacA.analogWrite(0, mV);       //write to DAC
        }
        else { // Last note priority
          if (notes[channel][noteMsg]) {  // If note is on and using last note priority, add to ordered list
            orderIndx[channel] = (orderIndx[channel] + 1) % 10;
            noteOrder[channel][orderIndx[channel]] = noteMsg;
          }
          mV = commandLastNote(channel);//get mV value to write to DAC
          myDacA.analogWrite(1, mV); //write to DAC
        }

        break;
    }
  }
  t = micros(); //take new timestamp

  //-------------------------------write to CUTOFF---------------------------------//
  CUTOFF = (cutoff_position + (adsr1.getWave(t) * CUTOFF_ADSR1_AMOUNT + lfo1.getWave(t) * CUTOFF_LFO1_AMOUNT)); //all modulations weighted and added together
  if (CUTOFF > 4095) {
    CUTOFF = 4095;
  }
  myDacB.analogWrite(0, CUTOFF); //write to DAC

  //-------------------------------write to RES---------------------------------//
  RES = (res_position + (adsr1.getWave(t) * RES_ADSR1_AMOUNT + lfo1.getWave(t) * RES_LFO1_AMOUNT)); //all modulations weighted and added together
  if (RES > 4095) {
    RES = 4095;
  }
  myDacB.analogWrite(1, RES); //write to DAC


  //-------------------------------write to wavemixer vca4---------------------------------//
  VCA4 = (vca4_position +(adsr1.getWave(t)*SHAPE1_ADSR1_AMOUNT + lfo1.getWave(t) * SHAPE1_LFO1_AMOUNT)); //all modulations weighted and added together
  if (VCA4 > 4095) {
    VCA4 = 4095;
  }
  myDacC.analogWrite(0, VCA4); //write to DAC


  //-------------------------------write to wavemixer vca5---------------------------------//
  VCA5 = (vca5_position + (adsr1.getWave(t) *SHAPE1_ADSR1_AMOUNT + lfo1.getWave(t) * SHAPE1_LFO1_AMOUNT)); //all modulations weighted and added together
  if (VCA5 > 4095) {
    VCA5 = 4095;
  }
  myDacC.analogWrite(1, VCA5); //write to DAC


  //-------------------------------write to OUTPUT VCA---------------------------------//
  VCA8 = (volume_position * adsr1.getWave(t) * (velocity / 127)); //hard coded adsr1 to control volume enveloppe at all time, no volume mod coded for this iteration
  if (VCA8 > 4095) {
    VCA8 = 4095;
  }
  myDacD.analogWrite(0, VCA8)); //write to DAC




  //----------Check if control commands have been received from Arduino------------//
  if (Serial1.available()) {
    connected_t0 = t;
    rx_state++;
    switch (rx_state) {
      case 1:                     // first byte is always 255 for sync
        int cc_sync = Serial1.read();
        if (cc_sync != 255) {    // reset if first is not 255 sync byte
          rx_state = 0;
        }
        break;
      case 2:                     // second is the control byte / ID byte
        int cc_control = Serial1.read();
        break;
      case 3:                     // third is the value
        int value = Serial1.read();
        rx_state = 0;

        // Track specific IDs
        if (cc_control == ID_SONG_BPM) {
          bpm = ((float)value) / 10;
          lfo1.setMode1Bpm(bpm);

        }
        if (cc_control == ID_NOTE_PRIORITY) {
          note_priority = value;
        }

        // update LFO1 paramaters
        else if (cc_control == ID_LFO1_MODE) { 
          lfo1.setMode(value);
        }

        else if ((int)cc_control == ID_LFO1_MODE0_FREQ) {
          lfo1.setMode0Freq(((float)value) / 100, t);
        }

        else if (cc_control == ID_LFO1_MODE1_RATE) {
          lfo1.setMode1Rate(_freqArray[(int)value]);
        }

        else if (cc_control == ID_LFO1_AMPL) {
          lfo1_ampl = value;
          lfo1.setAmpl(lfo1_ampl);
        }

        else if (cc_control == ID_LFO1_AMPL_OFFSET) {
          lfo1.setAmplOffset(value);
        }

        else if (cc_control == ID_LFO1_WAVEFORM) {
          lfo1.setWaveForm(value);
        }

        else if (cc_control == ID_LFO1_PHASE) {
          lfo1.setMode1Phase((360 - (float)value) / 360);
        }

        // update ADSR paramaters
        else if (cc_control == ID_ADSR1_ATTACK)
          adsr1.setAttack(1000 * value);                                        // times 1000 -> conversion from ms to µs
        else if (cc_control == ID_ADSR1_DECAY)
          adsr1.setDecay(1000 * value);                                         // times 1000 -> conversion from ms to µs
        else if (cc_control == ID_ADSR1_SUSTAIN)
          adsr1.setSustain(pow(10, -1 * (float)value / 1000) * (DACSIZE - 1));  // parameter is logarithmic from 0 to -70dB -> in MaxForLive it is multiplied with -100 for transportation to the Arduino. The value sent to the Arduino is thus an INT between 0 and 7000. To convert back -> time -1 and divide by 100. Then we need to convet from log to lin, which is done with 10^x/10 -> therefore we divide by 1000 here.
        else if (cc_control == ID_ADSR1_RELEASE)
          adsr1.setRelease(1000 * value);                                       // times 1000 -> conversion from ms to µs

        // modulation amounts to pitch bend 1
        else if (cc_control == ID_PB1_ADSR1_AMOUNT) {
          PB1_ADSR1_AMOUNT = (value - 100) / 100 ;
        }
        else if (cc_control == ID_PB1_LFO1_AMOUNT) {
          PB1_LFO1_AMOUNT = (value - 100) / 100 ;
        }

        // modulation amounts to vco1 shape
        else if (cc_control == ID_SHAPE1_ADSR1_AMOUNT) {
          SHAPE1_ADSR1_AMOUNT = (value - 100) / 100 ;
        }
        else if (cc_control == ID_SHAPE1_LFO1_AMOUNT) {
          SHAPE1_LFO1_AMOUNT = (value - 100) / 100 ;
        }

        // modulation amounts to vco2 volume
        else if (cc_control == ID_LVL1_ADSR1_AMOUNT) {
          LVL1_ADSR1_AMOUNT  = (value - 100) / 100 ;
        }
        else if (cc_control == ID_LVL1_LFO1_AMOUNT) {
          LVL1_LFO1_AMOUNT = (value - 100) / 100 ;
        }

        // modulation amounts to vcf cutoff
        else if (cc_control == ID_CUTOFF_ADSR1_AMOUNT) {
          CUTOFF_ADSR1_AMOUNT  = (value - 100) / 100 ;
        }
        else if (cc_control == ID_CUTOFF_LFO1_AMOUNT) {
          CUTOFF_LFO1_AMOUNT = (value - 100) / 100 ;
        }

        // modulation amounts to vcf RESONANCE
        else if (cc_control == ID_RES_ADSR1_AMOUNT) {
          RES_ADSR1_AMOUNT  = (value - 100) / 100 ;
        }
        else if (cc_control == ID_RES_LFO1_AMOUNT) {
          RES_LFO1_AMOUNT = (value - 100) / 100 ;
        }

        // modulation amounts to DRIVE
        else if (cc_control == ID_DRIVE_ADSR1_AMOUNT) {
          DRIVE_ADSR1_AMOUNT  = (value - 100) / 100 ;
        }
        else if (cc_control == ID_DRIVE_LFO1_AMOUNT) {
          DRIVE_LFO1_AMOUNT = (value - 100) / 100 ;
        }
        // parameter positions
        else if (cc_control == ID_VCO1_OCT) {
          VCO1_OCT = value - 1 ;
        }

        else if (cc_control == ID_VCO1_LVL) {
          lvl1_position = value / 100 ;
        }

        else if (cc_control == ID_CUTOFF_POSITION ) {
          cutoff_position = value / 100 ;
        }
        else if (cc_control == ID_VCF_RES) {
          res_position = value / 100 ;
        }

        break;
    }
  }
}

int commandTopNote(int channel) {
  //returns mV value for highest note played
  int topNote = 0;
  bool noteActive = false;

  for (int i = 0; i < 88; i++) {
    if (notes[channel][i]) {
      topNote = i;
      noteActive = true;
    }
  }

  if (noteActive) {
    return note2mV(topNote);
  }
  else { // All notes are off, turn off ADSR
    adsr1.noteOff(t);
  }
}
int commandBottomNote(int channel) {
  //returns mV value for lowest note played
  int bottomNote = 0;
  bool noteActive = false;

  for (int i = 87; i >= 0; i--) {
    if (notes[channel][i]) {
      bottomNote = i;
      noteActive = true;
    }
  }

  if (noteActive) {
    return note2mV(bottomNote);
  }
  else { // All notes are off, turn ADSR off
    adsr1.noteOff(t);
  }
}

int commandLastNote(int channel) {
  //returns mV value for last note played

  int8_t noteIndx;

  for (int i = 0; i < 10; i++) {
    noteIndx = noteOrder[channel][ mod(orderIndx[channel] - i, 10) ];
    if (notes[channel][noteIndx]) {

      return note2mV(noteIndx);
    }
  }
  else { // All notes are off, turn ADSR off
    adsr1.noteOff(t);
  }
}

#define NOTE_SF 46.534f

int note2mV(int noteMsg) {
// Rescale 88 notes to 4096 mV:
//    noteMsg = 0 -> 0 mV
//    noteMsg = 87 -> 4096 mV
// DAC output will be (4095/49) = 41.364 mV per note, and 496.364 mV per octave
  unsigned int mV = (unsigned int) ((float) noteMsg * NOTE_SF * 0.9454 + 17.5); //last 2 values can be tweaked for tuning
  return mV;
}

int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}