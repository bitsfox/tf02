#include"clsscr.h"

#define sfile		"/tmp/sysini_path0XAdb234WA99u.dtt"
//在debian9下，我所用到的系统信息中主要的变数是cpu温度，显卡温度和风扇转数
//所在目录是 /sys/class/hwmon/hwmon[0,1,2]中的随机一个，确定方法是在该目录下有个
//name的文件，可以确定当前目录存储的是上述三个信息的哪一个。确定后，将其写入临时
//文件保存,文件中保存的信息与存储位置是相关的，第一行存储cpu0温度，第二行存储显卡温度
//第三行存储风扇速度

#define hwmon0		"/sys/class/hwmon/hwmon0/"
#define hwmon1		"/sys/class/hwmon/hwmon1/"
#define hwmon2		"/sys/class/hwmon/hwmon2/"
#define temp1		"temp1_input"
#define temp2		"temp2_input"
#define temp3		"temp3_input"
#define temp4		"temp4_input"
#define fan1		"fan1_input"
#define fan2		"fan2_input"
#define fan3		"fan3_input"
#define name		"name"					//注意，在查看thinkpad机器的信息时，该文件同样可能不存在
#define dname		"device/"				//如果上述name文件不存在，应该在这里查找

#define cpu			"coretemp"
#define dell_vc		"nouveau"				//vc:video card
#define thk_vc		"acpitz"
#define dell_fan	"dell_smm"
#define thk_fan		"thinkpad"
#define len_vc		"acpitz"
#define len_fan		"nouveau"				//在debian9下这个机器没有fan,不过有个被我屏蔽的独立显卡

#define dmi			"dmidecode -t 1|grep Product"
#define dell		"Inspiron 560s"
#define thinkpad	"28425AC"
//#define lenovo		"HuronRiver Platform"

#define zero(A)		memset(A,0,sizeof(A))

char buf[3][1024];	//保存取得的文件名
char mch[3][256];
int  mchtype;		//机器类型，用于确定机器的显卡类型: 0:dell; 1:thinkpad; 2:lenovo

int main(int argc,char** argv);
int parse_dmi(); //解析当前机器类型
void get_pathfile();



