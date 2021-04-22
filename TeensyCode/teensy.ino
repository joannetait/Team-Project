// Four bytes interface is used between Arduino Due and Teensy on COM serial port:
// Byte 1: 255 (sync byte)
// Byte 2: <control> - [0:255]
// Byte 3: <value MSB> - [0:255]
// Byte 4: <value LSB> - [0:255]

// --------------------------------------------------
#include <MCP492X.h> // Include the library
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <lfo.h>          // required for function generation
#include <adsr.h>         // required for function generation


#define CHIP_SELECT_A 28 // Or any pin you'd like to use
#define CHIP_SELECT_B 29

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
//
// NOTE: all ID_xxxx variables below are CONTROL numbers for interfacing with Arduino Due
//       for instance: if Arduino sends over 255 - 210 - 0 - 100 that will mean that the attack of the ADSR is going to be set to 100µs
//       (Because of this definition -> #define ID_ADSR_ATTACK 210)
//NOTE2: you can change these definitions as you like, but dont forget to change the according numbers in the DUE code as well.

#define ID_SONG_BPM 250       // defines the BPM

// for ADSR1
#define ID_ADSR1_ATTACK 010
#define ID_ADSR1_DECAY 011
#define ID_ADSR1_SUSTAIN 012
#define ID_ADSR1_RELEASE 013
#define ID_ADSR1_TRIGGER 014      // 0 trigger off, 1 trigger on

// for ADSR2
#define ID_ADSR2_ATTACK 020
#define ID_ADSR2_DECAY 021
#define ID_ADSR2_SUSTAIN 022
#define ID_ADSR2_RELEASE 023
#define ID_ADSR2_TRIGGER 024      // 0 trigger off, 1 trigger on

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
#define ID_DAC1_ADSR1_ENABLE 117
#define ID_DAC1_ADSR2_ENABLE 117
#define ID_DAC1_LFO1_ENABLE 107
#define ID_DAC1_LFO2_ENABLE 107
#define ID_DAC1_LFO1_AMOUNT
#define ID_DAC1_LFO2_AMOUNT
#define ID_DAC1_ADSR1_AMOUNT
#define ID_DAC1_ADSR2_AMOUNT

#define ID_DAC2_ADSR1_ENABLE 117
#define ID_DAC2_ADSR2_ENABLE 117
#define ID_DAC2_LFO1_ENABLE 107
#define ID_DAC2_LFO2_ENABLE 107

#define ID_DAC3_ADSR1_ENABLE 117
#define ID_DAC3_ADSR2_ENABLE 117
#define ID_DAC3_LFO1_ENABLE 107
#define ID_DAC3_LFO2_ENABLE 107

#define ID_DAC4_ADSR1_ENABLE 117
#define ID_DAC4_ADSR2_ENABLE 117
#define ID_DAC4_LFO1_ENABLE 107
#define ID_DAC4_LFO2_ENABLE 107

#define ID_DAC5_ADSR1_ENABLE 117
#define ID_DAC5_ADSR2_ENABLE 117
#define ID_DAC5_LFO1_ENABLE 107
#define ID_DAC5_LFO2_ENABLE 107

#define ID_DAC6_ADSR1_ENABLE 117
#define ID_DAC6_ADSR2_ENABLE 117
#define ID_DAC6_LFO1_ENABLE 107
#define ID_DAC6_LFO2_ENABLE 107

#define ID_DAC7_ADSR1_ENABLE 117
#define ID_DAC7_ADSR2_ENABLE 117
#define ID_DAC7_LFO1_ENABLE 107
#define ID_DAC7_LFO2_ENABLE 107

#define ID_DAC8_ADSR1_ENABLE 117
#define ID_DAC8_ADSR2_ENABLE 117
#define ID_DAC8_LFO1_ENABLE 107
#define ID_DAC8_LFO2_ENABLE 107

#define ID_DAC9_ADSR1_ENABLE 117
#define ID_DAC9_ADSR2_ENABLE 117
#define ID_DAC9_LFO1_ENABLE 107
#define ID_DAC9_LFO2_ENABLE 107

#define ID_DAC10_ADSR1_ENABLE 117
#define ID_DAC10_ADSR2_ENABLE 117
#define ID_DAC10_LFO1_ENABLE 107
#define ID_DAC10_LFO2_ENABLE 107

#define ID_DAC11_ADSR1_ENABLE 117
#define ID_DAC11_ADSR2_ENABLE 117
#define ID_DAC11_LFO1_ENABLE 107
#define ID_DAC11_LFO2_ENABLE 107

