/*

  RAXBOY - A Powerful RPN Spreadsheet for the Arduboy

  This software is covered by the 3-clause BSD license. (c) 2023 by zooxo/deetee
  See also: https://github.com/zooxo/raxboy


  ____________________

    PREAMBLE
  ____________________

  It was quite a challenge to program a spreadheet application for an Arduino.
  On one hand there is a flash RAM restriction of 28 kilobytes - on the other
  hand the used Arduboy platform has six keys only.
  Even if the size of the spreadsheet is restricted to 4x6 cells RAXBOY became
  finally a powerful credit card sized spreadheet application that offers even
  a solver or a function graph plotter.

  Have fun!
  deetee


  ____________________

    NAVIGATION, MENUS
  ____________________

  After starting RAXBOY (RACKS + ARDUBOY) you will find yourself in the
  navigation mode. Select the desired cell with the navigation keys. When
  pressing SHIFT (button A) you enter the first navigation menu:
    NEW    Start a new spreadsheet (the recent one will be deleted
    SAVE   Save (EEPROM) recent spreadsheet to on of 4 slots
    LOAD   Load (EEPROM) a saved spreadsheet from one of 4 slots
    DEL    Delete selected cell

  If you press SHIFT again you enter the second navigation menu:
    ZERO   Select the character to represent zero/empty cells
    INS    Insert (paste) a cell from the clipboard
    COPY   Copy a cell to the clipboard
    TXT    Enter a text cell (also with SHIFT+ENTER)

  ENTER (button B) edits a cell (edit mode). Default is the command mode, but if
  the cell is defined a text cell (TXT) the text will be edited. Please note to
  reset a text cell (to command) with DEL.
  Once in edit mode you see the first edit menu:
    LEFT   Move cursor left
    INS    Insert a command (command cell) or a character (text cell)
    DEL    Delete command/character
    RIGHT  Move cursor right

  When in command mode another SHIFT shows the second edit menu:
    REF    Insert a reference to another cell (navigate to desired cell + ENTER)

  Whenn selecting a command/character (INS) use the left/right (previous/next)
  up/down (page up/down) keys. To select the desired command/character press
  ENTER (which leaves INS).


  ____________________

    COMMANDS
  ____________________

  Please note that RAXBOY uses RPN technology for formula input (enter all 
  arguments before operation). For example to add 1 and 2 insert "1 ENTER 2 +".
  All 115 commands are sorted into different groups:

  |_NUMERIC_|_STACK_|__BASIC__|_CONDITIONS_|_BAT_|_ADVANCED_|_PHYSICAL_CONST_|
   0       12      16        27           30    31         79              115
   0-9.      ENTER   + - * /   < = >        Vcc   10PWR ABS  c
   CHS       BSP     1/X PWR                      ACOS ...   ...
   EE        SWAP    SQRT SQR                     TAN TANH   C2
             ROT     PI % %CHG                    THEN XTR

  Numeric:    0 1 2 3 4 5 6 7 8 9 . CHS EE
  Stack:      ENTER BSP SWAP ROT
  Basic:      + - * / 1/X PWR SQRT SQR PI % %CHG
  Conditions: < = >
  Battery:    BAT
  Advanced:   10PWR ABS ACOS ACOSH ASIN ASINH ATAN ATANH C2F CM2IN COS COSH
              DEG2GRAD DEQ ELSE FRAC HMS2H IF INT INTEGRAL KG2LBS KM2MIL2GAL LN
              LNGAMMA LOG M2FT ND OVER PC PLOT PV QE REC2POL SUM L.R. COUNT
              MEAN/SDEV MIN/MAX SIN SINH SLOPE SOLVE TAN TANH THEN XTREMA
  Physical:   c    299792458         Speed of light
              g    9.80665           Acceleration of gravity
              G    6.67430e-11       Newton constant of gravity
              Vm   0.02271095464     Molar volume of ideal gas
              NA   6.02214076e23     Avogadro constant
              Rinf 10973731.568160   Rydberg constant
              h    6.62607015e-34    Planck constant
              Phi0 2.067833848e-15   Magnetic flux quantum
              a0   5.29177210903e-11 Bohr radius
              k    1.380649e-23      Boltzmann constant
              R    8.314462618       Molar gas constant
              F    96485.33212       Faraday constant
              t    273.15            Celsius temperature
              atm  101325            Standard atmosphere
              e    1.602176634e-19   Elementary charge
              eps0 8.8541878128e-12  Vacuum electric permittivity
              mu0  1.25663706212e-6  Vacuum magnetic permeability
              Z0   376.730313668     Impedance of vacuum
              mU   1.6605390666e-27  Atomic mass constant
              re   2.8179403262e-15  Electron radius
              me   9.1093837015e-31  Electron mass
              mp   1.67262192369e-27 Proton mass
              mn   1.67492749804e-27 Neutron mass
              mmu  1.883531627e-28   Muon mass
              muB  9.2740100783e-24  Bohr magneton
              muN  5.0507837461e-27  Nuclear magneton
              mue  -9.2847647043e-24 Electron magnetic moment
              mup  1.41060679736e-26 Proton magnetic moment
              mun  -9.6623651e-27    Neutron magnetic moment
              mumu -4.4904483e-26    Muon magnetic moment
              alph 7.2973525693e-3   Fine structure constant
              sigm 5.670374419e-8    Stefan-Boltzmann constant
              G0   7.748091729       Conductance quantum
              gamp 2.6752218744e8    Proton gyromagnetic ratio
              C1   3.741771852e-16   First radiation constant
              C2   1.438776877e-2    Second radiation constant

  Advanced commands:
    Conversion (ie KM2MI):
      Works in both directions (both conversions are pushed to the stack).
      For example to convert 1 km to miles enter 1 and KM2MI which shows
      0.62137 miles. Add BSP or SWAP to display 1.60934 km (= 1 mile).
    DEQ
      Differential equation (REF to function, x, y, x-target).
      DEQ solves a differential equation y'=f(x,y) with given start value y(x0)
      due to Runge-Kutta with 4th order (RK4). DEQ calculates the solution
      function (y value for the targeted x).
    Condition < = >
      Compares two stack values and returns 1 (true) or 0 (false)
    IF ELSE THEN
      Due to FORTH a conditional function consists of:
      <condition> IF <true-branch> ELSE <false-branch> THEN
      Please note that ELSE can be omitted and that there is no nesting.
    INTEGRAL, PLOT, SLOPE, SOLVE, XTREMA
      These functions evaluate a cell containing a function (REF to function)
      which depends itself of a referenced cell (REF to x). Additionally PLOT
      and INTEGRAL demand two range x-values (REF to a and b).
      Please note that PLOT plots a function graph when leaving the edit mode.
    PC
      Calculates permuations (nPr) and combinations (nCr)
    PV
      Calculates the present value for a given interest rate and time period.
    QE
      Calculates both solutions for a quadratic equation (y=xx+ax+b)
    REC2POL
      Converts rectangular to polar coordinates. Please note that REC2POL uses
      2 stack entries to represent complex numbers (Y=im/angle, X=re/absolute)
    SUM L.R. COUNT MEAN/SDEV MIN/MAX
      For this statistic functions a data zone has to be defined (REF to start
      and end). The best line fit (L.R.) requires 2 columns (x and y).


  ____________________

    SPECIFICATIONS
  ____________________

    115    Number of commands
    4x6    Size of a spreadsheet (4 columns, 6 rows) ... 24 cells
    2x3    Size of displayed cells
    7      Digits to represent a number or text
    10     Average number of commands/characters per cell (in bytes)
    4      Slots to store spreadsheets to EEPROM
    8      Stack size
    100    Maximal solver iterations
    100    Number of calculation stripes (integrate, differential equation)
    64x32  Plot resolution
    25k    Size of application (flash)


  ____________________

    SPECIAL KEYS
  ____________________

  To set the brightness of the display (6 levels) hold the left cursor button
  and press the upper (brighter) or lower cursor button (darker).
  To enter the sleep mode hold the left cursor button and press the right one.
  To wake up RAXBOY press button A.


  ____________________

    SCHEMATICS
  ____________________

   ____________________________________________________________
  |                                                            |
  |                     Arduino Pro Micro                      |
  |__GND_VCC_15__16___6___4_____________A2__A0__A1___A3___7_8__|
      |   |   |   |   |   |              |   |   |    |   | |
      |   |   |   |   |   |              |   |   |    |   | |
   __GND_VCC__|___|___|___|_GND__    ____|___|___|____|___|_|__
  |  GND VCC SCL SDA RES DC CS   |  |  LEFT UP DOWN RIGHT A B  |
  |     OLED Display 128x64      |  |         BUTTONS          |
  |_________SSD 1306_____________|  |_________(6xGND)__________|

*/


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// I N C L U D E S

#include <avr/power.h> // Needed for power management
#include <avr/sleep.h>
#include <EEPROM.h> // For saving data to EEPROM


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// F O N T

