#ifndef LCD_COMMAND_H
# define LCD_COMMAND_H


#ifndef LCD_DIR
#error LCD_DIR: LCD data port direction should be defined
#endif
#ifndef LCD_PORT
#error LCD_PORT:LCD data port should be defined
#endif
#ifndef LCD_RS
#error LCD_RS:Register Select pin should be defined
#endif
#ifndef LCD_EN
#error LCD_EN:Enable signal should be defined
#endif



void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str);
void LCD_String_xy (char row, char pos, char *str);
void LCD_Clear();

#endif /* LCD_COMMAND_H */
