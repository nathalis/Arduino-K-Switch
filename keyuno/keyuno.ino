//*****************************************************************************
//*  KEYBOARD INPUT
//*  beta version
//*  by Nathalis
//******************************************************************************



#include <PS2KeyAdvanced.h>
#include <SoftwareSerial.h>

/* Keyboard constants  Change to suit your Arduino
   define pins used for data and clock from keyboard */
#define DATAPIN 3
#define IRQPIN  2

#define VOLTAGEPIN 8


uint16_t c;
uint8_t breaks = 0;
uint8_t repeats = 0;

PS2KeyAdvanced keyboard;

SoftwareSerial keySerial_1 (6, 7);
SoftwareSerial keySerial_2 (4, 5);

byte KVM=1;
//*****************************************************************************
//*  MAIN SETUP
//*****************************************************************************
void setup( )
{
  Serial.begin( 115200 );
  Serial.println( "PS2 Advanced Key by Nathalis" );

  keySerial_1.begin(115200);
  keySerial_2.begin(115200);

  delay(100);
  pinMode(VOLTAGEPIN, OUTPUT);
  delay(100);
  digitalWrite(VOLTAGEPIN, LOW);
  delay(100);  
  digitalWrite(VOLTAGEPIN, HIGH);
  delay(100);

  // Configure the keyboard library
  keyboard.begin( DATAPIN, IRQPIN );

  delay(100);
  digitalWrite(VOLTAGEPIN, LOW);
  delay(100);  
  digitalWrite(VOLTAGEPIN, HIGH);

  delay(100);
  keyboard.echo( );              // ping keyboard to see if there
  delay(100);
/*  delay( 6 );
  c = keyboard.read( );
  if ( (c & 0xFF) == PS2_KEY_ECHO
       || (c & 0xFF) == PS2_KEY_BAT )
    Serial.println( "Keyboard OK.." );    // Response was Echo or power up
  else if ( ( c & 0xFF ) == 0 )
    Serial.println( "Keyboard Not Found" );
  else
  {
    Serial.print( "Invalid Code received of " );
    Serial.println( c, HEX );
  }*/
}

//*****************************************************************************
//*  MAIN LOOP
//*****************************************************************************

void loop( )
{
  if ( keyboard.available( ) )
  {
    // read the next key
    c = keyboard.read( );
    if ( ( c & 0xFF ) > 0 )
      Serial.println( c , HEX );


    delay(6); // IMPORTANT DELAY!
    
    if ((char)(c & 0xff)==0x02) {
       KVM++;
       if (KVM>2) KVM=1;
    } else {
      
    }

    if (KVM==1) {
    keySerial_1.print( (char)(c >> 8));
    keySerial_1.print( (char)(c & 0xff));
    } else if (KVM==2) {
    keySerial_2.print( (char)(c >> 8));
    keySerial_2.print( (char)(c & 0xff));      
    }
  }
}
