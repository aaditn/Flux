// LED
//#define DIM_LED
#define RedLEDPin 15
#define GreenLEDPin 14
#define BlueLEDPin 13

namespace LED {
  bool enabled=false;

  struct Color { // Describes a color with RGB values
    uint8_t R;
    uint8_t G;
    uint8_t B;
  };

  // Predefined colors
  constexpr Color red={255, 0, 0};
  constexpr Color orange={255, 20, 0};
  constexpr Color yellow={255, 100, 0};
  constexpr Color green={0, 255, 0};
  constexpr Color cyan={0, 255, 255};
  constexpr Color blue={0, 0, 255};
  constexpr Color purple{255, 0, 255};
  constexpr Color white={255, 240, 200};
  constexpr Color offColor={0, 0, 0};

  Color currentColor=offColor; // Last color used to call setColor() (zeroed when off() is called)

  void LED::disable() {
    off();
    enabled=false;
  }

  void LED::enable() {
    enabled=true;
  }

  void LED::setColor(const Color color) {
    if (!enabled) return;
    if (color.R==currentColor.R && color.G==currentColor.G && color.B==currentColor.B) return; // Nothing to do
    
    #ifndef DIM_LED
      analogWrite(RedLEDPin, color.R*128);
      analogWrite(GreenLEDPin, color.G*128);
      analogWrite(BlueLEDPin, color.B*128);
    #else
      analogWrite(RedLEDPin, color.R*2);
      analogWrite(GreenLEDPin, color.G*2);
      analogWrite(BlueLEDPin, color.B*2);
    #endif

    currentColor=color;

    // Log info to flash
    Flash::logTime(Flash::dataFile);
    Flash::logSpecifier(LEDSpecifier, Flash::dataFile);
    Flash::log(color.R, Flash::dataFile);
    Flash::log(color.G, Flash::dataFile);
    Flash::log(color.B, Flash::dataFile);
  }

  void LED::off() {
    setColor(offColor);
  }

  void init() {
    analogWriteResolution(15);
    pinMode(RedLEDPin, OUTPUT);
    pinMode(GreenLEDPin, OUTPUT);
    pinMode(BlueLEDPin, OUTPUT);
    LED::off();
  }
}

// Mic
#define PDMClockPin 21
#define PDMDataPin 8

void setup() {
  LED::init();
  pinMode(PDMClockPin, OUTPUT);
  pinMode(PDMDataPin, INPUT);
}

void loop() {
  LED::setColor(red);
  delay(250);
  LED::setColor(orange);
  delay(250);
  LED::setColor(yellow);
  delay(250);
  LED::setColor(green);
  delay(250);
  LED::setColor(cyan);
  delay(250);
  LED::setColor(blue);
  delay(250);
  LED::setColor(purple);
  delay(250);
  LED::setColor(white);
  delay(250);
  off();
}
