#define BAUD_RATE 115200

#define ADR_DATA A0
#define ADR_SCLK A1
#define ADR_RCLK A2

#define D0 2
#define D1 3
#define D2 4
#define D3 5
#define D4 6
#define D5 7
#define D6 8
#define D7 9

#define ROM_CE A3
#define ROM_OE A4
#define ROM_WE A5

#define CE(state) digitalWrite(ROM_CE, !state)
#define OE(state) digitalWrite(ROM_OE, !state)
#define WE(state) digitalWrite(ROM_WE, !state)

#define VERSION_MAJOR 0
#define VERSION_MINOR 0
#define VERSION_PATCH 1
