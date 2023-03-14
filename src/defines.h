#define IMU IMU_MPU6050
#define SECOND_IMU IMU
#define BOARD BOARD_WROOM32
#define IMU_ROTATION DEG_180
#define SECOND_IMU_ROTATION DEG_180

// Battery monitoring options (comment to disable):
// BAT_EXTERNAL for ADC pin, BAT_INTERNAL for internal - can detect only low battery, BAT_MCP3021 for external ADC
#define BATTERY_MONITOR BAT_EXTERNAL
#define BATTERY_SHIELD_RESISTANCE 180 //130k BatteryShield, 180k SlimeVR or fill in external resistor value in kOhm

#define PIN_IMU_SDA 21
#define PIN_IMU_SCL 22
#define PIN_IMU_INT 23
#define PIN_IMU_INT_2 25
#define PIN_BATTERY_LEVEL 36
