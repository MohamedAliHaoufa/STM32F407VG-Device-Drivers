/**
 * @file 0017rtc_lcd.c
 * @author Mohamed Ali Haoufa
 * @brief
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */


#include "../bsp/ds1307.h"
#include "../bsp/lcd.h"

#define SYSTICK_TIM_CLK		16000000UL // 16MHZ (Prescaler is 1 by default) = source clock

/* Enable this macro if you want to test RTC on LCD or comment it if you want to test with print-f */
#define PRINT_LCD

/*
#ifndef PRINT_LCD
	//printf command
#else
	//LCD command
#endif
*/

static void mdelay(uint32_t cnt){
	for(uint32_t i ; i < (cnt*1000); i++);
}

void init_systick_timer(uint32_t tick_hz)
{
	uint32_t *pSTRVR = (uint32_t*)0xE000E014; // SYST_RVR / RW / SysTick Reload Value Register
	uint32_t *pSTCSR = (uint32_t*)0xE000E010; // SYST_CSR / RW / SysTick Control and Status Register

	/*
	 * 0.0625 us (this much time required) --> for 1 single down counting
	 * 1 s (this much time required) --> for how much counting ??
	 *
	 * counter = 1s / (0.0625 * 10^-6) = 16MHZ/1HZ = 16*10^6/1 = 16 million counting
	 * SYSTICK_TIM_CLK/ tick = modify tick to increase the number of interrupts in one second
	 */

    /* calculation of reload value */
    uint32_t count_value = (SYSTICK_TIM_CLK/tick_hz)-1; // if tick_hz = 10 means 10 interrupt for every one second

    //Clear the value of SYST_RVR
    *pSTRVR &= ~(0x00FFFFFFFF);

    //load the value in to SYST_RVR
    *pSTRVR |= count_value;

    //do some settings in to SYST_CSR
    *pSTCSR |= ( 1 << 1); //Enables SysTick exception request:
    *pSTCSR |= ( 1 << 2);  //Indicates the clock source, processor clock source

    //enable the systick
    *pSTCSR |= ( 1 << 0); //enables the counter

}

char* get_day_of_week(uint8_t i) {

	char*  days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	return days[i-1];
}


void number_to_string(uint8_t num, char* buf){

	if(num < 10){
		buf[0] = '0';
		buf[1] = num + 48;
	} else if (num >= 10 && num < 99) {
		buf[0] = (num / 10) + 48;
		buf[1] = (num % 10) + 48;
	}
}

// hh:mm:ss
char* time_to_string(RTC_time_t *rtc_time){

	static char buf[9]; // static to not become a dangling pointer

	buf[2] = ':';
	buf[5] = ':';
	number_to_string(rtc_time->hours, &buf[0]);
	number_to_string(rtc_time->minutes, &buf[3]);
	number_to_string(rtc_time->seconds, &buf[6]);

	buf[8] = '\0';

	return buf;
}

// dd/mm/yy
char* date_to_string(RTC_date_t *rtc_date){

	static char buf[9]; // static to not become a dangling pointer

	buf[2] = '/';
	buf[5] = '/';
	number_to_string(rtc_date->date, &buf[0]);
	number_to_string(rtc_date->month, &buf[3]);
	number_to_string(rtc_date->year, &buf[6]);

	buf[8] = '\0';

	return buf;
}

int main(void){

	RTC_time_t current_time;
	RTC_date_t current_date;

#ifndef PRINT_LCD
	printf("RTC test...\n");
#else
	lcd_init();

	lcd_print_string("RTC Test...");

	mdelay(2000); // 2 seconds

	lcd_display_clear();
	lcd_display_return_home();
#endif

	// check if the CH is 0, if yes
	if (ds1307_init()){
		printf("RTC init has failed\n");
		while(1);
	}

	init_systick_timer(1);

	// initialize the current date
	current_date.day = FRIDAY;
	current_date.date = 15;
	current_date.month = 1;
	current_date.year = 21;

	// initialize the current time
	current_time.hours = 11;
	current_time.minutes = 59;
	current_time.seconds = 30; // 30seconds only and it'll change from PM to AM and to the next day too "Saturday"
	current_time.time_format = TIME_FORMAT_12HRS_PM;

	ds1307_set_current_date(&current_date);
	ds1307_set_current_time(&current_time);

	ds1307_get_current_date(&current_date);
	ds1307_get_current_time(&current_time);

	char *am_pm;

	if (current_time.time_format != TIME_FORMAT_24HRS){
		am_pm = (current_time.time_format) ? "PM" : "AM";
#ifndef PRINT_LCD
		printf("Current time = %s %s", time_to_string(&current_time),am_pm); //04:25:01 PM or AM
#else
		lcd_print_string(time_to_string(&current_time));
		lcd_print_string(am_pm);
#endif

	} else {
#ifndef PRINT_LCD
		printf("Current time = %s", time_to_string(&current_time)); //04:25:01
#else
		lcd_print_string(time_to_string(&current_time));
#endif
	}

#ifndef PRINT_LCD
	printf("Current date = %s <%s>", date_to_string(&current_date),get_day_of_week(current_date.day)); //15/01/21 <FRIDAY>
#else
	lcd_set_cursor(2, 1);
	lcd_print_string(date_to_string(&current_date));
	lcd_print_char('<');
	lcd_print_string(get_day_of_week(current_date.day)); // make a shotcuts for day of the week to fit the LCD like: Sunday = Sun
	lcd_print_char('>');
#endif

	while(1);

	return 0;
}

void SysTick_Handler(void){

	RTC_time_t current_time;
	RTC_date_t current_date;

	ds1307_get_current_time(&current_time);



	char *am_pm;

	if (current_time.time_format != TIME_FORMAT_24HRS){

		am_pm = (current_time.time_format) ? "PM" : "AM";
#ifndef PRINT_LCD
		printf("Current time = %s %s", time_to_string(&current_time),am_pm); //04:25:01 PM or AM
#else
		lcd_set_cursor(1, 1);
		lcd_print_string(time_to_string(&current_time));
		lcd_print_string(am_pm);
#endif

	} else {
#ifndef PRINT_LCD
		printf("Current time = %s", time_to_string(&current_time)); //04:25:01
#else
		lcd_print_string(time_to_string(&current_time));
#endif

	}

	ds1307_get_current_date(&current_date);

#ifndef PRINT_LCD
	printf("Current date = %s <%s>", date_to_string(&current_date),get_day_of_week(current_date.day)); //15/01/21 <FRIDAY>
#else
	lcd_set_cursor(2, 1);
	lcd_print_string(date_to_string(&current_date));
	lcd_print_char('<');
	lcd_print_string(get_day_of_week(current_date.day));
	lcd_print_char('>');
#endif

}

