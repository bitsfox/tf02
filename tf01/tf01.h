#include"clsscr.h"

//#define mtype		"lenvo"
//#define mtype		"thkpad"
#define mtype		"dell"

#define temp1		"/sys/class/hwmon/hwmon0/"
#define temp2		"/sys/class/hwmon/hwmon1/"
#define temp3		"/sys/class/hwmon/hwmon2/"
#define tname		"name"
#define ttemp1		"temp1_input"
#define ttemp2		"temp2_input"

char str[256],s1[128];

int identify_mech();
int get_office();
int get_dell();
int get_thk();
int main(int argc,char** argv);

