#include"tf01.h"
/*该程序为适应debian9的conky而重新编写的，新的conky中不适合多次运行外部程序（execi 不如原先版本的给力了）只需自己取得温度。
 另：多显卡的办公室本本比较麻烦，debian9中/sys/class/hwmon目录下的三个目录不再是固定指向某个固定的硬件设备了，与硬件设备的关系为随机映射 
 */
//{{{int main(int argc,char** argv)
int main(int argc,char** argv)
{
	int i;
	i=identify_mech();
	switch(i)
	{
	case 0://dell
		get_dell();
		break;
	case 1://office
		get_office();
		break;
	case 2://thinkpad
		get_thk();
		break;
	};
	return 0;
}
//}}}
//{{{int identify_mech()
int identify_mech()
{
	return strlen(mtype)-4;
}
//}}}
//{{{int get_dell()
int get_dell()
{
	int f,len;
	int b[2];
	memset(str,0,sizeof(str));
	snprintf(str,sizeof(str),"%s%s",temp2,ttemp2);//core temp
	f=open(str,O_RDONLY);
	if(f<=0)
	{
		printf("error 01");
		return 0;
	}
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
	{
		printf("error 11");
		return 0;
	}
	f=atoi(str);b[0]=f/1000;
	memset(str,0,sizeof(str));
	snprintf(str,sizeof(str),"%s%s",temp3,ttemp1);//nouveau
	f=open(str,O_RDONLY);
	if(f<=0)
	{
		printf("error 02");
		return 0;
	}
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
	{
		printf("error 12");
		return 0;
	}
	f=atoi(str);b[1]=f/1000;
	memset(str,0,sizeof(str));
	snprintf(str,sizeof(str),"cpu温度：%d℃       显卡温度：%d℃ ",b[0],b[1]);
	printf(str);
	return 0;
}
//}}}
//{{{int get_office()
int get_office()
{
	int f,len;
	int b[2];
	char buf[2][256];
	memset(buf[0],0,sizeof(buf[0]));
	memset(buf[1],0,sizeof(buf[1]));
	memset(str,0,sizeof(str));
	b[0]=0;
	snprintf(str,sizeof(str),"%s%s",temp1,tname);
	f=open(str,O_RDONLY);
	if(f<=0)
	{
		printf("error 01");
		return 0;
	}
	memset(s1,0,sizeof(s1));
	len=read(f,s1,sizeof(s1));
	close(f);
	if(len<=0)
	{
		printf("error 02");
		return 0;
	}
//{{{ confirm directory	
	if(s1[0]=='n' && s1[1]=='o') //nouveau
	{//排除了这个目录。
		memset(str,0,sizeof(str));
		snprintf(str,sizeof(str),"%s%s",temp2,tname);
		f=open(str,O_RDONLY);
		if(f<=0)
		{
			printf("error 11");
			return 0;
		}
		memset(s1,0,sizeof(s1));
		len=read(f,s1,sizeof(s1));
		close(f);
		if(len<=0)
		{
			printf("error 12");
			return 0;
		}
		if(s1[0]='a') //acpi
		{
			snprintf(buf[0],sizeof(buf[0]),"%s%s",temp2,ttemp1); //acpi
			snprintf(buf[1],sizeof(buf[1]),"%s%s",temp3,ttemp1); //core
		}
		else
		{
			snprintf(buf[0],sizeof(buf[0]),"%s%s",temp3,ttemp1);//
			snprintf(buf[1],sizeof(buf[1]),"%s%s",temp2,ttemp1);//
		}
	}
	else
	{
		if(s1[0]=='c' && s1[1]=='o') //coretemp
		{
			snprintf(buf[1],sizeof(buf[1]),"%s%s",temp1,ttemp1);//core
			memset(str,0,sizeof(str));
			snprintf(str,sizeof(str),"%s%s",temp2,tname);
			f=open(str,O_RDONLY);
			if(f<=0)
			{
				printf("error 21");
				return 0;
			}
			memset(s1,0,sizeof(s1));
			len=read(f,s1,sizeof(s1));
			close(f);
			if(len<=0)
			{
				printf("error 22");
				return 0;
			}
			if(s1[0]=='n' && s1[1]=='o') //nouveau
				snprintf(buf[0],sizeof(buf[0]),"%s%s",temp3,ttemp1);//acpi
			else
				snprintf(buf[0],sizeof(buf[0]),"%s%s",temp2,ttemp1);
		}
		else
		{
			snprintf(buf[0],sizeof(buf[0]),"%s%s",temp1,ttemp1);//acpi
			memset(str,0,sizeof(str));
			snprintf(str,sizeof(str),"%s%s",temp2,tname);
			f=open(str,O_RDONLY);
			if(f<=0)
			{
				printf("error 31");
				return 0;
			}
			memset(s1,0,sizeof(s1));
			len=read(f,s1,sizeof(s1));
			close(f);
			if(len<=0)
			{
				printf("error 32");
				return 0;
			}
			if(s1[0]=='n' && s1[1]=='o')
				snprintf(buf[1],sizeof(buf[1]),"%s%s",temp3,ttemp1);
			else
				snprintf(buf[1],sizeof(buf[1]),"%s%s",temp2,ttemp1);
		}//acpi
	}//}}}
	memset(str,0,sizeof(str));
	f=open(buf[1],O_RDONLY);//CORE
	if(f<=0)
	{
		printf("error 41");
		return 0;
	}
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
	{
		printf("error 42");
		return 0;
	}
	f=atoi(str);b[0]=f/1000;
	memset(str,0,sizeof(str));
	f=open(buf[0],O_RDONLY);//ACPI
	if(f<=0)
	{
		printf("error 51");
		return 0;
	}
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
	{
		printf("error 52");
		return 0;
	}
	f=atoi(str);b[1]=f/1000;
	memset(str,0,sizeof(str));
	snprintf(str,sizeof(str),"cpu温度：%d℃       显卡温度：%d℃ ",b[0],b[1]);
	printf(str);
	return 0;
}//}}}
//{{{int get_thk()
int get_thk()
{
	return 0;
}
//}}}
