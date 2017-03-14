//{{{
/*2017-3-14 重写i3msg，将我的三台机器的i3msg整合在一起
  这次将采用#if设置，直接在编译阶段分别编译各自机器的源代码
  抛弃了conky上取得信息的做法，即每次运行时通过取得dmi信息来确定
  执行的代码段。


  	tybitsfox
 */
//}}}
#include"clsscr.h"
//下面的这个定义决定了对不同机器采用不同的编译
/*MCH_ID 所代表的含义：
  =0				不代表任何机器，编译出错误信息
  =1				thinkpad
  =2				dell
  =3				office pad
 */
#define MCH_ID			1
//通用的定义
#define	 jc			6
#define  chlen		1024
#define  mem_len	256
#define weather			"/root/.conky/weather"
#define wfile			"/tmp/wthdata.dat"
#define mailfile		"/tmp/checkmail_00123"
//信息显示的格式
#define	 out_msg	"%s | CPU:%s%s| 内存:%s %s| 流量 %s%s| 电量:%s|显卡:%s| 泰安 %s %s | %s\n"  //2013-4-21添加天气 2014-4-2添加邮件检查
//macro define
#define  zero(A)	memset(A,0,sizeof(A))
#define  sys_log(a,b)	openlog(a,LOG_PID,LOG_USER);syslog(LOG_NOTICE,b);closelog();


//thinkpad
#if (MCH_ID == 1) 
//电池电量
#define sfile   "/sys/class/power_supply/BAT1/uevent"
#define power_base  "POWER_SUPPLY_ENERGY_FULL="
#define power_now	"POWER_SUPPLY_ENERGY_NOW="
//cpu
#define cpu_file	"/proc/stat"
//memory
#define mem_file	"/proc/meminfo"
//net
#define net_updown	"/proc/net/dev"
//cpu temperature
//#define cpu_temp	"/proc/acpi/ibm/thermal"
#define cpu_temp	"/sys/class/hwmon/hwmon2/temp2_input"
//video card temp
#define video_temp	"/sys/class/hwmon/hwmon0/temp1_input"
#endif
//office pad
#if (MCH_ID == 3) 
//电池电量
#define sfile   "/sys/class/power_supply/BAT0/uevent"
#define power_base  "POWER_SUPPLY_ENERGY_FULL="
#define power_now	"POWER_SUPPLY_ENERGY_NOW="
//cpu
#define cpu_file	"/proc/stat"
//memory
#define mem_file	"/proc/meminfo"
//net
#define net_updown	"/proc/net/dev"
//cpu temperature
#define cpu_temp "/sys/devices/platform/coretemp.0/hwmon/hwmon1/temp1_input"
//video card temp
#define video_temp "/sys/devices/virtual/thermal/thermal_zone0/temp"
#endif

//define var
char msg[11][100];
char fmt[chlen];
int  cpu_v[5]; //used to calc cpu avg
unsigned long long 	net_ud[2]; //calc net flow
void get_config();//因为没用配置文件，此函数改为初始化基本数据。
void format_msg(int i);//除了天气显示使用，其余的都在各自的函数独立实现了信息格式化。
int disp_msg();//完成后的信息输出
void get_batt();//battery get
void get_cpu();//cpu status
void get_mem();//mem status
void get_net();//net up/down
void get_temp();//cpu temperature
void get_mailchk();//2014-4-2 add mailcheck



