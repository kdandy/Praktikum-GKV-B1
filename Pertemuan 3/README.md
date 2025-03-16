##
Nama: Dandy Faishal Fahmi
NIM: 24060123140136 / LAB B1
Program: membuat lengan dan jari bergerak
##


# Cara Kerja Kode Lengan 3D OpenGL

Program ini membuat simulasi lengan 3D dengan GLUT/OpenGL yang terdiri dari:

- Lengan atas (dari bahu)
- Lengan bawah (dari siku)
- Telapak tangan
- 5 jari dengan 3 ruas per jari

## Teknis Implementasi

- Struktur hierarkis objek menggunakan transformasi matriks
- Rotasi persendian dengan glRotatef()
- Translasi posisi dengan glTranslatef()
- State matrix disimpan/dipulihkan dengan glPushMatrix()/glPopMatrix()
- Objek digambar sebagai wireframe cubes dengan glutWireCube()

## Interaksi Pengguna

- Mouse: Rotasi bahu (default), siku (dengan Shift), telapak (dengan Ctrl)
- Keyboard: Kontrol individual per-ruas jari
- Kamera dapat diputar dan di-zoom

## Kontrol Keyboard untuk Jari-Jari

### Jari Telunjuk:
- 1/! : Ruas pertama
- 2/@ : Ruas kedua
- 3/# : Ruas ketiga

### Jari Tengah:
- 4/$ : Ruas pertama
- 5/% : Ruas kedua
- 6/^ : Ruas ketiga

### Jari Manis:
- q/Q : Ruas pertama
- w/W : Ruas kedua
- e/E : Ruas ketiga

### Jari Kelingking:
- a/A : Ruas pertama
- s/S : Ruas kedua
- d/D : Ruas ketiga

### Jempol:
- z/Z : Ruas pertama
- x/X : Ruas kedua
- c/C : Ruas ketiga

### Telapak:
- p/P : Rotasi telapak

### Kontrol semua jari:
- f : Luruskan semua jari
- g : Tekuk semua jari (genggam)

### Reset:
- r : Reset ke posisi awal

## Operasi Sumbu X,Y,Z dengan Keyboard

- LEFT   → yRotation -= 5.0f   (rotasi ke kiri)
- RIGHT  → yRotation += 5.0f   (rotasi ke kanan)
- UP     → xRotation -= 5.0f   (rotasi ke atas)
- DOWN   → xRotation += 5.0f   (rotasi ke bawah)
- v      → zRotation += 5.0f   (rotasi searah jarum jam)
- V      → zRotation -= 5.0f   (rotasi berlawanan jarum jam)