#define FW 3 // Font width
#define FO 32 // Font offset
#define FMAX 158
const byte font[] PROGMEM = { // Font 3x8
  0x00, 0x00, 0x00, // space
  0x00, 0x5f, 0x00, // !
  0x03, 0x00, 0x03, // "
  0x24, 0x2e, 0x24, // # +-
  0x2e, 0x6b, 0x3a, // $
  0x12, 0x08, 0x24, // %
  0x36, 0x49, 0x76, // &
  0x00, 0x03, 0x00, // '
  0x7f, 0x41, 0x41, // (
  0x41, 0x41, 0x7f, // )
  0x14, 0x08, 0x14, // *
  0x08, 0x1c, 0x08, // +
  0x00, 0x60, 0x00, // ,
  0x08, 0x08, 0x08, // -
  0x00, 0x40, 0x00, // .
  0x10, 0x08, 0x04, // /
  0x7f, 0x41, 0x7f, // 0
  0x42, 0x7f, 0x40, // 1
  0x79, 0x49, 0x4f, // 2
  0x41, 0x49, 0x7f, // 3
  0x0f, 0x08, 0x7f, // 4
  0x4f, 0x49, 0x79, // 5
  0x7f, 0x49, 0x79, // 6
  0x03, 0x01, 0x7f, // 7
  0x7f, 0x49, 0x7f, // 8
  0x0f, 0x49, 0x7f, // 9
  0x00, 0x14, 0x00, // :
  0x00, 0x68, 0x00, // ;
  0x08, 0x14, 0x22, // <
  0x14, 0x14, 0x14, // =
  0x22, 0x14, 0x08, // >
  0x03, 0x59, 0x0f, // ?
  0x3e, 0x51, 0x4e, // @
  0x7f, 0x09, 0x7f, // A
  0x7f, 0x49, 0x3e, // B
  0x7f, 0x41, 0x41, // C
  0x7f, 0x41, 0x3e, // D
  0x7f, 0x49, 0x49, // E
  0x7f, 0x09, 0x09, // F
  0x7f, 0x41, 0x79, // G
  0x7f, 0x08, 0x7f, // H
  0x41, 0x7f, 0x41, // I
  0x60, 0x40, 0x7f, // J
  0x7f, 0x08, 0x77, // K
  0x7f, 0x40, 0x40, // L
  0x7f, 0x07, 0x7f, // M
  0x7f, 0x06, 0x7f, // N
  0x7f, 0x41, 0x7f, // O
  0x7f, 0x09, 0x0f, // P
  0x7f, 0x61, 0x7f, // Q
  0x7f, 0x19, 0x6f, // R
  0x4f, 0x49, 0x79, // S
  0x01, 0x7f, 0x01, // T
  0x7f, 0x40, 0x7f, // U
  0x1f, 0x70, 0x1f, // V
  0x7f, 0x70, 0x7f, // W
  0x77, 0x08, 0x77, // X
  0x4f, 0x78, 0x4f, // Y
  0x71, 0x49, 0x47, // Z
  0x02, 0x7f, 0x02, // [ arrow up
  //0x04, 0x08, 0x10, // backslash
  0x7f, 0x7f, 0x7f, // backslash cursor
  0x20, 0x7f, 0x20, // ] arrow down
  //0x02, 0x01, 0x02, // ^
  0x0c, 0x03, 0x0c, // ^
  0x40, 0x40, 0x40, // _
  0x22, 0x7f, 0x22, // ` updown
  0x70, 0x54, 0x7c, // a
  0x7f, 0x44, 0x7c, // b
  0x7c, 0x44, 0x44, // c
  0x7c, 0x44, 0x7f, // d
  0x7c, 0x54, 0x5c, // e
  0x04, 0x7f, 0x05, // f
  0x5c, 0x54, 0x7c, // g
  0x7f, 0x04, 0x7c, // h
  0x40, 0x7d, 0x40, // i
  0x40, 0x44, 0x7d, // j
  0x7f, 0x10, 0x6c, // k
  0x01, 0x7f, 0x40, // l
  0x7c, 0x0c, 0x7c, // m
  0x7c, 0x04, 0x7c, // n
  0x7c, 0x44, 0x7c, // o
  0x7c, 0x14, 0x1c, // p
  0x1c, 0x14, 0x7c, // q
  0x7c, 0x04, 0x04, // r
  0x5c, 0x54, 0x74, // s
  0x04, 0x7f, 0x44, // t
  0x7c, 0x40, 0x7c, // u
  0x1c, 0x60, 0x1c, // v
  0x7c, 0x60, 0x7c, // w
  0x6c, 0x10, 0x6c, // x
  0x5c, 0x50, 0x7c, // y
  0x74, 0x54, 0x5c, // z
  0x08, 0x1c, 0x3e, // { left arrow
  0x00, 0x7f, 0x00, // |
  0x3e, 0x1c, 0x08, // } right arrow
  0x77, 0x5d, 0x49, // ~ sum
  0x55, 0x2a, 0x55, // del grey rectangle 127
#define FDEGREE 128 //--- LETTERS
  0x07, 0x05, 0x07, // degree
#define FAE 129
  0x71, 0x54, 0x7d, // ä
#define FOE 130
  0x7d, 0x44, 0x7d, // ö
#define FUE 131
  0x7d, 0x40, 0x7d, // ü
#define FAO 132
  0x7c, 0x15, 0x7c, // ao
#define FNTILDE 133
  0x7d, 0x05, 0x7d, // n~
#define FQM 134
  0x60, 0x4d, 0x78, // ? flipped
#define FBETA 135 //--- GREEK
  0x7e, 0x25, 0x1a, // ß
#define FDELTA 136
  0x7b, 0x4d, 0x79, // delta
#define FMU 137
  0x7c, 0x50, 0x1c, // mu
#define FPI 138
  0x3f, 0x05, 0x77, // PI
#define FSIGMA 139
  0x7c, 0x4a, 0x7a, // sigma
#define FENTER 140 //--- MATH 
  0x55, 0x55, 0x55, // enter/stack
#define FSQRT 141
  0x10, 0x7f, 0x01, // squareroot
#define FSQR 142
  0x1d, 0x15, 0x17, // sqr
#define FEE 143
  0x3e, 0x2a, 0x2a, // EE
#define FDIV 144
  0x08, 0x2a, 0x08, // div
#define FINV 145
  0x54, 0x25, 0x54, // 1/x
#define FABS 146
  0x7f, 0x00, 0x7f, // abs
#define FINT 147
  0x40, 0x7f, 0x01, // integral
#define FLE 148
  0x28, 0x2c, 0x2a, // <=
#define FNE 149
  0x14, 0x3e, 0x14, // !=
#define FGE 150
  0x2a, 0x2c, 0x28, // >=
#define FANGLE 151
  0x3c, 0x20, 0x20, // angle
#define FMEAN 152
  0x6d, 0x11, 0x6d, // mean x~
#define FDOT 153 //--- SYMBOL
  0x00, 0x08, 0x00, // middle dot
#define FDOT3 154
  0x00, 0x2a, 0x00, // 3 dots
#define FSQRW 155
  0x1c, 0x14, 0x1c, // white square
#define FSQRB 156
  0x1c, 0x1c, 0x1c, // black square
#define FBATT 157
  0x7e, 0x7f, 0x7e, // batt
#define FHOME 158
  0x3c, 0x0e, 0x3c, // home
};


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// S Y S T E M

// PINS, PORTS
// Display
#define CS_PORT PORTD   // CS port
#define CS_BIT PORTD6   // CS physical bit number
#define DC_PORT PORTD   // DC port
#define DC_BIT PORTD4   // DC physical bit number
#define RST_PORT PORTD  // RST port
#define RST_BIT PORTD7  // RST physical bit number
// RGB LED
#define RED_LED 10           // Red LED pin
#define RED_LED_BIT PORTB6   // Red LED physical bit number
#define GREEN_LED 11         // Green LED pin
#define GREEN_LED_BIT PORTB7 // Green LED physical bit number
#define BLUE_LED 9           // Blue LED pin
#define BLUE_LED_BIT PORTB5  // Blue LED physical bit number
// Buttons
#define PIN_LEFT_BUTTON A2 // Left Button
#define LEFT_BUTTON_BIT PORTF5
#define PIN_RIGHT_BUTTON A1 // Right button
#define RIGHT_BUTTON_BIT PORTF6
#define PIN_UP_BUTTON A0
#define UP_BUTTON_BIT PORTF7
#define PIN_DOWN_BUTTON A3 // Down button
#define DOWN_BUTTON_BIT PORTF4
#define PIN_A_BUTTON 7 // A button
#define A_BUTTON_BIT PORTE6
#define PIN_B_BUTTON 8 // B button
#define B_BUTTON_BIT PORTB4
// Other
#define RAND_SEED_IN_BIT PORTF1
// SPI interface
#define SPI_MISO_BIT PORTB3
#define SPI_MOSI_BIT PORTB2
#define SPI_SCK_BIT PORTB1
#define SPI_SS_BIT PORTB0

static void bootpins(void) { // Declare and boot port pins
  PORTB |= _BV(RED_LED_BIT) | _BV(GREEN_LED_BIT) | _BV(BLUE_LED_BIT) | _BV(B_BUTTON_BIT); // Port B
  DDRB  &= ~(_BV(B_BUTTON_BIT) | _BV(SPI_MISO_BIT));
  DDRB  |= _BV(RED_LED_BIT) | _BV(GREEN_LED_BIT) | _BV(BLUE_LED_BIT) | _BV(SPI_MOSI_BIT) | _BV(SPI_SCK_BIT) | _BV(SPI_SS_BIT);
  PORTD |= _BV(CS_BIT); // Port D
  PORTD &= ~(_BV(RST_BIT));
  DDRD  |= _BV(RST_BIT) | _BV(CS_BIT) | _BV(DC_BIT);
  PORTE |= _BV(A_BUTTON_BIT); // Port E
  DDRE  &= ~(_BV(A_BUTTON_BIT));
  PORTF |= _BV(LEFT_BUTTON_BIT) | _BV(RIGHT_BUTTON_BIT) | _BV(UP_BUTTON_BIT) | _BV(DOWN_BUTTON_BIT); // Port F
  PORTF &= ~(_BV(RAND_SEED_IN_BIT));
  DDRF  &= ~(_BV(LEFT_BUTTON_BIT) | _BV(RIGHT_BUTTON_BIT) | _BV(UP_BUTTON_BIT) | _BV(DOWN_BUTTON_BIT) | _BV(RAND_SEED_IN_BIT));
  SPCR = _BV(SPE) | _BV(MSTR); // master, mode 0, MSB first, CPU clock / 2 (8MHz)
  SPSR = _BV(SPI2X);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// D I S P L A Y

#define EECONTRAST 17 // EEPROM address to save screencontrast
#define EEZERO 18 // EEPROM address to hold zero cell character
#define EEOFFSET 19 // Saving slots offset
#define CONTRASTSTEP 48 // Step for in/decreasing contrast
#define FRAMERATE 15 // Maximal number of screen refreshes per second (>3)
#define SW 64 // Virtual screen width
#define SH 32 // Virtual screen height
#define SCREENBYTES 256 // Number of bytes to address screen (64 x 32)/8

static byte dbuf[SCREENBYTES]; // Buffer for virtual screen (costs 256 bytes of dynamic memory)
static byte eachframemillis, thisframestart, lastframedurationms; // Framing times
static boolean justrendered; // True if frame was just rendered

// MACROS
#define _ones(x) ((x)%10)        // Calculates ones unit
#define _tens(x) (((x)/10)%10)   // Calculates tens unit
#define _huns(x) (((x)/100)%10)  // Calculates hundreds unit
#define _tsds(x) (((x)/1000)%10) // Calculates thousands unit


void dtransfer(byte data) { // Write to the SPI bus (display - MOSI pin)
  SPDR = data;
  asm volatile("nop"); // Tiny delay before wait
  while (!(SPSR & _BV(SPIF))) {} // Wait for byte to be sent
}

static void dcommandmode(void) { // Set display to command mode
  bitClear(DC_PORT, DC_BIT);
}
static void ddatamode(void) { // Set display to data mode
  bitSet(DC_PORT, DC_BIT);
}

const byte PROGMEM dinitsequence[] = { // SSD1306 boot sequence
  0x20, 0x00, // Adressing mode (0x00=horiz 0x01=vert 0x02=page)
  0x21, 0x00, 0x7F, // Set column start/end address
  0x22, 0x00, 0x07, // Set page start/end address
  0x40, // RAM start register 01fedcba (0-63)
  0x81, 0x00, // Set contrast (0-FF)
  0x8D, 0x14, // Charge Pump Setting (0x14=enable, 0x10=disabled)
  0xA0, // Normal/Inverse mode 1010011a (0xA6:a=0 normal, 0xA7:a=1 inverse)
  0xA1, // Segment remap - mirror (A0:col0=SEG0, A1:COL127=SEG0)
  0xA4, // Entire display on/off 1010010a (0xA4:a=0 Output follows RAM, 0xA5:a=1 Display ON)
  0xA8, 0x3F, // MUX ratio to N+1 **fedcba (N=3F/1F/F/7/3/1)
  0xAF, // Display on/off 1010111a (0xAE:a=0 off, 0xAF:a=1 on)
  0xB0, // Start address for page addressing mode (B0-B7)
  0xC8, // Set COM Output Scan Direction - flip (C0=normal, C8=remapped)
  0xD3, 0x00, // Display offset **fedcba (vertical shift 0-63)
  0xD5, 0xF1, // Osc_frequ/clock_divide_ratio hgfedcba (hgfe=oscFREQ, dcba=clockDIVratio)
  0xD9, 0x11, // Precharge period hgfedcba (hgfe=phase2, dcba=phase1)
  //0xDB, 0x30, // Vcom-deselect-level 0gfe0000 (30/20/10)
  0xDA, 0x12, // COMpin config 00fe0010 (e=seq/altPIN, f=disable/enableCOMleftrightremap)
};

static void dinit(void) { // Boot screen - reset the display
  bitSet(RST_PORT, RST_BIT); // Set reset pin high to come out of reset
  bitClear(CS_PORT, CS_BIT); // Select the display (permanently, since nothing else is using SPI)
  dcommandmode(); // Run customized boot-up command sequence
  for (byte i = 0; i < sizeof(dinitsequence); i++)
    dtransfer(pgm_read_byte(dinitsequence + i));
  ddatamode();
}

static void setframerate(byte rate) { // Calculate frameduration
  eachframemillis = 1000 / rate;
}

static void dcontrast(byte c) { // Set display contrast
  dcommandmode();
  dtransfer(0x81); dtransfer(c);
  ddatamode();
  EEPROM.write(EECONTRAST, c);
}
static void dcontrastup(void) { // Increase display contrast
  byte c = EEPROM.read(EECONTRAST);
  c = (c <= 255 - CONTRASTSTEP) ? c + CONTRASTSTEP : 255;
  dcontrast(c);
}
static void dcontrastdown(void) { // Decrease display contrast
  byte c = EEPROM.read(EECONTRAST);
  c = (c >= CONTRASTSTEP) ? c - CONTRASTSTEP : 0;
  dcontrast(c);
}

static void dbufclr(void) { // Clear display buffer
  for (int i = 0; i < SCREENBYTES; i++) dbuf[i] = 0;
}

static void delayshort(byte ms) { // Delay (with timer) in ms with 8 bit duration
  long t = millis();
  while ((byte)(millis() - t) < ms) ;
}

static void bootpowersaving(void) {
  PRR0 = _BV(PRTWI) | _BV(PRADC); // Disable I2C-Interface and ADC
  PRR1 |= _BV(PRUSART1); // Disable USART1
  power_adc_disable();
  power_usart0_disable();
  power_twi_disable();
  power_timer1_disable(); // Disable timer 1...3 (0 is used for millis())
  power_timer2_disable();
  power_timer3_disable();
  power_usart1_disable();
}

static void screenoff(void) { // Shut down the display
  dcommandmode();
  dtransfer(0xAE); // Display off
  dtransfer(0x8D); // Disable charge pump
  dtransfer(0x10);
  delayshort(100);
  bitClear(RST_PORT, RST_BIT); // Set RST to low (reset state)
}
static void screenon(void) { // Restart the display after a displayOff()
  dinit();
  dcontrast(EEPROM.read(EECONTRAST));
}

static void idle(void) { // Idle, while waiting for next frame
  SMCR = _BV(SE); // Select idle mode and enable sleeping
  sleep_cpu();
  SMCR = 0; // Disable sleeping
}

static bool nextFrame(void) { // Wait (idle) for next frame
  byte now = (byte) millis(), framedurationms = now - thisframestart;
  if (justrendered) {
    lastframedurationms = framedurationms;
    justrendered = false;
    return false;
  }
  else if (framedurationms < eachframemillis) {
    if (++framedurationms < eachframemillis) idle();
    return false;
  }
  justrendered = true;
  thisframestart = now;
  return true;
}

static void wakeupnow() {} // Dummy wakeup code

static void sleepnow(void) { // Power down - wake up by pressing A (interrupt 4)
  ledsoff();
  screenoff(); // Display off only if screensaver didn't
  pinMode(PIN_A_BUTTON, INPUT_PULLUP);
  attachInterrupt(4, wakeupnow, LOW);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(4, wakeupnow, LOW);
  sleep_mode();
  // SLEEP ... till A (interrupt 4 on Leonardo) is pressed //
  sleep_disable();
  detachInterrupt(4);
  screenon(); // Display on
  delayshort(200);
  ledsoff();
}

static int rawadc() { // Measure Vcc
  power_adc_enable();
  ADMUX = (_BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1)); // Set voltage bits
  delayshort(2); // Wait for ADMUX setting to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // Measuring
  power_adc_disable();
  return (ADC);
}

