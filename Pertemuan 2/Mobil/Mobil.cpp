//    Nama  : Dandy Faishal Fahmi 24060123140136
//    Tugas : Praktikum 2 tugas Mobil dari objek primitif sekreatif mungkin
//    Lab   : B1

#include <GLUT/glut.h>
#include <math.h>
#include <cstdlib>
#include <ctime>

//====================== DEFINISI KONSTANTA DAN VARIABEL GLOBAL ======================
const double PI = 3.142857143;
int i, radius, jumTitik, xTengah, yTengah;

int gerak = 0;
bool atas = true;

float r1 = 0.0f, g1 = 0.49f, b1 = 0.83f;
float r2 = 0.16f, g2 = 0.0f, b2 = 0.7f;
int colorPhase = 0;
float reflectionIntensity = 0.0f;
int reflectionDirection = 1;

// efek siang/malam
bool nightMode = false;
float skyBrightness = 1.0f;
int dayNightCycle = 0;

// kontrol animasi hujan
float rainAmount = 0.0f;
bool isRaining = false;
const int MAX_RAINDROPS = 500;
struct Raindrop {
    float x, y;     // posisi
    float speed;    // kecepatan jatuh
    float length;   // panjang tetesan
    float alpha;    // transparansi
} raindrops[MAX_RAINDROPS];

// tetesan hujan
void initRaindrops() {
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        raindrops[i].x = -50.0f + (rand() % 1000) / 10.0f;
        raindrops[i].y = -30.0f + (rand() % 800) / 10.0f;
        raindrops[i].speed = 0.2f + (rand() % 30) / 100.0f;
        raindrops[i].length = 0.3f + (rand() % 20) / 100.0f;
        raindrops[i].alpha = 0.3f + (rand() % 70) / 100.0f;
    }
}

//====================== FUNGSI PEMBENTUK OBJEK DASAR ======================

// menggambar lingkaran dengan posisi dan warna kustom
void drawCircle(float x, float y, float radius, float r, float g, float b, float alpha = 1.0f) {
    glColor4f(r, g, b, alpha);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float sudut = i * (2 * PI / 100);
        float xPos = x + radius * cos(sudut);
        float yPos = y + radius * sin(sudut);
        glVertex2f(xPos, yPos);
    }
    glEnd();
}

// membuat polygon dengan warna gradien
void drawGradientPolygon(float coords[][2], int numPoints, float r1, float g1, float b1, float r2, float g2, float b2) {
    glBegin(GL_POLYGON);
    // Titik awal dengan warna 1
    glColor3f(r1, g1, b1);
    for (int i = 0; i < numPoints / 2; i++) {
        glVertex2f(coords[i][0], coords[i][1]);
    }
    
    // Titik akhir dengan warna 2
    glColor3f(r2, g2, b2);
    for (int i = numPoints / 2; i < numPoints; i++) {
        glVertex2f(coords[i][0], coords[i][1]);
    }
    glEnd();
}

//====================== FUNGSI UNTUK OBJEK LANGIT DAN LINGKUNGAN ======================

// menggambar awan
void drawCloud(float x, float y, float size) {
    float cloudColor = nightMode ? 0.3f : 1.0f;
    glColor3f(cloudColor, cloudColor, cloudColor); // warna awan sesuai mode siang/malam
    
    // menggambar lingkaran-lingkaran yang membentuk awan
    glBegin(GL_POLYGON);
    radius = size*80;
    jumTitik = 100;
    xTengah = x*100;
    yTengah = y*100;
      
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/jumTitik);
        float xPos = xTengah + radius * cos(sudut);
        float yPos = yTengah + radius * sin(sudut);
        glVertex2f(xPos/100, yPos/100);
    }
    glEnd();
    
    // tambahan lingkaran untuk awan
    glBegin(GL_POLYGON);
    xTengah = (x + size*0.5)*100;
    yTengah = (y + size*0.2)*100;
    
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/jumTitik);
        float xPos = xTengah + radius * cos(sudut);
        float yPos = yTengah + radius * sin(sudut);
        glVertex2f(xPos/100, yPos/100);
    }
    glEnd();
    
    glBegin(GL_POLYGON);
    xTengah = (x - size*0.5)*100;
    yTengah = (y + size*0.1)*100;
    
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/jumTitik);
        float xPos = xTengah + radius * cos(sudut);
        float yPos = yTengah + radius * sin(sudut);
        glVertex2f(xPos/100, yPos/100);
    }
    glEnd();
}

