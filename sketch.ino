#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS     15
#define TFT_RST    4  
#define TFT_DC     2

// Khởi tạo màn hình TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Vị trí tròng
const int eye1_x = 70;  // Mắt trái
const int eye2_x = 170; // Mắt phải
const int eye_y = 120;  // Vị trí theo chiều dọc
const int r_ConNguoi = 15;  // Kích thước con ngươi
const int r_TrongMat = 40;    // Kích thước tròng

// Hàm vẽ tròng
void drawTrongMat() {
  tft.fillCircle(eye1_x, eye_y, r_TrongMat, ILI9341_GREEN);  // Vẽ tròng trái
  tft.fillCircle(eye2_x, eye_y, r_TrongMat, ILI9341_GREEN);  // Vẽ tròng phải
}

// Hàm vẽ hoặc xóa con ngươi
void drawConNguoi(int eyeX, int eyeY, int ConNguoiX, bool xoa) {
  int color = xoa ? ILI9341_GREEN : ILI9341_BLACK;  // Chọn màu nền hoặc màu con ngươi
  tft.fillCircle(ConNguoiX, eyeY, r_ConNguoi, color);  // Vẽ hoặc xóa con ngươi
}

// Hàm di chuyển con ngươi từ giữa sang trái và phải
void moveEyes() {
  int conNguoi1X = eye1_x;  // Lưu vị trí trước đó của con ngươi trái
  int conNguoi2X = eye2_x;  // Lưu vị trí trước đó của con ngươi phải
  
  // Con ngươi từ giữa sang trái
  for (int i = 0; i >= -20; i -= 2) {
    drawConNguoi(eye1_x, eye_y, conNguoi1X, true);  // Xóa con ngươi cũ
    drawConNguoi(eye2_x, eye_y, conNguoi2X, true);  // Xóa con ngươi cũ
    drawConNguoi(eye1_x, eye_y, eye1_x + i, false);  // Vẽ con ngươi mới trái
    drawConNguoi(eye2_x, eye_y, eye2_x + i, false);  // Vẽ con ngươi mới phải
    
    conNguoi1X = eye1_x + i;  // Cập nhật vị trí con ngươi trái
    conNguoi2X = eye2_x + i;  // Cập nhật vị trí con ngươi phải
    delay(10);
  }
  delay(1000);

  // Con ngươi từ trái sang phải
  for (int i = -20; i <= 20; i += 2) {
    drawConNguoi(eye1_x, eye_y, conNguoi1X, true);  // Xóa con ngươi cũ
    drawConNguoi(eye2_x, eye_y, conNguoi2X, true);  // Xóa con ngươi cũ
    drawConNguoi(eye1_x, eye_y, eye1_x + i, false);  // Vẽ con ngươi mới trái
    drawConNguoi(eye2_x, eye_y, eye2_x + i, false);  // Vẽ con ngươi mới phải
    
    conNguoi1X = eye1_x + i;  // Cập nhật vị trí con ngươi trái
    conNguoi2X = eye2_x + i;  // Cập nhật vị trí con ngươi phải
    delay(10);
  }
  delay(1000);
}

// Hàm chớp
void blinkEyes() {
  // Chớp bằng cách vẽ hình chữ nhật đen che
  tft.fillRect(eye1_x - r_TrongMat, eye_y - 10, r_TrongMat * 2, 20, ILI9341_BLACK);  // Chớp trái
  tft.fillRect(eye2_x - r_TrongMat, eye_y - 10, r_TrongMat * 2, 20, ILI9341_BLACK);  // Chớp phải
  delay(300);
  drawTrongMat();   // Vẽ lại tròng sau khi mở
  delay(200);
}

void setup() {
  tft.begin();
  tft.setRotation(1);
  drawTrongMat();      // Vẽ tròng ban đầu
}

void loop() {
  moveEyes();
  blinkEyes();
  delay(1000);
