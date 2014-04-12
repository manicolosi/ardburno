#include <Arduino.h>
#include <stdint.h>

#include "address_bus.h"
#include "data_bus.h"

uint8_t eeprom_read_byte(uint16_t address) {
  data_bus_input();

  address_bus_set(address);

  return data_bus_read();
}

void eeprom_write_byte(uint16_t address, uint8_t data) {
  data_bus_output();

  address_bus_set(address);

  data_bus_write(data);
}
