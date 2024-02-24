#include "lwip/apps/httpd.h"
#include "pico/cyw43_arch.h"
#include "pin_number.h"

// CGI handler which is run when a request for /led.cgi is detected
const char * cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[])
{
    // Check if an request for LED has been made (/led.cgi?led=x)
    if (strcmp(pcParam[0] , "led") == 0){
        // Look at the argument to check if LED is to be turned on (x=1) or off (x=0)
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
    
    // Send the index page back to the user
    return "/index.shtml";
}

// tCGI Struct
// Fill this with all of the CGI requests and their respective handlers
static const tCGI cgi_handlers[] = {
    {
        // Html request for "/led.cgi" triggers cgi_handler
        "/led.cgi", cgi_led_handler
    },
};

void cgi_init(void)
{
    http_set_cgi_handlers(cgi_handlers, 1);
}