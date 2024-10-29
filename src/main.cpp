#include <Arduino.h>
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <GyverINA.h>
#include <config.h>

INA226 ina_One(0.19f , 1.0f , 0x40);
INA226 ina_Two(0.19f , 1.0f , 0x44);
TaskHandle_t readINATaskHandle = NULL;  // Хендл для управления задачей

void StartMeasure(lv_event_t* e)
{
    vTaskResume(readINATaskHandle);  // Возобновление задачи
    Serial.println("INA231 Task resumed");
    Imin = current;
    Imax = current;
    Umin = voltage;
    Umax = voltage;
    dtostrf(current , 1 , 1 , buffer);
    lv_label_set_text(ui_Label15 , buffer);
    lv_label_set_text(ui_Label17 , buffer);
    dtostrf(voltage , 1 , 2 , buffer1);
    lv_label_set_text(ui_Label11 , buffer1);
    lv_label_set_text(ui_Label13 , buffer1);
}

void StopMeasure(lv_event_t* e)
{
    vTaskSuspend(readINATaskHandle);  // Приостановка задачи
    Serial.println("INA231 Task suspended");
}

// Функция для опроса INA231
void readINA231Task(void* pvParameters)
{
    while (1)
    {
        current = ina_One.getCurrent() * 1000;  // Ток в мА
        voltage = ina_One.getVoltage();        // Напряжение в В
        power = ina_One.getPower() * 1000;      // Мощность в мВт

        if ((fabs(current - current_prev)) > 0.1)
        {
            dtostrf(current , 1 , 1 , buffer);
            lv_label_set_text(ui_Label4 , buffer);
            current_prev = current;
            if (Imin > current)
            {
                Imin = current;
                lv_label_set_text(ui_Label15 , buffer);
            }
            if (Imax < current)
            {
                Imax = current;
                lv_label_set_text(ui_Label17 , buffer);
            }
        }

        if ((fabs(voltage - voltage_prev)) > 0.01)
        {
            dtostrf(voltage , 1 , 2 , buffer1);
            lv_label_set_text(ui_Label5 , buffer1);
            voltage_prev = voltage;
            if (Umin > voltage)
            {
                Umin = voltage;
                lv_label_set_text(ui_Label11 , buffer1);
            }
            if (Umax < voltage)
            {
                Umax = voltage;
                lv_label_set_text(ui_Label13 , buffer1);
            }
        }

        if ((fabs(power - power_prev)) > 1)
        {
            dtostrf(power , 1 , 2 , buffer2);
            lv_label_set_text(ui_Label6 , buffer2);
            power_prev = power;
        }



        vTaskDelay(240);
    }
}

void setup()
{
    Serial.begin(115200);

    Serial.setDebugOutput(true);
    log_i("Board: %s" , BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)" , ESP.getChipModel() , ESP.getChipRevision() , getCpuFrequencyMhz() , ESP.getChipCores());
    log_i("Free heap: %d bytes" , ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes" , ESP.getPsramSize());
    log_i("SDK version: %s" , ESP.getSdkVersion());

    smartdisplay_init();
    __attribute__((unused)) auto disp = lv_disp_get_default();

    // Проверяем наличие и инициализируем INA231
    if (ina_One.begin(21 , 22))
    { // ina_One.begin(4, 5) // Для ESP32/ESP8266 можно указать пины I2C
        Serial.println(F("ina_One connected!"));
        Serial.print(F("Calibration value ina_One: "));
        Serial.println(ina_One.getCalibration());
    }
    else
    {
        Serial.println(F("ina_One not found!"));
        while (1)
            delay(1000);
    }
    ina_One.adjCalibration(240);
    // ina_One.setCalibration(300);
    ui_init();

    current = ina_One.getCurrent() * 1000;  // Ток в мА
    voltage = ina_One.getVoltage();        // Напряжение в В
    power = ina_One.getPower() * 1000;      // Мощность в мВт

    Imin = current;
    Imax = current;
    Umin = voltage;
    Umax = voltage;

    // Воспроизведение мелодии
    for (int i = 0; i < 1; i++)
    {
        int frequency = melody[i];
        int duration = durations[i];

        // Воспроизведение одной ноты с нужной частотой
        tone(SPEAK , frequency , duration);

        // Задержка перед воспроизведением следующей ноты
        delay(duration * 1.3); // Немного увеличиваем задержку для чёткости звука
    }

    // Выключение звука
    noTone(SPEAK);

    xTaskCreate(readINA231Task , "INA231 Task" , 4096 , NULL , 1 , &readINATaskHandle);
    // vTaskSuspend(readINATaskHandle);  // Приостановка задачи
    // Serial.println("INA231 Task suspended");
}

ulong next_millis;
auto lv_last_tick = millis();

void loop()
{
    auto const now = millis();
    if (now > next_millis)
    {
        next_millis = now + 500;
    }
    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;
    // Update the UI
    lv_timer_handler();

    vTaskDelay(5 / portTICK_PERIOD_MS);
}