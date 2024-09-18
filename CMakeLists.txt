set(CORE_SRCS
  cores/esp32/esp32-hal-cpu.c
  cores/esp32/esp32-hal-gpio.c
  cores/esp32/esp32-hal-i2c.c
  cores/esp32/esp32-hal-matrix.c
  cores/esp32/esp32-hal-misc.c
  cores/esp32/esp32-hal-spi.c
  )

set(LIBRARY_SRCS
  libraries/SPI/src/SPI.cpp
  libraries/Wire/src/Wire.cpp
  )


set(includedirs
  variants/esp32/
  cores/esp32/
  libraries/SPI/src
  libraries/Wire/src
  )

set(srcs ${CORE_SRCS} ${LIBRARY_SRCS} ${BLE_SRCS})
set(requires spi_flash mbedtls wifi_provisioning driver)
set(priv_requires nvs_flash bootloader_support espcpputils)

idf_component_register(INCLUDE_DIRS ${includedirs} PRIV_INCLUDE_DIRS ${priv_includes} SRCS ${srcs} REQUIRES ${requires} PRIV_REQUIRES ${priv_requires})
set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 23)

if(IDF_TARGET STREQUAL "esp32")
target_compile_options(${COMPONENT_TARGET} PUBLIC -DARDUINO=10812 -DARDUINO_ESP32_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD="ESP32_DEV" -DARDUINO_VARIANT="esp32" -DESP32)
endif()
if(IDF_TARGET STREQUAL "esp32s2")
target_compile_options(${COMPONENT_TARGET} PUBLIC -DARDUINO=10812 -DARDUINO_ESP32S2_DEV -DARDUINO_ARCH_ESP32 -DARDUINO_BOARD="ESP32S2_DEV" -DARDUINO_VARIANT="esp32s2" -DESP32)
endif()
