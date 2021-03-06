//{{{
/*2017-3-14 重写i3msg，将我的三台机器的i3msg整合在一起
  这次将采用#if设置，直接在编译阶段分别编译各自机器的源代码
  抛弃了conky上取得信息的做法，即每次运行时通过取得dmi信息来确定
  执行的代码段。
  注：目前的设置是以debian 8 stable 为基础的。

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
#define tfile		"/tmp/sysini_path0XAdb234WA99u.dtt"
#define MCH_ID			3
//通用的定义
#define  chlen		1024
#define  mem_len	256
#define weather			"/root/.conky/weather"
#define wfile			"/tmp/wthdata.dat"
#define mailfile		"/tmp/checkmail_00123"
//信息显示的格式
#define	 out_msg	"%s | CPU:%s%s| 内存:%s %s| 流量 %s%s| 电量:%s| 显卡:%s| 泰安 %s %s | %s\n"  //2013-4-21添加天气 2014-4-2添加邮件检查
//macro define
#define  zero(A)	memset(A,0,sizeof(A))
#define  sys_log(a,b)	openlog(a,LOG_PID,LOG_USER);syslog(LOG_NOTICE,b);closelog();
//用于邮件检查的定义
#define fetchmail	"From fetchmail"
#define status		"Status: R"
#define tyyyyt		"/var/mail/tyyyyt"
#define tfox163		"/var/mail/tybitsfox163"
#define tfox126		"/var/mail/tybitsfox126"
#define fox126		"/var/mail/bitsfox126"
#define phone		"/var/mail/13325288100"
#define tfoxsina	"/var/mail/tybitsfoxsina"
#define foxsina		"/var/mail/bitsfoxsina"
#define wait_tm		5
//{{{根据不同的机器，分别进行编译
////////////////////////////////thinkpad/////////////////////////////////////////
#if (MCH_ID == 1) 
//下面这个定义是用来获取网络流量数据的，有wlan0的应设置为5,只有eth0的设为4,只有wlan0时设置为3
//2017-7-29 debian9下不再使用固定的行数取得流量数据，必须要根据行首的关键字符串判断是否是无线还是有线
#define  net_str	"wlp5s0"
#define	 jc			5
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
//#define cpu_temp	"/sys/class/hwmon/hwmon2/temp2_input"
//video card temp
//#define video_temp	"/sys/class/hwmon/hwmon0/temp1_input"
#endif
/////////////////////////////////office pad//////////////////////////////////////
#if (MCH_ID == 3) 
#define  net_str	"enp4s0"
#define	 jc			5
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
//#define cpu_temp "/sys/devices/platform/coretemp.0/hwmon/hwmon1/temp1_input"
//video card temp
//#define video_temp "/sys/devices/virtual/thermal/thermal_zone0/temp"
#endif
/////////////////////////////////dell/////////////////////////////////////////////
#if (MCH_ID == 2)
#define  net_str	"enp3s0"
#define	 jc			5
//电池电量获取所需
#define sfile   ""
//CPU
#define cpu_file	"/proc/stat"
//memory
#define mem_file	"/proc/meminfo"
//net
#define net_updown	"/proc/net/dev"
//cpu temperature
//#define cpu_temp	"/sys/class/hwmon/hwmon0/temp2_input"
//#define video_temp	"/sys/class/hwmon/hwmon1/temp1_input"

#endif
//}}}
//define var
char msg[11][100];
char fmt[chlen];
char cpu_temp[chlen],video_temp[chlen];
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
void check_mail();//2017-3-17 该函数替代原来的check_mail脚本


