//*****************************************************************************
//*  KEYBOARD EMULATOR
//*  beta version
//*  by Nathalis
//******************************************************************************


#include <Keyboard.h>


unsigned char VALUE1 = 0;
unsigned char VALUE2 = 0;
unsigned char OLDVALUE1 = 0;
unsigned char OLDVALUE2 = 0;

void loadKEYs() {
  OLDVALUE1 = VALUE1;
  OLDVALUE2 = VALUE2;

  VALUE1 = Serial1.read();
  VALUE2 = 0;
  delay(1);
  if (Serial1.available()) {
    VALUE2 = Serial1.read();
  }

}
//*****************************************************************************
//*  MAIN SETUP
//*****************************************************************************

void setup() {
  // open the serial port:
  Serial.begin(38400); //for console
  Serial1.begin(38400); //for input
  // initialize control over the keyboard:
  Keyboard.begin();
}
//*****************************************************************************
//*  MAIN LOOP
//*****************************************************************************

void loop() {
  // check for incoming serial data:

  if (Serial1.available()) {
    loadKEYs(); //read keyboard codes from Serial.
    delay(6);

    VALUE1 = VALUE1 & 0xff;
    VALUE2 = VALUE2 & 0xff;

    Serial.print(VALUE1, HEX);  //Print codes to console...
    Serial.print(" ");
    Serial.print(VALUE2, HEX);
    Serial.println(" ");

    //*****************************************************************************
    //*  KEY RELASE
    //******************************************************************************
    if (VALUE1 & 0x80) {  // Release KEY status

      if (VALUE2 == 0x06) {
        Keyboard.release(KEY_LEFT_SHIFT);
        Keyboard.release(KEY_RIGHT_SHIFT);
      } else if (VALUE2 == 0x07) {
        Keyboard.release(KEY_LEFT_SHIFT);
        Keyboard.release(KEY_RIGHT_SHIFT);
      } else if (VALUE2 == 0x08) {
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.release(KEY_RIGHT_CTRL);
      } else if (VALUE2 == 0x09) {
        Keyboard.release(KEY_LEFT_CTRL);
        Keyboard.release(KEY_RIGHT_CTRL);
      } else if (VALUE2 == 0x0A) {
        Keyboard.release(KEY_LEFT_ALT);
        Keyboard.release(KEY_RIGHT_ALT);
      } else if (VALUE2 == 0x0B) {
        Keyboard.release(KEY_LEFT_ALT);
        Keyboard.release(KEY_RIGHT_ALT);
      } else if (VALUE2 == 0x1D) {
        Keyboard.release(KEY_TAB);
        Keyboard.release(KEY_TAB);
      } else if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) { //keyboard A..Z
        Keyboard.release(VALUE2 + 0x20);
      } else if (VALUE2 == 0x1F) {
        Keyboard.release(' '); //SPACEBAR
        //------------------------
      } else if (VALUE2 >= 0x20 && VALUE2 <= 0x29) { //keyboard nums
        Keyboard.release(VALUE2 + 0x10);
      } else  if (VALUE2 >= 0x30 && VALUE2 <= 0x39) { //keyboard nums
        Keyboard.release(VALUE2);
        //------------------------
      } else if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.release(KEY_LEFT_ARROW);
      } else if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.release(KEY_RIGHT_ARROW);
      } else if (VALUE2 == 0x17) { //keypad UP
        Keyboard.release(KEY_UP_ARROW);
      } else if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.release(KEY_DOWN_ARROW);
        //------------------------
        if (VALUE2 == 0x11) { //keypad HOME
          Keyboard.release(KEY_HOME);
        }
        if (VALUE2 == 0x12) { //keypad END
          Keyboard.release(KEY_END);
        }
        if (VALUE2 == 0x13) { //keypad PAGE UP
          Keyboard.release(KEY_PAGE_UP);
        }
        if (VALUE2 == 0x14) { //keypad PAGE DOWN
          Keyboard.release(KEY_PAGE_DOWN);
        }
        if (VALUE2 == 0x19) { //keypad INSERT
          Keyboard.release(KEY_INSERT);
        }
        if (VALUE2 == 0x1A) { //keypad DELETE
          Keyboard.release(KEY_DELETE);
        }
        //------------------------
      } else { //Anything ELSE
        Keyboard.releaseAll();
      }
    }
    //*****************************************************************************
    //*  CTRL, SHITFT, ALT
    //*****************************************************************************

    if ((VALUE1 == 0x51 || VALUE1 == 0X41) && VALUE2 == 0x06) {
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    if ((VALUE1 == 0x51 || VALUE1 == 0x41) && VALUE2 == 0x07) {
      Keyboard.press(KEY_RIGHT_SHIFT);
    }
    if ((VALUE1 == 0x21 || VALUE1 == 0x31) && VALUE2 == 0x08) {
      Keyboard.press(KEY_LEFT_CTRL);
    }
    if ((VALUE1 == 0x21 || VALUE1 == 0x31) && VALUE2 == 0x09) {
      Keyboard.press(KEY_RIGHT_CTRL);
    }
    if ((VALUE1 == 0x19 || VALUE1 == 0x9) && VALUE2 == 0x0A) {
      Keyboard.press(KEY_LEFT_ALT);
    }
    if ((VALUE1 == 0x15 || VALUE1 == 0x5) && VALUE2 == 0x0B) {
      Keyboard.press(KEY_RIGHT_ALT);
    }
    //*****************************************************************************
    //* A..Z combinations with SHIFT,ALT,CTRL
    //*****************************************************************************
    if (VALUE1 == 0x00 ) {  //a..z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) { //keyboard a..z
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    //------------------------
    if (VALUE1 == 0x10 ) {  //caps lock + A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(VALUE2);
      }
    }
    if (VALUE1 == 0x40 ) {  //shift + A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(VALUE2);
      }
    }
    if (VALUE1 == 0x50 ) {  //shift+caps lock A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    //*****************************************************************************
    if (VALUE1 == 0x20 || VALUE1 == 0x30) { //CTRL +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    if (VALUE1 == 0x09 || VALUE1 == 0x19 || VALUE1 == 0x05 || VALUE1 == 0x15) { //ALT +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    if (VALUE1 == 0x60 || VALUE1 == 0x70) {  //SHIFT+CTRL +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    if (VALUE1 == 0x28 || VALUE1 == 0x38 || VALUE1 == 0x24 || VALUE1 == 0x34) {  //ALT+CTRL +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    if (VALUE1 == 0x48 || VALUE1 == 0x58 || VALUE1 == 0x44 || VALUE1 == 0x54) {  //ALT+SHIFT +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    if (VALUE1 == 0x68 || VALUE1 == 0x78 || VALUE1 == 0x64 || VALUE1 == 0x74) {  //ALT+CTRL+SHIFT +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    //*****************************************************************************
    //* NUMBERS on Numpad & Keypad
    //*****************************************************************************
    if (VALUE1 == 0x00 || VALUE1 == 0x10 || VALUE1 == 0x40 || VALUE1 == 0x50) { //DEFAULT + CAPSLOCK

      if (VALUE2 >= 0x20 && VALUE2 <= 0x29) { //numpad nums
        Keyboard.press(VALUE2 + 0x10);
      }
      if (VALUE2 >= 0x30 && VALUE2 <= 0x39) { //keyboard nums
        Keyboard.press(VALUE2);
      }
      //*****************************************************************************
      //**  NUMPAD KEYS:
      //*****************************************************************************
      if (VALUE2 == 0x2A) { //numpad .
        Keyboard.press('.');
      }
      if (VALUE2 == 0x2B) { //numpad enter
        Keyboard.press(KEY_RETURN);
      }
      if (VALUE2 == 0x2C) { //numpad +
        Keyboard.press('+');
      }
      if (VALUE2 == 0x2D) { //numpad -
        Keyboard.press('-');
      }
      if (VALUE2 == 0x2E) { //numpad *
        Keyboard.press('*');
      }
      //if (VALUE2 == 0x2F) { //numpad /  [Already Defined]
      //Keyboard.press('/');
      //}
      //------------------------
      if (VALUE2 == 0x40) { //
        Keyboard.press('`');
      }
      if (VALUE2 == 0x3C) { //
        Keyboard.press('-');
      }
      if (VALUE2 == 0x5F) { //
        Keyboard.press('=');
      }
      if (VALUE2 == 0x5D) { //
        Keyboard.press('[');
      }
      if (VALUE2 == 0x5E) { //
        Keyboard.press(']');
      }
      if (VALUE2 == 0x5B) { //
        Keyboard.press(';');
      }
      if (VALUE2 == 0x3A) { //
        Keyboard.press('\'');
      }
      if (VALUE2 == 0x5C) { //
        Keyboard.press('\\');
      }
      if (VALUE2 == 0x3B) { //
        Keyboard.press(',');
      }
      if (VALUE2 == 0x3D) { //
        Keyboard.press('.');
      }
      if (VALUE2 == 0x3E) { //
        Keyboard.press('/');
      }
      if (VALUE2 == 0x2F) { //
        Keyboard.press('/');
      }
    }
    //*****************************************************************************
    //** KEYBOARD CHARS
    //*****************************************************************************

    if (VALUE1 == 0x40 /*|| VALUE1 == 0x50*/ ) { //shift + SPECIAL CHARS
      if (VALUE2 == 0x31) { //
        Keyboard.press('!');
      }
      if (VALUE2 == 0x32) { //
        Keyboard.press('@');
      }
      if (VALUE2 == 0x33) { //
        Keyboard.press('#');
      }
      if (VALUE2 == 0x34) { //
        Keyboard.press('$');
      }
      if (VALUE2 == 0x35) { //
        Keyboard.press('%');
      }
      if (VALUE2 == 0x36) { //
        Keyboard.press('^');
      }
      if (VALUE2 == 0x37) { //
        Keyboard.press('&');
      }
      if (VALUE2 == 0x38) { //
        Keyboard.press('*');
      }
      if (VALUE2 == 0x39) { //
        Keyboard.press('(');
      }
      if (VALUE2 == 0x30) { //
        Keyboard.press(')');
      }

      //------------------------
      if (VALUE2 == 0x40) { //
        Keyboard.press('~');
      }
      if (VALUE2 == 0x3C) { //
        Keyboard.press('_');
      }
      if (VALUE2 == 0x5F) { //
        Keyboard.press('+');
      }
      if (VALUE2 == 0x5D) { //
        Keyboard.press('{');
      }
      if (VALUE2 == 0x5E) { //
        Keyboard.press('}');
      }
      if (VALUE2 == 0x5B) { //
        Keyboard.press(':');
      }
      if (VALUE2 == 0x3A) { //
        Keyboard.press('"');
      }
      if (VALUE2 == 0x5C) { //
        Keyboard.press('|');
      }
      if (VALUE2 == 0x3B) { //
        Keyboard.press('<');
      }
      if (VALUE2 == 0x3D) { //
        Keyboard.press('>');
      }
      if (VALUE2 == 0x3E) { //
        Keyboard.press('?');
      }
      if (VALUE2 == 0x2F) { //
        Keyboard.press('/');
      }
    }
    //*****************************************************************************
    //** SHIFT/CTRL/ALT + ARROWs/HOME..END
    //*****************************************************************************

    if (VALUE1 == 0x41 || VALUE1 == 0x51) { //SHIFT + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_DOWN_ARROW);
      }

      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.press(KEY_DELETE);
      }
    }
    //*****************************************************************************
    if (VALUE1 == 0x21 || VALUE1 == 0x31) { //CTRL + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_DELETE);
      }
      //------------------------
    }
    //*****************************************************************************
    if (VALUE1 == 0x09 || VALUE1 == 0x19 || VALUE1 == 0x05 || VALUE1 == 0x15) { //ALT + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DELETE);
      }
      //------------------------
    }
    //*****************************************************************************
    if (VALUE1 == 0x29 || VALUE1 == 0x39 || VALUE1 == 0x25 || VALUE1 == 0x35) { //ALT + CTRL + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DELETE);
      }
    }
    //*****************************************************************************
    if (VALUE1 == 0x49 || VALUE1 == 0x59 || VALUE1 == 0x45 || VALUE1 == 0x55) { //ALT + SHIFT + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DELETE);
      }
      //------------------------
    }
    //*****************************************************************************

    if (VALUE1 == 0x61 || VALUE1 == 0x71) { //SHIFT + CTRL + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_DELETE);
      }
      //------------------------
    }
    //*****************************************************************************

    if (VALUE1 == 0x69 || VALUE1 == 0x79 || VALUE1 == 0x65 || VALUE1 == 0x75) { //ALT + CTRL + shift + ARROWs/HOME..END
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_DELETE);
      }
      //------------------------
    }

    //*****************************************************************************
    //** FUNCTION KEYS:
    //*****************************************************************************

      if ((VALUE1 == 0x09 || VALUE1 == 0x19 || VALUE1 == 0x05 || VALUE1 == 0x15 || VALUE1 == 0x21 || VALUE1 == 0x31 || VALUE1 == 0x51 || VALUE1 == 0x61) && VALUE2 == 0x1C) { //backspace + combinations SHIFT/ALT/CTRL
        Keyboard.press(KEY_BACKSPACE);
      }


    if (VALUE1 == 0x01 || VALUE1 == 0x11) {
      if (VALUE2 == 0x1C) { //backspace
        Keyboard.press(KEY_BACKSPACE);
      }
      if (VALUE2 == 0x1D) { //tab
        Keyboard.press(KEY_TAB);
      }
      if (VALUE2 == 0x1E) { //keypad enter
        Keyboard.press(KEY_RETURN);
      }
      //------------------------
      if (VALUE2 == 0x11) { //keypad HOME
        Keyboard.press(KEY_HOME);
      }
      if (VALUE2 == 0x12) { //keypad END
        Keyboard.press(KEY_END);
      }
      if (VALUE2 == 0x13) { //keypad PAGE UP
        Keyboard.press(KEY_PAGE_UP);
      }
      if (VALUE2 == 0x14) { //keypad PAGE DOWN
        Keyboard.press(KEY_PAGE_DOWN);
      }
      if (VALUE2 == 0x19) { //keypad INSERT
        Keyboard.press(KEY_INSERT);
      }
      if (VALUE2 == 0x1A) { //keypad DELETE
        Keyboard.press(KEY_DELETE);
      }
      //------------------------
      if (VALUE2 == 0x15) { //keypad LEFT
        Keyboard.press(KEY_LEFT_ARROW);
      }
      if (VALUE2 == 0x16) { //keypad RIGHT
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      if (VALUE2 == 0x17) { //keypad UP
        Keyboard.press(KEY_UP_ARROW);
      }
      if (VALUE2 == 0x18) { //keypad DOWN
        Keyboard.press(KEY_DOWN_ARROW);
      }
      //------------------------
      if (VALUE2 == 0x1B) { //keypad ESC
        Keyboard.press(KEY_ESC);
      }

      if (VALUE2 >= 0x61 && VALUE2 <= 0x6c)  { //Function keys F1..F12
        if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
        if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
        if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
        if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
        if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
        if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
        if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
        if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
        if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
        if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
        if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
        if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
      }
    }

    if (VALUE1 == 0X11 && VALUE2 == 0x1E) { //keypad enter
      Keyboard.press(KEY_RETURN);
    }
    if (VALUE1 == 0x01 && VALUE2 == 0x1F) { //spacebar
      Keyboard.press(' ');
    }
    if (VALUE1 == 0x11 && VALUE2 == 0x1F) {
      Keyboard.press(' ');
    }
    if ((VALUE1 == 0x51 && VALUE2 == 0x1F) || (VALUE1 == 0x31 && VALUE2 == 0x1F) || (VALUE1 == 0x19 && VALUE2 == 0x1F) || (VALUE1 == 0x15 && VALUE2 == 0x1F)) {
      Keyboard.press(' ');
    }
    //*****************************************************************************
    //** WIN key
    //*****************************************************************************
    if (VALUE1 == 0x02) { //WIN +  A..Z
      if (VALUE2 >= 0x41 && VALUE2 <= 0x5A) {
        Keyboard.press(KEY_LEFT_GUI);
        Keyboard.press(VALUE2 + 0x20);
      }
    }
    if (VALUE2 == 0x1D && VALUE1 == 0x03)  { //WIN + TAB
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.press(KEY_TAB);
    }

    // WIN KEY
    if (((VALUE2 == 0x0C && VALUE1 == 0x03) || (VALUE2 == 0x0C && VALUE1 == 0x13))) {
      Keyboard.press(KEY_LEFT_GUI);
    }


    if ((VALUE2 == 0x0D && VALUE1 == 0x03) || (VALUE2 == 0x0d && VALUE1 == 0x13) ) {
      Keyboard.press(KEY_RIGHT_GUI);

    }


    //*****************************************************************************
    //** FUNCTION KEYS CTRL,ALT,SHIFT + F1..F12 combinations
    //*****************************************************************************

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C)  && (VALUE1 == 0x41 || VALUE1 == 0x51))  { //SHIFT+ F1..F12
      Keyboard.press(KEY_LEFT_ALT);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C)  && (VALUE1 == 0x09 || VALUE1 == 0x19 || VALUE1 == 0x05 || VALUE1 == 0x15))  { //ALT+F1..F12
      Keyboard.press(KEY_LEFT_ALT);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C) && (VALUE1 == 0x21 || VALUE1 == 0x31))  { //CTRL+F1..F12
      Keyboard.press(KEY_LEFT_CTRL);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C) && (VALUE1 == 0x29 || VALUE1 == 0x39 || VALUE1 == 0x25 || VALUE1 == 0x35))  { //ALT + CTRL+F1..F12
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_LEFT_CTRL);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C) && (VALUE1 == 0x49 || VALUE1 == 0x59 || VALUE1 == 0x45 || VALUE1 == 0x55))  { //ALT + SHIFT+F1..F12
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_LEFT_SHIFT);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C) && (VALUE1 == 0x61 || VALUE1 == 0x71))  { //SHIFT + CTRL+F1..F12
      Keyboard.press(KEY_RIGHT_SHIFT);
      Keyboard.press(KEY_LEFT_CTRL);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    if ( (VALUE2 >= 0x61 && VALUE2 <= 0x6C) && (VALUE1 == 0x69 || VALUE1 == 0x79 || VALUE1 == 0x65 || VALUE1 == 0x75))  { //ALT + CTRL+ SHIFT + +F1..F12
      Keyboard.press(KEY_RIGHT_ALT);
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_LEFT_SHIFT);
      if (VALUE2 == 0x61) Keyboard.press(KEY_F1);
      if (VALUE2 == 0x62) Keyboard.press(KEY_F2);
      if (VALUE2 == 0x63) Keyboard.press(KEY_F3);
      if (VALUE2 == 0x64) Keyboard.press(KEY_F4);
      if (VALUE2 == 0x65) Keyboard.press(KEY_F5);
      if (VALUE2 == 0x66) Keyboard.press(KEY_F6);
      if (VALUE2 == 0x67) Keyboard.press(KEY_F7);
      if (VALUE2 == 0x68) Keyboard.press(KEY_F8);
      if (VALUE2 == 0x69) Keyboard.press(KEY_F9);
      if (VALUE2 == 0x6a) Keyboard.press(KEY_F10);
      if (VALUE2 == 0x6b) Keyboard.press(KEY_F11);
      if (VALUE2 == 0x6c) Keyboard.press(KEY_F12);
    }

    //*****************************************************************************
    //** SPECIAL KEYS COMBINATION
    //*****************************************************************************

    if (VALUE2 == 0x1D && VALUE1 == 0x09)  { //alt+TAB
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_TAB);
    }

    if (VALUE2 == 0x1D && VALUE1 == 0x21)  { //CTRL+TAB
      Keyboard.press(KEY_LEFT_CTRL);
      Keyboard.press(KEY_TAB);
    }

    if (VALUE2 == 0x1D && VALUE1 == 0x41)  { //SHIFT+ TAB
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_TAB);
    }

    /*    if (VALUE2 == 0x1A && (VALUE1 == 0x29 ||  VALUE1 == 0x25))  { //ALT+CTRL DELETE
          Keyboard.press(KEY_RIGHT_CTRL);
          Keyboard.press(KEY_RIGHT_ALT);
          Keyboard.press(KEY_DELETE);
        }*/

    if (VALUE2 == 0x06 && VALUE1 == 0x49)  { //ALT+SHIFT
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_LEFT_SHIFT);
    }


  }
  //*****************************************************************************
  //** SPECIAL KEYS COMBINATION
  //*****************************************************************************
}
