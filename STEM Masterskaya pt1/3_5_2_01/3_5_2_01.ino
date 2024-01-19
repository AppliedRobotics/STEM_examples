#include <DxlSlave.h> // Подключение библиотеки
#define IS_INITED_REG 23 // Адрес регистра для проверки 1-го запуска
void setup() {
  DxlSlave.begin(1234, 12); // Инициализация интерфейса (номер модели 1234, версия 12)
  Serial.begin(9600); // Инициализация отладочного последовательного порта для вывода
  if(!DxlSlave.get(IS_INITED_REG)) { // Инициализация EEPROM при 1-м запуске
    for(int i = 6; i < 23; i++) {
      DxlSlave.set(i, i);  // Заполнение регистров EEPROM произвольными значениями
      DxlSlave.set(IS_INITED_REG, 1); // Установка флага «1-я инициализация выполнена»
    }
  }
  for(int i = 24; i < 255; i++) {
    DxlSlave.set(i, i); // Заполнение регистров RAM произвольными значениями
  }
}
void loop() {
  while(DxlSlave.poll()) { // Проверка наличия изменений регистров ведущим устройством
    uint8_t addr = DxlSlave.scan(); // Получение адреса измененного регистра из очереди
    Serial.print(" The value at address "); // Вывод информации
    Serial.print(addr);
    Serial.print(" was changed by master. New value is ");
    Serial.println(DxlSlave.get(addr));
  }
}
