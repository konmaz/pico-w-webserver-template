#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "pin_number.h"

// CGI handler which is run when a request for /power_button.cgi is detected
const char * cgi_power_button_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if an request for a power button pulse has been made
    if (strcmp(pcParam[0] , "duration") == 0){
        // Look at the argument to check the duration of the pulse (0=100ms) and (1=3500ms)
        if(strcmp(pcValue[0], "0") == 0){
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            
            // Set pin low
            gpio_put(PIN_NUMBER, 0);
            sleep_ms(100);
            // Set pin high
            gpio_put(PIN_NUMBER, 1);

            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
        else if(strcmp(pcValue[0], "1") == 0){
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            
            // Set pin low
            gpio_put(PIN_NUMBER, 0);
            sleep_ms(3500);
            // Set pin high
            gpio_put(PIN_NUMBER, 1);

            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        }
        
    }
    
    // Send an ok page as a reply
    return "/ok.shtml";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "/powerbutton.cgi" triggers cgi_handler
        "/power_button.cgi", cgi_power_button_handler
    },
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 1);
}