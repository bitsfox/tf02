#include"clsscr.h"


#define ctmp1	"/sys/class/hwmon/hwmon1/temp1_input"
#define ctmp2	"/sys/class/hwmon/hwmon1/temp2_input"
#define ctmp3	"/sys/class/hwmon/hwmon2/temp2_input"
#define ctmp4	"/sys/class/hwmon/hwmon2/temp3_input"
#define vtmp1	"/sys/class/hwmon/hwmon0/temp1_input"
#define vtmp2	"/sys/class/hwmon/hwmon0/temp2_input"
#define vtmp3	"/sys/class/hwmon/hwmon0/temp3_input"
//for thinkpad
#define bat1	"/sys/class/power_supply/BAT1/energy_now"
#define bat2	"/sys/class/power_supply/BAT1/energy_full"
//for office pad
#define bat3	"/sys/class/power_supply/BAT0/energy_now"
#define bat4	"/sys/class/power_supply/BAT0/energy_full"
//fan的目录各有不同
#define thk_fan	"/sys/devices/platform/thinkpad_hwmon/fan1_input"
#define dell_fan "/sys/devices/virtual/hwmon/hwmon0/fan1_input"
//only for debian testing, not for debian 8 stable
#define off_fan "/sys/devices/virtual/hwmon/hwmon0/fan1_input"
//dmidecode
#define dmi_cmd	"dmidecode -t 1|grep Version > /tmp/CVTMPPPADSXXX0927.txt"
#define dfile	"/tmp/CVTMPPPADSXXX0927.txt"
//0:单位本本，1：dell，2：thinkpad
//enum dmi_type{LenovoB470,aa,bb} dt;
#define danwei	"Lenovo B470"
#define dell	"00"
#define thinkpad	"ThinkPad SL410"
char str[256],s1[64];




