// Three bytes interface is used between Arduino Due and Teensy on COM serial port:
// Byte 1: 255 (sync byte)
// Byte 2: <control> - [0:255]
// Byte 3: <value MSB> - [0:255]

// --------------------------------------------------
#include <MCP492X.h> // Include the library
#include <SPI.h>
#include <lfo.h>          // required for function generation
#include <adsr.h>         // required for function generation

#define CHIP_SELECT_A 14 // =SC1 on schematic 
#define CHIP_SELECT_B 13 // =SC2 on schematic etc
#define CHIP_SELECT_C 12
#define CHIP_SELECT_D 11
#define CHIP_SELECT_E 10
#define CHIP_SELECT_F 9 
#define CHIP_SELECT_G 8
#define CHIP_SELECT_H 7


// DAC init: DAC_A holds DAC1 and 2, DAC_B holds DAC3 and 4 and so on
MCP492X myDacA(CHIP_SELECT_A);
MCP492X myDacB(CHIP_SELECT_B);
MCP492X myDacC(CHIP_SELECT_C);
MCP492X myDacD(CHIP_SELECT_D);
MCP492X myDacE(CHIP_SELECT_E);
MCP492X myDacF(CHIP_SELECT_F);
MCP492X myDacG(CHIP_SELECT_G);
MCP492X myDacH(CHIP_SELECT_H);

#define DACSIZE 4096             // vertical resolution of the DACs
#define CONNECTED_TIMEOUT 500000 // LED_BUILTIN goes on for CONNECTED_TIMEOUT micro seconds whenever a serial command is received
#define CD4066_SYNC 4
#define CD4066_EXPFM 5 
#define CD4066_LINFM 6
//
// NOTE: all ID_xxxx variables below are CONTROL numbers for interfacing with Arduino Due
//       for instance: if Arduino sends over 255 - 210 - 0 - 100 that will mean that the attack of the ADSR is going to be set to 100µs
//       (Because of this definition -> #define ID_ADSR_ATTACK 210)
//NOTE2: you can change these definitions as you like, but dont forget to change the according numbers in the DUE code as well.

#define ID_SONG_BPM 250       // defines the BPM
#define ID_NOTE_PRIORITY 251

#define ID_FM_SELECT 200 
#define ID_SYNC_SELECT 201

#define ID_VCO1_OCT 202
#define ID_VCO1_LVL 203
#define ID_VCO1_SHAPE 209
#define ID_VCO1_PWM 211

#define ID_VCO2_OCT 204
#define ID_VCO2_LVL 205
#define ID_VCO2_SHAPE 210
#define ID_VCO2_PWM 212

#define ID_CUTOFF_POSITION 206
#define ID_FM_POSITON 207
#define ID_DETUNE_POSITION 208

#define ID_VCF_RES 213
#define ID_DRIVE 214

// for ADSR1
#define ID_ADSR1_ATTACK 10
#define ID_ADSR1_DECAY 11
#define ID_ADSR1_SUSTAIN 12
#define ID_ADSR1_RELEASE 13

// for ADSR2
#define ID_ADSR2_ATTACK 20
#define ID_ADSR2_DECAY 21
#define ID_ADSR2_SUSTAIN 22
#define ID_ADSR2_RELEASE 23

// for LFO1
#define ID_LFO1_MODE 100
#define ID_LFO1_MODE0_FREQ 101
#define ID_LFO1_MODE1_RATE 102
#define ID_LFO1_WAVEFORM 103
#define ID_LFO1_AMPL 104
#define ID_LFO1_AMPL_OFFSET 105
#define ID_LFO1_PHASE 106

// for LFO2
#define ID_LFO2_MODE 110
#define ID_LFO2_MODE0_FREQ 111
#define ID_LFO2_MODE1_RATE 112
#define ID_LFO2_WAVEFORM 113
#define ID_LFO2_AMPL 114
#define ID_LFO2_AMPL_OFFSET 115
#define ID_LFO2_PHASE 116