#define ID_DAC12_ADSR1_ENABLE 117
#define ID_DAC12_ADSR2_ENABLE 117
#define ID_DAC12_LFO1_ENABLE 107
#define ID_DAC12_LFO2_ENABLE 107

#define ID_DAC13_ADSR1_ENABLE 117
#define ID_DAC13_ADSR2_ENABLE 117
#define ID_DAC13_LFO1_ENABLE 107
#define ID_DAC13_LFO2_ENABLE 107

#define ID_DAC14_ADSR1_ENABLE 117
#define ID_DAC14_ADSR2_ENABLE 117
#define ID_DAC14_LFO1_ENABLE 107
#define ID_DAC14_LFO2_ENABLE 107

#define ID_DAC15_ADSR1_ENABLE 117
#define ID_DAC15_ADSR2_ENABLE 117
#define ID_DAC15_LFO1_ENABLE 107
#define ID_DAC15_LFO2_ENABLE 107

#define ID_DAC16_ADSR1_ENABLE 117
#define ID_DAC16_ADSR2_ENABLE 117
#define ID_DAC16_LFO1_ENABLE 107
#define ID_DAC16_LFO2_ENABLE 107

// variables 
float           bpm = 120;
int             dac0_ampl = 4095;
bool            dac0_adsr_enable = 0;
int             dac1_ampl = 4095;
bool            dac1_adsr_enable = 0;


// internal variables
int rx_state = 0;
byte cc_sync;
byte cc_control;
byte cc_val1;
byte cc_val2;
unsigned long   t = 0;
unsigned long   sync_t0 = 0;
unsigned long   connected_t0 = 0;

float _freqArray[24] = {64, 48, 32, 24, 16, 12, 8, 6, 5.3333, 4, 3.2, 3, 2.667, 2, 1.333, 1, 0.667, 0.5, 0.333, 0.25, 0.167, 0.125, 0.0625, 0.03125};

// internal classes
lfo         lfo1(DACSIZE);
lfo         lfo2(DACSIZE);
adsr        adsr1(DACSIZE);
adsr        adsr2(DACSIZE);

int getInt(int l_highByte, int l_lowByte) {
  return ((unsigned int)l_highByte << 8) + l_lowByte;
}


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

