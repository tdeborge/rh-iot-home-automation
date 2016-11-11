//
//  home.h
//  
//
//  Created by Tim De Borger on 14/07/16.
//
//

#ifndef home_h
#define home_h

//When not looking at a serial monitor, it is better to disabel debugging
const boolean DEBUG = true;

//NNTP Server Address
IPAddress timeServerIP(129, 6, 15, 28);

//WIFI
const char* ssid = "TimAE";
const char* password = "progresssonic";

//MQTT
const int port = 1883;
char mqtt[] = "192.168.2.70";
IPAddress server(192, 168, 2, 71);

const char* mqtt_user = "admin";
const char* mqtt_password = "admin";

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//This controls if you subscribe to your own messages or not
const boolean loopBack = true;

//This is the timeout in ms for sending measuring information
unsigned long measureloop = 30000;

//Rate in ms for blinking in case the clock was not settable
unsigned long fatalNNTPblinkrate = 100;


uint8_t bender [] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 0xDF, 0x5F, 0x5F, 0x5F, 0x5F,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F,
    0x5F, 0xDF, 0xBF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0xF9, 0xFE, 0x07, 0x01, 0x00, 0x00, 0xF8, 0xFE, 0xFF,
    0xFF, 0xFF, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF, 0xFE, 0xFC, 0xF8, 0xF0, 0xE0, 0x00, 0x00, 0x00, 0x00,
    0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0x1F, 0x1F, 0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF8,
    0x00, 0x00, 0x01, 0x07, 0xFE, 0xF9, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF9, 0xE7, 0xDC, 0xB0, 0xA0, 0x40, 0x41, 0x47, 0x4F,
    0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x4F, 0x47, 0x43, 0x40, 0x40, 0x40, 0x40,
    0x43, 0x47, 0x4F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x5F, 0x4F, 0x47, 0x43, 0x40,
    0x40, 0xA0, 0xB0, 0xDE, 0xE7, 0xF9, 0xFE, 0x1F, 0x0F, 0x07, 0x73, 0x79, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F,
    0xBF, 0x5F, 0xEF, 0x0F, 0xEF, 0xEF, 0xDF, 0xDF, 0x1F, 0xDF, 0xDF, 0xDF, 0xDF, 0x1F, 0xDF, 0xDF,
    0xDF, 0xDF, 0xDF, 0x1F, 0xDF, 0xDF, 0xDF, 0xEF, 0x0F, 0xEF, 0xDF, 0xBF, 0x7F, 0xFF, 0xFF, 0xFF,
    0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0xFF, 0xFF, 0xFF, 0xBE, 0x9C, 0xC0, 0xE0, 0xF0, 0xF9, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
    0xB7, 0x6F, 0xEE, 0x00, 0xDE, 0xDE, 0xDE, 0xDD, 0x00, 0xDD, 0xDD, 0xDD, 0xDD, 0x00, 0xDD, 0xDD,
    0xDD, 0xC5, 0xC1, 0x00, 0xC9, 0xC5, 0xC1, 0x01, 0xC8, 0xC4, 0x42, 0x80, 0xC0, 0xE8, 0xE4, 0xE2,
    0xE0, 0xE0, 0xEF, 0xEF, 0xE6, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFE, 0xFE, 0xFD, 0xFD, 0xFD, 0xFB, 0xF8, 0xFB, 0xFB, 0xFB, 0xFB, 0xF8, 0xFB, 0xFB,
    0xFB, 0xFB, 0xFB, 0xF8, 0xFB, 0xFD, 0xFD, 0xFC, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
};

unsigned char bulb_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000011, 0b11100000, //       #####
    0b00000100, 0b00010000, //      #     #
    0b00001000, 0b00001000, //     #       #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00001000, 0b00001000, //     #       #
    0b00000100, 0b00010000, //      #     #
    0b00000011, 0b11100000, //       #####
    0b00000010, 0b00100000, //       #   #
    0b00000011, 0b11100000, //       #####
    0b00000010, 0b00100000, //       #   #
    0b00000011, 0b11100000, //       #####
};

