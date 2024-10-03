import rand
external CRGB *leds;
//external CRGB *ope;

external void clear();
external void show();
external void display(int h);
external CRGB hsv(uint8_t h, uint8_t s, uint8_t v);
external void resetStat();
//external CRGB hsv2(uint8_t h,uint8_t s,uint8_t v);
//external void __feed();
define width 128
define height 96
define panel_width 128
char copy[13000];
uint8_t line1[width];
uint8_t linec[width];
int size;
//int res;
CRGB palette[18];
int kl[18];


void create_leds(int o)
{
//hsv(o,255,255);
//CRGB color=hsv(o,255,255);

//uint8_t *line1=_line1;
//uint8_t *linec=_linec;
//ff
   for (int j = 1; j < height - 1; j++)
   {
      for (int h = 0; h < width; h++)
      {

         //int tmp = linec[h];
         line1[h] = linec[h];

         //tmp = copy[(j)*width + h];
         //linec[h] = tmp;
         linec[h] = copy[(j)*width + h];

      }
      for (int i = 1; i < width - 1; i++)
      {
         //int res=count_n(i, j);
   int res = 0;

   res = linec[i - 1] + linec[i + 1];
   res = res + line1[i - 1] + line1[i + 1] + line1[i];
   int pos = (j + 1) * width + i;

   res = res + copy[pos - 1] + copy[pos + 1] + copy[pos];

         int po = 0;
         int gh = width * j + i;
         int l = copy[gh];
         int gh2 = j * panel_width + i;
if(res==3)
{
int hqs=0;
po=1;
}
else
{
   
         if (l == 1)
         {
            
            if (res == 2)
            {
               po = 1;            
         }
          }
}
         if (po == 1)
         {
            leds[gh2] = hsv(o,255,255);
            copy[gh] = 1;
         }
         else
         {
            leds[gh2] = CRGB(0, 0, 0);
            copy[gh] = 0;
         }
      }
   }
 //  display(23);
}


int main()
{
resetStat();

  
   
   for (int h = 0; h < height; h++)
   {
      int pos = h * width + width / 2-20;
      copy[pos] = 1;
      copy[pos+20]=1;
      copy[pos+40]=1;
  }

   clear();
   show();
   for (int i = 0; i < 501; i++)
   {
   //CRGB color=hsv(i,255,255);
      create_leds(i);
      show();
//      __feed();
   }
}
