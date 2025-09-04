//lcd.h
void init_lcd(void);
void write_lcd(unsigned char);
void cmd_lcd(unsigned char);
void char_lcd(unsigned char);
void str_lcd(const char *p);
void u32LCD(int);
