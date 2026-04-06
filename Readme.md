### Arduino IDE set up for ubuntu

```bash
sudo apt install libfuse2 # for running appimage in ubuntu
```

```bash
sudo usermod -aG dialout $USER
```
```bash
reboot
```
# Free RTOS
```bash
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
```bash
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

## For ESP32 Camera Module 

### Connections For USB to TTL 
| Color    | Meaning  | ESP32-CAM |
| -------- | -------- | ------------------------ |
| 🔴 Red   | VCC (5V) | 5V pin                   |
| ⚫ Black  | GND      | GND                      |
| ⚪ White  | RX       | TX (U0T)                 |
| 🟢 Green | TX       | RX (U0R)                 |


### Connections (Specific for Flashing)
|ESP32-CAM Pin | ESP32-CAM Pin |
|--------------|---------------|
|IOO (GPIOO)   | GND |


### Select Board Type : AI Thinker ESP32CAM
