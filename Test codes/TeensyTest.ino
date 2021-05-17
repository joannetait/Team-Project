// Three bytes interface is used between Arduino Due and Teensy on COM serial port:
// Byte 1: 255 (sync byte)
// Byte 2: <control> - [0:255]
// Byte 3: <value MSB> - [0:255]

// --------------------------------------------------
#include <MCP492X.h> // Include the library
#include <SPI.h>
#include <lfo.h>          // required for function generation
#include <adsr.h>         // required for function generation

#define CHIP_SELECT_A 12 // =SC1 on schematic 
#define CHIP_SELECT_B 11 // =SC2 on schematic etc
#define CHIP_SELECT_C 10
#define CHIP_SELECT_D 9
#define CHIP_SELECT_E 8
#define CHIP_SELECT_F 7 
#define CHIP_SELECT_G 6
#define CHIP_SELECT_H 5


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


// internal variables
int i=0;

unsigned long   t = 0;
unsigned long   sync_t0 = 0;
unsigned long   connected_t0 = 0;

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

  PB1_LFO1_AMOUNT = -1;
  PB2_LFO1_AMOUNT = -0.5;
  PWM1_LFO1_AMOUNT = 0;
  PWM2_LFO1_AMOUNT = 0.5;
  LVL1_LFO1_AMOUNT = 1;
  LVL2_LFO1_AMOUNT = 0.5;
  CUTOFF_LFO1_AMOUNT = 0;
  RES_LFO1_AMOUNT = -0.5;
  DRIVE_LFO1_AMOUNT = -1.;
  SHAPE1_LFO1_AMOUNT = -0.5;
  SHAPE2_LFO1_AMOUNT = 0;
  VCA7_LFO1_AMOUNT = 0.5;

  lvl1_position = 1;
  lvl2_position = 1;
  drive_position = 1;
  fm_position = 1;
  detune_position = 1;
  cutoff_position = 1;
  res_position = 1;
  pwm1_position = 1;
  pwm2_position = 1;
  vca1_position = 1;
  vca2_position = 1;
  vca3_position = 1;
  vca4_position = 1;
  vca5_position = 1;
  vca6_position = 1;
  volume_position = 1; 
}

unsigned long trigTimer[3] = {0}; //from elkayem code, don't kno why it's in between setup and main and not in init stage
bool notes[3][88] = {0}, initial_loop = 1; 
int8_t noteOrder[3][10] = {0}, orderIndx[3] = {0};

void loop() {
    t = micros();           // take timestamp
    
    adsr1_sample = adsr1.getWave(t) -2048; //current sample from modulation (0 centered) to be multiplied by amounts to relevant DACs
    adsr2_sample = adsr2.getWave(t) -2048;
    lfo1_sample = lfo1.getWave(t) -2048;
    lfo2_sample = lfo2.getWave(t) -2048;

    lfo1.setMode(0);
    lfo1.setWaveForm(2); //triangle wave
    lfo1.setMode0Freq(40);

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


    }
  }
}

}

