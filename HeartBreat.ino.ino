int UpperThreshold = 518;
int LowerThreshold = 490;
    int reading = 0;
    float BPM = 0.0;
    bool IgnoreReading = false;
    bool FirstPulseDetected = false;
    unsigned long FirstPulseTime = 0;
    unsigned long SecondPulseTime = 0;
    unsigned long PulseInterval = 0;
    int old_value=0;
    int currentvalue,timestart,timecount,bpm;
    int i=0,j=0;
    int timing=millis();
    char bpm_val_str[20]="nil";
    void setup()
	{
      Serial.begin(9600);
    }
	void loop()
	{
      j++;
      //analogReadResolution(8);
      reading = analogRead(A0);
      //currentvalue=reading-old_value;
      currentvalue=reading;
      old_value=reading;
      if (currentvalue>512 && timestart==0)
      {
      timestart=1;
      timecount=millis();
      }
      if(currentvalue<500 && timestart==1)
      {
      timestart=2;  
      }
      if (currentvalue>512 && timestart==2)
      {
        bpm=millis()-timecount;
        timestart=0;      
	  }

      float bpm1,a1,a2;
      
      a1=bpm;
      a2=reading/1.0;
      bpm1=a1*80.0/1003.0;
      if(bpm1>50 && bpm1<110)
      {
      dtostrf(bpm1, 4, 2,bpm_val_str);
      }
      if(Serial.available() > 0)
      {
      int  inChar = Serial.read();
      if (inChar==49)
      {
        char buff[20];
     
       sprintf (buff,  "%i,%s%c",inChar,bpm_val_str,0);
     
      Serial.print(buff);
          
      }
      }
     
      if(j==100) j=0;
      
      delay(10);
         }
