import rand
external CRGB *leds;
external void show();
external void clear();
external CRGB hsv(int h, int s, int v);
external float sin(float angle);
external void display(int g);
external void resetStat();
define nb_balls 110
define rmax 10
define rmin 8
define width 128
define height 96
define panel_width 128 

float vx[nb_balls];
float vy[nb_balls];
float xc[nb_balls];
float yc[nb_balls];
float r[nb_balls];
int color[nb_balls];
//CRGB cc;

void drawBall(float xc, float yc, float r, int c)
{
   int startx = (float)(xc - r);
   int r2 =(float) (r * r);
   float r4=r*r*r*r;
   // int endx=(float)(xc+r);
   int starty = (float)(yc - r);
   // int endy=(float)(yc+r);
   int _xc=xc;
   int _yc=yc;
   CRGB *_leds=leds;
   for (int i = startx; i <= _xc; i++)
   {
      for (int j = starty; j <= _yc; j++)
      {
         int v;

         int distance = (float)((i - xc) * (i - xc) + (j - yc) * (j - yc));
  
         if (distance <= r2)
         {
            v = (float)(255 * (1 - distance * distance / (r4)));
            CRGB cc=hsv(c,255,v);
            _leds[i + j * panel_width] = cc;
            _leds[(int)(2 * xc - i) + j * panel_width] = cc;
            _leds[(int)(2 * xc - i) + (int)(2 * yc - j) * panel_width] = cc;
            _leds[i + (int)(2 * yc - j) * panel_width] = cc;
         }
      }
   }
}

void updateBall(int index)
{
///   float *__r=r;
 //  float £*__xc=xc;
  // float *__yc=yc;
 //  float *__vx=vx;
 //  float *__vy=vy;
   
   float _r =r[index];
   float _xc = xc[index];
   float _yc = yc[index];
   float _vx = vx[index];
   float _vy = vy[index];

   _xc = _xc + _vx;
   _yc = _yc + _vy;
   if ((int)(_xc) >= (int)(width - _r - 1))
   {
      _xc =width - _r - 1;
      _vx = -_vx;
   }
   if ((int)(_xc) < (int)(_r + 1))
   {
      _xc=_r + 1;
      _vx = -_vx;
   }
   if ((int)(_yc) >= (int)(height - _r - 1))
   {
      _yc=height - _r - 1;
      _vy = -_vy;
   }
   if ((int)(_yc) < (int)(_r + 1))
   {
      _yc = _r + 1;
      _vy = -_vy;
   }

   xc[index] = _xc;
   yc[index] = _yc;
   vx[index] = _vx;
   vy[index] = _vy;
   int _color = color[index];
   drawBall(_xc, _yc, _r, _color);
}

void main()
{
resetStat();
//cc=CRGB(255,0,0);
for(int i=0;i<nb_balls;i++)
{
   vx[i] = rand(280)/255+0.7;
   vy[i] = rand(280)/255+0.5;
   r[i] = (rmax-rmin)*(rand(280)/180) +rmin;
   xc[i] = width/2*(rand(280)/255+0.3)+15;
   yc[i] = height/2*(rand(280)/255+0.3)+15;
   
   color[i] = rand(255);
}  



   
   uint32_t h = 1;

  
   while (h > 0)
   {
      //clear();
     for(int i=0;i<width;i++)
     {
        for(int j=0;j<height;j++)
        {
           leds[i+panel_width*j]=hsv(i+h+j,255,180);
        }
     }
      for (int i = 0; i < nb_balls; i++)
      {
         updateBall(i);
        // drawBall(1,1,1,CRGB(255,255,255));
      }

      //}
      // }
      show();
   }
}
