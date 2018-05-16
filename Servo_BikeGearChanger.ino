#include <Servo.h>
Servo servo;

const int pinSwitchWheel = 12; //Pin Reed for Front Wheel

const int pinSwitchPedal = 11; //Pin Reed for Pedal

const int LED = 13; //Pin for LED Switch on Arduino

int StatoSwitchWheel = 0; //State of the Reed Switch

int StatoSwitchPedal = 0; //State of the Reed Switch

int SwitchMode = 0; //0 if servo should not switch, 1 if it should be on

int Num_Revs = 0; //Number of Revolutions of the bike

int rpm = 0; //Revolutions per minute calculated for the front wheel

void setup() {

  Serial.begin(9600); //Serial for testing

  servo.attach(9); //Assigns servo to pin 9

  pinMode(pinSwitchWheel, INPUT); //Assigns reed switch on front wheel to be an INPUT

  pinMode(pinSwitchPedal, INPUT); //Assigns reed switch on pedal to be an INPUT

  pinMode(LED, OUTPUT); //Assigns Arduino LED to OUTPUT

}

void loop() {

  for (int k = 0; k <= 2; k++)  { //Refresh loop for seeing if pedal is moving
    for (int i = 0; i <= 1000; i++) { //Refreshes loop every millisecond to check state of reed switch on the wheel

      delay(1);

      StatoSwitchPedal = digitalRead(pinSwitchPedal);//Check if reed switch for pedal is closed
      StatoSwitchWheel = digitalRead(pinSwitchWheel);//Check if reed switch for wheel is closed

      if (StatoSwitchPedal == HIGH) { //If  pedal is rotating, enable switching of gears by the servo
        SwitchMode = 1;
      }

      if (StatoSwitchWheel == HIGH)  { //If it is, add one to number of revs and delay so that the revolution doesn't get counted multiple times (debounce)

        Num_Revs++;
        digitalWrite(LED, HIGH);
        delay(50);
        digitalWrite(LED, LOW);

      }
    }

    rpm = Num_Revs * 60 / (1 + (Num_Revs * .05)); //Calculates the rpm of data collected from the for loop below

    Serial.print(rpm); //Print number of revolutions for debugging

    if (SwitchMode == 1)  { //If pedals are moving, switch gear based on what rpm was calculated by moving servo to whatever angle the gear needs to be at

      if (rpm <= 130) {
        servo.write(70);
      }
      if (rpm <= 170 && rpm > 130) {
        servo.write(58);
      }
      if (rpm <= 220 && rpm > 170) {
        servo.write(44);
      }
      if (rpm <= 270 && rpm > 220) {
        servo.write(35);
      }
      if (rpm <= 320 && rpm > 270) {
        servo.write(21);
      }
      if (rpm <= 370 && rpm > 320) {
        servo.write(10);
      }
      if (rpm <= 420 && rpm > 370) {
        servo.write(0);
      }

    }
    Num_Revs = 0; //Reset number of revolutions for next loop
  }

  SwitchMode == 0; //Turn off switch mode until next loop

}