void loop() {
  t = micros();           // take timestamp
  //-------------------------------write to DAC0---------------------------------//
  if(dac0_adsr_enable == false) {
    dac0_lfo.setAmpl(dac0_ampl);
    myDacA.analogWrite(0, dac0_lfo.getWave(t));
  }
  else {
    if (dac0_lfo.getWaveForm() == 0) {    // DC waveform -> dac0_lfo.getWave(t) will give constant "_ampl_offset" as return
      myDacA.analogWrite(0, map(adsr.getWave(t), 0, DACSIZE-1, dac0_lfo.getWave(t), DACSIZE-1));
    }
    else {                                // update amplitude of LFO with ADSR
      dac0_lfo.setAmpl(map(adsr.getWave(t), 0, DACSIZE-1, 0, dac0_ampl));
      myDacA.analogWrite(0, dac0_lfo.getWave(t));
    }
  }
  
  
  //-------------------------------write to DAC1---------------------------------//
  if(dac1_adsr_enable == false) { // and 
    dac1_lfo.setAmpl(dac1_ampl);
    myDacA.analogWrite(1, dac1_lfo.getWave(t));
  }
  else {
    if (dac1_lfo.getWaveForm() == 0) {    // DC waveform -> dac1_lfo.getWave(t) will give constant "_ampl_offset" as return
      myDacA.analogWrite(1, map(adsr.getWave(t), 0, DACSIZE-1, dac1_lfo.getWave(t), DACSIZE-1));
    }
    else {                                // update amplitude of LFO with ADSR
      dac1_lfo.setAmpl(map(adsr.getWave(t), 0, DACSIZE-1, 0, dac1_ampl));
      myDacA.analogWrite(1, dac1_lfo.getWave(t));
    }
  }
  
  //-------------------------------timeout led---------------------------------//
  if (digitalRead(LED_BUILTIN))
    if((t - connected_t0) > CONNECTED_TIMEOUT)
      digitalWrite(LED_BUILTIN, 0);

  //----------Check if control commands have been received from Ableton------------//
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
          dac0_lfo.setMode1Bpm(bpm);
          dac1_lfo.setMode1Bpm(bpm);
        }
        else if (cc_control == ID_SONG_MEASURE) {
            if(value !=0) {       // when track stops measure = 0
              if(dac0_lfo.getMode() and (int)(10*(value-1)/dac0_lfo.getMode1Rate())%10 == 0)
                dac0_lfo.sync(t);     // reset SYNC
              if(dac1_lfo.getMode() and (int)(10*(value-1)/dac1_lfo.getMode1Rate())%10 == 0)
                dac1_lfo.sync(t);     // reset SYNC
              if((int)(10*(value-1)/_freqArray[sync_mode1_rate])%10 == 0)
                sync_t0 = t;          // reset SYNC            
              digitalWrite(LED_MEASURE, !digitalRead(LED_MEASURE));
            }
        }
              
        // LFO - DAC0
        else if (cc_control == ID_DAC0_MODE)
          dac0_lfo.setMode(value);
        else if (cc_control == ID_DAC0_MODE0_FREQ)
          dac0_lfo.setMode0Freq(((float)value)/100, t);
        else if (cc_control == ID_DAC0_MODE1_RATE)
          dac0_lfo.setMode1Rate(_freqArray[(int)value]);
        else if(cc_control == ID_DAC0_AMPL) {
          dac0_ampl = value;
          dac0_lfo.setAmpl(dac0_ampl);
        }
        else if(cc_control == ID_DAC0_AMPL_OFFSET) 
          dac0_lfo.setAmplOffset(value);
        else if(cc_control == ID_DAC0_WAVEFORM) 
          dac0_lfo.setWaveForm(value);
        else if(cc_control == ID_DAC0_PHASE) 
          dac0_lfo.setMode1Phase((360 - (float)value) / 360); 
        else if(cc_control == ID_DAC0_ADSR_ENABLE) 
          dac0_adsr_enable = value; 
          
        // LFO - DAC1                                          
        else if (cc_control == ID_DAC1_MODE) 
          dac1_lfo.setMode(value);
        else if (cc_control == ID_DAC1_MODE0_FREQ)
          dac1_lfo.setMode0Freq(((float)value)/100, t);                         // freq is tuned in steps of 0.01 -> thus divide INT received by 100         
        else if (cc_control == ID_DAC1_MODE1_RATE)    
          dac1_lfo.setMode1Rate(_freqArray[(int)value]);
        else if(cc_control == ID_DAC1_AMPL) {
          dac1_ampl = value;
          dac1_lfo.setAmpl(dac1_ampl);
        }
        else if(cc_control == ID_DAC1_AMPL_OFFSET) 
          dac1_lfo.setAmplOffset(value);
        else if(cc_control == ID_DAC1_WAVEFORM) 
          dac1_lfo.setWaveForm(value);
        else if(cc_control == ID_DAC1_PHASE) 
          dac1_lfo.setMode1Phase((360 - (float)value) / 360); 
        else if(cc_control == ID_DAC1_ADSR_ENABLE) 
          dac1_adsr_enable = value; 
        
        // ADSR
        else if (cc_control == ID_ADSR_ATTACK)
          adsr.setAttack(1000*value);                                          // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR_DECAY)
          adsr.setDecay(1000*value);                                           // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR_SUSTAIN)
          adsr.setSustain(pow(10, -1*(float)value/1000)*(DACSIZE - 1));        // parameter is logarithmic from 0 to -70dB -> in MaxForLive it is multiplied with -100 for transportation to the Arduino. The value sent to the Arduino is thus an INT between 0 and 7000. To convert back -> time -1 and divide by 100. Then we need to convet from log to lin, which is done with 10^x/10 -> therefore we divide by 1000 here.
        else if (cc_control == ID_ADSR_RELEASE)
          adsr.setRelease(1000*value);                                         // times 1000 -> conversion from ms to µs  
        else if (cc_control == ID_ADSR_TRIGGER) {
          if(value == 1)
            adsr.noteOn(t);
          else if (value == 0)
            adsr.noteOff(t);
        }

        // Sync prob delete that stuff
        else if (cc_control == ID_SYNC_MODE)
          sync_mode = value;
        else if (cc_control == ID_SYNC_MODE0_FREQ)
          sync_mode0_freq = ((float)value)/100;                               // freq is tuned in steps of 0.01 -> thus divide INT received by 100
        else if (cc_control == ID_SYNC_MODE1_RATE)
          sync_mode1_rate = (int)value; 
        else if (cc_control == ID_SYNC_PHASE)
          sync_phase = (360 - (float)value) / 360;                          // phase is received in 360 steps -> convert to float from 0 to 1 
        break;
    }
  }
