#define C_PIN 13
#define C_SHARP_PIN 11
#define D_PIN 8
#define D_SHARP_PIN 9
#define E_PIN 7
#define F_PIN 6
#define F_SHARP_PIN 10
#define G_PIN 5
#define G_SHARP_PIN 12
#define A_PIN 4
#define A_SHARP_PIN 2
#define B_PIN 3
#define LOW_OCT_PIN 28
#define MID_OCT_PIN 26
#define HIGH_OCT_PIN 24


int noteON = 144;
int noteOFF = 128;
int defaultVelocity = 100;
int octaveOffset = 24;

bool noteState[] = {
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false,
  false, false, false, false, false, false, false, false, false, false 
 };

 class Switch {
  private:
    byte pin;
    byte state;
    byte lastReading;
    int baseNote;
    unsigned long lastDebounceTime = 0;
    unsigned long debounceDelay = 50;
  public:
    Switch(byte pin, int baseNote) {
      this->pin = pin;
      lastReading = LOW;
      this->baseNote = baseNote;
      init();
    }
    void init() {
      pinMode(pin, INPUT_PULLUP);
      update();
    }
    void update() {
      byte newReading = digitalRead(pin);
      
      if (newReading != lastReading) {
        lastDebounceTime = millis();
      }
      if (millis() - lastDebounceTime > debounceDelay) {
        state = newReading;
      }
      lastReading = newReading;
    }
    byte getState() {
      update();
      return state;
    }
    int getNote() {
      return baseNote;
    }
    bool isPressed() {
      return (getState() == HIGH);
    }
};

Switch key_C(C_PIN, 60);
Switch key_C_Sharp(C_SHARP_PIN, 61);
Switch key_D(D_PIN, 62);
Switch key_D_Sharp(D_SHARP_PIN, 63);
Switch key_E(E_PIN, 64);
Switch key_F(F_PIN, 65);
Switch key_F_Sharp(F_SHARP_PIN, 66);
Switch key_G(G_PIN, 67);
Switch key_G_Sharp(G_SHARP_PIN, 68);
Switch key_A(A_PIN, 69);
Switch key_A_Sharp(A_SHARP_PIN, 70);
Switch key_B(B_PIN, 71);
Switch oct_LOW(LOW_OCT_PIN, 0);
Switch oct_MID(MID_OCT_PIN, 0);
Switch oct_HIGH(HIGH_OCT_PIN, 0);

void setup() {
  Serial.begin(31250);
}

void loop() {
  // Look at all note switches
  // C
  if(key_C.isPressed()) {
    switchOnNote(key_C.getNote());
  } else {
    switchOffNote(key_C.getNote());
  }
  // C Sharp
  if(key_C_Sharp.isPressed()) {
    switchOnNote(key_C_Sharp.getNote());
  } else {
    switchOffNote(key_C_Sharp.getNote());
  }
  // D
  if(key_D.isPressed()) {
    switchOnNote(key_D.getNote());
  } else {
    switchOffNote(key_D.getNote());
  }
  // D Sharp
  if(key_D_Sharp.isPressed()) {
    switchOnNote(key_D_Sharp.getNote());
  } else {
    switchOffNote(key_D_Sharp.getNote());
  }
  // E
  if(key_E.isPressed()) {
    switchOnNote(key_E.getNote());
  } else {
    switchOffNote(key_E.getNote());
  }
  // F
  if(key_F.isPressed()) {
    switchOnNote(key_F.getNote());
  } else {
    switchOffNote(key_F.getNote());
  }
  // F Sharp
  if(key_F_Sharp.isPressed()) {
    switchOnNote(key_F_Sharp.getNote());
  } else {
    switchOffNote(key_F_Sharp.getNote());
  }
  // G
  if(key_G.isPressed()) {
    switchOnNote(key_G.getNote());
  } else {
    switchOffNote(key_G.getNote());
  }
  // G Sharp
  if(key_G_Sharp.isPressed()) {
    switchOnNote(key_G_Sharp.getNote());
  } else {
    switchOffNote(key_G_Sharp.getNote());
  }
  // A
  if(key_A.isPressed()) {
    switchOnNote(key_A.getNote());
  } else {
    switchOffNote(key_A.getNote());
  }
  // A Sharp
  if(key_A_Sharp.isPressed()) {
    switchOnNote(key_A_Sharp.getNote());
  } else {
    switchOffNote(key_A_Sharp.getNote());
  }
  // B
  if(key_B.isPressed()) {
    switchOnNote(key_B.getNote());
  } else {
    switchOffNote(key_B.getNote());
  }
}

void switchOnNote(int baseNote) {
  if(oct_MID.isPressed()) {
    if(noteState[baseNote] == false) {
      midiNoteOn(baseNote);
      noteState[baseNote] = true;
    }
  } else {
    if(noteState[baseNote] == true) {
      midiNoteOff(baseNote);
      noteState[baseNote] = false;
    }
  }

  if(oct_LOW.isPressed()) {
    if(noteState[baseNote - octaveOffset] == false) {
      midiNoteOn(baseNote - octaveOffset);
      noteState[baseNote - octaveOffset] = true;
    }
  } else {
    if(noteState[baseNote - octaveOffset] == true) {
      midiNoteOff(baseNote - octaveOffset);
      noteState[baseNote - octaveOffset] = false;
    }
  }

  if(oct_HIGH.isPressed()) {
    if(noteState[baseNote + octaveOffset] == false) {
      midiNoteOn(baseNote + octaveOffset);
      noteState[baseNote + octaveOffset] = true;
    }
  } else {
    if(noteState[baseNote + octaveOffset] == true) {
      midiNoteOff(baseNote + octaveOffset);
      noteState[baseNote + octaveOffset] = false;
    }
  }  
}

void switchOffNote(int baseNote) {
  if(noteState[baseNote] == true) {
    midiNoteOff(baseNote);
    noteState[baseNote] = false;
  }

  if(noteState[baseNote - octaveOffset] == true) {
    midiNoteOff(baseNote - octaveOffset);
    noteState[baseNote - octaveOffset] = false;
  }

  if(noteState[baseNote + octaveOffset] == true) {
    midiNoteOff(baseNote + octaveOffset);
    noteState[baseNote + octaveOffset] = false;
  }
}

void midiNoteOn(int pitch) {
  Serial.write(noteON);
  Serial.write(pitch);
  Serial.write(defaultVelocity);
}

void midiNoteOff(int pitch) {
  Serial.write(noteOFF);
  Serial.write(pitch);
  Serial.write(defaultVelocity);
}