unsigned char bulb_on_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00100011, 0b11100010, //   #   #####   #
    0b00010100, 0b00010100, //    # #     # #
    0b00001000, 0b00001000, //     #       #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00010000, 0b00000100, //    #         #
    0b00001000, 0b00001000, //     #       #
    0b00010100, 0b00010100, //    # #     # #
    0b00100011, 0b11100010, //   #   #####   #
    0b00000010, 0b00100000, //       #   #
    0b00000011, 0b11100000, //       #####
    0b00000010, 0b00100000, //       #   #
    0b00000011, 0b11100000, //       #####
};

unsigned char bulb_off_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b11110000, //      #######
    0b00001111, 0b11111000, //     #########
    0b00011111, 0b11111100, //    ###########
    0b00011111, 0b11111100, //    ###########
    0b00011111, 0b11111100, //    ###########
    0b00011111, 0b11111100, //    ###########
    0b00011111, 0b11111100, //    ###########
    0b00001111, 0b11111000, //     #########
    0b00000100, 0b00010000, //      #     #
    0b00000011, 0b11100000, //       #####
    0b00000010, 0b00100000, //       #   #
    0b00000011, 0b11100000, //       #####
    0b00000010, 0b00100000, //       #   #
    0b00000011, 0b11100000, //       #####
};

unsigned char bullet_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000011, 0b10000000, //       ###
    0b00001111, 0b11100000, //     #######
    0b00001111, 0b11100000, //     #######
    0b00011111, 0b11110000, //    #########
    0b00011111, 0b11110000, //    #########
    0b00011111, 0b11110000, //    #########
    0b00001111, 0b11100000, //     #######
    0b00001111, 0b11100000, //     #######
    0b00000011, 0b10000000, //       ###
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};

unsigned char cancel_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00111000, 0b00001110, //   ###       ###
    0b00111100, 0b00011110, //   ####     ####
    0b00111110, 0b00111110, //   #####   #####
    0b00011111, 0b01111100, //    ##### #####
    0b00001111, 0b11111000, //     #########
    0b00000111, 0b11110000, //      #######
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b11110000, //      #######
    0b00001111, 0b11111000, //     #########
    0b00011111, 0b01111100, //    ##### #####
    0b00111110, 0b00111110, //   #####   #####
    0b00111100, 0b00011110, //   ####     ####
    0b00111000, 0b00001110, //   ###       ###
    0b00000000, 0b00000000, //
};

unsigned char check_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000111, //              ###
    0b00000000, 0b00001111, //             ####
    0b00000000, 0b00011111, //            #####
    0b01110000, 0b00111110, //  ###      #####
    0b01111000, 0b01111100, //  ####    #####
    0b01111100, 0b11111000, //  #####  #####
    0b00011111, 0b11110000, //    #########
    0b00001111, 0b11100000, //     #######     
    0b00000111, 0b11000000, //      #####      
    0b00000011, 0b10000000, //       ###       
    0b00000000, 0b00000000, //                 
    0b00000000, 0b00000000, //                 
};

unsigned char heart_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00111100, 0b01111000, //   ####   ####
    0b01111110, 0b11111100, //  ###### ######
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111110, // ###############
    0b01111111, 0b11111100, //  #############
    0b01111111, 0b11111100, //  #############
    0b00111111, 0b11111000, //   ###########
    0b00011111, 0b11110000, //    #########
    0b00001111, 0b11100000, //     #######
    0b00000111, 0b11000000, //      #####
    0b00000011, 0b10000000, //       ###
    0b00000001, 0b00000000, //    	  #
};

unsigned char nocon_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000011, 0b11100000, //       #####
    0b00001111, 0b11111000, //     #########
    0b00011111, 0b11111100, //    ###########
    0b00111110, 0b00111110, //   #####   #####
    0b00111000, 0b01111110, //   ###    ######
    0b01110000, 0b11111111, //  ###    ########
    0b01110001, 0b11110111, //  ###   ##### ###
    0b01110011, 0b11000111, //  ###  ####   ###
    0b01110111, 0b10000111, //  ### ####    ###
    0b00111111, 0b00001110, //   ######    ###
    0b00111110, 0b00011110, //   #####    ####
    0b00011111, 0b11111100, //    ###########
    0b00001111, 0b11111000, //     #########
    0b00000011, 0b11100000, //       #####
    0b00000000, 0b00000000, //
};
unsigned char tool_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b01100000, //          ##
    0b00000000, 0b11100000, //         ###
    0b00000001, 0b11000000, //        ###
    0b00000001, 0b11000000, //        ###
    0b00000001, 0b11100110, //        ####  ##
    0b00000011, 0b11111110, //       #########
    0b00000111, 0b11111100, //      #########
    0b00001111, 0b11111000, //     #########
    0b00011111, 0b11000000, //    #######
    0b00111111, 0b10000000, //   #######
    0b01111111, 0b00000000, //  #######
    0b11111110, 0b00000000, // #######
    0b11111100, 0b00000000, // ######
    0b11111000, 0b00000000, // #####
    0b01110000, 0b00000000, //  ###
};