// menggambar bintang di langit
void drawStar(float x, float y, float size) {
    if (!nightMode) return; // bintang hanya muncul di malam hari
    
    glColor3f(1.0f, 1.0f, 0.8f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 5; i++) {
        // Titik luar
        float angle = i * 2 * PI / 5 - PI / 2;
        float xOuter = x + size * cos(angle);
        float yOuter = y + size * sin(angle);
        glVertex2f(xOuter, yOuter);
        
        // Titik dalam
        angle += PI / 5;
        float xInner = x + size * 0.4 * cos(angle);
        float yInner = y + size * 0.4 * sin(angle);
        glVertex2f(xInner, yInner);
    }
    glEnd();
}

// menggambar matahari atau bulan
void drawSunMoon(float x, float y, float size) {
    if (nightMode) {
        // Bulan di malam hari
        drawCircle(x, y, size, 0.9f, 0.9f, 0.8f);
        // Kawah bulan
        drawCircle(x - size * 0.3f, y + size * 0.1f, size * 0.15f, 0.8f, 0.8f, 0.7f);
        drawCircle(x + size * 0.4f, y - size * 0.2f, size * 0.1f, 0.8f, 0.8f, 0.7f);
    } else {
        // Matahari di siang hari
        drawCircle(x, y, size, 1.0f, 0.9f, 0.0f);
        // Efek sinar matahari
        glColor3f(1.0f, 0.9f, 0.0f);
        glLineWidth(2.0f);
        for (int i = 0; i < 12; i++) {
            float angle = i * PI / 6;
            glBegin(GL_LINES);
            glVertex2f(x + size * 1.1f * cos(angle), y + size * 1.1f * sin(angle));
            glVertex2f(x + size * 1.5f * cos(angle), y + size * 1.5f * sin(angle));
            glEnd();
        }
    }
}

// menggambar pohon
void drawTree(float x, float y, float size) {
    // Batang pohon
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.27f, 0.07f);
    glVertex2f(x - size*0.5, y - size*6);
    glVertex2f(x + size*0.5, y - size*6);
    glVertex2f(x + size*0.5, y);
    glVertex2f(x - size*0.5, y);
    glEnd();
    
    // daun pohon (bentuk segitiga)
    float leafColor = 0.0f;
    float leafSaturation = nightMode ? 0.3f : 0.5f; // daun terlihat lebih gelap di malam hari
    
    glBegin(GL_TRIANGLES);
    glColor3f(leafColor, leafSaturation, leafColor);
    glVertex2f(x - size*3, y);
    glVertex2f(x + size*3, y);
    glVertex2f(x, y + size*5);
    glEnd();
    
    // daun pohon bagian atas (bentuk segitiga)
    leafSaturation = nightMode ? 0.35f : 0.6f;
    glBegin(GL_TRIANGLES);
    glColor3f(leafColor, leafSaturation, leafColor);
    glVertex2f(x - size*2.5, y + size*3);
    glVertex2f(x + size*2.5, y + size*3);
    glVertex2f(x, y + size*7);
    glEnd();
    
    // daun pohon bagian paling atas (bentuk segitiga)
    leafSaturation = nightMode ? 0.4f : 0.7f;
    glBegin(GL_TRIANGLES);
    glColor3f(leafColor, leafSaturation, leafColor);
    glVertex2f(x - size*2, y + size*6);
    glVertex2f(x + size*2, y + size*6);
    glVertex2f(x, y + size*9);
    glEnd();
}

