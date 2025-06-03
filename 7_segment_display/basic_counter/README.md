# Contador con 8 GPIOs

Contador básico utilizando un visualizador de siete segmentos de cátodo común HDSP-513E de la marca Broadcom y una placa ESP32-C6 DevKitC-1 de Espressif Systems.

El objetivo de este pequeño circuito es controlar el visualizador para mostrar un contador de 0 a 9 que se vaya actualizando cada segundo, pero sin hacer uso de circuitos integrados externos u otras técnicas que ahorren cableado. La idea es realizar la comunicación de forma completamente paralela como práctica para futuros circuitos con componentes DIP.

El proyecto consiste en el archivo main.c con el código del contador y el esquema del circuito en formato PDF.