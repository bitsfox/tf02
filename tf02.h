#include"clsscr.h"


#define ctmp1	"/sys/class/hwmon/hwmon1/temp1_input"
#define ctmp2	"/sys/class/hwmon/hwmon1/temp2_input"
#define vtmp1	"/sys/class/hwmon/hwmon0/temp1_input"
#define vtmp2	"/sys/class/hwmon/hwmon0/temp2_input"
//dmidecode
#define dmi_cmd	"dmidecode -t 1|grep Version > /tmp/CVTMPPPADSXXX0927.txt"
#define dfile	"/tmp/CVTMPPPADSXXX0927.txt"
//0:单位本本，1：dell，2：thinkpad
//enum dmi_type{LenovoB470,aa,bb} dt;
#define danwei	"Lenovo B470"
#define dell	"DELL"
#define thinkpad	"ThinkPad"
char str[256],s1[64];




