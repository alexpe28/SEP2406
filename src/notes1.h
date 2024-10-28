// char text_buffer[32];
// sprintf(text_buffer, "%lu", now);
// lv_label_set_text(ui_lblMillisecondsValue, text_buffer);

// #ifdef BOARD_HAS_RGB_LED
//         auto const rgb = (now / 2000) % 8;
//         smartdisplay_led_set_rgb(rgb & 0x01, rgb & 0x02, rgb & 0x04);
// #endif

// #ifdef BOARD_HAS_CDS
//         auto cdr = analogReadMilliVolts(CDS);
//         sprintf(text_buffer, "%d", cdr);
//         lv_label_set_text(ui_lblCdrValue, text_buffer);
// #endif

    // lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_270);

    // To use third party libraries, enable the define in lv_conf.h: #define LV_USE_QRCODE 1
    // auto ui_qrcode = lv_qrcode_create(ui_scrMain);
    // lv_qrcode_set_size(ui_qrcode, 100);
    // lv_qrcode_set_dark_color(ui_qrcode, lv_color_black());
    // lv_qrcode_set_light_color(ui_qrcode, lv_color_white());
    // const char *qr_data = "https://github.com/rzeldent/esp32-smartdisplay";
    // lv_qrcode_update(ui_qrcode, qr_data, strlen(qr_data));
    // lv_obj_center(ui_qrcode);

    // static uint32_t cnt = 0;
    // cnt++;
    // lv_label_set_text_fmt(ui_lblCountValue, "%u", cnt);

    // auto disp = lv_disp_get_default();
    // auto rotation = (lv_display_rotation_t)((lv_disp_get_rotation(disp) + 1) % (LV_DISPLAY_ROTATION_270 + 1));
    // lv_display_set_rotation(disp, rotation);


    //==================================== I2C scanner ============================

//     #include <Arduino.h>
// #include <Wire.h>

// void setup() {
//     Serial.begin(115200);
    
//     // Явная инициализация I2C
//     Wire.begin(21, 22);  // SDA=21, SCL=22

//     // // Убедитесь, что драйвер установлен
//     // if (Wire.begin() == false) {
//     //     Serial.println("I2C init failed");
//     // } else {
//     //     Serial.println("I2C init success");
//     // }
// }

// void loop() {
//    byte error, address;
//   int nDevices;
 
//   Serial.println("Scanning...");
 
//   nDevices = 0;
//   for(address = 1; address < 127; address++ ) 
//   {
 
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
 
//     if (error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if (address<16) 
//         Serial.print("0");
//       Serial.print(address,HEX);
//       Serial.println("  !");
 
//       nDevices++;
//     }
//     else if (error==4) 
//     {
//       Serial.print("Unknow error at address 0x");
//       if (address<16) 
//         Serial.print("0");
//       Serial.println(address,HEX);
//     }    
//   }
//   if (nDevices == 0)
//     Serial.println("No I2C devices found\n");
//   else
//     Serial.println("done\n");
 
//   delay(5000);           // wait 5 seconds for next scan
// }

//============================================== старый прототип кода ======================================

#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <ui/ui.h>

// void OnAddOneClicked(lv_event_t *e)
// {
//     static uint32_t cnt = 0;
//     cnt++;
//     lv_label_set_text_fmt(ui_lblCountValue, "%u", cnt);
// }

// void OnRotateClicked(lv_event_t *e)
// {
//     auto disp = lv_disp_get_default();
//     auto rotation = (lv_display_rotation_t)((lv_disp_get_rotation(disp) + 1) % (LV_DISPLAY_ROTATION_270 + 1));
//     lv_display_set_rotation(disp, rotation);
// }

void setup()
{
// #ifdef ARDUINO_USB_CDC_ON_BOOT
//     delay(5000);
// #endif
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());

    smartdisplay_init();

    __attribute__((unused)) auto disp = lv_disp_get_default();
    // lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_270);

    ui_init();

    // To use third party libraries, enable the define in lv_conf.h: #define LV_USE_QRCODE 1
    // auto ui_qrcode = lv_qrcode_create(ui_scrMain);
    // lv_qrcode_set_size(ui_qrcode, 100);
    // lv_qrcode_set_dark_color(ui_qrcode, lv_color_black());
    // lv_qrcode_set_light_color(ui_qrcode, lv_color_white());
    // const char *qr_data = "https://github.com/rzeldent/esp32-smartdisplay";
    // lv_qrcode_update(ui_qrcode, qr_data, strlen(qr_data));
    // lv_obj_center(ui_qrcode);
}

ulong next_millis;
auto lv_last_tick = millis();

void loop()
{
    auto const now = millis();
    if (now > next_millis)
    {
        next_millis = now + 500;

        // char text_buffer[32];
        // sprintf(text_buffer, "%lu", now);
        // lv_label_set_text(ui_lblMillisecondsValue, text_buffer);

// #ifdef BOARD_HAS_RGB_LED
//         auto const rgb = (now / 2000) % 8;
//         smartdisplay_led_set_rgb(rgb & 0x01, rgb & 0x02, rgb & 0x04);
// #endif

// #ifdef BOARD_HAS_CDS
//         auto cdr = analogReadMilliVolts(CDS);
//         sprintf(text_buffer, "%d", cdr);
//         lv_label_set_text(ui_lblCdrValue, text_buffer);
// #endif
    }

    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    // Update the UI
    lv_timer_handler();
}
//==========================================

float value = 3.14159;
char buffer[10];  // Буфер для строки (размер подбирается в зависимости от точности)

// Преобразуем float в строку: `value` — число, 1 — минимальное количество символов до точки, 
// 2 — количество знаков после точки, результат записывается в `buffer`
dtostrf(value, 1, 2, buffer);

// Теперь buffer содержит строку "3.14", которая является const char*
Serial.println(buffer);