// menggambar lingkungan jalanan
void drawRoad() {
    // Jalan aspal
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-50.0, 0.0);
    glVertex2f(-50.0, -7.0);
    glVertex2f(100.0, -7.0);
    glVertex2f(100.0, 0.0);
    glEnd();
    
    // Batas tepi jalan
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-50.0, 0.0);
    glVertex2f(-50.0, 0.5);
    glVertex2f(100.0, 0.5);
    glVertex2f(100.0, 0.0);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-50.0, -7.0);
    glVertex2f(-50.0, -7.5);
    glVertex2f(100.0, -7.5);
    glVertex2f(100.0, -7.0);
    glEnd();
    
    // Garis putih di tengah jalan
    float stripeBrightness = nightMode ? 0.8f : 1.0f;
    glColor3f(stripeBrightness, stripeBrightness, stripeBrightness);
    
    // Garis-garis putus di tengah jalan
    for (float x = -40.0f; x < 100.0f; x += 10.0f) {
        glBegin(GL_QUADS);
        glVertex2f(x, -3.4);
        glVertex2f(x, -3.6);
        glVertex2f(x + 5.0, -3.6);
        glVertex2f(x + 5.0, -3.4);
        glEnd();
    }
}

// Efek hujan yang lebih realistis
void drawRain() {
    // Hujan hanya muncul di malam hari
    if (!nightMode || !isRaining) return;
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLineWidth(1.0f);
    
    // Gambar setiap tetesan hujan
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        glBegin(GL_LINES);
        // Warna tetesan hujan
        glColor4f(0.7f, 0.7f, 1.0f, raindrops[i].alpha);
        
        // Titik awal dan akhir tetesan dengan sudut miring
        glVertex2f(raindrops[i].x, raindrops[i].y);
        glVertex2f(raindrops[i].x - raindrops[i].length, raindrops[i].y - raindrops[i].length * 2.0f);
        glEnd();
        
        // Cipratan air saat hujan menyentuh permukaan jalan
        if (raindrops[i].y < -6.5f && raindrops[i].y > -7.0f) {
            // Gambar cipratan kecil
            drawCircle(raindrops[i].x, -7.0f, raindrops[i].length * 0.3f,
                       0.7f, 0.7f, 1.0f, 0.2f);
        }
    }
    
    glDisable(GL_BLEND);
}

// mengupdate posisi tetesan hujan
void updateRain() {
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        // Memindahkan tetesan hujan ke bawah
        raindrops[i].y -= raindrops[i].speed;
        
        // jika tetesan mencapai batas bawah layar, reset ke atas
        if (raindrops[i].y < -30.0f) {
            raindrops[i].y = 30.0f;
            raindrops[i].x = -50.0f + (rand() % 1000) / 10.0f;
            raindrops[i].speed = 0.2f + (rand() % 30) / 100.0f;
            raindrops[i].alpha = 0.3f + (rand() % 70) / 100.0f;
        }
    }
}

//====================== FUNGSI UNTUK MOBIL DAN KOMPONENNYA ======================

// menggambar velg roda dengan jari-jari
void drawWheelRim(float centerX, float centerY, float radius) {
    // Lingkaran luar velg
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_POLYGON);
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/100);
        float x = centerX + radius*0.6 * cos(sudut);
        float y = centerY + radius*0.6 * sin(sudut);
        glVertex2f(x, y);
    }
    glEnd();
    
    // Pusat velg
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/100);
        float x = centerX + radius*0.15 * cos(sudut);
        float y = centerY + radius*0.15 * sin(sudut);
        glVertex2f(x, y);
    }
    glEnd();
    
    // Jari-jari velg
    for (int spoke = 0; spoke < 12; spoke++) {
        float angle = spoke * (2*PI/12);
        
        if (spoke % 2 == 0) {
            glColor3f(0.75f, 0.75f, 0.75f);
        } else {
            glColor3f(0.6f, 0.6f, 0.6f);
        }
        
        glBegin(GL_QUADS);
        float x1 = centerX + radius*0.17 * cos(angle - 0.05);
        float y1 = centerY + radius*0.17 * sin(angle - 0.05);
        float x2 = centerX + radius*0.17 * cos(angle + 0.05);
        float y2 = centerY + radius*0.17 * sin(angle + 0.05);
        float x3 = centerX + radius*0.58 * cos(angle + 0.05);
        float y3 = centerY + radius*0.58 * sin(angle + 0.05);
        float x4 = centerX + radius*0.58 * cos(angle - 0.05);
        float y4 = centerY + radius*0.58 * sin(angle - 0.05);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glVertex2f(x4, y4);
        glEnd();
    }
    
    // Baut-baut roda
    glColor3f(0.3f, 0.3f, 0.3f);
    for (int baut = 0; baut < 6; baut++) {
        float angle = baut * (2*PI/6);
        float bautX = centerX + radius*0.4 * cos(angle);
        float bautY = centerY + radius*0.4 * sin(angle);
        drawCircle(bautX, bautY, radius*0.06, 0.3f, 0.3f, 0.3f);
    }
}

