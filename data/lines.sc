external CRGB *leds;

external void clear();
external void show();
external int millis();
external void dp(float h);

void main()
{
    while (2>1) {
        clear();
        int row = (int)((millis()/50) % 96 );
        for (int col=0;col<128;col++)
        {
            leds[col+row*128]=CRGB(255,0,0);
        }
        int col = (int)((millis()/50) % 128);
        for(int row=0;row<96;row++)
        {
            leds[col+row*128]=CRGB(255,0,0);
        }
        show();
    }
}
