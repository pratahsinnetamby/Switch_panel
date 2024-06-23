#include <switch_panel.h>

SwitchPanel::SwitchPanel() = default;

SwitchPanel::SwitchPanel (const char* _deviceName, const char *_switchName[NUMBER_OF_SWITCHES], int _maxDuration[NUMBER_OF_SWITCHES], MQTTClient* _mqttClient, const char * _deviceTopic, int _statusUpdateInterval, int _attributeUpdateInterval):
            deviceName(_deviceName), statusUpdateInterval(_statusUpdateInterval), attributeUpdateInterval(_attributeUpdateInterval), deviceTopic(_deviceTopic), mqttClient(_mqttClient){
  
  multiplexer.initialise(deviceAddress, portConfig[0], portConfig[1]);
  
  for (int i= 0; i < NUMBER_OF_SWITCHES; i++){
    switchName[i] = _switchName[i];
    maxDuration[i] =_maxDuration[i];
  }
  initialiseSwitches();
}

void SwitchPanel::initialise(const char* _deviceName, const char *_switchName[NUMBER_OF_SWITCHES], int _maxDuration[NUMBER_OF_SWITCHES], MQTTClient* _mqttClient, const char * _deviceTopic, int _statusUpdateInterval, int _attributeUpdateInterval){
  deviceName = _deviceName;
  statusUpdateInterval = _statusUpdateInterval;
  attributeUpdateInterval = _attributeUpdateInterval;
  deviceTopic = _deviceTopic;
  mqttClient = _mqttClient;
  multiplexer.initialise(deviceAddress, portConfig[0], portConfig[1]);

  for (int i= 0; i < NUMBER_OF_SWITCHES; i++){
    switchName[i] = _switchName[i];
    maxDuration[i] =_maxDuration[i];
  }
  initialiseSwitches();
}

void SwitchPanel::control(){
  for (int i= 0; i < NUMBER_OF_SWITCHES; i++){
    switches[i].control();
  }
}

void SwitchPanel::turnOn(int switchId){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].turnOn();
  }
}

void SwitchPanel::turnOn(int switchId, int durationSecs){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].turnOn(durationSecs);
  }
}

void SwitchPanel::turnOff(int switchId){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].turnOff();
  }
}

void SwitchPanel::makeAvailable(int switchId){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].makeAvailable();
  }
}

void SwitchPanel::makeUnavailable(int switchId){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].makeUnavailable();
  }
}

bool SwitchPanel::availabe(int switchId){
  bool availability = 0;
  if(switchId <= NUMBER_OF_SWITCHES){
    availability = switches[swithIndex(switchId)].available();
  }
  return availability;
}

void SwitchPanel::startTimer(int switchId, int durationSecs){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].startTimer(durationSecs);
  }
}

void SwitchPanel::cancelTimer(int switchId){
  if(switchId <= NUMBER_OF_SWITCHES){
    switches[swithIndex(switchId)].cancelTimer();
  }
}

boolean SwitchPanel::switchStateOn(int switchId){
  boolean switchStateOn = 0;
  if(switchId <= NUMBER_OF_SWITCHES){
    switchStateOn = switches[swithIndex(switchId)].switchStateOn();
  }
  return switchStateOn;
}

void SwitchPanel::turnAllOn(){
  for (int i= 1; i <= NUMBER_OF_SWITCHES; i++){
    turnOn(i);
  }
}

void SwitchPanel::turnAllOff(){
  for (int i= 1; i <= NUMBER_OF_SWITCHES; i++){
    turnOff(i);
  }
}

void SwitchPanel::makeAllAvailable(){
  for (int i= 1; i <= NUMBER_OF_SWITCHES; i++){
    makeAvailable(i);
  }
}

void SwitchPanel::makeAllUnavailable(){
  for (int i= 1; i <= NUMBER_OF_SWITCHES; i++){
    makeUnavailable(i);
  }
}

boolean SwitchPanel::switchesOn(){
  boolean switchesOn = false;
  for (int i= 1; i <= NUMBER_OF_SWITCHES; i++){
    if (switchStateOn(i)) {
      switchesOn = switchStateOn(i);
    }
  }
  return switchesOn;
}
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

void SwitchPanel::initialiseSwitches(){
  
  for (int i= 0; i < NUMBER_OF_SWITCHES; i++){
    Serial.print("Initialising switch : ");
    Serial.println(i+1);
    switches[i].initialise(i+1, switchName[i], deviceName, maxDuration[i], statusUpdateInterval, attributeUpdateInterval , deviceTopic, &multiplexer, mqttClient);
  }
}

int SwitchPanel::swithIndex(int switchID){
  return switchID - 1;
}
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
