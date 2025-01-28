# Reverse-Timer
Схема, собранная на микроконтроллере Atmega328p, осуществляет обратный отсчет относительно выбранной уставки.
Выбор уставки осуществляется с помощью инкрементального энкодера в пределах 100 сек.
Индикация уставки и дальнейшего отсчета происходит на дисплейном модуле TM1637.
Запуск и остановка таймера осуществляется одинарным нажатием кнопки энкодера.
После нажатия происходит сохранение уставки в энергонезависимой памяти.
Для сброса уставки производится длинное (>2,5сек) нажатие.
По истичении отсчета происходит световая и звуковая сигнализация.
Fuse Hgh-D2, Low-E2, Ext-05, Lock-3F