// efek refleksi cahaya pada mobil
void drawReflection(float x, float y, float width, float height) {
    if (nightMode) {
        // Refleksi lebih lemah di malam hari
        glBegin(GL_POLYGON);
        glColor4f(1.0f, 1.0f, 1.0f, reflectionIntensity * 0.5f);
        glVertex2f(x, y);
        glVertex2f(x + width*0.7, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height*0.8);
        glEnd();
    } else {
        // Refleksi penuh di siang hari
        glBegin(GL_POLYGON);
        glColor4f(1.0f, 1.0f, 1.0f, reflectionIntensity);
        glVertex2f(x, y);
        glVertex2f(x + width*0.7, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height*0.8);
        glEnd();
    }
}

// menggambar lampu depan dengan efek cahaya
void drawHeadlight(float x, float y, float radius) {
    // Bodi lampu
    drawCircle(x, y, radius, 0.9f, 0.9f, 0.9f);
    
    // Lensa lampu
    drawCircle(x, y, radius * 0.8f, 0.96f, 0.8f, 0.4f);
    
    // Efek cahaya dari lampu saat malam hari
    if (nightMode) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Kerucut cahaya
        glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f, 1.0f, 0.7f, 0.8f);
        glVertex2f(x, y);
        
        glColor4f(1.0f, 1.0f, 0.7f, 0.0f);
        for (int i = -30; i <= 30; i += 10) {
            float angle = i * PI / 180.0f;
            glVertex2f(x + 10.0f * cos(angle), y + 10.0f * sin(angle));
        }
        glEnd();
        
        glDisable(GL_BLEND);
    }
}

// menggambar lampu belakang
void drawTaillight(float x, float y, float width, float height) {
    // Bodi lampu
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.0f, 0.0f); // Merah
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
    
    // Efek pencahayaan saat malam hari
    if (nightMode) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glBegin(GL_QUADS);
        glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
        glVertex2f(x, y);
        glVertex2f(x, y + height);
        glVertex2f(x + width, y + height);
        glVertex2f(x + width, y);
        glEnd();
        
        glDisable(GL_BLEND);
    }
}

// menggambar pelat nomor
void drawLicensePlate(float x, float y, float width, float height) {
    // Pelat dasar
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
    
    // Bingkai pelat
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(x, y);
    glVertex2f(x, y + height);
    glVertex2f(x + width, y + height);
    glVertex2f(x + width, y);
    glEnd();
    
    // Nomor pelat
    glColor3f(0.0f, 0.0f, 0.0f);
    
    // Huruf B
    float charWidth = width / 8;
    float charX = x + charWidth;
    
    glBegin(GL_LINES);
    // B vertikal
    glVertex2f(charX, y + height * 0.3f);
    glVertex2f(charX, y + height * 0.7f);
    // B horizontal atas
    glVertex2f(charX, y + height * 0.7f);
    glVertex2f(charX + charWidth * 0.6f, y + height * 0.7f);
    // B horizontal tengah
    glVertex2f(charX, y + height * 0.5f);
    glVertex2f(charX + charWidth * 0.6f, y + height * 0.5f);
    // B horizontal bawah
    glVertex2f(charX, y + height * 0.3f);
    glVertex2f(charX + charWidth * 0.6f, y + height * 0.3f);
    glEnd();
    
    // Angka 1234
    for (int i = 0; i < 4; i++) {
        charX = x + 2.5f * charWidth + i * charWidth;
        
        glBegin(GL_LINES);
        // Garis horizontal (untuk semua angka)
        glVertex2f(charX, y + height * 0.5f);
        glVertex2f(charX + charWidth * 0.6f, y + height * 0.5f);
        glEnd();
    }
}

