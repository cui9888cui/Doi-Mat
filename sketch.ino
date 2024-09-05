#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Chân kết nối cho màn hình TFT ILI9341 trên ESP32
#define TFT_CS     15
#define TFT_RST    4  
#define TFT_DC     2

// Khởi tạo màn hình TFT
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Vị trí tròng mắt
const int eye1_x = 70;  // Mắt trái
const int eye2_x = 170; // Mắt phải
const int eye_y = 120;  // Vị trí mắt theo chiều dọc
const int pupil_radius = 15;  // Kích thước con ngươi
const int eye_radius = 40;    // Kích thước tròng mắt

// Hàm vẽ tròng mắt
void drawEyeOutline() {
  tft.fillCircle(eye1_x, eye_y, eye_radius, ILI9341_WHITE);  // Vẽ tròng mắt trái
  tft.fillCircle(eye2_x, eye_y, eye_radius, ILI9341_WHITE);  // Vẽ tròng mắt phải
}

// Hàm vẽ hoặc xóa con ngươi
void drawPupil(int eyeX, int eyeY, int pupilX, bool erase) {
  int color = erase ? ILI9341_WHITE : ILI9341_BLACK;  // Chọn màu nền hoặc màu con ngươi
  tft.fillCircle(pupilX, eyeY, pupil_radius, color);  // Vẽ hoặc xóa con ngươi
}

// Hàm di chuyển con ngươi từ giữa sang trái và phải mượt mà
void moveEyesSmoothly() {
  int prevPupil1X = eye1_x;  // Lưu vị trí trước đó của con ngươi mắt trái
  int prevPupil2X = eye2_x;  // Lưu vị trí trước đó của con ngươi mắt phải
  
  // Con ngươi từ giữa sang trái
  for (int i = 0; i >= -20; i -= 2) {
    drawPupil(eye1_x, eye_y, prevPupil1X, true);  // Xóa con ngươi cũ
    drawPupil(eye2_x, eye_y, prevPupil2X, true);  // Xóa con ngươi cũ
    drawPupil(eye1_x, eye_y, eye1_x + i, false);  // Vẽ con ngươi mới mắt trái
    drawPupil(eye2_x, eye_y, eye2_x + i, false);  // Vẽ con ngươi mới mắt phải
    
    prevPupil1X = eye1_x + i;  // Cập nhật vị trí con ngươi mắt trái
    prevPupil2X = eye2_x + i;  // Cập nhật vị trí con ngươi mắt phải
    delay(30);  // Điều chỉnh tốc độ để tạo chuyển động mượt mà hơn
  }

  // Dừng lại 1 giây
  delay(1000);

  // Con ngươi từ trái sang phải
  for (int i = -20; i <= 20; i += 2) {
    drawPupil(eye1_x, eye_y, prevPupil1X, true);  // Xóa con ngươi cũ
    drawPupil(eye2_x, eye_y, prevPupil2X, true);  // Xóa con ngươi cũ
    drawPupil(eye1_x, eye_y, eye1_x + i, false);  // Vẽ con ngươi mới mắt trái
    drawPupil(eye2_x, eye_y, eye2_x + i, false);  // Vẽ con ngươi mới mắt phải
    
    prevPupil1X = eye1_x + i;  // Cập nhật vị trí con ngươi mắt trái
    prevPupil2X = eye2_x + i;  // Cập nhật vị trí con ngươi mắt phải
    delay(30);  // Điều chỉnh tốc độ để tạo chuyển động mượt mà hơn
  }

  // Dừng lại 1 giây
  delay(1000);

  // Trả con ngươi về giữa
  for (int i = 20; i >= 0; i -= 2) {
    drawPupil(eye1_x, eye_y, prevPupil1X, true);  // Xóa con ngươi cũ
    drawPupil(eye2_x, eye_y, prevPupil2X, true);  // Xóa con ngươi cũ
    drawPupil(eye1_x, eye_y, eye1_x + i, false);  // Vẽ con ngươi mới mắt trái
    drawPupil(eye2_x, eye_y, eye2_x + i, false);  // Vẽ con ngươi mới mắt phải
    
    prevPupil1X = eye1_x + i;  // Cập nhật vị trí con ngươi mắt trái
    prevPupil2X = eye2_x + i;  // Cập nhật vị trí con ngươi mắt phải
    delay(30);  // Điều chỉnh tốc độ để tạo chuyển động mượt mà hơn
  }

  // Dừng lại 1 giây trước khi chớp mắt
  delay(1000);
}

// Hàm chớp mắt
void blinkEyes() {
  // Chớp mắt bằng cách vẽ hình chữ nhật đen che mắt
  tft.fillRect(eye1_x - eye_radius, eye_y - 10, eye_radius * 2, 20, ILI9341_BLACK);  // Chớp mắt trái
  tft.fillRect(eye2_x - eye_radius, eye_y - 10, eye_radius * 2, 20, ILI9341_BLACK);  // Chớp mắt phải
  delay(300);  // Chớp mắt trong 300ms
  drawEyeOutline();  // Vẽ lại tròng mắt sau khi mở mắt
  delay(200);  // Tạo hiệu ứng chờ giữa các lần chớp
}

void setup() {
  tft.begin();           // Khởi động màn hình TFT
  tft.setRotation(1);    // Đặt hướng màn hình
  drawEyeOutline();      // Vẽ tròng mắt ban đầu
}

void loop() {
  moveEyesSmoothly();   // Mắt di chuyển từ giữa sang trái, phải và trở về giữa
  blinkEyes();          // Chớp mắt sau khi di chuyển
  delay(1000);          // Dừng lại trước khi lặp lại
}
