# Autonomous boat

## Pin map

| Pin    | Label       | Description                                       |
| ------ | ----------- | ------------------------------------------------- |
| PA2    | USART2_TX   | Serial communication transmiter for debug purpose |
| PA3    | USART2_RX   | Serial communication receiver for debug purpose   |
| PA6    | L293D_LATCH | Latch pin from L293D driver                       |
| PA7    | L293D_PWM   | PWM pin for motor 1 from L293D driver             |
| PA8    | L293D_EN    | Enable pin from L293D driver                      |
| PA9    | L293D_SER   | Data pin from L293D driver                        |
| PB5    | L293D_CLK   | Clock pin from L293D driver                       |
| PB6    | SG90_PWM    | PWM pin for servo 1 from L293D driver             |
| PB7    | I2C1_SDA    | SDA pin for I2C communication with magnetometer   |
| PB8    | I2C1_SCL    | SCL pin for I2C communication with magnetometer   |
| PC5    | USART3_RX   | Serial communication receiver for BLE module      | 
| PC10   | USART3_TX   | Serial communication transmiter for BLE module    |