//For modulation amount to DACs
#define ID_PB1_ADSR1_AMOUNT 30
#define ID_PB1_ADSR2_AMOUNT 31
#define ID_PB1_LFO1_AMOUNT 130
#define ID_PB1_LFO2_AMOUNT 131

#define ID_PWM1_ADSR1_AMOUNT 34
#define ID_PWM1_ADSR2_AMOUNT 35
#define ID_PWM1_LFO1_AMOUNT 134
#define ID_PWM1_LFO2_AMOUNT 135

#define ID_SHAPE1_ADSR1_AMOUNT 38
#define ID_SHAPE1_ADSR2_AMOUNT 39
#define ID_SHAPE1_LFO1_AMOUNT 138
#define ID_SHAPE1_LFO2_AMOUNT 139                 

#define ID_LVL1_ADSR1_AMOUNT 42
#define ID_LVL1_ADSR2_AMOUNT 43
#define ID_LVL1_LFO1_AMOUNT 142
#define ID_LVL1_LFO2_AMOUNT 143

#define ID_PB2_ADSR1_AMOUNT 46
#define ID_PB2_ADSR2_AMOUNT 47
#define ID_PB2_LFO1_AMOUNT 146
#define ID_PB2_LFO2_AMOUNT 147

#define ID_PWM2_ADSR1_AMOUNT 50
#define ID_PWM2_ADSR2_AMOUNT 51
#define ID_PWM2_LFO1_AMOUNT 150
#define ID_PWM2_LFO2_AMOUNT 151

#define ID_SHAPE2_ADSR1_AMOUNT 54
#define ID_SHAPE2_ADSR2_AMOUNT 55
#define ID_SHAPE2_LFO1_AMOUNT 154
#define ID_SHAPE2_LFO2_AMOUNT 155

#define ID_LVL2_ADSR1_AMOUNT 58
#define ID_LVL2_ADSR2_AMOUNT 59
#define ID_LVL2_LFO1_AMOUNT 158
#define ID_LVL2_LFO2_AMOUNT 159

#define ID_FM_ADSR1_AMOUNT 62
#define ID_FM_ADSR2_AMOUNT 63
#define ID_FM_LFO1_AMOUNT 162
#define ID_FM_LFO2_AMOUNT 163

#define ID_DETUNE_ADSR1_AMOUNT 64
#define ID_DETUNE_ADSR2_AMOUNT 65
#define ID_DETUNE_LFO1_AMOUNT 164
#define ID_DETUNE_LFO2_AMOUNT 165

#define ID_CUTOFF_ADSR1_AMOUNT 66
#define ID_CUTOFF_ADSR2_AMOUNT 67
#define ID_CUTOFF_LFO1_AMOUNT 166
#define ID_CUTOFF_LFO2_AMOUNT 167

#define ID_RES_ADSR1_AMOUNT 70
#define ID_RES_ADSR2_AMOUNT 71
#define ID_RES_LFO1_AMOUNT 170
#define ID_RES_LFO2_AMOUNT 171

#define ID_DRIVE_ADSR1_AMOUNT 74
#define ID_DRIVE_ADSR2_AMOUNT 75
#define ID_DRIVE_LFO1_AMOUNT 174
#define ID_DRIVE_LFO2_AMOUNT 175

// internal variables
int rx_state = 0;
int i=0;
byte cc_sync;
byte cc_control;
byte cc_val1;
byte cc_val2;

unsigned long   t = 0;
unsigned long   sync_t0 = 0;
unsigned long   connected_t0 = 0;

uint8_t pitchBendChan;
float sfAdj[3];
float _freqArray[24] = {64, 48, 32, 24, 16, 12, 8, 6, 5.3333, 4, 3.2, 3, 2.667, 2, 1.333, 1, 0.667, 0.5, 0.333, 0.25, 0.167, 0.125, 0.0625, 0.03125}; //array representing the different
                                                                                                                                                      //bpm subdivision for sync lfos
