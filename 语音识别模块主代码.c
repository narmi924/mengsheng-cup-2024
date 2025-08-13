#include "asr.h"

extern "C"{ void * __dso_handle = 0 ;}

#include "setup.h"
#include "myLib/asr_event.h"
#include "HardwareSerial.h"

uint32_t snid;

void ASR_CODE();

/*描述该功能...*/
void ASR_CODE(){
  switch (snid) {
    case 1:
     digitalWrite(4,0);
     Serial.print("11");
     break;
    case 2:
     digitalWrite(4,1);
     Serial.print("22");
     break;
    case 3:
     digitalWrite(2,0);
     Serial.print("33");
     break;
    case 4:
     digitalWrite(2,1);
     Serial.print("44");
     break;
  }
}

void hardware_init(){
  setPinFun(13,SECOND_FUNCTION);
  setPinFun(14,SECOND_FUNCTION);
  Serial.begin(9600);
  vTaskDelete(NULL);
}

void setup()
{
  set_wakeup_forever();

  //{ID:1,keyword:"命令词",ASR:"打开灯光",ASRTO:""}
  //{ID:2,keyword:"命令词",ASR:"关闭灯光",ASRTO:""}
  //{ID:3,keyword:"命令词",ASR:"打开空调",ASRTO:""}
  //{ID:4,keyword:"命令词",ASR:"关闭空调",ASRTO:""}

  setPinFun(4,FIRST_FUNCTION);
  pinMode(4,output);
  setPinFun(4,FIRST_FUNCTION);
}