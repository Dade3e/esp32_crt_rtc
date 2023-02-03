# ESP32 crt rtc

![esp32_crt_date](https://github.com/Dade3e/esp32_crt_rtc/blob/main/img/crt_date.jpeg)

## HARDWARE
Ho usato un crt M01JVV47WB di una videocamera che ho trovato a casa

ha un driver per segnale sincrono AN2514S e vedendo il datasheet, si trova che il segnale video è sul pin 11.

## SOFTWARE

Ho usato la libreria ESP_8_BIT_composite (https://github.com/Roger-random/ESP_8_BIT_composite)

e la libreria ESP32Time.h per la parte rtc.

Per il set Data e Ora, ho usato i pin touch 4 e 27 



