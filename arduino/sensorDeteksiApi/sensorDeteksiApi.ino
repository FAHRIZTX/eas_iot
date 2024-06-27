#include <LiquidCrystal.h> // Memasukkan library untuk mengendalikan LCD

#define FLAME_SENSOR_PIN 8 // Mendefinisikan pin 8 sebagai pin untuk Flame Sensor

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Menginisialisasi objek LCD dengan pin yang terhubung ke Arduino

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial dengan baud rate 9600
  lcd.begin(16, 2); // Menginisialisasi LCD dengan ukuran 16x2
  lcd.setCursor(0,0); // Menempatkan kursor pada posisi kolom 0 baris 0
  lcd.print("UAS IoT"); // Menampilkan teks "UAS IoT" pada baris pertama LCD
  lcd.setCursor(0,1); // Menempatkan kursor pada posisi kolom 0 baris 1
  lcd.print("1462100013"); // Menampilkan teks "1462100013" pada baris kedua LCD
  pinMode(FLAME_SENSOR_PIN, INPUT); // Mengatur pin Flame Sensor sebagai input
  delay(2000); // Menunggu selama 2 detik
}

void loop() {
  lcd.clear(); // Membersihkan layar LCD
  lcd.setCursor(0,0); // Menempatkan kursor pada posisi kolom 0 baris 0
  lcd.print("Status Sensor: "); // Menampilkan teks "Status Sensor: " pada baris pertama LCD
  lcd.setCursor(4,1); // Menempatkan kursor pada posisi kolom 4 baris 1
  int statusSensor = digitalRead(FLAME_SENSOR_PIN); // Membaca status dari Flame Sensor

  if (statusSensor == HIGH) { // Jika Flame Sensor mendeteksi api
    String json = (String)"{\"sensor_status\": \"true\"}"; // Membuat string JSON dengan status sensor true
    Serial.println(json); // Mengirim string JSON ke monitor serial
    lcd.print("MENYALA"); // Menampilkan teks "MENYALA" pada LCD
  } else { // Jika Flame Sensor tidak mendeteksi api
    String json = (String)"{\"sensor_status\": \"false\"}"; // Membuat string JSON dengan status sensor false
    Serial.println(json); // Mengirim string JSON ke monitor serial
    lcd.print("MATI"); // Menampilkan teks "MATI" pada LCD
  }
  
  delay(500); // Menunggu selama 0,5 detik sebelum iterasi berikutnya
}