// menggambar seluruh mobil
void drawCar() {
    glPushMatrix();
    glTranslatef(gerak, 0, 0);
    
    //====================== BODY MOBIL ======================
    // Bodi utama - gradien warna biru-ungu
    float coords[][2] = {
        {-10.0, 5.0}, {-10.0, 4.0}, {-10.0, 3.0}, {-10.0, 2.0},
        {-10.0, 0.0}, {-10.0, -1.0}, {-9.0, -2.0}, {-8.0, -3.0},
        {-7.0, -3.0}, {-6.0, -3.0}, {-5.0, -3.0}, {-4.0, -3.0},
        {0.0, -3.0}, {1.0, -3.0}, {10.0, -3.0}, {14.5, -3.0},
        {14.0, -2.0}, {14.0, 1.5}, {14.0, 3.0}, {13.0, 4.0},
        {9.0, 4.0}, {4.0, 10.0}, {-4.0, 10.0}, {-5.5, 10.0},
        {-6.5, 9.5}, {-7.2, 8.8}, {-8.0, 7.9}, {-9.5, 6.0}
    };
    
    drawGradientPolygon(coords, 28, r1, g1, b1, r2, g2, b2);
    
    // Efek refleksi cahaya pada bodi mobil
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    drawReflection(-8.0, 1.0, 8.0, 7.0);
    glDisable(GL_BLEND);
    
    //====================== LAMPU & DETAIL MOBIL ======================
    // Lampu depan
    drawHeadlight(13.5, 1.0, 1.0);
    
    // Lampu belakang
    drawTaillight(-9.8, 0.0, 0.8, 2.0);
    
    // Grid depan (grill)
    glColor3f(0.2f, 0.2f, 0.2f);
    for (float y = -2.0f; y <= 2.0f; y += 0.5f) {
        glBegin(GL_LINES);
        glVertex2f(14.0f, y);
        glVertex2f(12.0f, y);
        glEnd();
    }
    
    // Wiper kaca depan
    glLineWidth(2.0f);
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
    glVertex2f(5.0, 6.0);
    glVertex2f(7.0, 8.0);
    glEnd();
    
    // Handle pintu
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(3.0, 2.8);
    glVertex2f(3.0, 3.2);
    glVertex2f(4.5, 3.2);
    glVertex2f(4.5, 2.8);
    glEnd();
    
    // Detail handle pintu
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(3.2, 2.9);
    glVertex2f(3.2, 3.1);
    glVertex2f(4.3, 3.1);
    glVertex2f(4.3, 2.9);
    glEnd();
    
    // Pelat nomor depan
    drawLicensePlate(11.0, -2.8, 3.0, 0.8);
    
    // Pelat nomor belakang
    drawLicensePlate(-9.8, -2.8, 3.0, 0.8);
    
    //====================== KACA & JENDELA ======================
    // Kaca depan
    glBegin(GL_POLYGON);
    glColor4f(0.3f, 0.5f, 0.7f, 0.9f);
    glVertex2f(0.0, 9.0);
    glVertex2f(0.0, 8.0);
    glVertex2f(0.0, 7.0);
    glVertex2f(0.0, 6.0);
    glVertex2f(0.0, 5.0);
    glVertex2f(0.0, 4.0);
    glVertex2f(1.0, 4.0);
    glVertex2f(2.0, 4.0);
    glVertex2f(3.0, 4.0);
    glVertex2f(5.0, 4.0);
    glVertex2f(5.0, 6.0);
    glVertex2f(4.5, 7.0);
    glVertex2f(4.0, 8.0);
    glVertex2f(3.0, 9.0);
    glVertex2f(0.0, 9.0);
    glEnd();
    
    // Kaca belakang
    glBegin(GL_POLYGON);
    glColor4f(0.3f, 0.5f, 0.7f, 0.9f);
    glVertex2f(-1.0, 9.0);
    glVertex2f(-5.0, 9.0);
    glVertex2f(-6.0, 8.0);
    glVertex2f(-7.0, 7.0);
    glVertex2f(-8.0, 6.0);
    glVertex2f(-8.0, 5.0);
    glVertex2f(-1.0, 5.0);
    glEnd();
    
    // Efek refleksi pada kaca saat malam hari
    if (nightMode) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glBegin(GL_POLYGON);
        glColor4f(0.9f, 0.9f, 1.0f, 0.2f);
        glVertex2f(4.2, 9.0);
        glVertex2f(5.0, 8.0);
        glVertex2f(5.7, 7.0);
        glVertex2f(6.9, 6.0);
        glVertex2f(7.5, 5.0);
        glVertex2f(8.0, 4.0);
        glVertex2f(9.1, 4.0);
        glVertex2f(5.1, 9.2);
        glEnd();
        
        glDisable(GL_BLEND);
    }
    
    //====================== PINTU & ATAP ======================
    // Pintu
    glBegin(GL_POLYGON);
    glColor3f(r1 * 0.8, g1 * 0.8, b1 * 0.8);
    glVertex2f(0.0, 4.0);
    glVertex2f(0.0, 1.0);
    glVertex2f(0.2, 0.2);
    glVertex2f(1.0, 0.0);
    glVertex2f(4.0, 0.0);
    glVertex2f(4.8, 0.2);
    glVertex2f(5.0, 1.0);
    glVertex2f(5.0, 4.0);
    glVertex2f(2.0, 4.0);
    glVertex2f(0.0, 4.0);
    glEnd();
    
    // Detail pintu - garis panel
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(0.1f, 0.1f, 0.2f);
    // Garis horizontal
    glVertex2f(0.2f, 0.5f);
    glVertex2f(4.8f, 0.5f);
    // Garis vertikal batas pintu
    glVertex2f(0.0f, 4.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    
    // Atap
    glBegin(GL_QUADS);
    glColor3f(r2, g2, b2);
    glVertex2f(-5.0, 12.0);
    glVertex2f(-5.0, 11.0);
    glColor3f(r1, g1, b1);
    glVertex2f(1.0, 11.0);
    glVertex2f(1.0, 12.0);
    glEnd();
    
    // Rak atap
    glLineWidth(3.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    // Batang vertikal
    glVertex2f(-4.0, 10.0);
    glVertex2f(-4.0, 11.5);
    glVertex2f(-2.0, 10.0);
    glVertex2f(-2.0, 11.5);
    glVertex2f(0.0, 10.0);
    glVertex2f(0.0, 11.5);
    glEnd();
    
    // Batang horizontal rak atap
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-4.5, 11.5);
    glVertex2f(-4.5, 12.0);
    glVertex2f(0.5, 12.0);
    glVertex2f(0.5, 11.5);
    glEnd();
    
    //====================== RODA & KOMPONEN BAWAH ======================
    // Roda depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(7.0, -2.0, 0.0);
    glBegin(GL_POLYGON);
    radius = 250;
    jumTitik = 100;
    xTengah = 90;
    yTengah = -90;
      
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/jumTitik);
        float x = xTengah + radius * cos(sudut);
        float y = yTengah + radius * sin(sudut);
        glVertex2f(x/100, y/100);
    }
    glEnd();
    
    // Velg roda depan
    drawWheelRim(0.9, -0.9, 0.25);
              
    // Roda belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-10.0, -0.5, 0.0);
    glBegin(GL_POLYGON);
    radius = 250;
    jumTitik = 100;
    xTengah = -90;
    yTengah = -90;
      
    for (i=0; i<=360; i++) {
        float sudut = i * (2*PI/jumTitik);
        float x = xTengah + radius * cos(sudut);
        float y = yTengah + radius * sin(sudut);
        glVertex2f(x/100, y/100);
    }
    glEnd();
    
    // Velg roda belakang
    drawWheelRim(-0.9, -0.9, 0.25);
    
    // Detail knalpot
    glTranslatef(0.0, 0.0, 0.0);
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-10.0, -2.8);
    glVertex2f(-10.0, -3.2);
    glVertex2f(-11.5, -3.2);
    glVertex2f(-11.5, -2.8);
    glEnd();
    
    // Uap knalpot saat mobil bergerak
    if (gerak % 4 == 0) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        for (int cloud = 0; cloud < 3; cloud++) {
            float offset = cloud * 0.7f;
            float alpha = 0.7f - cloud * 0.2f;
            
            drawCircle(-11.5 - offset, -3.0, 0.2 + cloud * 0.1, 0.6, 0.6, 0.6, alpha);
        }
        
        glDisable(GL_BLEND);
    }
    
    glPopMatrix();
}

