#define NUM_LEDS_PER_STRIP 256
#ifdef GO_VIRTUAL
  #define CORE_DEBUG_LEVEL 1 //used in I2SClocklessVirtualLedDriver.h
  #define DELTA_OFFSET_LATCH 0

  #define USE_FASTLED
  #define __NB_DMA_BUFFER 10
  #define BRIGHTNESS_BIT 5
  #define NBIS2SERIALPINS 6
  #define LED_WIDTH 128
  #define LED_HEIGHT 96
  #include "esp_heap_caps.h"
  #define I2S_MAPPING_MODE (I2S_MAPPING_MODE_OPTION_MAPPING_IN_MEMORY)

  #define ICVD_LOGD(tag, format, ...) Serial.printf(format, ##__VA_ARGS__)
  #define ICVD_LOGE(tag, format, ...) Serial.printf(format, ##__VA_ARGS__)
  #define ICVD_LOGV(tag, format, ...) Serial.printf(format, ##__VA_ARGS__)
  #define ICVD_LOGI(tag, format, ...) Serial.printf(format, ##__VA_ARGS__)


  #include "I2SClocklessVirtualLedDriver.h"
  #include "math.h"
  #define NUM_LEDS (LED_HEIGHT * LED_WIDTH)
  #define LATCH_PIN 27
  #define CLOCK_PIN 26

  uint16_t mapfunction(uint16_t pos)
  {
    int panelnumber = pos / 256;
    int datainpanel = pos % 256;
    int Xp = 7 - panelnumber % 8;

    Xp=(Xp+1)%8; //fix for ewowi panels

    int yp = panelnumber / 8;
    int X = Xp; //panel on the x axis
    int Y = yp; //panel on the y axis

    int y = datainpanel % 16;
    int x = datainpanel / 16;

    if (x % 2 == 0) //serpentine
    {
      Y = Y * 16 + y;
      X = X * 16 + x;
    }
    else
    {
      Y = Y * 16 + 16 -y-1;
      X = X * 16 + x;
    }

    // return (95-Y) * 16 * 8 + (127-X);
    return Y * 128 + X;
  }

  Pixel leds[LED_HEIGHT * LED_WIDTH];
  int Pins[6] = { 14, 12, 13, 25, 33, 32 };


  I2SClocklessVirtualLedDriver driver;
#else
  #define NUM_STRIPS 1
  #define NUM_LEDS (NUM_LEDS_PER_STRIP * NUM_STRIPS)

  #include "FastLED.h"
  #include "I2SClocklessLedDriver.h"

  CRGB leds[NUM_STRIPS*NUM_LEDS_PER_STRIP];
  int pins[16]={16};
  I2SClocklessLedDriver driver;
#endif

#include "ledOS.h"
#include "ESPLiveScript.h"


// static void showError(int line,uint32_t size, uint32_t got)
// {
//   LedOS.pushToConsole(string_format ("Overflow error line %d max size: %d got %d",line,size,got),true);
// }
static void displayfloat(float j)
{
 LedOS.pushToConsole(string_format ("display float %f",j),true);
}
static void clearleds()
{ 
  memset(leds,0,NUM_LEDS*3);
}

long time1;
static float _min=9999;
static float _max=0;
static uint32_t _nb_stat=0;
static float _totfps;

static void show ()
 {
    // SKIPPED: check nargs (must be 3 because arg[0] is self)
   long time2=ESP.getCycleCount();
 driver.showPixels(WAIT);
  float k=(float)(time2-time1)/240000000;
  float fps=1/k;
  _nb_stat++;
  if(_min>fps && fps > 10 && _nb_stat>10)
   _min=fps;
   if (_max<fps  && fps<200 && _nb_stat>10)
   _max=fps;
   if(_nb_stat>10)
   _totfps+=fps;
  LedOS.pushToConsole(string_format ("current fps:%.2f  average:%.2f min:%.2f max:%.2f",fps,_totfps/(_nb_stat-10),_min,_max));
  time1=time2;
    // SKIPPED: check that both v1 and v2 are int numbers
   // RETURN_VALUE(VALUE_FROM_INT(0), rindex);
}

static CRGB POSV(uint8_t h,uint8_t s, uint8_t v)
{
  return CHSV(h,s,v);
}

static void resetShowStats()
{
  float min=999;
  float max=0;
  _nb_stat=0;
  _totfps=0;
}

static void dispshit(int g)
{
  LedOS.pushToConsole(string_format ("coming from assembly int %x %d",g,g),true);
}

static float _sin(float j)
{
  return sin(j);
}
static void __print(char *s)
{
  LedOS.pushToConsole(string_format("from assembly :%s\r\n",s),true);
}
static void pre()
{
  //Serial.printf("ii\r\n");
  driver.__enableDriver=false;
  while(driver.isDisplaying){};
//delay(20);
}
static void post()
{
//delay(10);
//Serial.printf("iiend\r\n");
 driver.__enableDriver=true;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {};
  #ifdef GO_VIRTUAL
    driver.initled(leds, Pins, CLOCK_PIN, LATCH_PIN);
    driver.setMapLed(&mapfunction);
  #else
    driver.initled((uint8_t*)leds,pins,NUM_STRIPS,NUM_LEDS_PER_STRIP,ORDER_GRB);
  #endif
    driver.setBrightness(10);
LedOS.current_hightlight=&highLighting[0];
 addExternal("leds", externalType::value, (void *)leds);
  addExternal("show", externalType::function, (void *)&show);
   addExternal("display", externalType::function, (void *)&dispshit);
  addExternal("hsv",externalType::function,(void*)POSV);
  addExternal("clear",externalType::function,(void*)clearleds);
         addExternal("dp",externalType::function,(void*)displayfloat);
         addExternal("sin",externalType::function,(void*)_sin);
          addExternal("resetStat",externalType::function,(void*)&resetShowStats);
          addExternal("error",externalType::function,(void*)&showError);
          addExternal("print",externalType::function,(void*)__print);
              addExternal("millis",externalType::function, (void *)millis);

                  // vector<string> j;
//parseasm(&LedOS,j);
//  SCExecutable.setPrekill(pre,post);
runningPrograms.setPrekill(pre, post);
runningPrograms.setFunctionToSync(show);
LedOS.script.clear();
}
// int k=4;
// int h=4;
void loop() {
  // put your main code here, to run repeatedly:
LedOS.run();
}
