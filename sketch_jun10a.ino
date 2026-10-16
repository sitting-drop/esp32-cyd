#include <SPI.h>
#include <XPT2046_Touchscreen.h>

// Cấu hình chân chuẩn cho CYD (Cheap Yellow Display)
#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

// Khởi tạo SPI giao tiếp với cảm ứng
SPIClass mySPI(HSPI); 
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);

void setup() {
  Serial.begin(115200);
  
  // Bắt đầu SPI với cấu hình chân cụ thể của CYD
  mySPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  ts.begin(mySPI);
  
  // Đảo trục nếu cảm ứng bị ngược (tùy board)
  ts.setRotation(1); 
  
  Serial.println("CYD Touch Test đã khởi tạo!");
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();
    // In ra tọa độ Raw để kiểm tra
    Serial.printf("X: %d | Y: %d | Z: %d\n", p.x, p.y, p.z);
    delay(50);
  }
}