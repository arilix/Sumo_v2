#include <Ps3Controller.h>

int ena_kanan=26;
int ena_kiri=33;
int RPWM_kanan=13;
int LPWM_kanan=15;
int RPWM_kiri=5;
int LPWM_kiri=25;
int pwm_ki, pwm_ka;
const int frequency = 30000; //1000
const int pwm_channel = 0;
const int pwm_channel1 = 1;
const int pwm_channel2 = 2;
const int pwm_channel3 = 3;
const int resolution = 8;

void kanan(){
  ledcWrite(pwm_channel,pwm_ki);
  ledcWrite(pwm_channel1,0);
  ledcWrite(pwm_channel2,pwm_ka);
  ledcWrite(pwm_channel3,0);
}
void kiri(){
  ledcWrite(pwm_channel,0);
  ledcWrite(pwm_channel1,pwm_ki);
  ledcWrite(pwm_channel2,0);
  ledcWrite(pwm_channel3,pwm_ka);
}
void maju(){
  ledcWrite(pwm_channel,0);
  ledcWrite(pwm_channel1,pwm_ki);
  ledcWrite(pwm_channel2,pwm_ka);
  ledcWrite(pwm_channel3,0);
}
void mundur(){
  ledcWrite(pwm_channel,pwm_ki);
  ledcWrite(pwm_channel1,0);
  ledcWrite(pwm_channel2,0);
  ledcWrite(pwm_channel3,pwm_ka);
}
void stopped(){
  ledcWrite(pwm_channel,0);
  ledcWrite(pwm_channel1,0);
  ledcWrite(pwm_channel2,0);
  ledcWrite(pwm_channel3,0);
}

void setup(){
  Serial.begin(9600);
  Ps3.begin("55:aa:8b:bc:92:81");
  ledcSetup(pwm_channel, frequency, resolution);
  ledcSetup(pwm_channel1, frequency, resolution);
  ledcSetup(pwm_channel2, frequency, resolution);
  ledcSetup(pwm_channel3, frequency, resolution);
  ledcAttachPin(RPWM_kiri, pwm_channel);
  ledcAttachPin(LPWM_kiri, pwm_channel1);
  ledcAttachPin(RPWM_kanan, pwm_channel2);
  ledcAttachPin(LPWM_kanan, pwm_channel3);
  pinMode(RPWM_kanan,OUTPUT);
  pinMode(LPWM_kanan,OUTPUT);
  pinMode(RPWM_kiri,OUTPUT);
  pinMode(LPWM_kiri,OUTPUT); 
  pinMode(ena_kiri,OUTPUT); 
  pinMode(ena_kanan,OUTPUT); 
}

void loop(){
  if(Ps3.isConnected()){
    digitalWrite(ena_kanan,HIGH);
    digitalWrite(ena_kiri,HIGH);
    if((Ps3.data.button.up) && (Ps3.data.button.l1)){
      pwm_ki=255; pwm_ka=255;
      maju();
      Serial.println("maju");
    }
    else if(( Ps3.data.button.left) && (Ps3.data.button.l1)){
      pwm_ki=255; pwm_ka=255;
      kiri();
      Serial.println("kiri");
    }
    else if(( Ps3.data.button.right) && (Ps3.data.button.l1)){
      pwm_ki=255; pwm_ka=255;
      kanan();
      Serial.println("kanan");
    }
    else if(( Ps3.data.button.down) && (Ps3.data.button.l1)){
      pwm_ki=255; pwm_ka=255;
      mundur();
      Serial.println("mundur");
    } 
    else if(Ps3.data.button.up && Ps3.data.button.left){
      pwm_ki=pwm_ki-5; pwm_ka=120;
      maju();
      //Serial.println("maju");
    }
    else if(Ps3.data.button.up && Ps3.data.button.right){
      pwm_ki=120; pwm_ka=pwm_ka-5;
      maju();
      //Serial.println("maju");
    }
    else if(Ps3.data.button.up){
      pwm_ki=160; pwm_ka=160;
      maju();
      //Serial.println("maju");
    }
    else if(Ps3.data.button.left){
      pwm_ki=140; pwm_ka=140;
      kiri();
      //Serial.println("kiri");
    }
    else if(Ps3.data.button.right){
      pwm_ki=140; pwm_ka=140;
      kanan();
      //Serial.println("kanan");
    }
    else if(Ps3.data.button.down){
      pwm_ki=140; pwm_ka=140;
      mundur();
      //Serial.println("mundur");
    }    
    else{
      stopped();
      Serial.println("stop");
    }
  }
}
