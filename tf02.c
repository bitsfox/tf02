#include"tf02.h"
int parse_dmi();

//{{{int main(int argc,char **argv)
int main(int argc,char **argv)
{
	char *p;
	int i;
	if(parse_dmi()==0)
		return 0;
	if(memcmp(s1,danwei,strlen(danwei))==0)
	{
		printf(s1);
		printf("\n");

		return 0;
	}
	if(memcmp(s1,dell,strlen(dell))==0)
	{
		return 0;
	}
	if(memcmp(s1,thinkpad,strlen(thinkpad))==0)
	{
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

