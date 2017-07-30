#include"iniget.h"

//{{{int main(int argc,char** argv)
int main(int argc,char** argv)
{
	int fd,i;
	char ch[2048];
	/*fd=open(sfile,O_RDONLY);
	if(fd < 0)
	{
		printf("errno is: %d\t%s\n",errno,strerror(errno));
	}
	else
		close(fd);*/
	for(i=0;i<3;i++)
	{
		zero(buf[i]);
		zero(mch[i]);
	}
	memcpy(mch[0],cpu,strlen(cpu));
	mchtype=parse_dmi();
	switch(mchtype)
	{
	case 0: //dell
		memcpy(mch[1],dell_vc,strlen(dell_vc));
		memcpy(mch[2],dell_fan,strlen(dell_fan));
		break;
	case 1: //thinkpad
		memcpy(mch[1],thk_vc,strlen(thk_vc));
		memcpy(mch[2],thk_fan,strlen(thk_fan));
		break;
	default: //lenovo
		memcpy(mch[1],len_vc,strlen(len_vc));
		memcpy(mch[2],len_fan,strlen(len_fan));
		break;
	};
	get_pathfile();
	fd=open(sfile,O_RDWR);
	if(fd < 0)
		return 0;
	zero(ch);
	snprintf(ch,sizeof(ch),"%s\n%s\n%s\n",buf[0],buf[1],buf[2]);
	write(fd,ch,strlen(ch));
	close(fd);
	return 0;
}//}}}
//{{{int parse_dmi()
int parse_dmi()
{
	int file,i,j;
	char ch[256];
	memset(ch,0,sizeof(ch));
	snprintf(ch,sizeof(ch),"%s > %s",dmi,sfile);
	system(ch);
	memset(ch,0,sizeof(ch));
	file=open(sfile,O_RDONLY);
	i=read(file,ch,sizeof(ch));
	close(file);
	if(strstr(ch,dell) != NULL)
		return 0;
	if(strstr(ch,thinkpad) != NULL)
		return 1;
	return 2;
}//}}}
//{{{void get_pathfile()
void get_pathfile()
{
	FILE *file;
	int s,i,j,k;
	char ch[1024],cm[3][256],cn[3][256],ch1[256];
	zero(ch);
	for(i=0;i<3;i++)
	{
		zero(cm[i]);
		zero(cn[i]);
	}
	memcpy(cm[0],hwmon0,strlen(hwmon0));
	memcpy(cm[1],hwmon1,strlen(hwmon1));
	memcpy(cm[2],hwmon2,strlen(hwmon2));
	memcpy(cn[0],temp1,strlen(temp1));
	memcpy(cn[1],temp2,strlen(temp2));
	memcpy(cn[2],temp3,strlen(temp3));
	for(i=0;i<3;i++)
	{
		s=0;//确定是否使用dname
		zero(ch1);
		snprintf(ch,sizeof(ch),"%s%s",cm[i],name);
		file=fopen(ch,"r");
		if((file == NULL) && (errno == 2)) //not such file...
		{
			zero(ch);
			snprintf(ch,sizeof(ch),"%s%s%s",cm[i],dname,name);
			file=fopen(ch,"r");
			if(file == NULL)
				return; //error!
			if(fgets(ch1,sizeof(ch1),file)==NULL)
			{
				fclose(file);
				return; //error!
			}
			s=1;//s=1表示使用dname
		}
		else
		{
			if(fgets(ch1,sizeof(ch1),file)==NULL)
			{
				fclose(file);
				return; //error!
			}
		}
		fclose(file); //到这里，取得了name文件中存储的设备信息
		for(j=0;j<3;j++)//决定行数的循环
		{
			if(strstr(ch1,mch[j]) != NULL)
				break;
		}//j=0 cpu =1 video vard =2 fan
		if(j==2) //fan
		{
			zero(cn[0]);zero(cn[1]);zero(cn[2]);
			memcpy(cn[0],fan1,strlen(fan1));
			memcpy(cn[1],fan2,strlen(fan2));
			memcpy(cn[2],fan3,strlen(fan3));
		}
		else
		{
			zero(cn[0]);zero(cn[1]);zero(cn[2]);
			memcpy(cn[0],temp1,strlen(temp1));
			memcpy(cn[1],temp2,strlen(temp2));
			memcpy(cn[2],temp3,strlen(temp3));
		}
		for(k=0;k<3;k++)//在文件中查找
		{
			zero(ch);
			if(s==0)
				snprintf(ch,sizeof(ch),"%s%s",cm[i],cn[k]);
			else
				snprintf(ch,sizeof(ch),"%s%s%s",cm[i],dname,cn[k]);
			file=fopen(ch,"r");
			if(file)
			{
				zero(buf[j]);
				memcpy(buf[j],ch,strlen(ch));
				fclose(file);
				break;
			}
		}
	}
}//}}}


