#ifndef CL_ALLOW_L3
/*! 
 * \file      use_cases.c
 * \brief     Sablony zakladnych pripadov uzitia pre moju kniznicu
 * \details   
 * Tento subor obsahuje kostry aplikacii vyuzivajucich kniznicu pre spravu kontextu
 * na plnenie roznych funkcii. Aplikacie je mozne v tomto simulovanom prostredi spustit,
 * ale sluzia najma ako zaklad pre implementaciu na realnych mikrokontroleroch.
 * \author    Michal Zidzik
 * \date      21.03.2026
 * \note Aplikacie vyuzivaju pseudo port z adresara \c platform/posix
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "context_manager.h"
#include "tests_helper.h"
#include "use_cases.h"

/*!
* \brief Periferie na MCU, ktore sa striedavo vypinaju a zapinaju
* 
* MCU obsahuje sadu periferii. Ak tieto periferie nevyuzivame, mozeme ulozit ich 
* konfiguraciu a odpojit ich od napajania. Pri ich naslednom pripojeni sa konfiguracia
* naspat nacita.
* 
* Aplikacia na realnom MCU bude vyzerat velmi podobne
*/
void use_case1()
{
    // inicializuje kniznicu
    cl_init();
    // chrani dane periferie
    cl_protect_memory(10);
    cl_protect_memory(202);  // I2C
    cl_protect_memory(203); // TIMER
    cl_protect_memory(204); // GPIO

    // naplni periferie nejakymi hodnotami
    // pri skutocnej aplikacii to bude konfiguracia periferii
    i2c0_fill();
    timer0_fill();
    gpio_fill();

    // tu moze prebiehat praca s periferiami
    //usleep(10000000);

    // skoncilo vysielanie cez I2C
    // oznami kniznici ze dojde k vypnutiu I2C
    cl_area_off(202,NULL);
    // simuluje odpojenie I2C od napajania
    i2c0_clear();
    print_i2c0_regs();

    // prechod do nizkoprikonoveho rezimu tu sposobi vypnutie periferii
    cl_change_mode(CL_VLLS,NULL);
    
    // simuluje odpojenie pamate
    // tu by bol realny program na prejdenie do LP rezimu
    registers_clear();
    lram_clear();
    
    // mcu je v LP rezime
    usleep(1000);

    // tu by sa MCU prebudilo z LP rezimu

    // oznamenie pre kniznicu ze doslo k prebudeni
    cl_change_mode(CL_RUN,NULL);

    print_i2c0_regs(); // neobsahuje konfiguraciu: i2c bolo vypnute
    print_timer0_regs(); // obsahuje konfiguraciu
    print_gpio_regs(); // obsahuje konfiguraciu
   
    // start i2c rozhrania
    cl_area_on(202,NULL); // oznamenie pre kniznicu ze i2c bolo zapnute
    print_i2c0_regs(); // obsahuje konfiguraciu
}

/*!
* \brief Periferie mimo MCU, ktore sa striedavo vypinaju a zapinaju
* 
* K MCU prepojime externe moduly (ADC,senzor, displej...). Podobne ako v prvom 
* pripade maju tieto moduly nejaku konfiguraciu, ktoru do nich nahrame.
* 
* Rozdiel oproti prvemu pripadu je v pouziti inej low-level funkcie pre citanie a 
* zapis dat. use_case2 by vyzeral vpodstate totozne ako 1, preto ho otestujem az
* na realnom MCU
* 
*/
void use_case2()
{
}

/*!
* V pamati RAM mam ulozene nejake podstatne data: Napriklad pocitam priemer, minimum, maximum
* dat zo senzoru. Tieto udaje si chcem zapamatat ked z nejakeho dovodu vypnem MCU. Napriklad
* kazdych 10s zapnem senzor, nacitam 5 serii dat, vyratam priemer, minimum maximum a MCU zase vypnem
*
*/

void use_case3()
{
    cl_init();
    cl_protect_memory(105);

    // HRAM + 50 oznacuje zaciatok chraneneho bloku pamate
    // viz. context_lib_port.c
    int *sensor_d = (int *)(HRAM + 50);
    srand(time(NULL));   

    int avg = 0;
    int min = 101;
    int max = 0;
    int sum = 0;
    int num = 0;
    // desat serii 'merania'
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            // jedno 'meranie'
            int val = rand() % 100;
            if (val < min) min = val;
            if (val > max) max = val;
            sum += val;
            num++;
        }

        avg = sum / num;
        // ulozenie dat;
        sensor_d[0] = avg;
        sensor_d[1] = max;
        sensor_d[2] = min;
        sensor_d[3] = num;   

        printf("BEFORE SLEEP: avg=%d max=%d min=%d\n",
               sensor_d[0], sensor_d[1], sensor_d[2]);
        // kniznica uklada kontext
        cl_change_mode(CL_VLLS, NULL);

        // simulacia spanku
        hram_clear();
        sleep(10); 
        printf("SLEEP avg=%d max=%d min=%d\n",
               sensor_d[0], sensor_d[1], sensor_d[2]);

        // simulacia prebudenia
        cl_change_mode(CL_RUN, NULL);
        printf("AFTER WAKE avg=%d max=%d min=%d\n\n",
               sensor_d[0], sensor_d[1], sensor_d[2]);
        // obnova nacitanych dat
        num = sensor_d[3];
        sum = sensor_d[0] * num;
        max  = sensor_d[1];
        min = sensor_d[2];
    }
}

/*!
* \brief Ulozenie velkej casti pamate do externeho uloziska
*
* Podobne ako use case 3 ale s vyuzitim externeho uloziska. Implementujem
* az na realnom MCU ked budem mat k dispozicii externu pamat
*/
void use_case4()
{
}

int main()
{
    use_case1();
    //use_case3();
    return 0;
}

#else
int main()
{
    puts("use_cases\tDoes not work if Layer 3 is not allowed");
}
#endif