// * FILENAME:           NokiaLCD.c 
// * DESCRIPTION:
//   Functions declarations of the prototypes in NokiaLCD.h
//   C file contains a reusable driver for Nokia LCD 
//   Middle layer APIs interfaces Nokia LCD, built on the lower
//   layer APIs of the SPI device of the TM4C123 ucontroller
// * AUTHOR:
//   ABDULMAGUID EISSA
// See initializations of SPI in SPI.c and intializations of 
// the LCD in Sparkfun datasheet.

#include <stdint.h>
#include <stdbool.h>

#include "tm4c123gh6pm.h"
#include "nokialcd.h"
#include "main.h"
#include "port.h"

// ************* static data declarations **************
uint8_t static screen_buf[(LCD_MAX_X * LCD_MAX_Y) / 8];

// ************* private functions declarations **************
bool static
bitmap_parameter_check(uint32_t x_pos, uint32_t y_pos, 
	                   uint32_t height, uint32_t width,
	                   uint8_t* threshold);

// ************* nokialcd_write **************
// follow the recommnded procesure by the manfacturer data sheet
// for sending a command to the LCD.
void
NOKIALCD_write(write_t type, uint8_t message) {
	if (type == COMMAND) {
		while ((SSI_STATUS_R & SSI_SR_BSY) == SSI_SR_BSY) {}; // Wait until SSI isn’t busy
		DC = LCD_COMMAND;                                 // Acknowledge LCD command
		SSI_DATA_R = message;                             // Send the commmand
		while ((SSI_STATUS_R & SSI_SR_BSY) == SSI_SR_BSY) {};
	}
	else {
		while (!(SSI_STATUS_R & SSI_SR_TNF)) {};            // Wait till transmission FIFO not full
		DC = LCD_DATA;
		SSI_DATA_R = message;                           // Send the data.
	}
}


// ************* nokialcd_init **************
// NOTE: See LCD datasheet for explanation of the commmand
// values sent to the display in the setup.
// Values can be changed for different performance.
// Refer to Main.h for defined values.
// Refer to Port.h for defined registers.
void 
NOKIALCD_init(void){
	volatile uint8_t delay;

	SPI_init();                            // Initiate the SPI
	RESET = RESET_LOW;                     // Reset trigger

	for(delay = 0; delay < 10; delay++);   // wait about 100 ns

	RESET = RESET_HIGH;
	// Setting up the LCD configuration using command mode
	NOKIALCD_write(COMMAND, FUNCTION_SET); 
	NOKIALCD_write(COMMAND, V_OPERATION);
	NOKIALCD_write(COMMAND, TEMP_COEFF);
	NOKIALCD_write(COMMAND, BIAS_MOD);
	NOKIALCD_write(COMMAND, PRE_CTRL);
	NOKIALCD_write(COMMAND, DISP_CTRL);
}


// ************* nokialcd_send_char **************
void 
NOKIALCD_send_char(uint8_t ch){
	uint8_t i;

	NOKIALCD_write(DATA, BLANK);    // Blank padding the LCD

	for (i = 0; i < 5; i++) {
		NOKIALCD_write(DATA, ASCII[ch - 32][i]);
	}
	NOKIALCD_write(DATA, BLANK);    // Blank padding the LCD
}

// ************* nokialcd_send_string **************
void 
NOKIALCD_send_string(uint8_t *string){
	while(*string){
		NOKIALCD_send_char((uint8_t)*string);
		string = string + 1;
	}
}

// ************* nokialcd_set_cursor **************
// Coordinates must be as specified in the datasheet
// 0 <= x <= 11
// 0 <= y <= 5
void 
NOKIALCD_set_cursor(uint8_t x_position, uint8_t y_position){
	if (x_position > 11 || y_position > 5) {
		return;
	}
	NOKIALCD_write(COMMAND, X_POSITION | x_position * 7);  // Character is 7 columns wide
	NOKIALCD_write(COMMAND, Y_POSITION | y_position);
}

