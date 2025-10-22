#include <Ps3Controller.h>

// ========== KONFIGURASI PIN (Menggunakan pin dari sumo versi 1.txt) ==========
int ena_kanan = 12;
int ena_kiri = 14;
int RPWM_kanan = 13;
int LPWM_kanan = 15;
int RPWM_kiri = 5;
int LPWM_kiri = 25;
int pwm_ki, pwm_ka;

const int frequency = 30000;
const int pwm_channel = 0;
const int pwm_channel1 = 1;
const int pwm_channel2 = 2;
const int pwm_channel3 = 3;
const int resolution = 8;

// ========== FUNGSI GERAKAN (Logika disesuaikan dengan soccer fix.txt) ==========
void kanan() {
  ledcWrite(pwm_channel, pwm_ki);
  ledcWrite(pwm_channel1, 0);
  ledcWrite(pwm_channel2, pwm_ka);
  ledcWrite(pwm_channel3, 0);
}

void kiri() {
  ledcWrite(pwm_channel, 0);
  ledcWrite(pwm_channel1, pwm_ki);
  ledcWrite(pwm_channel2, 0);
  ledcWrite(pwm_channel3, pwm_ka);
}

void maju() {
  ledcWrite(pwm_channel, 0);
  ledcWrite(pwm_channel1, pwm_ki);
  ledcWrite(pwm_channel2, pwm_ka);
  ledcWrite(pwm_channel3, 0);
}

void mundur() {
  ledcWrite(pwm_channel, pwm_ki);
  ledcWrite(pwm_channel1, 0);
  ledcWrite(pwm_channel2, 0);
  ledcWrite(pwm_channel3, pwm_ka);
}

// Fungsi gerakan serong (Logika baru dari soccer fix.txt)
void maju_kiri() {
  ledcWrite(pwm_channel, 0);
  ledcWrite(pwm_channel1, pwm_ki / 2);
  ledcWrite(pwm_channel2, pwm_ka);
  ledcWrite(pwm_channel3, 0);
}

void maju_kanan() {
  ledcWrite(pwm_channel, 0);
  ledcWrite(pwm_channel1, pwm_ki);
  ledcWrite(pwm_channel2, pwm_ka / 2);
  ledcWrite(pwm_channel3, 0);
}

void mundur_kiri() {
  ledcWrite(pwm_channel, pwm_ki);
  ledcWrite(pwm_channel1, 0);
  ledcWrite(pwm_channel2, 0);
  ledcWrite(pwm_channel3, pwm_ka / 2);
}

void mundur_kanan() {
  ledcWrite(pwm_channel, pwm_ki / 2);
  ledcWrite(pwm_channel1, 0);
  ledcWrite(pwm_channel2, 0);
  ledcWrite(pwm_channel3, pwm_ka);
}

void stopped() {
  ledcWrite(pwm_channel, 0);
  ledcWrite(pwm_channel1, 0);
  ledcWrite(pwm_channel2, 0);
  ledcWrite(pwm_channel3, 0);
}

void setup() {
  Serial.begin(9600); // Inisialisasi Serial Monitor
  Ps3.begin("55:aa:44:f4:88:98"); // MAC Address dari sumo versi 1.txt
  ledcSetup(pwm_channel, frequency, resolution);
  ledcSetup(pwm_channel1, frequency, resolution);
  ledcSetup(pwm_channel2, frequency, resolution);
  ledcSetup(pwm_channel3, frequency, resolution);
  ledcAttachPin(RPWM_kiri, pwm_channel);
  ledcAttachPin(LPWM_kiri, pwm_channel1);
  ledcAttachPin(RPWM_kanan, pwm_channel2);
  ledcAttachPin(LPWM_kanan, pwm_channel3);
  pinMode(RPWM_kanan, OUTPUT);
  pinMode(LPWM_kanan, OUTPUT);
  pinMode(RPWM_kiri, OUTPUT);
  pinMode(LPWM_kiri, OUTPUT);
  pinMode(ena_kiri, OUTPUT);
  pinMode(ena_kanan, OUTPUT);
}

