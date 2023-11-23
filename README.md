# RAXBOY - A Powerful RPN Spreadsheet for the Arduboy

# ... COMING SOON ...


This software is covered by the 3-clause BSD license.
(c)2023 by zooxo/deetee

![raxboy](https://github.com/zooxo/raxboy/assets/16148023/d4ee09a1-2f92-4da1-921e-e43001ac3185)

See a short video of RAXBOY:  
Version 1.0: https://youtu.be/


```

  ____________________

    PREAMBLE
  ____________________

  It was quite a challenge to program a spreadheet application for an Arduino.
  On one hand there is a flash RAM restriction of 28 kilobytes - on the other
  hand the used Arduboy platform has six keys only.
  But finally RAXBOY became a powerful credit card sized spreadheet application
  that offers even a solver or a function graph plotter.

  Have fun!
  deetee


  ____________________

    NAVIGATION, MENUS
  ____________________

  After starting RAXBOY (RACKS + ARDUBOY) you will find yourself in the
  navigation mode. Select the desired cell with the navigation keys. When
  pressing SHIFT (button A) you enter the first navigation menu:
    NEW    Start a new spreadsheet (the recent one will be deletet)
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

  When selecting a command all commands are sorted into different groups:

  |_NUMERIC_|_STACK_|__BASIC__|_CONDITIONS_|_BAT_|_ADVANCED_|_PHYSICAL_CONST_|
  0        12      16        27           30    31         79              115
  0-9.       ENTER   + - * /   < = >        Vcc   10PWR ABS  c
  CHS        BSP     1/X PWR                      ACOS ...   ...
  EE         SWAP    SQRT SQR                     TAN TANH   C2
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
    Conversions (ie KM2MI) work in both directions (both conversions are pushed
    to the stack). For example to convert 1 km to miles enter 1 and KM2MI which
    shows 0.62137 miles. Enter BSP or SWAP to display 1.60934 km (= 1 mile).
    DEQ
      Differential equation (REF to function, x, y, x-target).
      DEQ solves a differential equation y'=f(x,y) with given start value y(x0)
      due to Runge-Kutta with 4th order (RK4). DEQ calculates the solution
      function (y value for the targeted x).
    Condition < = >
      Compares two stack values and returns 1 (true) or 0 (false)
    IF ELSE THEN
      Due to FORTH a condition consists of:
      <condition> IF <true-branch> ELSE <false-branch> THEN
      Please note that ELSE can be omitted and that there is no nesting.
    INTEGRAL, PLOT, SLOPE, SOLVER, XTREMA
      These functions evaluate a cell containing a function (REF to function)
      which depends itself of a referenced cell (REF to x). Additionally PLOT
      and INTEGRAL demand two range x-values (REF to a and b).
      Please note that PLOT plots a function graph when leaving the edit mode.
    PC
      Calculates the permuation (nPr) and combination (nCr)
    PV
      PV calculates a present value for a given interest rate and time period.
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
    4x6    Size of a spreadsheet (4 columns, r rows) ... 24 cells
    7      Digits to represent a number or text
    10     Average number of commands/characters per cell (in bytes)
    4      Slots to store spreadsheets to EEPROM
    8      Stack size
    100    Maximal solver iterations
    100    Number of calculation stripes (integrate, differential equation)
    64x32  Plot resolution



  ____________________

    SPECIAL KEYS
  ____________________

  Set the brightness (6 levels) by pressing (and holding) the left cursor key
  and pressing the upper (brighter) or lower cursor key (darker).
  Goto sleep mode with pressing (and holding) the left cursor key and pressing
  the right kursor key. To wake up the IVBOY press key A.


  ____________________

    SCHEMATICS
  ____________________

   ____________________________________________________________
  |                                                            |
  |                     Arduino Pro Micro                      |
  |__________15__16___6___4_____________A2__A0__A1___A3___7_8__|
              |   |   |   |              |   |   |    |   | |

   __GND_VCC__|___|___|___|_GND__    ____|___|___|____|___|_|__
  |  GND VCC SCL SDA RES DC CS   |  |  LEFT UP DOWN RIGHT A B  |
  |        OLED Display          |  |         BUTTONS          |
  |________128x64 SSD 1306_______|  |__________________________|




```
