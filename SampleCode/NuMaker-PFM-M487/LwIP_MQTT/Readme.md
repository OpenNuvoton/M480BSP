# MQTT client implementation for embedded platform

This repository contains the source code for the application layer implementation of MQTT client. 
The lower level MQTT client functions are from [eclipse paho implementation of MQTT Client Libraries]
(https://www.eclipse.org/paho/clients/c/embedded/).
[FreeRTOS](www.freertos.org) is used for RTOS. 
[lwIP](https://savannah.nongnu.org/projects/lwip) is used for tcp/ip stack. 
[mbedtls](https://tls.mbed.org) is used for ssl/tls implementation. 
The documentation for the functions have been written in the respective header files. 
An example has been included with lan.c. Source code for other libraries have not been included.

This is my first attempt to contribute, so let me know if I need to add further documentation or in case of any encountered bugs.