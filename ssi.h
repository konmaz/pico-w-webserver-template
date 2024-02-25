#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "hardware/adc.h"

// SSI tags - tag length limited to 8 bytes by default
const char * ssi_tags[] = {"temp","timeup"};

u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {
  size_t printed;
  switch (iIndex) {
  case 0: // temp
    {
    const float voltage = adc_read() * 3.3f / (1 << 12);
    const float tempC = 27.0f - (voltage - 0.706f) / 0.001721f;
    printed = snprintf(pcInsert, iInsertLen, "%.2f", tempC);
    }
    break;
  case 1: // timeup
    {
        uint32_t uptime_micros = time_us_32();
        
        // Convert microseconds to seconds
        uint32_t uptime_seconds = uptime_micros / 1000000;
        
        // Calculate hours, minutes, and remaining seconds
        uint32_t uptime_hours = uptime_seconds / 3600;
        uint32_t uptime_minutes = (uptime_seconds % 3600) / 60;
        uint32_t remaining_seconds = uptime_seconds % 60;


      printed = snprintf(pcInsert, iInsertLen, "%lu:%02lu:%02lu", uptime_hours, uptime_minutes, remaining_seconds);
    }
    break;
  default:
    printed = 0;
    break;
  }

  return (u16_t)printed;
}

// Initialise the SSI handler
void ssi_init() {
  // Initialise ADC (internal pin)
  adc_init();
  adc_set_temp_sensor_enabled(true);
  adc_select_input(4);

  http_set_ssi_handler(ssi_handler, ssi_tags, LWIP_ARRAYSIZE(ssi_tags));
}