// ************* nokialcd_clear **************
// Clear the entire screen by writing zeros and setting 
// the cursor to 0 for x and y positions.
void 
NOKIALCD_clear(void) {
	uint16_t byte;

	for (byte = 0; byte < ((LCD_MAX_X * LCD_MAX_Y) / 8); byte++) {
		NOKIALCD_write(DATA, BLANK);
	}
	NOKIALCD_set_cursor(0, 0);
}

// ************* nokialcd_draw_image **************
void 
NOKIALCD_draw_image(const uint8_t* p_image) {
	uint16_t byte;

	NOKIALCD_set_cursor(0, 0);

	for (byte = 0; byte < ((LCD_MAX_X * LCD_MAX_Y) / 8); byte++) {
		NOKIALCD_write(DATA, p_image[byte]);
	}
}

// ************* nokialcd_print_bitmap **************
void
NOKIALCD_print_bitmap(uint8_t x_pos, uint8_t y_pos,
					  const uint8_t* p_bitmap, uint8_t threshold) 
{
	uint32_t height = p_bitmap[18];
	uint32_t width  = p_bitmap[22];
	uint32_t byte;
	uint32_t pixel;
	uint16_t screen_x;
	uint16_t screen_y;
	uint8_t  mask;
	bool     check;

	check = bitmap_parameter_check(x_pos, y_pos, height, width, &threshold);

	if (check == false) {
		return;
	}
	// bitmaps are encoded backwards, so start at the bottom left corner of the image
	screen_y = y_pos / 8;
	screen_x = x_pos + LCD_MAX_X * screen_y;
	mask     = y_pos % 8;    // rows 0 to 7
	mask     = 0x01 << mask; // now stores a mask 0x01 to 0x80
	byte     = p_bitmap[10];

	for (pixel = 1; pixel <= ((height * width) / 2); pixel++) {
		if (((p_bitmap[byte] >> 4) & 0xF) > threshold) {       // the upper 4 bits
			screen_buf[screen_x] |= mask;
		}
		else {
			screen_buf &= ~mask;
		}
		screen_x++;

		if ((p_bitmap[byte] & 0xF) > threshold) {       // the lower 4 bits
			screen_buf[screen_x] |= mask;
		}
		else {
			screen_buf &= ~mask;
		}
		screen_x++;
		byte++;

		if ((pixel % (width / 2)) == 0) {
			if (mask > 0x01) {
				mask >>= 1;
			}
			else {
				mask = 0x80;
				screen_y--;
			}
			screen_x = x_pos + LCD_MAX_X * screen_y;
			switch ((width / 2) % 4) {
				case 0:
					byte = byte + 0;
				break;
				case 1:
					byte = byte + 3;
				break;
				case 2:
					byte = byte + 2;
				break;
				case 3:
					byte = byte + 1;
				break;
				default:
				break;
			}
		}
	}
}

// ************* nokialcd_clear_buf **************
void 
NOKIALCD_clear_buf(void){
	uint16_t byte;

	for ( byte = 0; byte < (LCD_MAX_X * LCD_MAX_Y) / 8; byte++){
		screen_buf[byte] = 0;
	}
}

// ************* nokialcd_display_buf **************
void 
NOKIALCD_display_buf(void){
	NOKIALCD_draw_image(screen_buf);
}


// ************* private functions definitions **************
bool static
bitmap_parameter_check(uint32_t x_pos, uint32_t y_pos,
	uint32_t height, uint32_t width,
	uint8_t* threshold) 
{
	if ((height <= 0) ||
		(width % 2 != 0) ||
		((x_pos + width) > LCD_MAX_X) ||
		(y_pos < (height - 1)) ||
		(y_pos > LCD_MAX_Y)) {
		return false;
	}
	if ((*threshold) > 14) {
		*threshold = 14;
	}
	return true;
}

// ************* END OF NOKIA LCD FILE *************

