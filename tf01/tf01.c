#include"tf01.h"
/*该程序为适应debian9的conky而重新编写的，新的conky中不适合多次运行外部程序（execi 不如原先版本的给力了）只需自己取得温度。
 另：多显卡的办公室本本比较麻烦，debian9中/sys/class/hwmon目录下的三个目录不再是固定指向某个固定的硬件设备了，与硬件设备的关系为随机映射 
 2017-7-30 由于上述原因，我将具体目录文件和设备的对应关系的取得放到了一个专门的程序中：gettempfan。并且通过该程序屏蔽了不同机器的差别。
 因此这里的处理就方便了许多，只要将已经取得的文件路径从一个临时文件中读出即可使用。所以也就不需要在按照不同的机器写不同的函数来实现了！
 */
//{{{int main(int argc,char** argv)
int main(int argc,char** argv)
{
	int i,f,len;
	int b[2];
	FILE *file;
	memset(str,0,sizeof(str));
	for(i=0;i<3;i++)
		memset(fn[i],0,sizeof(fn[i]));
	file=fopen(sfile,"r");
	if(file==NULL)
	{
		snprintf(str,sizeof(str),"cpu温度：%d℃       显卡温度：%d℃ ",0,0);
		return 0;
	}
	memset(ch,0,sizeof(ch));
	i=0;
	while(fgets(ch,sizeof(ch),file))
	{
		memcpy(fn[i],ch,strlen(ch));
		if(fn[i][strlen(ch)-1]=='\n')
			fn[i][strlen(ch)-1]=0;
		i++;
		if(i>2)
			break;
	}//取得文件名
	fclose(file);
	f=open(fn[0],O_RDONLY);//core temp
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
	f=open(fn[1],O_RDONLY);//nouveau
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