unsigned char plug_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000110, 0b01100000, //      ##  ##
    0b00000110, 0b01100000, //      ##  ##
    0b00000110, 0b01100000, //      ##  ##
    0b00000110, 0b01100000, //      ##  ##
    0b00111111, 0b11111100, //   ############
    0b00111111, 0b11111100, //   ############
    0b00111111, 0b11111100, //   ############
    0b00111111, 0b11111100, //   ############
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000111, 0b11100000, //      ######
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};

unsigned char powerbutton_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000001, 0b11000000, //        ###
    0b00001101, 0b11011000, //     ## ### ##
    0b00011101, 0b11011100, //    ### ### ###
    0b00111101, 0b11011110, //   #### ### ####
    0b00111001, 0b11001110, //   ###  ###  ###
    0b01110001, 0b11000111, //  ###   ###   ###
    0b01110001, 0b11000111, //  ###   ###   ###
    0b01110001, 0b11000111, //  ###   ###   ###
    0b01110000, 0b00000111, //  ###         ###
    0b00111000, 0b00001110, //   ###       ###
    0b00111110, 0b00011110, //   #####    ####
    0b00011111, 0b11111100, //    ###########
    0b00001111, 0b11111000, //     #########
    0b00000011, 0b11100000, //       #####
    0b00000000, 0b00000000, //
};

unsigned char wallplug_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b11111111, 0b11111111, // ################
    0b10000000, 0b00000001, // #              #
    0b10111111, 0b11111101, // # ############ #
    0b10100000, 0b00000101, // # #          # #
    0b10100000, 0b00000101, // # #          # #
    0b10100000, 0b00000101, // # #          # #
    0b10100000, 0b00000101, // # #          # #
    0b10100110, 0b01100101, // # #  ##  ##  # #
    0b10100110, 0b01100101, // # #  ##  ##  # #
    0b10100000, 0b00000101, // # #          # #
    0b10100000, 0b00000101, // # #          # #
    0b10100000, 0b00000101, // # #          # #
    0b10111111, 0b11111101, // # ############ #
    0b10000000, 0b00000001, // #              #
    0b11111111, 0b11111111, // ################
};

unsigned char wifi1_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000111, 0b11100000, //      ######
    0b00011111, 0b11111000, //    ##########
    0b00111111, 0b11111100, //   ############
    0b01110000, 0b00001110, //  ###        ###
    0b01100111, 0b11100110, //  ##  ######  ##
    0b00001111, 0b11110000, //     ########
    0b00011000, 0b00011000, //    ##      ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00000100, 0b00100000, //      #    #
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};

unsigned char wifi2_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000111, 0b11100000, //      ######
    0b00001111, 0b11110000, //     ########
    0b00011000, 0b00011000, //    ##      ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00000100, 0b00100000, //      #    #
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};

unsigned char clock_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b11110000, //      #######
    0b00001100, 0b00011000, //     ##     ##
    0b00011000, 0b00001100, //    ##       ##
    0b00110000, 0b00000110, //   ##         ##
    0b00110000, 0b00000110, //   ##         ##
    0b00110000, 0b11111110, //   ##    #######
    0b00110000, 0b10000110, //   ##    #    ##
    0b00110000, 0b10000110, //   ##    #    ##
    0b00011000, 0b10001100, //    ##   #   ##
    0b00001100, 0b00011000, //     ##     ##
    0b00000111, 0b11110000, //      #######
    0b00000011, 0b11100000, //       #####
    0b00000000, 0b00000000, //
};

unsigned char timer_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b11110000, //      #######
    0b00001100, 0b10011000, //     ##  #  ##
    0b00011000, 0b00111100, //    ##     ####
    0b00110000, 0b01110110, //   ##     ### ##
    0b00110000, 0b11100110, //   ##    ###  ##
    0b00111001, 0b11001110, //   ###  ###  ###
    0b00110000, 0b10000110, //   ##    #    ##
    0b00110000, 0b00000110, //   ##         ##
    0b00011000, 0b00001100, //    ##       ##
    0b00001100, 0b10011000, //     ##  #  ##
    0b00000111, 0b11110000, //      #######
    0b00000011, 0b11100000, //       #####
    0b00000000, 0b00000000, //
};

