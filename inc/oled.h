//GPIO B
#define OLED_SCLK 12
#define OLED_MOSI 15
#define OLED_SS 13

void generic_lcd_startup(void);
void initOLED(void);
void setupPorts(void);
void display1(const char *s);
void display2(const char *s);
void nano_wait(unsigned int n);
void spi_cmd(char b);