float           bpm = 120;
int             dac0_ampl = 4095;
bool            dac0_adsr_enable = 0;
int             dac1_ampl = 4095;
bool            dac1_adsr_enable = 0;
int             note_priority = 2; // 0 = bottom note 1=top note 2=last note //receive from teensy in note priority menu default is last note 
int             VCO1_OCT = 0;
int             VCO2_OCT =0;
int             adsr1_sample = 0; //current sample from modulation to be multiplied by amounts to relevant DACs
int             adsr2_sample = 0;
int             lfo1_sample = 0;
int             lfo2_sample = 0;
int             lfo1_ampl= DACSIZE-1;
int             lfo2_ampl= DACSIZE-1;
int             VCO1_SHAPE=0;
int             VCO2_SHAPE=0;
// internal classes
lfo         lfo1(DACSIZE);
lfo         lfo2(DACSIZE);
adsr        adsr1(DACSIZE);
adsr        adsr2(DACSIZE);

//initialise integers to write to DACs
int             PB1=0;  
int             PB2=0;
int             PWM1=0;
int             PWM2=0;
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
float           fm_position = 0.;
float           detune_position = 0.;
float           cutoff_position = 0.;
float           res_position = 0.;
float           pwm1_position = 0.;
float           pwm2_position = 0.;

float           vca1_position = 0.;
float           vca2_position = 0.;
float           vca3_position = 0.;
float           vca4_position = 0.;
float           vca5_position = 0.;
float           vca6_position = 0.;
float           volume_position = 0.; 
//modulation amounts value, range -1/1
float           PB1_ADSR1_AMOUNT = 0.;
float           PB1_ADSR2_AMOUNT = 0.;
float           PB1_LFO1_AMOUNT = 0.;
float           PB1_LFO2_AMOUNT = 0.;

float           PB2_ADSR1_AMOUNT = 0.;
float           PB2_ADSR2_AMOUNT = 0.;
float           PB2_LFO1_AMOUNT = 0.;
float           PB2_LFO2_AMOUNT = 0.;

float           PWM1_ADSR1_AMOUNT = 0.;
float           PWM1_ADSR2_AMOUNT = 0.;
float           PWM1_LFO1_AMOUNT = 0.;
float           PWM1_LFO2_AMOUNT = 0.;

float           PWM2_ADSR1_AMOUNT = 0.;
float           PWM2_ADSR2_AMOUNT = 0.;
float           PWM2_LFO1_AMOUNT = 0.;
float           PWM2_LFO2_AMOUNT = 0.;

float           LVL1_ADSR1_AMOUNT = 0.;
float           LVL1_ADSR2_AMOUNT = 0.;
float           LVL1_LFO1_AMOUNT = 0.;
float           LVL1_LFO2_AMOUNT = 0.;

float           LVL2_ADSR1_AMOUNT = 0.;
float           LVL2_ADSR2_AMOUNT = 0.;
float           LVL2_LFO1_AMOUNT = 0.;
float           LVL2_LFO2_AMOUNT = 0.;

float           CUTOFF_ADSR1_AMOUNT = 0.;
float           CUTOFF_ADSR2_AMOUNT = 0.;
float           CUTOFF_LFO1_AMOUNT = 0.;
float           CUTOFF_LFO2_AMOUNT = 0.;

float           RES_ADSR1_AMOUNT = 0.;
float           RES_ADSR2_AMOUNT = 0.;
float           RES_LFO1_AMOUNT = 0.;
float           RES_LFO2_AMOUNT = 0.;

float           DRIVE_ADSR1_AMOUNT = 0.;
float           DRIVE_ADSR2_AMOUNT = 0.;
float           DRIVE_LFO1_AMOUNT = 0.;
float           DRIVE_LFO2_AMOUNT = 0.;

float           SHAPE1_ADSR1_AMOUNT = 0.;
float           SHAPE1_ADSR2_AMOUNT = 0.;
float           SHAPE1_LFO1_AMOUNT = 0.;
float           SHAPE1_LFO2_AMOUNT = 0.;

float           SHAPE2_ADSR1_AMOUNT = 0.;
float           SHAPE2_ADSR2_AMOUNT = 0.;
float           SHAPE2_LFO1_AMOUNT = 0.;
float           SHAPE2_LFO2_AMOUNT = 0.;

