#ifndef _SWITCH_PANEL_H
#define _SWITCH_PANEL_H

#include <Arduino.h>
#include <config.h>
#include <MUX_TCA9539.h>
#include <switch.h>

class SwitchPanel {

public:
  SwitchPanel();  
  SwitchPanel (const char* _deviceName, const char *_switchName[NUMBER_OF_SWITCHES], int _maxDuration[NUMBER_OF_SWITCHES], MQTTClient* _mqttClient, const char * _deviceTopic, int _statusUpdateInterval = 1, int _attributeUpdateInterval = 10);
  
  void initialise(const char* _deviceName, const char *_switchName[NUMBER_OF_SWITCHES], int _maxDuration[NUMBER_OF_SWITCHES], MQTTClient* _mqttClient, const char * _deviceTopic, int _statusUpdateInterval = 1, int _attributeUpdateInterval = 10);
  void control();
  void turnOn(int switchId); 
  void turnOn(int switchId, int durationSecs);
  void turnOff(int switchId);
  void makeAvailable(int switchId);
  void makeUnavailable(int switchId);
  bool availabe(int switchId);
  void startTimer(int switchId, int durationSecs);
  void cancelTimer(int switchId);
  boolean switchStateOn(int switchId);
  void turnAllOn();
  void turnAllOff();
  void makeAllAvailable();
  void makeAllUnavailable();
  boolean switchesOn();
 /*
  void fillUp(int _velocity){
    int velocity = 50;
    if (_velocity > velocity){
      velocity = _velocity;
    }
    for (int i= 0; i < NUMBER_OF_REGISTERS; i++){
      registers[i].allPinsOff();
    }
    for (int i=1;i < NUMBER_OF_SWITCHES +1; i++){
      turnOn(i);
      delay(velocity);
    }
  }

  void fillDown(int _velocity){
    int velocity = 30;
    if (_velocity > velocity){
      velocity = _velocity;
    }
    for (int i= 0; i < NUMBER_OF_REGISTERS; i++){
      registers[i].allPinsOff();
    }
    for (int i=NUMBER_OF_SWITCHES;i > 0; i--){
      turnOn(i);
      delay(velocity);
    }
  }

  void shrinkDown(int _velocity){
    int velocity = 30;
    if (_velocity > velocity){
      velocity = _velocity;
    }
    for (int i= 0; i < NUMBER_OF_REGISTERS; i++){
      registers[i].allPinsOn();
    }
    latchRegisters();
    for (int i=NUMBER_OF_SWITCHES;i > 0; i--){
      turnOff(i);
      delay(velocity);
    }
  }

  void shrinkUp(int _velocity){
    int velocity = 30;
    if (_velocity > velocity){
      velocity = _velocity;
    }
    for (int i= 0; i < NUMBER_OF_REGISTERS; i++){
      registers[i].allPinsOn();
    }
    latchRegisters();
    for (int i=1; i < NUMBER_OF_SWITCHES +1; i++){
      turnOff(i);
      delay(velocity);
    }
  }

  void fillShrinkUp(int _velocity){
    int velocity = 30;
    if (_velocity > velocity){
      velocity = _velocity;
    }
    fillUp(velocity);
    shrinkDown(velocity);
  }

  void fillShrinkDown(int _velocity){
    int velocity = 30;
    if (_velocity > velocity){
      velocity = _velocity;
    }
    fillDown(velocity);
    shrinkUp(velocity);
  }
*/

private:
  const char *switchName[NUMBER_OF_SWITCHES];
  const char* deviceName;
  int maxDuration[NUMBER_OF_SWITCHES]; 
  int statusUpdateInterval = 1; // in minutes
  int attributeUpdateInterval = 10; // in seconds
  const char* deviceTopic = "home/switch"; 
  MQTTClient* mqttClient;
  String switchNamePrefix = "switch";
  int deviceAddress = 116;
  int portConfig[2] = {0b00000000, 0b00000000} ;
  Multiplexer multiplexer;
  Switch* switches = new Switch[NUMBER_OF_SWITCHES];

  void initialiseSwitches();
  int swithIndex(int switchID);
/*
void populateSwitchDetails(){
  int registerID = 0;
  int pinID = 1;
  for (int i=1; i < NUMBER_OF_SWITCHES +1; i++){
      switchDetails[i][0] = i;
      switchDetails[i][1] = registerID;
      switchDetails[i][2] = pinID;

      Serial.print("Switch ID: ");
      Serial.print(switchDetails[i][0]);
      Serial.print(", Register ID: ");
      Serial.print(switchDetails[i][1]);
      Serial.print(", Pin ID: ");
      Serial.println(switchDetails[i][2]);

      pinID = pinID + 1;
      if (pinID > registers[registerID].noOfPins){
//      if (pinID > 8){
        pinID = 1;
        registerID = registerID + 1;
      }
  }
}
*/

/*
void latchRegisters(){
  digitalWrite(LATCH_PIN, LOW);
  
  for(int i = NUMBER_OF_REGISTERS - 1; i >= 0; i= i - 1){
     registers[i].shiftOutRegister();
  }
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}
*/

/*
void initialiseRegisters(){
  digitalWrite(LATCH_PIN, LOW);
  for(int i = NUMBER_OF_REGISTERS - 1; i > -1; i= i - 1){
     registers[i].allPinsOff();
     registers[i].shiftOutRegister();
  }
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}
*/

};

#endif //_SWITCH_PANEL_H