void loop() {
  if (Ps3.isConnected()) {
    digitalWrite(ena_kanan, HIGH);
    digitalWrite(ena_kiri, HIGH);

    bool isMoving = false;
    // Kecepatan ditentukan oleh tombol R1 atau L1
    int speed;
    const char* speed_mode_text;
    if (Ps3.data.button.r1 || Ps3.data.button.l1) {
      speed = 255;
      speed_mode_text = " cepat";
    } else {
      speed = 140;
      speed_mode_text = "";
    }

    // ========== KONTROL MENGGUNAKAN LEFT ANALOG STICK ==========
    int ly = Ps3.data.analog.stick.ly;
    int lx = Ps3.data.analog.stick.lx;

    // Gerakan diagonal
    if (ly < -50 && lx < -50) {
      pwm_ki = speed;
      pwm_ka = speed;
      maju_kiri();
      Serial.print("L3: maju kiri"); Serial.println(speed_mode_text);
      isMoving = true;
    } else if (ly < -50 && lx > 50) {
      pwm_ki = speed;
      pwm_ka = speed;
      maju_kanan();
      Serial.print("L3: maju kanan"); Serial.println(speed_mode_text);
      isMoving = true;
    } else if (ly > 50 && lx < -50) {
      pwm_ki = speed;
      pwm_ka = speed;
      mundur_kiri();
      Serial.print("L3: mundur kiri"); Serial.println(speed_mode_text);
      isMoving = true;
    } else if (ly > 50 && lx > 50) {
      pwm_ki = speed;
      pwm_ka = speed;
      mundur_kanan();
      Serial.print("L3: mundur kanan"); Serial.println(speed_mode_text);
      isMoving = true;
    }
    // Gerakan lurus
    else if (ly < -50) {
      pwm_ki = speed;
      pwm_ka = speed;
      maju();
      Serial.print("L3: maju"); Serial.println(speed_mode_text);
      isMoving = true;
    } else if (ly > 50) {
      pwm_ki = speed; pwm_ka = speed;
      mundur();
      Serial.print("L3: mundur"); Serial.println(speed_mode_text);
      isMoving = true;
    } else if (lx < -50) {
      pwm_ki = speed; pwm_ka = speed;
      kiri();
      Serial.print("L3: kiri"); Serial.println(speed_mode_text);
      isMoving = true;
    } else if (lx > 50) {
      pwm_ki = speed; pwm_ka = speed;
      kanan();
      Serial.print("L3: kanan"); Serial.println(speed_mode_text);
      isMoving = true;
    }

    // ========== KONTROL MENGGUNAKAN D-PAD (HANYA JIKA ANALOG TIDAK DIGUNAKAN) ==========
    if (!isMoving) {
      // Gerakan diagonal D-pad
      if (Ps3.data.button.up && Ps3.data.button.left) {
        pwm_ki = speed;
        pwm_ka = speed;
        maju_kiri();
        Serial.print("D-pad: maju kiri"); Serial.println(speed_mode_text);
        isMoving = true;
      } else if (Ps3.data.button.up && Ps3.data.button.right) {
        pwm_ki = speed;
        pwm_ka = speed;
        maju_kanan();
        Serial.print("D-pad: maju kanan"); Serial.println(speed_mode_text);
        isMoving = true;
      } else if (Ps3.data.button.down && Ps3.data.button.left) {
        pwm_ki = speed;
        pwm_ka = speed;
        mundur_kiri();
        Serial.print("D-pad: mundur kiri"); Serial.println(speed_mode_text);
        isMoving = true;
      } else if (Ps3.data.button.down && Ps3.data.button.right) {
        pwm_ki = speed;
        pwm_ka = speed;
        mundur_kanan();
        Serial.print("D-pad: mundur kanan"); Serial.println(speed_mode_text);
        isMoving = true;
      }
      // Gerakan lurus D-pad
      else if (Ps3.data.button.up) {
        pwm_ki = speed;
        pwm_ka = speed;
        maju();
        Serial.print("D-pad: maju"); Serial.println(speed_mode_text);
        isMoving = true;
      } else if (Ps3.data.button.down) {
        pwm_ki = speed;
        pwm_ka = speed;
        mundur();
        Serial.print("D-pad: mundur"); Serial.println(speed_mode_text);
        isMoving = true;
      } else if (Ps3.data.button.left) {
        pwm_ki = speed;
        pwm_ka = speed;
        kiri();
        Serial.print("D-pad: kiri"); Serial.println(speed_mode_text);
        isMoving = true;
      } else if (Ps3.data.button.right) {
        pwm_ki = speed;
        pwm_ka = speed;
        kanan();
        Serial.print("D-pad: kanan"); Serial.println(speed_mode_text);
        isMoving = true;
      }
    }

    // Jika tidak ada input gerakan sama sekali, berhenti
    if (!isMoving) {
      stopped();
      Serial.println("stop");
    }
  } else {
    stopped();
    Serial.println("PS3 Disconnected - STOP");
  }
}