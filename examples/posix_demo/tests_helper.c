
#include "context_manager.h"
#include "tests_helper.h"

void lram_clear()
{
    cl_int_t i;
    for (i = 0; i < 1024; i++){
        LRAM[i] = 0;
    }
}

void hram_clear()
{
    cl_int_t i;
    for (i = 0; i < 1024; i++){
        HRAM[i] = 0;
    }
}

void rf_clear()
{
    cl_int_t i;
    for (i = 0; i < 128; i++){
        REGISTER_FILE[i] = 0;
    }
}

void outside1_clear()
{
    cl_int_t i;
    for (i = 0; i < 256; i++){
        OUTSIDE1[i] = 0;
    }
}

void outside2_clear()
{
    cl_int_t i;
    for (i = 0; i < 256; i++){
        OUTSIDE2[i] = 0;
    }
}

void flash_clear()
{
    cl_int_t i;
    for (i = 0; i < 1024; i++){
        FLASH[i] = 0;
    }
}

void gpio_clear()
{
    cl_int_t i;
    for (i = 0; i < 16; i++){
        GPIO_REGS[i] = 0;
    }
}   

void uart0_clear()
{
    cl_int_t i;
    for (i = 0; i < 8; i++){
        UART0_REGS[i] = 0;
    }
}

void spi0_clear()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        SPI0_REGS[i] = 0;
    }
}

void i2c0_clear()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        I2C0_REGS[i] = 0;
    }
} 

void timer0_clear()
{
    cl_int_t i;
    for (i = 0; i < 10; i++){
        TIMER0_REGS[i] = 0;
    }
}

void registers_clear()
{
    gpio_clear();
    uart0_clear();
    spi0_clear();
    i2c0_clear();
    timer0_clear();
}

void clear_all()
{
    lram_clear();
    hram_clear();
    rf_clear();
    outside1_clear();
    outside2_clear();
    flash_clear();
    gpio_clear();
    uart0_clear();
    spi0_clear();
    i2c0_clear();
    timer0_clear();
}

void uart0_fill()
{
    cl_int_t i;
    for (i = 0; i < 8; i++){
        UART0_REGS[i] = 2000 + i;
    }
}

void spi0_fill()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        SPI0_REGS[i] = 2010 + i;
    }
}

void i2c0_fill()
{
    cl_int_t i;
    for (i = 0; i < 6; i++){
        I2C0_REGS[i] = 2020 + i;
    }
}

void timer0_fill()
{
    cl_int_t i;
    for (i = 0; i < 10; i++){
        TIMER0_REGS[i] = 2030 + i;
    }
}

void gpio_fill()
{
    cl_int_t i;
    for (i = 0; i < 16; i++){
        GPIO_REGS[i] = 2040 + i;
    }
}

void registers_fill()
{
    uart0_fill();
    spi0_fill();
    i2c0_fill();
    timer0_fill();
    gpio_fill();
}

void hram_fill1()
{
    cl_int_t i,j,k;
    cl_int_t arr1[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    for(i = 0; i < 5; i++){
        HRAM[i] = arr1[i];
    }
    for(i = 0; i < 5; i++){
        HRAM[i + 10] = arr1[i + 5];
    }
    for(i = 0; i < 5; i++){
        HRAM[i + 20] = arr1[i + 10];
    }
    for(i = 0; i < 6; i++){
        HRAM[i + 30] = arr1[i + 15];
    }
    for(i = 0; i < 7; i++){
        HRAM[i + 40] = arr1[i + 20];
    }
    for(i = 0; i < 4; i++){
        HRAM[i + 50] = arr1[i + 25];
    }
}

void lram_fill2(cl_int_t *array,cl_int_t start, cl_int_t elements)
{
    cl_int_t i;
    for (i = start; i < start + elements; i++){
        LRAM[i] = array[i];
    }
}

void hram_fill2(cl_int_t *array,cl_int_t start, cl_int_t elements)
{
    cl_int_t i;
    for (i = start; i < start + elements; i++){
        HRAM[i] = array[i];
    }
}

void print_lram(cl_int_t start_i,cl_int_t end_i)
{
    printf("LRAM[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",LRAM[i]);
    }
    printf("\n");
}

void print_hram(cl_int_t start_i,cl_int_t end_i)
{
    printf("HRAM[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",HRAM[i]);
    }
    printf("\n");
}

void print_rf(cl_int_t start_i,cl_int_t end_i)
{
    printf("REGISTER_FILE[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",REGISTER_FILE[i]);
    }
    printf("\n");
}

void print_rf2(cl_int_t start_i,cl_int_t end_i)
{
    printf("REGISTER_FILE2[%lu-%lu]:\n",start_i,end_i);
    cl_int_t i;
    for (i = start_i; i < end_i; i++){
        printf("%lu,",REGISTER_FILE2[i]);
    }
    printf("\n");
}

void print_uart0_regs()
{
    printf("UART0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 8; i++){
        printf("%lu,",UART0_REGS[i]);
    }
    printf("\n");
}

void print_spi0_regs()
{
    printf("SPI0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 6; i++){
        printf("%lu,",SPI0_REGS[i]);
    }
    printf("\n");
}

void print_i2c0_regs()
{
    printf("I2C0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 6; i++){
        printf("%lu,",I2C0_REGS[i]);
    }
    printf("\n");
}

void print_timer0_regs()
{
    printf("TIMER0_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 10; i++){
        printf("%lu,",TIMER0_REGS[i]);
    }
    printf("\n");
}

void print_gpio_regs()
{
    printf("GPIO_REGS:\n");
    cl_int_t i;
    for (i = 0; i < 16; i++){
        printf("%lu,",GPIO_REGS[i]);
    }
    printf("\n");
}

void registers_print()
{
    print_uart0_regs();
    print_spi0_regs();
    print_i2c0_regs();
    print_timer0_regs();
    print_gpio_regs();
}