static void flashmode(void) { //  Secure wait to flash software (UP is pressed when switching on)
  if (!digitalRead(PIN_UP_BUTTON)) {
    digitalWrite(BLUE_LED, LOW);
    while (true) {}; // Wait
  }
}
static void ledsoff(void) { // Disable LEDs
  digitalWrite(RED_LED, HIGH); digitalWrite(GREEN_LED, HIGH); digitalWrite(BLUE_LED, HIGH);
  PORTD |= (1 << 5); PORTB |= (1 << 0); // TX/RX off
}

static double pow10(int8_t e) { // Calculates 10 raised to the power of e
  double f = 1.0F;
  if (e > 0) while (e--) f *= 10.0F;
  else while (e++) f /= 10.0F;
  return (f);
}

static byte expand4bit(byte b) { // 0000abcd  Expand 4 bits (lower nibble)
  b = (b | (b << 2)) & 0x33;     // 00ab00cd
  b = (b | (b << 1)) & 0x55;     // 0a0b0c0d
  return (b | (b << 1));         // aabbccdd
}

static void ddisplay(void) { // Print display buffer (64x32) to real screen (128x64)
  for (byte l = 0; l < 4; l++) { // Four lines
    for (byte k = 0; k < 2; k++) { // Double height
      for (byte j = 0; j < SW; j++) {
        byte tmp = expand4bit((dbuf[j + l * SW] >> (k * 4)) & 0x0f); // Expand 0000abcd
        for (byte i = 0; i < 2; i++) dtransfer(tmp); // Double width
      }
    }
  }
}

static void printcat(byte ch, int x, int y, byte shift) { // Print character
  for (int i = 0; i < FW; i++) {
    byte tmp = pgm_read_byte(&font[FW * (ch - FO) + i]);
    if (shift < 8) {
      dbuf[y * SW + x + i] = tmp << shift; // Upper part
      if (shift > 1) dbuf[(y + 1) * SW + x + i] = tmp >> (8 - shift); // Lower part
    }
    else dbuf[(y + 1) * SW + x + i] = tmp << 1; // Shift one (without 2nd part)
  }
}
static void printsat(const char* s, int x, int y, byte shift) { // Print string
  for (byte i = 0; i < strlen(s); i++) printcat(s[i], x + col2x(i), y, shift);
}

static void pixset(byte x, byte y) { // Sets pixel in dbuf
  int p = x + (y / 8 * SW);
  if (p < SCREENBYTES) dbuf[p] |= (1 << (y % 8));
}

