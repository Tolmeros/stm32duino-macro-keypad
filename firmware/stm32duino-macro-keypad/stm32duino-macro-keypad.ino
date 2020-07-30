#include <Key.h>
#include <Keypad.h>

#include <USBComposite.h>
/*
 * This example types which cardinal direction the mouse will be moved
 * and then moves the mouse in that direction. If the mouse doesn't recenter
 * at the end, it is probably due to mouse acceleration 
 */

USBHID HID;
HIDKeyboard Keyboard(HID);
HIDMouse Mouse(HID);

const byte ROWS = 2;
const byte COLS = 3;

//#define ROWS 2
//#define COLS 3

const char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
};

byte rowPins[ROWS] = {PA0, PA1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {PA2, PA3, PA4}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        switch (key) {
          case '1':
            Keyboard.press('[');
            break;
          case '2':
            Keyboard.press(']');
            break;
          case '3':
            Keyboard.press(KEY_LEFT_ALT);
            break;
          case '4':
            Keyboard.press(KEY_LEFT_CTRL);
            break;
          case '5':
            Keyboard.press(KEY_LEFT_SHIFT);
            break;
          case '6':
            Mouse.press(MOUSE_MIDDLE);
            break;
        }
        break;

    case RELEASED:
        switch (key) {
          case '1':
            Keyboard.release('[');
            break;
          case '2':
            Keyboard.release(']');
            break;
          case '3':
            Keyboard.release(KEY_LEFT_ALT);
            break;
          case '4':
            Keyboard.release(KEY_LEFT_CTRL);
            break;
          case '5':
            Keyboard.release(KEY_LEFT_SHIFT);
            break;
          case '6':
            Mouse.release(MOUSE_MIDDLE);
            break;
        }
        break;

    case HOLD:
        if (key == '1') {
            //blink = true;    // Blink the LED when holding the * key.
        }
        break;
    }
}
 
void setup() {
  Serial.begin(115200);
  HID.begin(HID_KEYBOARD_MOUSE);
  delay(2000);

  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
}

void loop() {
  char key = keypad.getKey();

  if (key) {
      Serial.println(key);
  }
}
