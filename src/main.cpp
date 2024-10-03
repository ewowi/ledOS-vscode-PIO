#define NUM_LEDS_PER_STRIP 256
#define NUM_STRIPS 1
#define NUM_LEDS (NUM_LEDS_PER_STRIP * NUM_STRIPS)

#include "FastLED.h"
#include "I2SClocklessLedDriver.h"
#include "ledOS.h"
#include "newParser.h"

CRGB leds[NUMSTRIPS*NUM_LEDS_PER_STRIP];
int pins[16]={16};
I2SClocklessLedDriver driver;

static void showError(int line,uint32_t size, uint32_t got)
{
  LedOS.pushToConsole(string_format ("Overflow error line %d max size: %d got %d",line,size,got),true);
}
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
      driver.initled((uint8_t*)leds,pins,NUMSTRIPS,NUM_LEDS_PER_STRIP,ORDER_GRB);
    driver.setBrightness(30);
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
                  vector<string> j;
//parseasm(&LedOS,j);
 SCExecutable.setPrekill(pre,post);
LedOS.script.clear();
}
int k=4;
int h=4;
void loop() {
  // put your main code here, to run repeatedly:
LedOS.run();
}
