#ifdef MY__DEBUG 
BLYNK_WRITE(V2)
{
//counter =  param.asInt();//38 желтый 

//r=  param.asInt();
r = param.asInt();
   // Red (0..) "HUE_RED"
    //Orange (32..) "HUE_ORANGE"
   // Yellow (64..) "HUE_YELLOW"
   // Green (96..) "HUE_GREEN"
   // Aqua (128..) "HUE_AQUA"
   // Blue (160..) "HUE_BLUE"
   // Purple (192..) "HUE_PURPLE"
   // Pink(224..) «HUE_PINK»
 

}

BLYNK_WRITE(V3)
{
//saturation =  param.asInt();//38 желтый 

//g=  param.asInt();
g = param.asInt();
}
BLYNK_WRITE(V4)
{
//saturation =  param.asInt();//38 желтый 

//b=  param.asInt();
b = param.asInt();

}
#endif





/*
BLYNK_WRITE(V5)
{

int R = param[0].asInt();
int G = param[1].asInt();
int B = param[2].asInt();
terminal.println(R);
terminal.println(G);
terminal.println(B);
for(int i=0;i<NUMPIXELS;i++){

pixels.setPixelColor(i, pixels.Color(R,G,B));

pixels.show();
}
}*/
