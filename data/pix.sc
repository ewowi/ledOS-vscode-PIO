external void show();
external CRGB *leds;
external void clear();
void main()
{
    clear();
    while (2>1) {
    for(int i=0;i<48;i++)
    {
        for (int j=0;j<i+1;j++)
        {
            leds[j+i*256]=CRGB(255,0,0);
        }
    }
    show();
    }
}