float           VCA7_ADSR1_AMOUNT = 0.;
float           VCA7_ADSR2_AMOUNT = 0.;
float           VCA7_LFO1_AMOUNT = 0.;
float           VCA7_LFO2_AMOUNT = 0.;

void setup() {
  delay(100);

  lfo1.setAmpl(DACSIZE); // init amplitude
  lfo2.setAmpl(DACSIZE); // init amplitude

  sync_t0 = t;
  connected_t0 = t;

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, false);
  
  myDacA.begin();
  myDacB.begin();
  myDacC.begin();
  myDacD.begin();
  myDacE.begin();
  myDacF.begin();
  myDacG.begin();
  myDacH.begin();
  
  Serial.begin(115200);
}
unsigned long trigTimer[3] = {0}; //from elkayem code, don't kno why it's in between setup and main and not in init stage
bool notes[3][88] = {0}, initial_loop = 1; 
int8_t noteOrder[3][10] = {0}, orderIndx[3] = {0};

void loop() {
    t = micros();           // take timestamp
    //from https://github.com/elkayem/usbMIDI2CV_MC/blob/master/usbMIDI2CV_MC.ino#L195
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
            adsr2.noteOff(t);
            }
            else {
            notes[channel][noteMsg] = true;
            adsr1.noteOn(t);
            adsr2.noteOn(t);
            }

            if (note_priority == 1){ // Top note priority
              commandTopNote(channel);
            }
            else if (note_priority == 0){ // Bottom note priority
              commandBottomNote(channel);
            }
            else { // Last note priority  
              if (notes[channel][noteMsg]) {  // If note is on and using last note priority, add to ordered list
                  orderIndx[channel] = (orderIndx[channel]+1) % 10;
                  noteOrder[channel][orderIndx[channel]] = noteMsg;                 
              }
              commandLastNote(channel);
            }
                
            break;

            case usbMIDI.PitchBend:
            if (usbMIDI.getChannel() == pitchBendChan) {
            // Pitch bend output from 0 to 1023 mV.  Left shift d2 by 4 to scale from 0 to 2047.
            // With DAC gain = 1X, this will yield a range from 0 to 1023 mV.  Additional amplification
            // after DAC will rescale to -1 to +1V.
            d2 = usbMIDI.getData2(); // d2 from 0 to 127, mid point = 64
            myDacA.analogWrite(1, d2<<4);  
            myDacB.analogWrite(1, d2<<4);
            }
            break;
        }
    }
    adsr1_sample = adsr1.getWave(t) -2048; //current sample from modulation (0 centered) to be multiplied by amounts to relevant DACs
    adsr2_sample = adsr2.getWave(t) -2048;
    lfo1_sample = lfo1.getWave(t) -2048;
    lfo2_sample = lfo2.getWave(t) -2048;


    //-------------------------------write to PB1---------------------------------//
    PB1=int(adsr1_sample*PB1_ADSR1_AMOUNT + adsr2_sample*PB1_ADSR2_AMOUNT + lfo1_sample*PB1_LFO1_AMOUNT + lfo2_sample*PB1_LFO2_AMOUNT + 2048); //all modulations weighted and added together 
    if (PB1 > 4095){
        PB1=4095;
    }
    myDacA.analogWrite(1,PB1); 

    //-------------------------------write to PB2---------------------------------//
    PB2= int(detune_position*(adsr1_sample*PB2_ADSR1_AMOUNT + adsr2_sample*PB2_ADSR2_AMOUNT + lfo1_sample*PB2_LFO1_AMOUNT + lfo2_sample*PB2_LFO2_AMOUNT)) + 2048; //all modulations weighted and added together 
    if (PB2 > 4095){
        PB2=4095;
    }
    myDacB.analogWrite(1,PB2); 


    //-------------------------------write to PWM1---------------------------------//
    PWM1=int(pwm1_position*(adsr1_sample*PWM1_ADSR1_AMOUNT + adsr2_sample*PWM1_ADSR2_AMOUNT + lfo1_sample*PWM1_LFO1_AMOUNT + lfo2_sample*PWM1_LFO2_AMOUNT) + 2048); //all modulations weighted and added together 
    if (PWM1 > 4095){
        PWM1=4095;
    }
    myDacC.analogWrite(0,PWM1); 

    //-------------------------------write to PWM2---------------------------------//
    PWM2=int(pwm2_position*(adsr1_sample*PWM2_ADSR1_AMOUNT + adsr2_sample*PWM2_ADSR2_AMOUNT + lfo1_sample*PWM2_LFO1_AMOUNT + lfo2_sample*PWM2_LFO2_AMOUNT) + 2048); //all modulations weighted and added together 
    if (PWM2 > 4095){
        PWM2=4095;
    }
    myDacC.analogWrite(1,PWM2); 
  
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

    //-------------------------------write to wavemixer vca1---------------------------------//
    VCA1=int(drive_position*vca1_position + 2048); 
    if (VCA1 > 4095){
        VCA1=4095;
    }
    myDacE.analogWrite(0,VCA1); 

    //-------------------------------write to wavemixer vca2---------------------------------//
    VCA2=int(drive_position*vca2_position+ 2048);
    if (VCA2 > 4095){
        VCA2=4095;
    }
    myDacE.analogWrite(1,VCA2); 

    //-------------------------------write to wavemixer vca3---------------------------------//
    VCA3=int(drive_position*vca3_position + 2048);  
    if (VCA3 > 4095){
        VCA3=4095;
    }
    myDacF.analogWrite(0,VCA3); 

    //-------------------------------write to wavemixer vca4---------------------------------//
    VCA4=int(drive_position*vca4_position + 2048); 
    if (VCA4 > 4095){
        VCA4=4095;
    }
    myDacF.analogWrite(1,VCA4); 

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

    //-------------------------------write to FM VCA---------------------------------//
    VCA7=int(fm_position*(adsr1_sample*VCA7_ADSR1_AMOUNT + adsr2_sample*VCA7_ADSR2_AMOUNT + lfo1_sample*VCA7_LFO1_AMOUNT + lfo2_sample*VCA7_LFO2_AMOUNT) + 2048); //all modulations weighted and added together 
    if (VCA7 > 4095){
        VCA7=4095;
    }
    myDacH.analogWrite(0,VCA7); 
    
    //-------------------------------write to OUTPUT VCA---------------------------------//
    VCA8=int(volume_position*(adsr1_sample+2048)); //hard coded adsr1 to control volume enveloppe at all time, no volume mod coded for this iteration
    if (VCA8 > 4095){
        VCA8=4095;
    }
    myDacH.analogWrite(1,VCA8);         




  //-------------------------------timeout led---------------------------------//
  if (digitalRead(LED_BUILTIN))
    if((t - connected_t0) > CONNECTED_TIMEOUT)
      digitalWrite(LED_BUILTIN, 0);

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
        
         // LFO2
        else if (cc_control == ID_LFO2_MODE){
            lfo2.setMode(value);
        }
        else if (cc_control == ID_LFO2_MODE0_FREQ){
            lfo2.setMode0Freq(((float)value)/100, t); // freq is tuned in steps of 0.01 -> thus divide INT received by 100  
        }
        else if (cc_control == ID_LFO2_MODE1_RATE){
            lfo2.setMode1Rate(_freqArray[(int)value]);
        }
        else if(cc_control == ID_LFO2_AMPL) {
            lfo2_ampl = value;
            lfo2.setAmpl(lfo2_ampl);
        }
        else if(cc_control == ID_LFO2_AMPL_OFFSET){
            lfo2.setAmplOffset(value);
        }
        else if(cc_control == ID_LFO2_WAVEFORM){
            lfo2.setWaveForm(value);
        }
        else if(cc_control == ID_LFO2_PHASE){
            lfo2.setMode1Phase((360 - (float)value) / 360);         
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

        // ADSR2
        else if (cc_control == ID_ADSR2_ATTACK)
            adsr2.setAttack(1000*value);                                          // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR2_DECAY)
            adsr2.setDecay(1000*value);                                           // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR2_SUSTAIN)
            adsr2.setSustain(pow(10, -1*(float)value/1000)*(DACSIZE - 1));        // parameter is logarithmic from 0 to -70dB -> in MaxForLive it is multiplied with -100 for transportation to the Arduino. The value sent to the Arduino is thus an INT between 0 and 7000. To convert back -> time -1 and divide by 100. Then we need to convet from log to lin, which is done with 10^x/10 -> therefore we divide by 1000 here.
        else if (cc_control == ID_ADSR2_RELEASE)
            adsr2.setRelease(1000*value);                                         // times 1000 -> conversion from ms to µs  
     
        // modulation amounts to pitch bend 1
        else if (cc_control == ID_PB1_ADSR1_AMOUNT){
            PB1_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB1_ADSR2_AMOUNT ){
            PB1_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB1_LFO1_AMOUNT){
            PB1_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB1_LFO2_AMOUNT){
            PB1_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco1 PWM
        else if (cc_control == ID_PWM1_ADSR1_AMOUNT){
            PWM1_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PWM1_ADSR2_AMOUNT ){
            PWM1_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PWM1_LFO1_AMOUNT){
            PWM1_LFO2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PWM1_LFO2_AMOUNT){
            PWM1_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco1 shape
        else if (cc_control == ID_SHAPE1_ADSR1_AMOUNT){
            SHAPE1_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE1_ADSR2_AMOUNT ){
            SHAPE1_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE1_LFO1_AMOUNT){
            SHAPE1_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE1_LFO2_AMOUNT){
            SHAPE1_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 volume
        else if (cc_control == ID_LVL1_ADSR1_AMOUNT){
            LVL1_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL1_ADSR2_AMOUNT ){
            LVL1_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL1_LFO1_AMOUNT){
            LVL1_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL1_LFO2_AMOUNT){
            LVL1_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to pitch bend 2
        else if (cc_control == ID_PB2_ADSR1_AMOUNT){
            PB2_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB2_ADSR2_AMOUNT ){
            PB2_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB2_LFO1_AMOUNT){
            PB2_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PB2_LFO2_AMOUNT){
            PB2_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 PWM
        else if (cc_control == ID_PWM2_ADSR1_AMOUNT){
            PWM2_ADSR1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PWM2_ADSR2_AMOUNT ){
            PWM2_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PWM2_LFO1_AMOUNT){
            PWM2_LFO2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_PWM2_LFO2_AMOUNT){
            PWM2_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 shape
        else if (cc_control == ID_SHAPE2_ADSR1_AMOUNT){
            SHAPE1_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE2_ADSR2_AMOUNT ){
            SHAPE2_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE2_LFO1_AMOUNT){
            SHAPE2_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_SHAPE2_LFO2_AMOUNT){
            SHAPE2_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vco2 volume
        else if (cc_control == ID_LVL2_ADSR1_AMOUNT){
            LVL2_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL2_ADSR2_AMOUNT ){
            LVL2_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL2_LFO1_AMOUNT){
            LVL2_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_LVL2_LFO2_AMOUNT){
            LVL2_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vcf cutoff
        else if (cc_control == ID_CUTOFF_ADSR1_AMOUNT){
            CUTOFF_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_CUTOFF_ADSR2_AMOUNT ){
            CUTOFF_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_CUTOFF_LFO1_AMOUNT){
            CUTOFF_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_CUTOFF_LFO2_AMOUNT){
            CUTOFF_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to vcf RESONANCE
        else if (cc_control == ID_RES_ADSR1_AMOUNT){
            RES_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_RES_ADSR2_AMOUNT ){
            RES_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_RES_LFO1_AMOUNT){
            RES_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_RES_LFO2_AMOUNT){
            RES_LFO2_AMOUNT = (value -100)/100 ;
        }

        // modulation amounts to DRIVE
        else if (cc_control == ID_DRIVE_ADSR1_AMOUNT){
            DRIVE_ADSR1_AMOUNT  = (value -100)/100 ;
        }
        else if (cc_control == ID_DRIVE_ADSR2_AMOUNT ){
            DRIVE_ADSR2_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_DRIVE_LFO1_AMOUNT){
            DRIVE_LFO1_AMOUNT = (value -100)/100 ;
        }
        else if (cc_control == ID_DRIVE_LFO2_AMOUNT){
            DRIVE_LFO2_AMOUNT = (value -100)/100 ;
        }

        // parameter positions 
        else if (cc_control == ID_VCO1_OCT){
            VCO1_OCT=value -1 ;
        }
        else if (cc_control == ID_VCO2_OCT){
            VCO2_OCT=value -1 ;
        }
        else if (cc_control == ID_VCO1_SHAPE ){
            VCO1_SHAPE = value*2 ;
        }
        else if (cc_control == ID_VCO2_SHAPE ){
            VCO2_SHAPE = value*2 ;
        }
        else if (cc_control == ID_VCO1_PWM){
            pwm1_position = value/100 ;
        }
        else if (cc_control == ID_VCO2_PWM){
            pwm2_position = value/100 ;
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
        else if (cc_control == ID_FM_POSITON){
            fm_position = value/100 ;
        }
        else if (cc_control == ID_DETUNE_POSITION){
            detune_position = value/100 ;
        }
        else if (cc_control == ID_VCF_RES){
            res_position = value/100 ;
        }
        else if (cc_control == ID_DRIVE){
            drive_position = value/100 ;
        }

        else if (cc_control == ID_FM_SELECT){
            if(value ==0){ //lin FM
                digitalWrite(CD4066_EXPFM,0);
                digitalWrite(CD4066_LINFM,1);
            }
            if(value ==1){ //lin FM
                digitalWrite(CD4066_LINFM,0); 
                digitalWrite(CD4066_EXPFM,1); 
            }

        }
        else if (cc_control == ID_SYNC_SELECT){
            digitalWrite(CD4066_SYNC,value);
        }

        break;
    }
  }
}

int getInt(int l_highByte, int l_lowByte) {
  return ((unsigned int)l_highByte << 8) + l_lowByte;
}

void commandTopNote(int channel){
  int topNote = 0;
  bool noteActive = false;
 
  for (int i=0; i<88; i++){
    if (notes[channel][i]) {
      topNote = i;
      noteActive = true;
    }
  }

  if (noteActive){
    commandNote(topNote, channel);
  }
  else{ // All notes are off, turn off gate
  // turn adsrs off
  }
}
void commandBottomNote(int channel){

  int bottomNote = 0;
  bool noteActive = false;
 
  for (int i=87; i>=0; i--){
    if (notes[channel][i]) {
      bottomNote = i;
      noteActive = true;
    }
  }

  if (noteActive){
    commandNote(bottomNote, channel);
  }
  else{ // All notes are off, turn off gate
   // turn adsrs off
  }
}
void commandLastNote(int channel){

  int8_t noteIndx;
  
  for (int i=0; i<10; i++) {
    noteIndx = noteOrder[channel][ mod(orderIndx[channel]-i, 10) ];
    if (notes[channel][noteIndx]) {
      commandNote(noteIndx,channel);
      return;
    }
  }
  // turn adsrs off
}

// Rescale 88 notes to 4096 mV:
//    noteMsg = 0 -> 0 mV 
//    noteMsg = 87 -> 4096 mV
// DAC output will be (4095/87) = 47.069 mV per note, and 564.9655 mV per octave
// Note that DAC output will need to be amplified by 1.77X for the standard 1V/octave 
#define NOTE_SF 47.069f 

void commandNote(int noteMsg, int channel) {
  //turn ADSRs ON
  trigTimer[channel] = millis();
  
  unsigned int mV = (unsigned int) ((float) noteMsg * NOTE_SF * sfAdj[channel] + 0.5);   
  myDacA.analogWrite(0, mV); 
  myDacC.analogWrite(0, mV); 
}

int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}
