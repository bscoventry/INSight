/*
Author: Brandon S Coventry        Purdue University, now with University of Wisconsin-Madison and the Wisconsin Institute for Translational Neuroengineering
Purpose: Arduino Pulser interface for INS stimulation System
Citation: Coventry BS, Krogmeier CK, Bartlett EL ...
Revision History: N/A
Device: Due, or an arduino with 3.3V logic levels and a DAC.
Hardware notes: Trigger pulse should come in on digital I/O on pin 7. This pin should have a pulldown resistor (10k is good) to ground to ensure trigger stability.
*/

void setup() {
    attachInterrupt(7, pulse_ISR, RISING);     // Setup our trigger pin. Pulses will be made when receiving a logic high, rising edge on digital pin 7.
    pinMode(DAC0, OUTPUT);                     // Set up as output. Not strictly necessary, but good to do.
    analogWriteResolution(12);                 // Waveform resolution is 12 bits.
    int pw = 5; // Time in ms of pulsewidth
    int isi = 100; // Time between pulses
    int numPulses = 5;      // Number of pulses
    //outVoltage = 2048;                       //12 bit resolution assumed here. 
    int outVoltage[] = {2048, 777, 1024, 512, 3456};        // Create a random array and put here for randomized stimulation.
    int lenExperiment = 5;                     //Number of total stimuli
    int stimNumber = 0;                        // Used to index when calling stimuli.
}

void loop() {
    
}
// Output waveform on interrupt. The interrupt is handled after receiving a logic 1 on digital pin 7
void outputSquareWave() {
  for (int i = 0; i <= numPulses; i++) {
    analogWrite(DAC0, outVoltage[stimNumber]);
    delay(pw)
    analogWrite(DAC0,0);           //Note, the lowest value output of arduino DACs is 1/6 VCC, or about 0.5V. This should be subtreshold for most lasing, but you may need a resistor divider on output to account for this
    delay(isi)
  }
  stimNumber = stimNumber + 1;
  if (stimNumber > lenExperiment){
    stimNumber = 0;
  }
}

void pulse_ISR(){
  // This is the service routine handeling a trigger on pulse.
  outputSquareWave()
}