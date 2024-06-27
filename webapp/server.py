from fastapi import FastAPI  # Mengimpor FastAPI untuk membuat aplikasi web
from fastapi.responses import HTMLResponse  # Mengimpor HTMLResponse untuk mengembalikan respon HTML

import random  # Mengimpor modul random (walaupun tidak digunakan di sini)
import serial  # Mengimpor modul serial untuk komunikasi serial
import json  # Mengimpor modul json untuk memproses data JSON


app = FastAPI()  # Membuat instance dari aplikasi FastAPI

# Membuka port serial dalam loop hingga berhasil dibuka
while True:
    try:
        ser = serial.Serial('COM4', 9600)  # Mencoba membuka port serial COM4 dengan baud rate 9600
        print("Serial port opened successfully")  # Menampilkan pesan jika port serial berhasil dibuka
        break  # Keluar dari loop jika berhasil membuka port
    except:
        print("Error opening serial port")  # Menampilkan pesan jika terjadi kesalahan saat membuka port serial
        pass  # Melanjutkan loop untuk mencoba membuka kembali port

# Mendefinisikan endpoint root
@app.get("/", response_class=HTMLResponse)
async def read_root():
    with open("index.html") as f:  # Membuka file index.html
        html_file = f.read()  # Membaca isi file
        f.close()  # Menutup file
        return HTMLResponse(content=html_file, status_code=200)  # Mengembalikan isi file sebagai respon HTML dengan status kode 200

# Mendefinisikan endpoint untuk mendapatkan data dari serial
@app.get("/api/data")
async def get_data():
    if ser.in_waiting > 0:  # Memeriksa apakah ada data yang menunggu di buffer serial
        data = ser.readline().decode('utf-8').strip()  # Membaca satu baris data dari serial dan menghapus karakter whitespace
        status = json.loads(data)  # Mengonversi data JSON menjadi dictionary Python
        ser.flushInput()  # Membersihkan buffer input serial
        return status  # Mengembalikan status sensor sebagai respon JSON
    else:
        return {'sensor_status': 'N/A'}  # Mengembalikan respon jika tidak ada data yang tersedia
