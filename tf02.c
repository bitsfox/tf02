#include"tf02.h"
int parse_dmi();
int get_office(int i);
int get_dell(int i);
int get_thk(int i);
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
//		printf(s1);
//		printf("\n");
		get_office(j);
		return 0;
	}
	if(memcmp(s1,dell,strlen(dell))==0)
	{
		get_dell(j);
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
		memcpy(str,vtmp2,strlen(vtmp2));
		break;
	case 1://core temp2
		memcpy(str,vtmp3,strlen(vtmp3));
		break;
	case 2://nouveau
		memcpy(str,ctmp1,strlen(ctmp1));
		break;
	case 3://invalid
		printf("acpitz temp2 invalid\n");
		return 0;
	case 4://fan invalid
		printf("fan invalid\n");
		return 0;
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
	f=atoi(str);f/=1000;
	printf("%d℃ \n",f);
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
		memcpy(str,ctmp1,strlen(ctmp1));
		break;
	case 1://core temp2
		memcpy(str,ctmp2,strlen(ctmp2));
		break;
	case 2://acpitz
		memcpy(str,vtmp1,strlen(vtmp1));
		break;
	case 3://acpitz
		memcpy(str,vtmp2,strlen(vtmp2));
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






