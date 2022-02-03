# Датчики входной двери 
Система основана на esp32, используются три датчика VL6180X для замков и датчик холла для определения положения ригелей и двери. Информация о них выводится на матрицу ws2812 5х5 и приложение blynk. 

![IMG_20201130_213348](https://user-images.githubusercontent.com/47436708/152415962-f8123e88-000b-4dea-b8f4-cf3f366aac48.jpg)

# Недостатки:
Показания с датчик имеют малую точность, шум и изменчивость показаний со временем. По мере работы системы для корректного считывания показаний было написано множество правок, самой действенной оказалась добавление мертвой зоны на промежутке между двумя состояниями ригеля и активная коррекция италонных значений регелей самой программой во время работы.  Также в ходе эксплуатании обнаружились редко воникающие помехи на пинах матрицы и датчика хола, исправил их программно. 
Одной из причин изменения показаний можно назвать запыление датчиков в особеннсти после срабатывания пожарной тревоги и включения системы дымоудаления. 