unsigned char water_tap_icon16x16[] =
{
    0b00000001, 0b10000000, //        ##
    0b00000111, 0b11100000, //      ######
    0b00000001, 0b10000000, //        ##
    0b00001111, 0b11110000, //     ########
    0b11111111, 0b11111110, // ###############
    0b11111111, 0b11111111, // ################
    0b11111111, 0b11111111, // ################
    0b11111111, 0b11111111, // ################
    0b00000000, 0b00001111, //             ####
    0b00000000, 0b00001111, //             ####
    0b00000000, 0b00000000, //
    0b00000000, 0b00001100, //             ##
    0b00000000, 0b00001100, //             ##
    0b00000000, 0b00000000, //
    0b00000000, 0b00001100, //             ##
    0b00000000, 0b00001100, //             ##
};

unsigned char humidity_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000001, 0b10000000, //        ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00001110, 0b01110000, //     ###  ###
    0b00001100, 0b00110000, //     ##    ##
    0b00011100, 0b00111000, //    ###    ###
    0b00011000, 0b00011000, //    ##      ##
    0b00111000, 0b00011100, //   ###      ###
    0b00111000, 0b00011100, //   ###      ###
    0b00111000, 0b00011100, //   ###      ###
    0b00011100, 0b00111000, //    ###    ###
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000011, 0b11000000, //       ####
    0b00000000, 0b00000000, //
};

unsigned char humidity2_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000001, 0b10000000, //        ##
    0b00000011, 0b11000000, //       ####
    0b00000111, 0b11100000, //      ######
    0b00001111, 0b11110000, //     ########
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11011000, //    ####### ##
    0b00111111, 0b10011100, //   #######  ###
    0b00111111, 0b10011100, //   #######  ###
    0b00111111, 0b00011100, //   ######   ###
    0b00011110, 0b00111000, //    ####   ###
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000011, 0b11000000, //       ####
    0b00000000, 0b00000000, //
};

unsigned char sun_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00100000, 0b10000010, //   #     #     #
    0b00010000, 0b10000100, //    #    #    #
    0b00001000, 0b00001000, //     #       #
    0b00000001, 0b11000000, //        ###
    0b00000111, 0b11110000, //      #######
    0b00000111, 0b11110000, //      #######
    0b00001111, 0b11111000, //     #########
    0b01101111, 0b11111011, //  ## ######### ##
    0b00001111, 0b11111000, //     #########
    0b00000111, 0b11110000, //      #######
    0b00000111, 0b11110000, //      #######
    0b00010001, 0b11000100, //    #   ###   #
    0b00100000, 0b00000010, //   #           #
    0b01000000, 0b10000001, //  #      #      #
    0b00000000, 0b10000000, //         #
};

unsigned char temperature_icon16x16[] =
{
    0b00000001, 0b11000000, //        ###
    0b00000011, 0b11100000, //       #####
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b00100000, //      ###  #
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00000111, 0b11100000, //      ######
};

unsigned char noninverted_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01011111, 0b11111110, //  # ############
    0b01001111, 0b11111110, //  #  ###########
    0b01000111, 0b11111110, //  #   ##########
    0b01000011, 0b11111110, //  #    #########
    0b01000001, 0b11111110, //  #     ########
    0b01000000, 0b11111110, //  #      #######
    0b01000000, 0b01111110, //  #       ######
    0b01000000, 0b00111110, //  #        #####
    0b01000000, 0b00011110, //  #         ####
    0b01000000, 0b00001110, //  #          ###
    0b01000000, 0b00000110, //  #           ##
    0b01111111, 0b11111110, //  ##############
    0b00000000, 0b00000000, //
};

unsigned char inverted_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b01111111, 0b11111110, //  ##############
    0b01100000, 0b00000010, //  ##           #
    0b01110000, 0b00000010, //  ###          #
    0b01111000, 0b00000010, //  ####         #
    0b01111100, 0b00000010, //  #####        #
    0b01111110, 0b00000010, //  ######       #
    0b01111111, 0b00000010, //  #######      #
    0b01111111, 0b10000010, //  ########     #
    0b01111111, 0b11000010, //  #########    #
    0b01111111, 0b11100010, //  ##########   #
    0b01111111, 0b11110010, //  ###########  #
    0b01111111, 0b11111010, //  ############ #
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b00000000, 0b00000000, //
};

