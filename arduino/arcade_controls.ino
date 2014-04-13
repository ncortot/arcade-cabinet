#define DEBOUNCE_DELAY 50

// Set this pin LOW to disable HID emulation
#define HID_ENABLE_PIN A0

static const uint8_t select_pins[] = {3,4,5};
static const uint8_t input_pins[] = {6,7,8,9};

static const char keymap[sizeof(select_pins)][sizeof(input_pins)] = {
  {'1', '2', '3', '4'},
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'}
};

static uint8_t last_state[sizeof(select_pins)][sizeof(input_pins)];
static uint8_t read_state[sizeof(select_pins)][sizeof(input_pins)];
static long change_time[sizeof(select_pins)][sizeof(input_pins)];

static uint8_t hid_enable = HIGH;
static uint8_t hid_state = HIGH;

void setup() {
  pinMode(HID_ENABLE_PIN, INPUT_PULLUP);

  for (int i = 0; i < sizeof(select_pins); ++i) {
    pinMode(select_pins[i], OUTPUT);
    digitalWrite(select_pins[i], HIGH);
    for (int j = 0; j < sizeof(input_pins); ++j) {
      last_state[i][j] = HIGH;
      read_state[i][j] = HIGH;
      change_time[i][j] = 0;
    }
  }
  for (int i = 0; i < sizeof(input_pins); ++i) {
    pinMode(input_pins[i], INPUT_PULLUP);
  }

  Serial.begin(9600);
  Keyboard.begin();
}

void key_change(char key, int state) {
  if (hid_enable == HIGH) {
    if (state == LOW) {
      Keyboard.press(key);
    } else {
      Keyboard.release(key);
    }
  } else {
    Serial.print("Button ");
    Serial.print(key);
    if (state == LOW) {
      Serial.println(" pressed");
    } else {
      Serial.println(" released");
    }
  }
}

void loop() {
  hid_enable = digitalRead(HID_ENABLE_PIN);
  if (hid_enable != hid_state) {
    if (hid_enable == LOW) {
      // Release all keys when disabling HID emulation
      Keyboard.releaseAll();
    }
    hid_state = hid_enable;
  }

  long time = millis();

  for (int i = 0; i < sizeof(select_pins); ++i) {
    // Select the row of buttons to read
    digitalWrite(select_pins[i], LOW);

    for (int j = 0; j < sizeof(input_pins); ++j) {
      // Read the state of button (i, j)
      int state = digitalRead(input_pins[j]);

      if (state != read_state[i][j]) {
        // The state changed since last reading, reset the timer.
        change_time[i][j] = time;
      }

      if (time - change_time[i][j] > DEBOUNCE_DELAY) {
        // The reading has been constant for the debounce delay,
        // consider it the current state.
        if (state != last_state[i][j]) {
          key_change(keymap[i][j], state);
          last_state[i][j] = state;
        }
      }

      read_state[i][j] = state;
    }
    digitalWrite(select_pins[i], HIGH);
  }
}
