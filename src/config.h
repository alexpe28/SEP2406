const int melodyLength = 8;   // Количество нот в мелодии

// Массив частот и длительностей для воспроизведения мелодии
const int melody[melodyLength] = { 262, 294, 330, 349, 392, 440, 494, 523 }; // Пример частот
const int durations[melodyLength] = { 200, 200, 200, 200, 200, 200, 200, 200 }; // Длительность каждой ноты

char buffer[10];
char buffer1[10];
char buffer2[10];

float power;
float voltage;
float current;

float power_prev;
float voltage_prev;
float current_prev;

float Imin;
float Imax;
float Umin;
float Umax;

