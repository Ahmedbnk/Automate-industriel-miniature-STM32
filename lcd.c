#define LCD_ADDR (0x27 << 1)
extern I2C_HandleTypeDef hi2c1;
static void lcd_send(uint8_t data) {
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, &data, 1, 100);
}

static void lcd_pulse(uint8_t d) {
    lcd_send(d | 0x04); HAL_Delay(1);
    lcd_send(d & ~0x04); HAL_Delay(1);
}

static void lcd_nibble(uint8_t n, uint8_t rs) {
    lcd_pulse((n & 0xF0) | 0x08 | rs);
}

void lcd_char(uint8_t ch) {
    lcd_nibble(ch, 0x01);
    lcd_nibble(ch << 4, 0x01);
}

void lcd_print(const char *s) {
    while (*s) lcd_char((uint8_t)*s++);
}

void lcd_putnbr(int n) {
    if (n == -2147483648) {
        lcd_print("-2147483648");
        return;
    }
    if (n < 0) {
        lcd_char('-');
        n = -n;
    }

    if (n >= 1000000000) lcd_char('0' + (n / 1000000000) % 10);
    if (n >= 100000000)  lcd_char('0' + (n / 100000000)  % 10);
    if (n >= 10000000)   lcd_char('0' + (n / 10000000)   % 10);
    if (n >= 1000000)    lcd_char('0' + (n / 1000000)    % 10);
    if (n >= 100000)     lcd_char('0' + (n / 100000)     % 10);
    if (n >= 10000)      lcd_char('0' + (n / 10000)      % 10);
    if (n >= 1000)       lcd_char('0' + (n / 1000)       % 10);
    if (n >= 100)        lcd_char('0' + (n / 100)        % 10);
    if (n >= 10)         lcd_char('0' + (n / 10)         % 10);
    lcd_char('0' + (n % 10));
}
extern I2C_HandleTypeDef hi2c1;

void lcd_cmd(uint8_t cmd) {
    lcd_nibble(cmd, 0);
    lcd_nibble(cmd << 4, 0);
}



void lcd_cursor(uint8_t col, uint8_t row) {
    lcd_cmd(0x80 | (col + (row ? 0x40 : 0x00)));
}



// void lcd_print_distance(float d) {
//     if (d < 0) {
//         lcd_print("  No object     ");
//         return;
//     }
//     int n = (int)(d * 10);
//     char buf[16] = "               ";
//     buf[2] = '0' + (n / 1000) % 10;
//     buf[3] = '0' + (n / 100)  % 10;
//     buf[4] = '0' + (n / 10)   % 10;
//     buf[5] = '.';
//     buf[6] = '0' + (n % 10);
//     buf[7] = ' ';
//     buf[8] = 'c';
//     buf[9] = 'm';
//     buf[15] = '\0';
//     lcd_print(buf);
// }
void lcd_print_distance(float d) {
    if (d < 0) {
        lcd_print("  No object     ");
        return;
    }

    int n = (int)(d * 10);  // e.g. 253.7cm → 2537

    int hundreds = (n / 1000) % 10;  // 2
    int tens     = (n / 100)  % 10;  // 5
    int units    = (n / 10)   % 10;  // 3
    int decimal  = (n % 10);         // 7

    // lcd_char(' ');
    // lcd_char(' ');

    // skip leading zeros
    if (hundreds > 0)
        lcd_char('0' + hundreds);
    else
        lcd_char(' ');

    if (tens > 0 || hundreds > 0)
        lcd_char('0' + tens);
    else
        lcd_char(' ');

    lcd_char('0' + units);
    lcd_char('.');
    lcd_char('0' + decimal);
    lcd_char(' ');
    lcd_char('c');
    lcd_char('m');
    // lcd_char(' ');
    // lcd_char(' ');
    // lcd_char(' ');
    // lcd_char(' ');
    // lcd_char(' ');
}
void lcd_init(void) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_I2C1_CLK_ENABLE();

    GPIO_InitTypeDef g = {0};
    g.Pin   = GPIO_PIN_6 | GPIO_PIN_7;
    g.Mode  = GPIO_MODE_AF_OD;
    g.Pull  = GPIO_PULLUP;
    g.Speed = GPIO_SPEED_FREQ_LOW;
    g.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &g);

    hi2c1.Instance             = I2C1;
    hi2c1.Init.ClockSpeed      = 100000;
    hi2c1.Init.DutyCycle       = I2C_DUTYCYCLE_2;
    hi2c1.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hi2c1);

    HAL_Delay(50);
    lcd_nibble(0x30, 0); //HAL_Delay(5);
    lcd_nibble(0x30, 0); //HAL_Delay(1);
    lcd_nibble(0x30, 0); //HAL_Delay(1);
    lcd_nibble(0x20, 0);
    lcd_cmd(0x28);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);
    //lcd_cmd(0x01); HAL_Delay(2);

}
