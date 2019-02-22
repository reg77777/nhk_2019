


























.build/mega2560/src/ps3.o : src/ps3.cpp
	@echo [93msrc/ps3.cpp[0m
	@mkdir -p .build/mega2560/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/mega -fno-exceptions  -o $@ -c src/ps3.cpp
include .build/mega2560/src/ps3.d

.build/mega2560/src/dog.o : src/dog.cpp
	@echo [93msrc/dog.cpp[0m
	@mkdir -p .build/mega2560/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/mega -fno-exceptions  -o $@ -c src/dog.cpp
include .build/mega2560/src/dog.d

.build/mega2560/src/omni.o : src/omni.cpp
	@echo [93msrc/omni.cpp[0m
	@mkdir -p .build/mega2560/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/mega -fno-exceptions  -o $@ -c src/omni.cpp
include .build/mega2560/src/omni.d

.build/mega2560/src/sensor.o : src/sensor.cpp
	@echo [93msrc/sensor.cpp[0m
	@mkdir -p .build/mega2560/src
	@/usr/share/arduino/hardware/tools/avr/bin/avr-g++ -mmcu=atmega2560 -DF_CPU=16000000L -DARDUINO=105 -I/usr/share/arduino/hardware/arduino/cores/arduino -ffunction-sections -fdata-sections -g -Os -w -I/usr/share/arduino/hardware/arduino/variants/mega -fno-exceptions  -o $@ -c src/sensor.cpp
include .build/mega2560/src/sensor.d







.build/mega2560/firmware.elf : .build/mega2560/src/ps3.o .build/mega2560/src/dog.o .build/mega2560/src/omni.o .build/mega2560/src/sensor.o
	@echo [92mLinking firmware.elf[0m
	@/usr/share/arduino/hardware/tools/avr/bin/avr-gcc -mmcu=atmega2560 -Wl,-Os -Wl,--gc-sections -o $@ $^ -lm


.build/mega2560/firmware.hex : .build/mega2560/firmware.elf
	@echo [92mConverting to firmware.hex[0m
	@/usr/share/arduino/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom $^ $@

include .build/mega2560/src/dependencies.d

all : .build/mega2560/firmware.hex
	@true