unsigned char lock_closed_icon16x16[] =
{
    0b00111111, 0b11111100, //   ############
    0b00111111, 0b11111100, //   ############
    0b00111000, 0b00011100, //   ###      ###
    0b00111000, 0b00011100, //   ###      ###
    0b00111000, 0b00011100, //   ###      ###
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01111110, 0b01111110, //  ######  ######
    0b01111110, 0b01111110, //  ######  ######
    0b01111110, 0b01111110, //  ######  ######
    0b01111110, 0b01111110, //  ######  ######
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b00000000, 0b00000000, //
};

unsigned char lock_open_icon16x16[] =
{
    0b00111111, 0b11111100, //   ############
    0b00111111, 0b11111100, //   ############
    0b00111000, 0b00011100, //   ###      ###
    0b00111000, 0b00000000, //   ###
    0b00111000, 0b00000000, //   ###
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b01111110, 0b01111110, //  ######  ######
    0b01111110, 0b01111110, //  ######  ######
    0b01111110, 0b01111110, //  ######  ######
    0b01111110, 0b01111110, //  ######  ######
    0b01111111, 0b11111110, //  ##############
    0b01111111, 0b11111110, //  ##############
    0b00000000, 0b00000000, //
};

unsigned char person_icon16x16[] =
{
    0b00000111, 0b11100000, //      ######
    0b00001111, 0b11110000, //     ########
    0b00001111, 0b11110000, //     ########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00001111, 0b11110000, //     ########
    0b00001111, 0b11110000, //     ########
    0b00000111, 0b11100000, //      ######
    0b00000111, 0b11100000, //      ######
    0b00111111, 0b11111100, //   ############
    0b01111111, 0b11111110, //  ##############
    0b11111111, 0b11111111, // ################
    0b11111111, 0b11111111, // ################
    0b11111111, 0b11111111, // ################
};
unsigned char window_icon16x16[] =
{
    0b01111111, 0b11111111, //  ###############
    0b01111111, 0b11111111, //  ###############
    0b01100001, 0b10001111, //  ##    ##   ####
    0b01100001, 0b10011011, //  ##    ##  ## ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01111111, 0b10110011, //  ######## ##  ##
    0b01111111, 0b10110011, //  ######## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01100001, 0b10110011, //  ##    ## ##  ##
    0b01111111, 0b11111111, //  ###############
    0b01111111, 0b11111111, //  ###############
};
unsigned char door_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001011, 0b11111000, //     # #######
    0b00001000, 0b11111000, //     #   #####
    0b00001000, 0b00111000, //     #     ###
    0b00001000, 0b00111000, //     #     ###
    0b00001000, 0b00111000, //     #     ###
    0b00001000, 0b10111000, //     #   # ###
    0b00001000, 0b10111000, //     #   # ###
    0b00001000, 0b00111000, //     #     ###
    0b00001000, 0b00111000, //     #     ###
    0b00001100, 0b00111000, //     ##    ###
    0b00000011, 0b00100000, //       ##  #
    0b00000000, 0b11100000, //         ###
};
unsigned char face_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000001, 0b11000000, //        ###
    0b00001111, 0b11111000, //     #########
    0b00011101, 0b11011000, //    ### ### ##
    0b00011000, 0b00001100, //    ##       ##
    0b00010000, 0b00000100, //    #         #
    0b00101111, 0b11111010, //   # ######### #
    0b01111111, 0b01111111, //  ####### #######
    0b01100111, 0b01111011, //  ##  ### #### ##
    0b01100111, 0b01110011, //  ##  ### ###  ##
    0b00100000, 0b10000010, //   #     #     #
    0b00010000, 0b00100000, //    #         #
    0b00001011, 0b11101000, //     # ##### #
    0b00000100, 0b00010000, //      #     #
    0b00000011, 0b11100000, //       #####
    0b00000000, 0b00000000, //
};
unsigned char siren_icon16x16[] =
{
    0b10000000, 0b10000001, // #       #      #
    0b01000000, 0b10000010, //  #      #     #
    0b00100000, 0b10000100, //   #     #    #
    0b00010011, 0b11101000, //    #  ##### #
    0b00000111, 0b11110000, //      #######
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b10111000, //     ##### ###
    0b00011111, 0b10011100, //    ######  ###
    0b00011111, 0b10011100, //    ######  ###
    0b00011111, 0b10001100, //    ######   ##
    0b00111111, 0b10001110, //   #######   ###
    0b00111111, 0b10001110, //   #######   ###
    0b01111111, 0b11111111, //  ###############
    0b01111111, 0b11111111, //  ###############
    0b01111111, 0b11111111, //  ###############
    0b00000000, 0b00000000, //
};
unsigned char warning_icon16x16[] =
{
    0b00000000, 0b10000000, //         #
    0b00000001, 0b11000000, //        ###
    0b00000001, 0b11000000, //        ###
    0b00000011, 0b11100000, //       #####
    0b00000011, 0b01100000, //       ## ##
    0b00000111, 0b01110000, //      ### ###
    0b00000110, 0b00110000, //      ##   ##
    0b00001110, 0b10111000, //     ### # ###
    0b00001100, 0b10011000, //     ##  #  ##
    0b00011100, 0b10011100, //    ###  #  ###
    0b00011000, 0b10001100, //    ##   #   ##
    0b00111000, 0b00001110, //   ###       ###
    0b00110000, 0b10000110, //   ##    #    ##
    0b01111111, 0b11111111, //  ###############
    0b01111111, 0b11111111, //  ###############
    0b00000000, 0b00000000, //
};
unsigned char plus_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000001, 0b10000000, //        ##
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};
unsigned char minus_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00011111, 0b11111000, //    ##########
    0b00011111, 0b11111000, //    ##########
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
};
unsigned char mobile_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00110000, //           ##
    0b00000000, 0b00110000, //           ##
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001100, 0b00011000, //     ##     ##
    0b00001100, 0b00011000, //     ##     ##
    0b00001100, 0b00011000, //     ##     ##
    0b00001100, 0b00011000, //     ##     ##
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
    0b00001111, 0b11111000, //     #########
};
unsigned char signal1_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b01000000, 0b00000000, //  #
    0b11000000, 0b00000000, // ##
    0b11000000, 0b00000000, // ##
};
unsigned char signal2_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000100, 0b00000000, //      #
    0b00001100, 0b00000000, //     ##
    0b00011100, 0b00000000, //    ###
    0b00011100, 0b00000000, //    ###
    0b01011100, 0b00000000, //  # ###
    0b11011100, 0b00000000, // ## ###
    0b11011100, 0b00000000, // ## ###
};
unsigned char signal3_icon16x16[] =
{
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //
    0b00000000, 0b00000000, //                 
    0b00000000, 0b00000000, //                 
    0b00000000, 0b01000000, //          #      
    0b00000000, 0b11000000, //         ##      
    0b00000001, 0b11000000, //        ###      
    0b00000001, 0b11000000, //        ###      
    0b00000101, 0b11000000, //      # ###      
    0b00001101, 0b11000000, //     ## ###      
    0b00011101, 0b11000000, //    ### ###      
    0b00011101, 0b11000000, //    ### ###      
    0b01011101, 0b11000000, //  # ### ###      
    0b11011101, 0b11000000, // ## ### ###      
    0b11011101, 0b11000000, // ## ### ###      
};
unsigned char signal4_icon16x16[] =
{
    0b00000000, 0b00000000, //                 
    0b00000000, 0b00000100, //              #  
    0b00000000, 0b00001100, //             ##  
    0b00000000, 0b00011100, //            ###  
    0b00000000, 0b00011100, //            ###  
    0b00000000, 0b01011100, //          # ###  
    0b00000000, 0b11011100, //         ## ###  
    0b00000001, 0b11011100, //        ### ###  
    0b00000001, 0b11011100, //        ### ###  
    0b00000101, 0b11011100, //      # ### ###  
    0b00001101, 0b11011100, //     ## ### ###  
    0b00011101, 0b11011100, //    ### ### ###  
    0b00011101, 0b11011100, //    ### ### ###  
    0b01011101, 0b11011100, //  # ### ### ###  
    0b11011101, 0b11011100, // ## ### ### ###  
    0b11011101, 0b11011100, // ## ### ### ###  
};



#endif /* home_h */