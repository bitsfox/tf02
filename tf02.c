#include"tf02.h"
int parse_dmi();
int get_office(int i);
int get_dell(int i);
int get_thk(int i);
int get_della(int i);
int get_dellb(int i);
int get_officea(int i);
//{{{int main(int argc,char **argv)
int main(int argc,char **argv)
{
	char *p;
	int i,j;
	if(argc != 2)
	{
		printf("usage: %s [0-5]\n0:get core temp1\n\
1:get core temp2\n\
2:get acpitz temp1\n\
3:get acpitz temp2 <thinkpad not used>\n\
4:get fan number\n\
5:get battery\n",argv[0]);
		return 0;
	}
	j=atoi(argv[1]);
	if((j<0) || (j>5))
		return 0;
	if(parse_dmi()==0)
		return 0;
	if(memcmp(s1,danwei,strlen(danwei))==0)
	{
//		get_office(j);
		get_officea(j);
		return 0;
	}
	if(memcmp(s1,dell,strlen(dell))==0)
	{
		//get_dell(j);
		get_dellb(j);
		return 0;
	}
	if(memcmp(s1,thinkpad,strlen(thinkpad))==0)
	{
		get_thk(j);
		return 0;
	}
	return 0;
}//}}}
//{{{int parse_dmi()
int parse_dmi()
{
	char *p;
	int f,i;
	system(dmi_cmd);
	f=open(dfile,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	i=read(f,str,sizeof(str));
	close(f);
	if(i<=0)
		return 0;
	memset(s1,0,sizeof(s1));
	p=strchr(str,':');
	if(p==NULL)
		return 0;
	p+=2;
	snprintf(s1,sizeof(s1),"%s",p);
	i=strlen(s1);
	if(s1[i-1]=='\n')
		s1[i-1]=0;
	//printf(s1);
	return 1; //success
}//}}}
//{{{int get_thk(int i);
int get_thk(int i)
{
	int f,len;
	float ft,ft1;
	memset(str,0,sizeof(str));
	switch(i)
	{
	case 0://core temp1
		memcpy(str,ctmp3,strlen(ctmp1));
		break;
	case 1://core temp2
		memcpy(str,ctmp4,strlen(ctmp2));
		break;
	case 2://acpitz temp1
		memcpy(str,vtmp1,strlen(vtmp1));
		break;
	case 3://acpitz temp2 --thinkpad nouse
		//memcpy(str,vtmp2,strlen(vtmp2));
		//break;
		printf("invalid\n");
		return 0;
	case 4://fan
		memcpy(str,thk_fan,strlen(thk_fan));
		break;
	case 5://battery
		f=open(bat1,O_RDONLY);
		if(f<=0)
			return 0;
		memset(s1,0,sizeof(s1));
		len=read(f,s1,sizeof(s1));
		close(f);
		if(len<=0)
			return 0;
		ft=atof(s1);
		f=open(bat2,O_RDONLY);
		if(f<=0)
			return 0;
		memset(s1,0,sizeof(s1));
		len=read(f,s1,sizeof(s1));
		close(f);
		if(len<=0)
			return 0;
		ft1=atof(s1);
		printf("%2.0f%%\n",(ft/ft1)*100);
		return 0;
	};
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);f/=1000;
	if(i<4)
		printf("%d℃ \n",f);
	else
		printf("%d转/秒\n",f);
	return 0;
}//}}}
//{{{int get_dell(int i)
int get_dell(int i)
{
	int f,len;
	memset(str,0,sizeof(str));
	switch(i)
	{
	case 0://core temp1
		memcpy(str,ctmp6,strlen(ctmp6));
		break;
	case 1://core temp2
		memcpy(str,ctmp2,strlen(ctmp2));
		break;
	case 2://nouveau
		memcpy(str,ctmp5,strlen(ctmp5));
		break;
	case 3://invalid
		printf("acpitz temp2 invalid\n");
		return 0;
	case 4://fan invalid
		memcpy(str,dell_fan,strlen(dell_fan));
	//	printf("fan invalid\n");
		break;
	case 5://battery
		printf("battery invalid\n");
		return 0;
	};
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);//f/=1000;
	if(i==4)
		printf("%d转/秒\n",f);
	else
		printf("%d℃ \n",f/1000);
	return 0;
}//}}}
//{{{int get_office(int i)
int get_office(int i)
{
	int f,len;
	float ft,ft1;
	memset(str,0,sizeof(str));
	switch(i)
	{
	case 0://core temp1
		memcpy(str,ctmp3,strlen(ctmp3));
		break;
	case 1://core temp2
		memcpy(str,ctmp4,strlen(ctmp4));
		break;
	case 2://acpitz
		memcpy(str,vtmp1,strlen(ctmp1));
		break;
	case 3://acpitz
		memcpy(str,vtmp2,strlen(ctmp2));
		break;
	case 4://fan invalid
		printf("fan invalid\n");
		return 0;
	case 5://battery
		f=open(bat3,O_RDONLY);
		if(f<=0)
			return 0;
		memset(s1,0,sizeof(s1));
		len=read(f,s1,sizeof(s1));
		close(f);
		if(len<=0)
			return 0;
		ft=atof(s1);
		f=open(bat4,O_RDONLY);
		if(f<=0)
			return 0;
		memset(s1,0,sizeof(s1));
		len=read(f,s1,sizeof(s1));
		close(f);
		if(len<=0)
			return 0;
		ft1=atof(s1);
		printf("%2.0f%%\n",(ft/ft1)*100);
		return 0;
	};
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);f/=1000;
	printf("%d℃ \n",f);
	return 0;
}//}}}
//{{{int get_della(int i)
int get_della(int i)
{
	int f,len;
	int b[4];
	memset(str,0,sizeof(str));
	//core temp1
	memcpy(str,ctmp6,strlen(ctmp6));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[0]=f/1000;
	memset(str,0,sizeof(str));
	//core temp2
	memcpy(str,ctmp2,strlen(ctmp2));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[1]=f/1000;
	memset(str,0,sizeof(str));
	//nouveau
	memcpy(str,ctmp5,strlen(ctmp5));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[2]=f/1000;
	memset(str,0,sizeof(str));
	//fan of processor
	memcpy(str,dell_fan,strlen(dell_fan));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[3]=f;
	memset(destr,0,sizeof(destr));
	snprintf(destr,sizeof(destr),ffmt1,nullchar1,b[0],septors,nullchar1,b[1],septors,nullchar1,b[2],septors,nullchar2,b[3],septors);
	//snprintf(destr,sizeof(destr),ffmt,b[0],b[1],b[2],b[3]);
	printf(destr);
	return 0;
}//}}}
//{{{int get_dellb(int i)
int get_dellb(int i)
{
	int f,len;
	int b[2];
	memset(str,0,sizeof(str));
	//core temp1
	memcpy(str,ctmp6,strlen(ctmp6));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[0]=f/1000;
	memset(str,0,sizeof(str));
	//nouveau temp
	memcpy(str,ctmp5,strlen(ctmp5));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[1]=f/1000;
	memset(str,0,sizeof(str));
	snprintf(str,sizeof(str),"cup温度：%d℃       显卡温度：%d℃ ",b[0],b[1]);
	printf(str);
	return 0;
}//}}}
//{{{int get_officea(int i)
int get_officea(int i)
{
	int len,f;
	int b[2];
	memset(str,0,sizeof(str));
	//core temp1
	memcpy(str,core_temp1,strlen(core_temp1));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[0]=f/1000;
	memset(str,0,sizeof(str));
	//acpitz temp1
	memcpy(str,vcad_temp1,strlen(vcad_temp1));
	f=open(str,O_RDONLY);
	if(f<=0)
		return 0;
	memset(str,0,sizeof(str));
	len=read(f,str,sizeof(str));
	close(f);
	if(len<=0)
		return 0;
	f=atoi(str);b[1]=f/1000;
	memset(str,0,sizeof(str));
	snprintf(str,sizeof(str),"cup温度：%d℃       显卡温度：%d℃ ",b[0],b[1]);
	printf(str);
	return 0;
}//}}}



