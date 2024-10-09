//Original Code from Zranger1 adapted
//https://github.com/zranger1/PixelblazePatterns/blob/master/2D_and_3D/mandelbrot2D.js
// Reference:
// https://mathworld.wolfram.com/MandelbrotSet.html
// Version  Author        Date        
//  1.0.0    JEM(ZRanger1) 12/08/2020  

//save_reg
//safe_mode
external void show();
external CRGB *leds;
external CRGB hsv(int h, int s, int v);
external void dp(float h);
external void display(int h);
external void resetStat();
external void clear();
external void millis();
external void time(float j);
external void triangle(float j);
define maxIterations 15
define width 128
define height 96
define panel_width 128
define scale 0.5
    
    float cR; // = -0.94299;
float cI;     // = 0.3162;


float cX;
float cY;
float fX;
float fY;

// timers used to animate movement and color
float t1;
float t2;
int iter;
// UI

float fmod(float a, float b)
{

  int tmp = (float)(a / b);
    //float res=a-b*tmp;
//  return res;
    return a-b*tmp;

}

float triangle(float h)
 {
 
  float res=  fabs(fmod(2 * h, 2.0) - 1.0);
//dp(res);
  return 1-res;
}



float time(float par1) 
{
  float myVal = millis();
//dp(myVal);
  myVal = myVal / 10000/ par1; //65535
//dp(myVal);
  myVal = fmod(myVal, 1.0);     
//dp(myVal);
  return myVal;
}

void beforeRender()
{
//  float jj=triangle(time(0.2));
//     dp(2.4*(jj-0.5));
//§§float g=2.4;
 //§ t1 = g*(triangle(time(0.2)) - 0.5);
//dp(t1);
  t1 = (triangle(time(0.2)) - 0.5)*2.4 ;
//dp(t1);
  t2 = time(0.05);

  cX = cR + t1;
  cY = cI + (t1 / 2.5);
  //  dp(cY);
// dp(cX);
//  dp(t1);
//  display(11111);
 // dp(t2);
}


void render2D(int x1, int y1)
{
  float x = (x1/width-0.5)/scale;
  float y = (y1/height-0.5)/scale; 
  int iter;
  for (iter = 0; iter < maxIterations; iter++)
  {
    float x2 = x ^ 2;
    float y2 = y ^ 2;
    if ((int)(x2 + y2) >= 4)
    {
      break; 
    }
    fX = x2 - y2 + cX;
    fY = 2 * x * y + cY;
    x = fX;
    y = fY;
  }
 

  if (iter < maxIterations)
  {
    leds[panel_width * y1 + x1] = hsv((float)((t2 + (iter / maxIterations)) * 255), 255, 255);
  }
  else
  {
    leds[panel_width * y1 + x1] = CRGB(0, 0, 0);
  } 
}

void main()
{
clear();
resetStat();
  cR = -0.94299;
  cI = 0.3162;
  int h = 1 ;
  while (h > 0)
  {
    beforeRender();
    for (int i = 0; i < width; i++)
    {
      for (int j = 0; j < height; j++)
      {
        render2D(i, j);
      }
    }
    show();
  }
}