//====================== FUNGSI UTAMA & ANIMASI ======================

void Mobil(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Warna langit (tergantung siang atau malam)
    if (nightMode) {
        glClearColor(0.05f, 0.05f, 0.2f, 0.0f); // Langit malam biru tua
    } else {
        glClearColor(0.431f, 0.698f, 0.89f, 0.0f); // Langit siang biru cerah
    }
    
    // Menggambar bintang-bintang di langit malam
    if (nightMode) {
        for (int i = 0; i < 20; i++) {
            float x = -25.0f + (i * 2.5f);
            float y = 15.0f + (i % 5);
            drawStar(x, y, 0.15);
        }
    }
    
    // Menggambar matahari atau bulan
    drawSunMoon(20.0, 20.0, 2.5);
    
    // Menggambar awan-awan
    drawCloud(-15, 18, 1.5);
    drawCloud(0, 22, 2);
    drawCloud(15, 20, 1.8);
    drawCloud(-25, 23, 1.2);
    
    // Menggambar pohon-pohon
    drawTree(-23, 0, 0.5);
    drawTree(-18, 0, 0.4);
    drawTree(20, 0, 0.6);
    drawTree(25, 0, 0.45);
    
    // Menggambar jalan
    drawRoad();
    
    // Menggambar mobil
    drawCar();
    
    // Efek hujan (khusus malam hari aja)
    drawRain();
    
    glFlush();
}