static void lineh(byte x1, byte y, byte x2) { // Print horizontal line
  for (byte x = x1; x < x2; x++) pixset(x, y);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// B U T T O N S

#define B_A 0x01 // Bit of A
#define B_B 0x02 // Bit of B
#define B_L 0x04 // Bit of L
#define B_U 0x08 // Bit of U
#define B_R 0x10 // Bit of R
#define B_D 0x20 // Bit of D

static byte buttonscan(void) { // Scan buttons
  byte b = 0;
  if (!digitalRead(PIN_B_BUTTON)) b |= B_A; // Shift key
  if (!digitalRead(PIN_A_BUTTON)) b |= B_B;
  if (!digitalRead(PIN_LEFT_BUTTON)) b |= B_L;
  if (!digitalRead(PIN_UP_BUTTON)) b |= B_U;
  if (!digitalRead(PIN_RIGHT_BUTTON)) b |= B_R;
  if (!digitalRead(PIN_DOWN_BUTTON)) b |= B_D;
  return (b);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// A P P L I C A T I O N

#define RAD (180.0F/PI) // 180/PI ... used for _atan and _cos
#define IN2CM 2.54F // Conversions
#define LBS2KG 0.4535923F
#define MI2KM 1.609344F
#define GAL2L 3.785412F
#define M2FT 0.2967289F

#define CMDSTEP 11 // Page up/down step when selecting a command
#define ASCSTEP 11 // Page up/down step when selecting a character

#define _END 255 // Terminator
#define _TXT 254 // Text cell
#define _REF 253 // Reference

#define _min(a,b) (((a)<(b))?a:b) // Minimum
#define _max(a,b) (((a)>(b))?a:b) // Maximum
//#define _dec(x,n) (((x)+((n)-1))%(n)) // Decrement
#define _inc(x,n) (((x)+1)%(n)) // Increment

static byte key, oldkey; // Holds entered and old key (prevent keyrepeat)
static boolean iskeyloop = false;
static byte isfg = 0; // Shift status
static boolean isprintscreen = true; // True, if screen should be printed

static boolean isnewnumber = true; // True if stack has to be lifted before entering a new number
static byte decimals = 0; // Number of decimals entered (input after decimal dot)
static boolean isdot = false; // True if dot was pressed and decimals will be entered

double const pc[] PROGMEM = { // Physical constants
  //double const pc[] = { // Physical constants
  299792458.0F, 9.80665F, 6.67430e-11, 0.02271095464F, 6.02214076e23, 10973731.568160F,
  // c: Speed of light, g: Acceleration of gravity, G: Newton constant of gravity
  // Vm: Molar volume of ideal gas, NA: Avogadro constant, Rinf: Rydberg constant
  6.62607015e-34, 2.067833848e-15, 5.29177210903e-11, 1.380649e-23, 8.314462618F, 96485.33212F,
  // h: Planck constant,  Phi0: Magnetic flux quantum, a0: Bohr radius
  // k: Boltzmann constant, R: Molar gas constant, F: Faraday constant
  273.15F, 101325.0F, 1.602176634e-19, 8.8541878128e-12, 1.25663706212e-6, 376.730313668F,
  // t: Celsius temperature, atm: Standard atmosphere, e: Elementary charge
  // eps0: Vacuum electric permittivity, mu0: Vacuum magnetic permeability, Z0: Impedance of vacuum
  1.6605390666e-27, 2.8179403262e-15, 9.1093837015e-31, 1.67262192369e-27, 1.67492749804e-27, 1.883531627e-28,
  // mU: Atomic mass constant, re: Electron radius, me:Electron mass
  // mp: Proton mass, mn: Neutron mass, Mmu: Muon mass
  9.2740100783e-24, 5.0507837461e-27, -9.2847647043e-24, 1.41060679736e-26, -9.6623651e-27, -4.4904483e-26,
  // B: Bohr magneton, muN: Nuclear magneton, mue: Electron magnetic moment
  // mup: Proton magnetic moment, mun: Neutron magnetic moment, mumu: Muon magnetic moment
  7.2973525693e-3, 5.670374419e-8, 7.748091729F, 2.6752218744e8, 3.741771852e-16, 1.438776877e-2,
  // alpha: Fine structure constant, sigma: Stefan-Boltzmann constant, G0: Conductance quantum
  // gamp: Proton gyromagnetic ratio, C1: First radiation constant, C2: Second radiation constant
};

static double absolute(double a, double b) { // Absolute of complex
  return (sqrt(a * a + b * b));
}
static double angle(double a, double b) { // Angle of complex
  double tmp = atan(b / a) * 180.0F / PI;
  if (a < 0.0F) return (b < 0.0F ? tmp - 180.0F : tmp + 180.0F); // Quadrant 2 or 3
  return (tmp); // Quadrant 1 or 4
}

template <class T> void EEwrite(int ee, const T& value) { // Write any datatype to EEPROM
  const byte* p = (const byte*)(const void*)&value;
  for (byte i = 0; i < sizeof(value); i++) EEPROM.write(ee++, *p++);
}
template <class T> void EEread(int ee, T& value) { // Read any datatype from EEPROM
  byte* p = (byte*)(void*)&value;
  for (byte i = 0; i < sizeof(value); i++) *p++ = EEPROM.read(ee++);
}

static void shortcuts() { // Checks button shortcuts (ie contrast, sleep)
  boolean isb = !digitalRead(PIN_B_BUTTON) ? true : false,
          isl = !digitalRead(PIN_LEFT_BUTTON) ? true : false,
          isu = !digitalRead(PIN_UP_BUTTON) ? true : false,
          isr = !digitalRead(PIN_RIGHT_BUTTON) ? true : false,
          isd = !digitalRead(PIN_DOWN_BUTTON) ? true : false;

  if (isb && isl) _nop(); //
  else if (isb && isu) _nop(); //
  else if (isb && isr) _nop(); //
  else if (isb && isd) _nop(); //

  if (isl && isu) dcontrastup(); // Lit+
  else if (isl && isr) sleepnow(); // Sleep
  else if (isl && isd) dcontrastdown(); // Lit-

  else if (isu && isr) _nop(); //
  else if (isu && isd) _nop(); //
  else if (isr && isd) _nop(); //
}

static void strcharat(char *s, char c, byte pos) { // Insert c to string at pos
  memmove(s + pos + 1, s + pos, strlen(s) - pos + 1);
  s[pos] = c;
}
static void strstrat(char * s, char * s1, byte pos) { // Write s1 to s at pos
  memcpy(s + pos, s1, strlen(s1));
}
static void strdelpos(char * s, byte n) { // Delete n-th char from string
  memcpy(s + n, s + n + 1, strlen(s) - n);
}

static byte bytedigits(byte n) { // Count digits of n
  if (n >= 100) return (3); if (n >= 10) return (2); return (1);
}
static void byteat(byte n, byte x, byte r, byte shift) { // Print number at x, row
  byte i = 0, digits = bytedigits(n);
  do {
    printcat((n % 10) + '0', x + col2x(digits - i - 1), r, shift); n /= 10; i++;
  } while (n);
}

static void meter(byte i, byte n) { // Print meter
  lineh(0, SH - 1, i * SW / n);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// S T A C K S

#define DATASTACKSIZE 8 // DATA STACK
double ds[DATASTACKSIZE];
static byte dp = 0;

static void stacklift(void) { // End number entry
  decimals = 0; isdot = false; isnewnumber = true;
}
static void stackreset(void) { // Reset stack
  stacklift(); dp = 0;
}

static double push(double d) { // Push number to data-stack
  if (dp >= DATASTACKSIZE) { // Float stack
    memcpy(ds, &ds[1], (DATASTACKSIZE - 1) * sizeof(double));
    dp--;
  }
  return (ds[dp++] = d);
}
static double pop(void) { // Pop number from data-stack
  return (dp ? ds[--dp] : 0.0F);
}
static void push1(void) { // PUSH 1
  push(1.0F);
}
static void push2(void) { // PUSH 2
  push(2.0F);
}
static void push10(void) { // PUSH 10
  push(10.0F);
}

#define REFSTACKSIZE 5 // REF STACK
static byte refstack[REFSTACKSIZE], refp = 0; // Reference stack
static void pushrefstack(byte n) {
  if (refp >= REFSTACKSIZE) { // Float stack
    memcpy(refstack, &refstack[1], (REFSTACKSIZE - 1)*sizeof(byte));
    refp--;
  }
  refstack[refp++] = n;
}
static byte poprefstack(void) {
  return (refp ? refstack[--refp] : 0);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// F U N C T I O N S - Function table

#define MAXCMDCHAR 5 // Max size of command names

const char c0[] PROGMEM = "0"; // Command names
const char c1[] PROGMEM = "1";
const char c2[] PROGMEM = "2";
const char c3[] PROGMEM = "3";
const char c4[] PROGMEM = "4";
const char c5[] PROGMEM = "5";
const char c6[] PROGMEM = "6";
const char c7[] PROGMEM = "7";
const char c8[] PROGMEM = "8";
const char c9[] PROGMEM = "9";
const char c10[] PROGMEM = ".";
const char c11[] PROGMEM = "#"; // NEG
const char c12[] PROGMEM = {(char)FEE, '\0'};
const char c13[] PROGMEM = {(char)FENTER, '\0'};
const char c14[] PROGMEM = "{"; // CLR, DROP
const char c15[] PROGMEM = "`"; // SWAP
const char c16[] PROGMEM = "]"; // ROT
const char c17[] PROGMEM = "+";
const char c18[] PROGMEM = "-";
const char c19[] PROGMEM = "*";
const char c20[] PROGMEM = {(char)FDIV, '\0'};
const char c21[] PROGMEM = {(char)FINV, '\0'};
const char c22[] PROGMEM = "["; // Power
const char c23[] PROGMEM = {(char)FSQRT, '\0'};
const char c24[] PROGMEM = {(char)FSQR, '\0'};
const char c25[] PROGMEM = {(char)FPI, '\0'};
const char c26[] PROGMEM = "%";
const char c27[] PROGMEM = {(char)FDELTA, '%', '\0'}; // CHG%
const char c28[] PROGMEM = "<";
const char c29[] PROGMEM = "=";
const char c30[] PROGMEM = ">";
const char c31[] PROGMEM = {(char)FBATT, '\0'};
const char c32[] PROGMEM = "10[";
const char c33[] PROGMEM = "ABS";
const char c34[] PROGMEM = "ACOS";
const char c35[] PROGMEM = "ACOSH";
const char c36[] PROGMEM = "ASIN";
const char c37[] PROGMEM = "ASINH";
const char c38[] PROGMEM = "ATAN";
const char c39[] PROGMEM = "ATANH";
const char c40[] PROGMEM = "C`F";
const char c41[] PROGMEM = "cm`in";
const char c42[] PROGMEM = "COS";
const char c43[] PROGMEM = "COSH";
const char c44[] PROGMEM = "d`r";
const char c45[] PROGMEM = "DEQ";
const char c46[] PROGMEM = "ELSE";
const char c47[] PROGMEM = "EXP";
const char c48[] PROGMEM = "FRAC";
const char c49[] PROGMEM = "hms`h";
const char c50[] PROGMEM = "IF";
const char c51[] PROGMEM = "INT";
const char c52[] PROGMEM = {'I', 'N', 'T', (char)FINT, '\0'}; // Integral
const char c53[] PROGMEM = "kg`lb";
const char c54[] PROGMEM = "km`mi";
const char c55[] PROGMEM = "l`gal";
const char c56[] PROGMEM = "LN";
const char c57[] PROGMEM = "LN!";
const char c58[] PROGMEM = "LOG";
const char c59[] PROGMEM = "m`ft";
const char c60[] PROGMEM = "ND";
const char c61[] PROGMEM = "OVER";
const char c62[] PROGMEM = {'P', (char)FDOT3, 'C', '\0'}; // Perm|Comb
const char c63[] PROGMEM = "PLOT";
const char c64[] PROGMEM = "PV";
const char c65[] PROGMEM = "QE";
const char c66[] PROGMEM = "R`P";
const char c67[] PROGMEM = "~~"; // Statistics
const char c68[] PROGMEM = "~LRab";
const char c69[] PROGMEM = "~n";
const char c70[] PROGMEM = {'~', (char)FMEAN, (char)FSIGMA, '\0'};
const char c71[] PROGMEM = "~xtr";
const char c72[] PROGMEM = "SIN";
const char c73[] PROGMEM = "SINH";
const char c74[] PROGMEM = "SLOPE";
const char c75[] PROGMEM = "SOLVE";
const char c76[] PROGMEM = "TAN";
const char c77[] PROGMEM = "TANH";
const char c78[] PROGMEM = "THEN";
const char c79[] PROGMEM = "XTR";
const char c80[] PROGMEM = "c"; // PHYSICAL CONSTANTS (pushes in eval())
const char c81[] PROGMEM = "g";
const char c82[] PROGMEM = "G";
const char c83[] PROGMEM = "Vm";
const char c84[] PROGMEM = "NA";
const char c85[] PROGMEM = "Rinf";
const char c86[] PROGMEM = "h";
const char c87[] PROGMEM = "PHI0";
const char c88[] PROGMEM = "a0";
const char c89[] PROGMEM = "k";
const char c90[] PROGMEM = "R";
const char c91[] PROGMEM = "F";
const char c92[] PROGMEM = "t";
const char c93[] PROGMEM = "atm";
const char c94[] PROGMEM = "e";
const char c95[] PROGMEM = "eps0";
const char c96[] PROGMEM = {(char)FMU, '0', '\0'};
const char c97[] PROGMEM = "Z0";
const char c98[] PROGMEM = "mU";
const char c99[] PROGMEM = "re";
const char c100[] PROGMEM = "me";
const char c101[] PROGMEM = "mp";
const char c102[] PROGMEM = "mn";
const char c103[] PROGMEM = {'m', (char)FMU, '\0'};
const char c104[] PROGMEM = {(char)FMU, 'B', '\0'};
const char c105[] PROGMEM = {(char)FMU, 'N', '\0'};
const char c106[] PROGMEM = {(char)FMU, 'e', '\0'};
const char c107[] PROGMEM = {(char)FMU, 'p', '\0'};
const char c108[] PROGMEM = {(char)FMU, 'n', '\0'};
const char c109[] PROGMEM = {(char)FMU, (char)FMU, '\0'};
const char c110[] PROGMEM = "alpha";
const char c111[] PROGMEM = "siga";
const char c112[] PROGMEM = "G0";
const char c113[] PROGMEM = "gamp";
const char c114[] PROGMEM = "C1";
const char c115[] PROGMEM = "C2";

#define DOT 10 // Defines for commands
#define RPLOT 63
#define RIF 50
#define RELSE 46
#define RTHEN 78
#define RCONST 80 // Start of (36) physical constants

const char* const cmds[] PROGMEM = { // Array of command names
  c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15, c16, c17, c18, c19, c20,
  c21, c22, c23, c24, c25, c26, c27, c28, c29, c30, c31, c32, c33, c34, c35, c36, c37, c38, c39, c40,
  c41, c42, c43, c44, c45, c46, c47, c48, c49, c50, c51, c52, c53, c54, c55, c56, c57, c58, c59, c60,
  c61, c62, c63, c64, c65, c66, c67, c68, c69, c70, c71, c72, c73, c74, c75, c76, c77, c78, c79, c80,
  c81, c82, c83, c84, c85, c86, c87, c88, c89, c90, c91, c92, c93, c94, c95, c96, c97, c98, c99, c100,
  c101, c102, c103, c104, c105, c106, c107, c108, c109, c110, c111, c112, c113, c114, c115
};
byte maxcmd = sizeof(cmds) / sizeof(int); // Number of commands

static void (*dispatch[])(void) = { // Function pointer array
  &_nop, &_nop, &_nop, &_nop, &_nop, &_nop, &_nop, &_nop, &_nop, &_nop, //0 num
  &_nop, &_neg, &_ee, &_dup, &_drop, &_swap, &_rot, //10 stack
  &_add, &_sub, &_mul, &_div, &_inv, &_pow, &_sqrt, &_sqr, &_pi, //17 math1
  &_pct, &_pctchg, &_condlt, &_condeq, &_condgt, &_batt, //26 math2
  &_pow10, &_abs, &_acos, &_acosh, &_asin, &_asinh, &_atan, &_atanh, &_c2f, &_cm2in, //32 functions
  &_cos, &_cosh, &_deg2rad, &deq, &_nop, &_exp, &_frac, &_hms2h, &_nop, &_int, //42 (nop1=else, nop2=if)
  &integral, &_kg2lbs, &_km2mi, &_l2gal, &_ln, &_lngamma, &_log, &_m2ft, &_nd, &_over, //52
  &_pc, &_plot, &_pv, &_qe, &_r2p, &_statsum, &_statlrab, &_statcount, &_statmeanstddev, &_statminmax, //62
  &_sin, &_sinh, &slope, &solve, &_tan, &_tanh, &_nop, &xtrema, //72 (nop=then)
  //80 CONST
};

static void _nop(void) {} // NOP - no operation

static void _abs(void) { // ABS
  push(fabs(pop()));
}
static void _acos(void) { // ACOS =atan(sqrt(1/x/x-1))
  _acossin(); _atan();
}
static void _acossin(void) { // ACOSSIN common
  _dup(); _mul(); _inv(); push1(); _sub(); _sqrt();
}
static void _acosh(void) { // ACOSH =ln(x+sqrt(x*x-1))
  _dup(); _dup(); _mul(); push1(); _sub(); _sqrt(); _add(); _ln();
}
static void _add(void) { // ADD +
  push(pop() + pop());
}
static void _asin(void) { // ASIN =atan(1/(sqrt(1/x/x-1))
  _acossin(); _inv(); _atan();
}
static void _asinh(void) { // ASINH =ln(x+sqrt(x*x+1))
  _dup(); _dup(); _mul(); push1(); _add(); _sqrt(); _add(); _ln();
}
static void _atan(void) { // ATAN
  push(atan(pop()) * RAD);
}
static void _atanh(void) { // ATANH =ln(sqrt((1+x)/(1-x)))
  _dup(); push1(); _add(); _swap(); _neg(); push1(); _add(); _div(); _sqrt(); _ln();
}
static void _batt(void) { // BATT
  push((double)(1126400L / rawadc()) / 1000.0);
}
static void _c2f(void) { // C<>F
  _dup(); push(32.0F); _sub(); push(1.8F); _div(); _swap(); push(1.8F); _mul(); push(32.0F); _add();
}
static void _cm2in(void) { // CM<>IN
  _convert(IN2CM);
}
static void _condeq(void) { // CONDITION =
  push(pop() == pop());
}
static void _condgt(void) { // CONDITION >
  push(pop() < pop());
}
static void _condlt(void) { // CONDITION <
  push(pop() > pop());
}
static void _convert(double f) { // Convert units
  _dup(); push(f); _dup(); _rot(); _mul(); _rot(); _div();
}
static void _cos(void) { // COS
  push(cos(pop() / RAD));
}
static void _cosh(void) { // COSH =(exp(x)+exp(-x))/2
  _exp(); _dup(); _inv(); _add(); push2(); _div();
}
static void _deg2rad(void) { // DEG<>RAD
  _dup(); push(RAD); _dup(); _rot(); _mul(); _rot(); _div();
}
static void _div(void) { // DIV /
  _inv(); _mul();
}
static void _dot(void) { // DOT .
  if (isnewnumber) {
    push(0.0F); // Start new number with 0
    decimals = 0; isnewnumber = false;
  }
  isdot = true;
}
static void _drop(void) { // DROP
  pop();
}
static void _dup(void) { // DUP
  if (dp) push(ds[dp - 1]);
}
static void _ee(void) { // EE
  push(pow10(pop())); _mul();
}
static void _exp(void) { // EXP
  push(exp(pop()));
}
static void _frac(void) { // FRAC
  _dup(); _int(); _sub();
}
static void _hms2h(void) { // HMS>H
  double a = pop() + 1e-10; // Add delta to avoid leap
  double s = a * 3600.0F;
  double hh = (long)(s / 3600.0F), mm = (long)((s - hh * 3600.0F) / 60.0F), ss = (s - mm * 60.0F - hh * 3600.0F);
  push(hh + mm / 100.0F + ss / 10000.0F); // h2hms
  hh = (long)a; mm = (long)((a - hh) * 100.0F); ss = ((a - hh) * 100.0F - mm) * 100.0F;
  push((ss / 60.0F + mm) / 60.0F + hh); // hms2h
}
static void _int(void) { // INT
  push((long)pop());
}
static void _inv(void) { // INV
  push(1.0F / pop());
}
static void _kg2lbs(void) { // KG>LBS
  _convert(LBS2KG);
}
static void _km2mi(void) { // KM>MI
  _convert(MI2KM);
}
static void _l2gal(void) { // L>GAL
  _convert(GAL2L);
}
static void _ln(void) { // LN
  push(log(pop()));
}
static void _lngamma(void) { // LNGAMMA =(ln(2*PI)-ln(x))/2+x*(ln(x+1/(12*x-1/10/x))-1)
  push1(); _add(); _dup(); _dup(); _dup(); _dup(); push(12.0F); _mul();
  _swap(); push1(); _mul(); _inv(); _sub(); _inv(); _add(); _ln(); push1(); _sub(); _mul();
  _swap(); _ln(); _neg(); push2(); push(PI); _mul(); _ln(); _add(); push2(); _div(); _add();
}
static void _log(void) { // LOG
  _ln(); push10(); _ln(); _div();
}
static void _m2ft(void) { // M>FT
  _convert(M2FT);
}
static void _mul(void) { // MULT *
  push(pop()*pop());
}
static void _nd(void) { // ND
  _dup(); _dup(); _dup(); _dup(); _mul(); _mul(); push(0.07F); _mul(); _neg();
  _swap(); push(1.6F); _mul(); _neg(); _add(); _exp(); push1(); _add(); _inv(); _swap();
  _dup(); _mul(); _neg(); push2(); _div(); _exp(); push(2 * PI); _sqrt(); _inv(); _mul();
}
static void _neg(void) { // NEGATE
  push(-pop());
}
static void _numinput(byte k) { // NUM Numeric input (0...9)
  if (isdot) { // Append decimal
    push(k); push(pow10(++decimals)); _div(); _add();
  }
  else if (isnewnumber) push(k); // Push new numeral
  else { // Append numeral
    push10(); _mul();
    push(k); _add();
  }
  isnewnumber = false;
}
static void _over(void) { // OVER
  _swap(); _dup(); _rot(); //_rot();
}

static void _pct(void) { // %  =B*x/100%
  _over(); _mul(); push(100.0F); _div();
}
static void _pctchg(void) { // %CHG =(x/B-1)*100%
  _over(); _div(); push1(); _sub(); push(100.0F); _mul();
}
static void _pc(void) { // PC PERMCOMB
  byte a = pop(), b = pop(), k = a; // Save k for Comb
  a = b - a; push1();
  for (byte i = a; i < b; i++) push(pop() * (i + 1)); // Perm
  _dup(); // Push Perm
  for (byte i = 1; i <= k; i++) push(pop() / i); // Comb
}
static void _pi(void) { // PI
  push(PI);
}
static void _plot(void) { // PLOT
  plot();
}
static void _pow10(void) { // POW10 =exp(b*ln(10))
  push10(); _ln(); _mul(); _exp();
}
static void _pow(void) { // POWER =a^b=exp(b*ln(a))
  _swap(); _ln(); _mul(); _exp();
}
static void _pv(void) { // PV PRESENT VALUE PV(i,n)= (1-(1/(1+i)^n))/i = ((1+i)^n-1)/(1+i)^n/i
  _over(); push1(); _add(); _swap(); _pow(); _inv(); _neg(); push1(); _add(); _swap(); _div();
}
static void _qe(void) { // QE QUADRATIC EQUATION x12=-p/2+-sqrt(p*p/4-q)
  _swap(); push2(); _div(); _neg(); _dup(); _sqr(); _rot(); _rot(); _sub(); _sqrt();
  _over(); _over(); _sub(); _rot(); _add();
}
static void _r2p2r(double a, double b) { // ->R
  push(a * sin(b * PI / 180.0F)); push(a * cos(b * PI / 180.0F));
}
static void _r2p2p(double a, double b) { // ->P
  push(angle(a, b)); push(absolute(a, b));
}
static void _r2p(void) { // R<>P
  double a = pop(), b = pop();
  _r2p2r(a, b); _r2p2p(a, b);
}
static void _rot(void) { // ROT
  double a = pop(), b = pop();
  push(a); _swap(); push(b);
}
static void _sin(void) { // SIN =cos(90-x)
  push(90.0F); _swap(); _sub(); _cos();
}
static void _sinh(void) { // SINH =(exp(x)-exp(-x))/2
  _exp(); _dup(); _inv(); _neg(); _add(); push2(); _div();
}
static void _sqrt(void) { // SQRT
  _ln(); push2(); _div(); _exp();
}
static void _sqr(void) { // SQR
  _dup(); _mul();
}
static void _stat(byte result) { // STAT (result: 0n, 1sum, 2meanstddev, 3minmax)
  double sx = 0.0, sxx = 0.0, minx, maxx;
  byte count = 0, to = poprefstack(), from = poprefstack();
  minx = maxx = rvalread(from);
  for (byte i = n2col(from); i <= n2col(to); i++) // Sums
    for (byte j = n2row(from); j <= n2row(to); j++) {
      double val = rvalread(colrow2n(i, j));
      count++; sx += val; sxx += (val * val);
      if (val > maxx) maxx = val; if (val < minx) minx = val;
    }
  pop(); pop(); // Remove unused stack arguments
  double mean = sx / count;
  if (result == 1) push(sx);
  else if (result == 2) {
    push(mean); push(sqrt((sxx - count * mean * mean) / (count - 1)));
  }
  else if (result == 3) {
    push(minx); push(maxx);
  }
  else push(count);
}
static void _statcount(void) { // STAT COUNT
  _stat(0);
}
static void _statlrab(void) { // STAT LRa =(n*Sxy-Sx*Sy)/(n*Sxx-Sx*Sx) LRb =(Sy-LRa*Sx)/n
  double sx = 0.0, sxx = 0.0, sy = 0.0, sxy = 0.0;
  byte count = 0, to = poprefstack(), from = poprefstack();
  byte c = n2col(from); // x-col (y-col = x-col +1)
  for (byte i = n2row(from); i <= n2row(to); i++) {
    double valx = rvalread(colrow2n(c, i)), valy = rvalread(colrow2n(c + 1, i));
    count++; sx += valx; sxx += (valx * valx); sy += valy; sxy += (valx * valy);
  }
  pop(); pop(); // Remove unused stack arguments
  double LRa = (count * sxy - sx * sy) / (count * sxx - sx * sx);
  push(LRa); push((sy - LRa * sx) / count);
}
static void _statmeanstddev(void) { // STAT MEAN =Sx/n
  _stat(2);
}
static void _statminmax(void) { // STAT MIN MAX
  _stat(3);
}
static void _statsum(void) { // STAT SUM
  _stat(1);
}
static void _sub(void) { // SUB -
  _neg(); _add();
}
static void _swap(void) { // SWAP
  //if (dp > 1) {
    double a = pop(), b = pop();
    push(a); push(b);
  //}
}
static void _tan(void) { // TAN =sin/cos
  _dup(); _dup(); _sin(), _swap(); _cos(); _div();
}
static void _tanh(void) { // TANH =sinh/cosh
  _dup(); _sinh(); _swap(); _cosh(); _div();
}


static void execute(byte cmd) { // Execute command
  if (cmd < maxcmd) {
    (*dispatch[cmd])(); // Dispatch intrinsic/builtin command
    stacklift(); // New number - except 0-9. (treated in evalall)
  }
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// M E N U - 'Star' menus

#define MAXSTARCHAR 4 // Maximal number of characters for a 'star' menu entry

#define MINSDEL 0 // Codes for menus
#define MSAVLOAD 1
#define M1234 2
#define MREF 3
#define MZERO 4

const char m0[] PROGMEM = "{";
const char m1[] PROGMEM = "INS";
const char m2[] PROGMEM = "}";
const char m3[] PROGMEM = "DEL";
const char m4[] PROGMEM = "NEW";
const char m5[] PROGMEM = "SAVE";
const char m7[] PROGMEM = "LOAD";
const char m8[] PROGMEM = "1";
const char m9[] PROGMEM = "2";
const char m10[] PROGMEM = "3";
const char m11[] PROGMEM = "4";
const char m12[] PROGMEM = "REF";
const char m13[] PROGMEM = "[";
const char m15[] PROGMEM = "]";
const char m16[] PROGMEM = "ZERO";
const char m18[] PROGMEM = "TXT";
const char m19[] PROGMEM = "COPY";

const char* const mtxt[] PROGMEM = {
  m0, m1, m2, m3, //    {    INS  }   DEL
  m4, m5, m3, m7, //    NEW  SAVE DEL LOAD
  m8, m9, m10, m11, //  1    2    3   4
  m12, m13, m2, m15, // REF  [    }   ]
  m16, m1, m18, m19 //  ZERO INS  TXT COPY
};

static void printstar(const char* sw, const char* sn, const char* se, const char* ss) { // Print strings as star
  printsat(sw, 20 - strlen(sw) * 5, 2, 5); // W (right-justified)
  printsat(sn, 22 + (MAXSTARCHAR - strlen(sn)) * 5 / 2, 2, 1); // N (centered)
  printsat(se, 44, 2, 5); // E (left-justified)
  printsat(ss, 22 + (MAXSTARCHAR - strlen(ss)) * 5 / 2, 2, 9); // S (centered)
}

static void printmenu(byte n) {
  char s[4][MAXSTARCHAR+1];
  for (byte i = 0; i < 4; i++) strcpy_P(s[i], pgm_read_word(mtxt + 4 * n + i));
  printstar(s[0], s[1], s[2], s[3]);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// R A X C O M M O N - Common code for RAX

#define RMEM 10 // Average formula memory per cell (>1)
#define RC 4 // Spreadsheet dimensions
#define RR 6
#define DC 2 // Display cell dimensions
#define DR 3
#define RCELLS (RR*RC) // Max number of cells (24)
#define RMEMMAX (RR*RC*RMEM) // Max size of rmem (240)
#define CELLSIZE 7 // Max number of digits/chars per cell

#define MAXITERATE 100 // Max number of solver iterations
#define DELTAX 1E-3 // Infinitesimal difference
#define STRIPES 100 // Number of calculation stripes (integrate, differential equation)

#define MAXLONGSTRINGSIZE 32 // String size to treat formulae
#define MAXSHORTSTRINGSIZE 10 // String size to treat numbers
#define BBUFLEN 64 // Length of common buffer (copy/paste, plot)

static byte rmem[RMEMMAX]; // Spreadsheet array
static double rval[RMEMMAX]; // Cell value array

static byte selcell = 0, oldselcell = 0; // Selected cell
static byte startcol = 1, startrow = 1, oldstartcol = 1, oldstartrow = 1; // Start cell for printing
static byte editcurpos = 1; // Cursor position in edited cell
static byte select; // Selected command or character
static byte xcell, ycell; // Referenced variable cell (in formula of fcell)
static byte bbuf[BBUFLEN]; // Common buffer (copy/paste, plot)
static byte zerochar = FO; // Zero cell character

static double xtmp, ytmp; // Temporary x variable (solve, integrate, fnplot, deq)
static double miny, maxy; // Minimum/Maximum function value

static boolean isinsert = false; // Insert command or character
static boolean isref = false; // Demand reference
static boolean isextval = false; // To eval cell with other/given reference value


static double rvalread(byte n) { // Read value from rval
  return (rval[n]);
}

static boolean istxtcell(byte n) { // True if cell n is a text cell
  if (rmem[rmseek(n)] == _TXT) return (true);
  return (false);
}

static void initpos() { // Init cell position
  startrow = startcol = 1; selcell = 0;
}

static void rinit(void) { // Init complete spreadsheet
  zerochar = EEPROM[EEZERO]; if (zerochar < FO || zerochar > FMAX) zerochar = FO;
  memset(rmem, _END, RMEMMAX);
  initpos();
  evalall();
}

static byte rmseek(byte n) { // Seek start address of n-th cell
  byte cell = 0, p = 0;
  n = min(n, RCELLS); // Minimum
  while (cell < n) if (rmem[p++] == _END) cell++;
  return (p);
}

static byte memlen(void) { // Length of selcell
  return (rmseek(selcell + 1) - rmseek(selcell) - 1);
}

static byte n2col(byte n) { // n -> col
  return ((n % RC) + 1);
}
static byte n2row(byte n) { // n -> row
  return ((int)(n / RC) + 1);
}
static byte colrow2n(byte c, byte r) { // (col|row) -> n
  return (((r - 1) * RC) + (c - 1));
}

static byte col2x(byte col) {
  return (col * (FW + 1));
}

static void cell2s(char*s, byte n) { // Convert cell to string
  s[0] = n2col(n) + 'A' - 1; s[1] = n2row(n) + '0'; s[2] = '\0';
}

static byte b2slot(byte b) { // Converts button to slot number
  if (b == B_L) return (1);
  else if (b == B_U) return (2);
  else if (b == B_R) return (3);
  else return (4);
}

static boolean isslot(byte b) { // True if cursor button is pressed
  if (b == B_L || b == B_U || b == B_R || b == B_D) return (true);
  return (false);
}

static void delcell(byte n) {
  rval[n] = 0.0F;
  byte p = rmseek(n), next = rmseek(n + 1);
  if (rmem[p] != _END) memcpy(rmem + p, rmem + next - 1, rmseek(RCELLS) - next + 1);
}

static void slope(void) { // SLOPE = (f2- - 8 * f1- + 8 * f1 - f2) / 12 / deltax
  double x, slope = 0.0F;
  xcell = poprefstack();
  byte fcell = poprefstack();
  if (fcell != selcell) { // Prevent self reference
    x = rval[xcell];
    isextval = true; // Evaluate references with start value (xtmp)
    xtmp = x - 2.0F * DELTAX; eval(fcell); slope = rval[fcell]; // f-2
    xtmp = x - DELTAX; eval(fcell); slope -= 8.0F * rval[fcell]; // f-1
    xtmp = x + DELTAX; eval(fcell); slope += 8.0F * rval[fcell]; // f1
    xtmp = x + 2.0F * DELTAX; eval(fcell); slope -= rval[fcell]; // f2
    isextval = false;
    eval(fcell); // Inits stack
    push(slope / 12.0F / DELTAX);
  }
  else selcell++; // Workaround to eval self referenced cells
}

static void solve(void) { // SOLVE xi+1 = xi - fxi / y' ... y'=(fxi - fxi+d ) / d
  double x, y, slope, diff = 1.0F;
  xcell = poprefstack();
  byte fcell = poprefstack();
  if (fcell != selcell) { // Prevent self reference
    x = rval[xcell];
    isextval = true; // Evaluate references with start value (xtmp)
    for (byte i = 0; fabs(diff) > DELTAX && i < MAXITERATE; i++) {
      xtmp = x; eval(fcell); y = rval[fcell]; // f(x)
      xtmp = x + DELTAX; eval(fcell); slope = (rval[fcell] - y) / DELTAX; // slope =(f(x)-f(x+d))/d
      diff = y / slope; x -= diff; // xnew =xold-f(x)/slope
    }
    isextval = false;
    eval(fcell); // Inits stack
    push(x);
  }
  else selcell++; // Workaround to eval self referenced cells
}

static void minmax(void) { // Min/Max
  plotminmax(false);
}
static void xtrema(void) { // Extrema
  minmax();
  push(miny); push(maxy);
}

static void integral(void) { // INTEGRAL =(fa+fb+2*feven+4*fodd)*deltax/3
  double b = rval[poprefstack()], a = rval[poprefstack()], deltax = (b - a) / STRIPES, sum = 0.0;
  xcell = poprefstack();
  byte fcell = poprefstack();
  if (fcell != selcell) { // Prevent self reference
    isextval = true; // Evaluate references with start value (xtmp)
    xtmp = a; eval(fcell); sum += rval[fcell]; // fa
    xtmp = b; eval(fcell); sum += rval[fcell]; // fb
    for (byte i = 1; i < STRIPES; i++) { // fi
      byte m = 4 * ((i / 2.0F - (int)(i / 2.0F)) + 0.5F);
      xtmp = a + i * deltax; eval(fcell); sum = sum + m * rval[fcell];
    }
    isextval = false;
    eval(fcell); // Inits stack
    push(sum * deltax / 3.0F);
  }
  else selcell++; // Workaround to eval self referenced cells
}

static void deq(void) { // DIFFERENTIAL EQUATION (Runge-Kutta RK4) - y'=f(x,y) y(x0)=y0
  double b = rval[poprefstack()]; // Target x
  ycell = poprefstack(); xcell = poprefstack(); // y- and x-cell
  ytmp = rval[ycell];
  byte fcell = poprefstack(); // f(x,y)-cell
  double a = rval[xcell], deltax = (b - a) / STRIPES;
  double k1, k2, k3, k4; // Calculation variables
  if (fcell != selcell) { // Prevent self reference
    isextval = true; // Evaluate references with start value (xtmp and ytmp)
    for (byte i = 0; i < STRIPES; i++) {
      double xi = a + i * deltax, yi = ytmp;
      xtmp = xi; ytmp = yi; eval(fcell); k1 = deltax * rval[fcell]; // xi, yi
      xtmp = xi + deltax / 2; ytmp = yi + k1 / 2; eval(fcell); k2 = deltax * rval[fcell]; // xi+h/2, yi+k1/2
      ytmp = yi + k2 / 2; eval(fcell); k3 = deltax * rval[fcell]; // xi+h/2, yi+k2/2
      xtmp = xi + deltax; ytmp = yi + k3; eval(fcell); k4 = deltax * rval[fcell]; // xi+h, yi+k3
      ytmp = yi + (k1 + 2 * k2 + 2 * k3 + k4) / 6; // y|i+1|
    }
    isextval = false;
    eval(fcell); // Inits stack
    ycell = _END; // Prevent impact of other calculus functions
    push(ytmp);
  }
}

static void bbufclr() { // Clear bbuf
  memset(bbuf, _END, BBUFLEN);
}

static void copy(void) { // Select copycell
  bbufclr();
  unsigned int p = rmseek(selcell);
  byte cmd = 0, pos = 0;
  while ((cmd = rmem[p + pos]) != _END && pos < MAXLONGSTRINGSIZE) bbuf[pos++] = cmd;
}

static void paste(void) { // Paste copied cell
  if (bbuf[0] != _END) {
    delcell(selcell);
    byte pos = 0;
    while (bbuf[pos++] != _END && pos < BBUFLEN) memcharat(selcell, bbuf[pos - 1], pos - 1);
  }
  evalall();
}

static double eval(byte n) { // Eval mem of cell n
  byte p = rmseek(n), mp = 0, c; // Pointer, mempointer and command
  boolean istrue = false; // IF-TRUE-clause-detection
  double oldval = rval[n]; // To calculate squared error
  stackreset(); refp = 0; // Reset stacks
  while ((c = rmem[p + mp]) != _END) { // Execute commands
    if (c == _REF) { // Reference
      mp++;
      byte addr = rmem[p + mp];
      pushrefstack(rmem[p + mp]);
      if (isextval && addr == xcell) push(xtmp); // Pipe xvalue
      else if (isextval && addr == ycell) push(ytmp); // Pipe yvalue
      else push(rval[rmem[p + mp]]); // Regular (non-solve) value
      mp++;
    }
    else if (istrue && c == RELSE) { // Ignore FALSE clause
      do c = rmem[p + mp++]; while (c != RTHEN && c != _END);
      stacklift(); istrue = false;
    }
    else if (c == RIF) { // IF
      if (pop() == true) { // TRUE clause
        mp++; istrue = true;
      }
      else { // FALSE clause
        do c = rmem[p + mp++]; while (c != RELSE && c != _END);
      }
    }
    else if (c >= RCONST) {
      push(pgm_read_float(&pc[c - RCONST])); mp++;
    }
    else if (c < DOT) { // Numinput
      _numinput(c); mp++;
    }
    else if (c == DOT) { // Dotinput
      _dot(); mp++;
    }
    else if (c < maxcmd) { // Dispatch key
      execute(c); mp++;
    }
    else mp++;
  }
  rval[n] = pop(); // Assign value
  return ((rval[n] - oldval) * (rval[n] - oldval));
}


static void evalall(void) { // Eval all cells
  //for (byte i = 0; i < RCELLS; i++) eval(i); // One time calculation
  //for (byte j = 0; j < RCELLS; j++) for (byte i = 0; i < RCELLS; i++) eval(i); // n² times
  for (byte j = 0; j < RCELLS; j++) { // n² times with SSE - Outer loop
    double sse = 0.0F; // Sum of squares error (SSE)
    for (byte i = 0; i < RCELLS; i++) if (!istxtcell(i)) sse += eval(i); // Eval and SSE (not for text cell)
    if (sse < DELTAX) break; // Break outer loop if SSE is low
  }
  /*byte frequ[RCELLS] = {0}; // Calculate due to REF frequency
    for (byte i = 0; i < rmseek(RCELLS); i++) if (rmem[i] == _REF) frequ[rmem[i + 1]]++; // Count frequency of REFs
    byte maxf = 0; for (byte i = 0; i < RCELLS; i++) if (frequ[i] > maxf) maxf = frequ[i]; // Evaluate frequency maximum
    for (byte f = maxf + 1; f > 0; f--) for (byte i = 0; i < RCELLS; i++) if (frequ[i] == f - 1) eval(i); // Eval high frequ cells first
  */
}

static void memdelat(byte n, byte pos) { // Delete mem at pos
  byte p = rmseek(n) + pos;
  memcpy(rmem + p, rmem + p + 1, rmseek(RCELLS) - p);
}
static void memcharat(byte n, byte c, byte pos) { // Insert c to cell n at pos
  byte eomem = rmseek(RCELLS);
  if (eomem < RMEMMAX) { // Space left
    byte p = rmseek(n) + pos;
    memmove(rmem + p + 1, rmem + p, eomem - p);
    rmem[p] = c;
  }
}

static void printtxtcell() { // Print cell text
  if (!editcurpos) printcat('\\', col2x(3), 0, 0); // Empty
  else {
    byte p = rmseek(selcell) + 1, curpos = 0, mp = 0, c;
    while ((c = rmem[p + mp]) != _END && mp < 8) {
      printcat(rmem[p + mp], col2x(3 + curpos), 0, 0);
      if (curpos == editcurpos - 1) printcat('\\', col2x(3 + ++curpos), 0, 0); // Cursor
      curpos++; mp++;
    }
  }
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// P L O T - Plot function graph

static boolean isplot = false;

#define PLOTX 64 // Plot dimensions
#define PLOTY 32

byte xaxis, yaxis; // Coordinates of axis
boolean isyaxis; // True, if y-axis is to be plotted

static void plotminmax(boolean isdoplot) { // Min/Max and plot
  double b = rval[poprefstack()], a = rval[poprefstack()], deltax = (b - a) / PLOTX;
  xcell = poprefstack();
  byte fcell = poprefstack();
  if (fcell != selcell) { // Prevent self reference
    isextval = true; // Evaluate references with start value (xtmp)
    xtmp = a; eval(fcell); miny = maxy = rval[fcell]; // Init miny maxy
    for (byte i = 1; i < PLOTX; i++) { // Evaluate miny maxy
      xtmp = a + i * deltax; eval(fcell); miny = _min(rval[fcell], miny); maxy = _max(rval[fcell], maxy);
    }
    if (isdoplot) {
      xaxis = a / (a - b) * PLOTX, yaxis = SH - miny / (miny - maxy) * PLOTY; // Save plotting parameters
      isyaxis = false; if (a * b <= 0.0F) isyaxis = true;
      for (byte i = 0; i < PLOTX; i++) { // Evaluate plot values
        xtmp = a + i * deltax; eval(fcell);
        bbuf[i] = PLOTY - 1 - round((miny - rval[fcell]) / (miny - maxy) * PLOTY);
      }
      isextval = false;
      eval(fcell); // Inits stack
    }
    push(miny); push(maxy);
  }
  else selcell++; // Workaround to eval self referenced cells
}

static void plot() {
  plotminmax(true);
}

static void printplot(void) { // Print plot sheet
  if (isyaxis) for (byte i = 0; i < PLOTX; i++) pixset(xaxis , i); // Y-axis
  for (byte i = 0; i < PLOTX; i++) pixset(i, yaxis); // X-axis
  for (byte i = 0; i < PLOTX; i++) pixset(i, bbuf[i]); // Function graph
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// R A X A S C - Insert character (ASCII+)

static boolean isasc = false;

static void ascnav(void) { // Navigation for ascii selection
  iskeyloop = true;
  if (key == B_U) { // PgUp
    if (select > FO + ASCSTEP) select -= ASCSTEP; else select = FO;
  }
  else if (key == B_D) { // PgDn
    if (select < FMAX - ASCSTEP) select += ASCSTEP; else select = FMAX;
  }
  else if (key == B_L && select > FO) select--; // Prev
  else if (key == B_R && select < FMAX) select++; // Next
}

static void printasc(void) { // Print ascii selection screen
  byteat(select, col2x(0), 2, 7); // Cmd#
  printcat('{', col2x(5), 2, 7); printcat(select, col2x(7), 2, 7); printcat('}', col2x(9), 2, 7);
  meter(select - FO, FMAX - 1 - FO);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// R A X T X T - Edit text cell

static boolean istxt = false;

static void aligneditcurpos(void) { // Align editcurpos
  if (editcurpos < memlen() - 1) editcurpos++;
}

static void edittxtcell(void) { // Prepare text cell editing
  select = FO;
  istxt = true; editcurpos = 0;
  if (istxtcell(selcell)) editcurpos = memlen() - 1;
  else memcharat(selcell, _TXT, editcurpos);
}

static void printtxt(void) {
  printselcell();
  printtxtcell();
  if (isinsert) printasc(); else printmenu(MINSDEL);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// R A X E D I T - Edit command cell

static boolean isedit = false;

static void seteditcurpos(void) { // Set editcurpos to end of formula of cell n
  byte delta = memlen() + 1;
  editcurpos = (delta ? delta - 1 : 0);
}

static void createtxtstring(char* s, byte cell, boolean iscursor) { // Create text of text cell
  if (iscursor) {
    byte p = rmseek(cell) + 1, pend = rmseek(cell + 1);
    for (byte i = 0; i < pend - p - 1 && i < 7; i++) {
      if (i == editcurpos) s[i] = '\\'; else s[i] = rmem[p + i];
    }
    s[pend - p - 1] = '\0';
  }
  else {
    byte p = rmseek(cell) + 1, pend = rmseek(cell + 1);
    for (byte i = 0; i < pend - p - 1 && i < 7; i++) s[i] = rmem[p + i];
    s[pend - p - 1] = '\0';
  }
}

static void createeditstring(char * s, boolean iscursor) { // Create editable string
  byte c, pos = 0, txtpos = 0, curtxtpos = 0;
  byte p = rmseek(selcell);
  if (istxtcell(selcell)) createtxtstring(s, selcell, iscursor); // Text
  else { // Formula
    if (iscursor && rmem[p] == _END) s[0] = '\\'; // Start editing a new line
    while ((c = rmem[p + pos]) != _END && txtpos < MAXLONGSTRINGSIZE - 4) { // Create string
      if (c == _REF) { // Reference
        char tmpstr[3]; cell2s(tmpstr, rmem[p + pos + 1]); // Cell name
        strstrat(s, tmpstr, txtpos); txtpos += strlen(tmpstr);// + 1; // +1 for blank
        if (iscursor && editcurpos && pos == editcurpos - 2) strcharat(s, '\\', txtpos++); // Cursor
        pos++;
      }
      else { // Insert command
        char cmdstr[MAXCMDCHAR + 1]; strcpy_P(cmdstr, pgm_read_word(cmds + c)); // Command
        strstrat(s, cmdstr, txtpos); txtpos += strlen(cmdstr);
        if (iscursor && editcurpos && pos == editcurpos - 1) strcharat(s, '\\', txtpos++); // Cursor
      }
      pos++;
    }
    for (byte i = 0; i < strlen(s); i++) {
      if (s[i] == ' ' && s[i + 1] == '\\') strdelpos(s, i); // Remove blank infront of cursor
      if (s[i] == '\\') curtxtpos = i; // Store cursor text position
    }
    if (curtxtpos > 12) memcpy(s, s + curtxtpos - 12, 13); s[13] = '\0'; // Trim (long) string
  }
}

static void printedit(void) { // Print edit page (formula, menu)
  char s[MAXLONGSTRINGSIZE] = {0};
  createeditstring(s, true); printsat(s, col2x(3), 0, 0); // Formula
  if (isinsert) {
    byteat(select, col2x(0), 2, 7);
    strcpy_P(s, pgm_read_word(cmds + select)); strcharat(s, ' ', 0); strcharat(s, '{', 0); strcat(s, " }");
    printsat(s, col2x(6), 2, 7); // Selected command
    meter(select, maxcmd);
  }
  else printmenu(MINSDEL);
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// R A X - RAX core

static boolean issave = false, isload = false;

#define BIGNUMBER 1e7 // Limits between float and sci number format
#define SMALLNUMBER 0.001F

static void navright(void) { // Navigate right and calculate startcell
  if (selcell < RCELLS - 1) selcell++;
  byte c = n2col(selcell);
  if (c == 1) { // Next line
    startcol = 1;
    if (n2row(selcell) >= startrow + DR) startrow++; // End of screen
  }
  else if (c >= startcol + DC) startcol++; // Next col
}
static void navleft(void) { // Navigate left and calculate startcell
  if (selcell) selcell--;
  byte c = n2col(selcell);
  if (c == RC) { // Previous line
    startcol = RC - DC + 1;
    if (n2row(selcell) < startrow) startrow--; // Begin of screen
  }
  else if (c < startcol) startcol--; // Previous col
}
static void navdown(void) { // Navigate down
  if (selcell < RCELLS - RC) {
    selcell += RC;
    if (n2row(selcell) >= startrow + DR) startrow++; // End of screen
  }
}
static void navup(void) { // Navigate up
  if (selcell >= RC) {
    selcell -= RC;
    if (n2row(selcell) < startrow) startrow--; // Begin of screen
  }
}

static void save(byte slot) { // Save sheet
  for (byte i = 0; i < RMEMMAX; i++) EEPROM[EEOFFSET + (slot - 1) * RMEMMAX + i] = rmem[i];
}
static void load(byte slot) { // Load sheet
  for (byte i = 0; i < RMEMMAX; i++) rmem[i] = EEPROM[EEOFFSET + (slot - 1) * RMEMMAX + i ];
}

static byte log2p(int8_t l) { // Log to prec digits
  return (max(min(5 - l, 5), 0));
}

static void f2s(char* s, double f) { // Converts float to string
  // dtostre(double val, char* s, unsigned char prec, unsigned char flags)
  // format: -d.pppE-ee   flag-bits: 1_spc_for_+   2_+_for_+   4_E_instead of_e
  // dtostrf(double val, unsigned char min_width, unsigned char prec, char* s)
  if (f == 0.0F) { // Zero
    s[0] = zerochar; s[1] = '\0';
  }
  else { // Nonzero
    byte neg = 0;
    if (f < 0.0F) { // Check negative number
      f = -f; neg = 1;
    }
    if (f >= BIGNUMBER || f < SMALLNUMBER) { // EE-Format
      if (neg) dtostre(-f, s, 1, 2); // Convert
      else { // Convert and delete sign
        dtostre(f, s, 2, 2); strdelpos(s, 0);
      }
      strdelpos(s, 4); // Delete E
    }
    else { // Float-Format
      dtostrf(f, CELLSIZE, log2p(log10(f)) - neg, s);
      if (neg) s[0] = '-'; // Negative number
      s[CELLSIZE] = '\0'; // dtostrf produces longer strings sometimes (ie: 20 200 %)
    }
  }
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// P R I N T I N G - Display

static void printcell(byte cell, byte x, byte r, byte shift) { // Print cell value
  char s[MAXSHORTSTRINGSIZE];
  if (istxtcell(cell)) createtxtstring(s, cell, false); // Text cell
  else f2s(s, rval[cell]); // Numeric value
  printsat(s, x, r, shift);
}

static void printsheet(void) { // Print cells (value, marker, formula)
  for (byte c = startcol; c < startcol + DC; c++) for (byte r = startrow; r < startrow + DR; r++) {
      printcell(colrow2n(c, r), (c - startcol) * 32 + 4, r - startrow + 1, 1); // Val
      if (colrow2n(c, r) == selcell)  printcat('}', (c - startcol) * 32, r - startrow + 1, 1); // Marker
    }
  char s[MAXLONGSTRINGSIZE] = {' '};
  createeditstring(s, false); printsat(s, col2x(3), 0, 0); // Formula
}

static void printselcell(void) { // Print name of selcell
  char s[3]; cell2s(s, selcell); printsat(s, 0, 0, 0);
}

static boolean printscreen(void) { // Print screen due to state
  dbufclr(); // Clear screen buffer

  if (isplot) printplot();
  else if (isasc) printasc(); // Enter ascii
  else if (istxt) { // RAXtext
    printtxt(); printcat('T', col2x(15), 0, 0);
  }
  else if (isedit) { // RAXedit
    if (isfg) printmenu(MREF);
    else {
      printedit();
      printselcell();
      printcell(selcell, col2x(4), 1, 1);
    }
  }
  else { // RAX
    if (isfg == 2) {
      printmenu(MZERO);
    }
    else if (isfg == 1) {
      if (isload || issave) printmenu(M1234);
      else printmenu(MSAVLOAD);
    }
    else {
      printselcell(); printsheet();
      if (isref) printcat('R', col2x(14), 0, 0);
    }
  }

  ddisplay(); // Send screen buffer to display
  return (false); // Determine isprintscreen
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// K E Y   E V A L U A T I O N - Key logic

static void kplot(void) { // Plot
  isplot = false;
}

static void kasc(void) { // Insert ascii character
  ascnav();
  if (key == B_A) { // Select/Quit
    zerochar = EEPROM[EEZERO] = select;
    isasc = iskeyloop = false;
  }
  delayshort(150);
}

static void ktxt(void) { // Edit text cell
  if (isinsert) {
    ascnav();
    if (key == B_A) { // Select/Quit
      if (memlen() < CELLSIZE + 1) memcharat(selcell, select, 1 + editcurpos++);
      isinsert = iskeyloop = false;
    }
    delayshort(150);
  }
  else if (key == B_U) isinsert = true; // Insert
  else if (key == B_D) { // Delete
    if (editcurpos) {
      memdelat(selcell, editcurpos--);
      if (!editcurpos) aligneditcurpos();
    }
  }
  else if (key == B_L) { // Left
    if (editcurpos > 1) editcurpos--;
  }
  else if (key == B_R) aligneditcurpos(); // Right
  else if (key == B_A) { // Quit
    istxt = false; isfg = 0;
  }
}

static void kedit(void) { // Edit cell
  if (isfg) { // # Shifted key
    if (key == B_L) { // Demand reference
      oldstartrow = startrow; oldstartcol = startcol; oldselcell = selcell;
      isref = true; isedit = false;
    }
    isfg = 0;
  }
  else { // # Regular (not shifted) key
    if (isinsert) { // Input command
      iskeyloop = true;
      if (key == B_A) { // Select, quit
        memcharat(selcell, select, editcurpos++); eval(selcell);
        isinsert = iskeyloop = false;
      }
      else if (key == B_L && select) select--; // Previous
      else if (key == B_R && select < maxcmd - 1) select++; // Next
      else if (key == B_U) { // PgUp
        if (select > CMDSTEP) select -= CMDSTEP; else select = 0;
      }
      else if (key == B_D) { // PgDn
        if (select < maxcmd - 1 - CMDSTEP) select += CMDSTEP; else select = maxcmd - 1;
      }
      delayshort(150);
    }
    else { // Main edit menu
      if (key == B_L) { // LEFT
        if (editcurpos == 2 && rmem[rmseek(selcell) + editcurpos - 2] == _REF) {}
        else if (editcurpos > 1 && rmem[rmseek(selcell) + editcurpos - 2] == _REF) editcurpos -= 2;
        else if (editcurpos > 1) editcurpos--;
      }
      else if (key == B_R) { // RIGHT
        if (rmem[rmseek(selcell) + editcurpos] == _REF) editcurpos += 2;
        else if (editcurpos < memlen()) editcurpos++;
      }
      else if (key == B_U) {  // INS
        isinsert = true;
      }
      else if (key == B_D) { // DEL/BSP
        if (editcurpos) {
          if (editcurpos == 2 && rmem[rmseek(selcell) + editcurpos - 2] == _REF) {
            memdelat(selcell, editcurpos - 1); memdelat(selcell, editcurpos - 2);
            if (rmem[rmseek(selcell) + editcurpos - 2] != _REF) editcurpos--;
          }
          else if (editcurpos > 1 && rmem[rmseek(selcell) + editcurpos - 2] == _REF) {
            memdelat(selcell, editcurpos - 1); memdelat(selcell, editcurpos - 2);
            editcurpos--;
          }
          else {
            memdelat(selcell, editcurpos - 1); editcurpos--;
          }
          if (editcurpos == 0) { // Prevent curpos 0
            if (rmem[rmseek(selcell)] != _END) {
              editcurpos++;
              if (rmem[rmseek(selcell)] == _REF) editcurpos++;
            }
          }
        }
        eval(selcell);
      }
      else if (key == B_A) { // Exit edit
        evalall();
        isedit = isplot = false;
        for (byte i = rmseek(selcell); i < rmseek(selcell + 1); i++) if (rmem[i] == RPLOT) isplot = true; // Demand plot
      }
    }
  }
}

static void krax(void) {
  if (isfg == 2) { // Shift G
    if (key == B_L) { // Zero char
      select = FO; isasc = true;
    }
    else if (key == B_R) edittxtcell(); // Edit text cell
    else if (key == B_U) paste(); // Paste cell
    else if (key == B_D) copy(); // Copy cell
    isfg = 0;
  }
  else if (isfg == 1) { // Shift F
    if (issave && isslot(key)) { // Save sheet
      save(b2slot(key));
      issave = false; isfg = 0;
    }
    else if (isload && isslot(key)) { // Load sheet
      load(b2slot(key));
      evalall(); initpos(); isload = false; isfg = 0;
    }
    else if (key == B_U) issave = true; // Set save
    else if (key == B_D) isload = true; // Set load
    else if (key == B_L) { // New sheet
      rinit(); isfg = 0;
    }
    else if (key == B_R) { // Delete cell
      delcell(selcell); evalall(); isfg = 0;
    }
    else if (key == B_A) edittxtcell(); // Edit text cell
  }
  else { // Nonshifted
    if (key == B_A) {
      if (isref) { // Insert Reference
        memcharat(oldselcell, _REF, editcurpos++); memcharat(oldselcell, selcell, editcurpos++);
        selcell = oldselcell; startrow = oldstartrow; startcol = oldstartcol;
        eval(selcell);
        isedit = true; isref = false;
      }
      else if (istxtcell(selcell)) { // Edit text cell
        istxt = true; select = FO; editcurpos = memlen() - 1;
      }
      else { // Edit numeric cell
        isedit = true; seteditcurpos();
      }
    }
    else if (key == B_U) navup();
    else if (key == B_R) navright();
    else if (key == B_D) navdown();
    else if (key == B_L) navleft();
  }
}


//--v----1----v----2----v----3----v----4----v----5----v----6----v----7----v----8
// S E T U P  &  L O O P

void setup() {
  bootpins(); // System boot procedure
  dinit();
  bootpowersaving();
  setframerate(FRAMERATE);
  flashmode(); // Secure waiting for flashing new software (UP+on)
  ledsoff();
  dcontrast(EEPROM.read(EECONTRAST)); // Set contrast
  rinit(); // Init RAX
}

void loop() {
  if (isprintscreen) isprintscreen = printscreen(); // Print screen
  if (!(nextFrame())) return; // Pause render (idle) until it's time for the next frame
  key = buttonscan(); // Get key

  if (key != oldkey || iskeyloop) { // New key entered
    oldkey = key; // Save as old key
    shortcuts(); // Check shortcuts

    if (key) { // Regular/valid key pressed
      if (key == B_B) { // Shift
        if (isasc || istxt || isinsert) isfg = 0; // No shift
        else if (isedit) isfg = _inc(isfg, 2); // One shift
        else isfg = _inc(isfg, 3); // Two shifts
        if (isinsert) isinsert = iskeyloop = false; // Quit ins
        issave = isload = false;
      }
      else if (isplot) kplot();
      else if (isasc) kasc();
      else if (istxt) ktxt();
      else if (isedit) kedit();
      else krax();
      isprintscreen = true;
    } // End of evaluating key
  }
}