void timer(int t) {
    // Animasi pergerakan mobil
    if (atas) {
        gerak += 1;
    } else {
        gerak -= 1;
    }
    
    if (gerak > 20) {
        atas = false;
    } else if (gerak < -20) {
        atas = true;
    }
    
    // Animasi untuk efek refleksi cahaya
    reflectionIntensity += 0.02f * reflectionDirection;
    if (reflectionIntensity > 0.3f) {
        reflectionDirection = -1;
    } else if (reflectionIntensity < 0.05f) {
        reflectionDirection = 1;
    }
    
    // Animasi untuk efek perubahan warna gradual
    colorPhase = (colorPhase + 1) % 300;
    float phase = colorPhase / 300.0f;
    
    r1 = 0.0f + 0.1f * sin(phase * 2 * PI);
    g1 = 0.49f + 0.05f * sin(phase * 2 * PI);
    b1 = 0.83f + 0.07f * sin(phase * 2 * PI);
    
    r2 = 0.16f + 0.05f * sin(phase * 2 * PI);
    g2 = 0.0f + 0.03f * sin(phase * 2 * PI);
    b2 = 0.7f + 0.1f * sin(phase * 2 * PI);
    
    // Animasi siklus siang/malam
    dayNightCycle = (dayNightCycle + 1) % 600;
    if (dayNightCycle == 0) {
        nightMode = !nightMode;
        
        // saat berganti ke malam, mulai hujan dengan probabilitas tertentu
        if (nightMode && (rand() % 100 < 60)) { // bikin 60% kemungkinan hujan saat malam
            isRaining = true;
            initRaindrops(); // Inisialisasi ulang posisi hujan
        } else if (!nightMode) {
            // Di siang hari, selalu tidak hujan
            isRaining = false;
        }
    }
    
    // Animasi gerakan hujan (hanya dijalankan jika malam dan hujan)
    if (nightMode && isRaining) {
        updateRain();
    }
    
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutCreateWindow("Mobil Pixel - Dandy Faishal Fahmi 24060123140136");
    glutDisplayFunc(Mobil);
    gluOrtho2D(-30.0, 30.0, -30.0, 30.0);
    
    // tetesan hujan
    srand(static_cast<unsigned int>(time(NULL)));
    initRaindrops();
    
    glutTimerFunc(1, timer, 0);
    glClearColor(0.431f, 0.698f, 0.89f, 0.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glutMainLoop();
    return 0;
}