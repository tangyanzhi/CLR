#include<stdio.h>
#include<string.h>
#include <malloc.h>

/*
以下纯为模仿，Roslyn+CLR+JIT的运作模式，并不是它真正的运行模式。因为真正的运行模式
代码高达几百万行，这里短短几行代码，完全无法实现。
*/

int main(int argc, char** argv)
{
	// Roslyn前端编译部分 把源码编译成IL和IR
	char* filepath = argv[1];
	char str[100];
	FILE* read = fopen(filepath, "r"); //VS2022里注意fopen会报错不安全，解决：右键属性-》配置属性-》C/C++-》预处理器-》预处理器定义输入：_CRT_SECURE_NO_WARNINGS
	if (read == NULL)
	{
		printf("读取文件出错");
		return 0;
	}

	FILE* write = fopen("D:\\Roslyn.h", "w"); //这里 Roslyn.h文件在根目录下，你可以改成自己的目录
	fgets(str, 100, read);
	if (str[0] == 0x75)
	{
		fputs("0x177 0x2102 0x6703 IL_Using IL_System.Core\0\r\n", write); //IL表示
		fputs("0x177 0x2102 0x6703 IR_Using IR_System.Core\0\r\n", write); //IR表示
		//fclose(write);
	}
	fgets(str, 100, read);
	if (str[0] == 0x76)
	{
		fputs("IL_void IL_Main\0\r\n", write);//IL表示
		fputs("IR_void IR_Main\0\r\n", write);//IR表示
		//fclose(write);
	}
	fgets(str, 100, read);
	if (str[0] == 0x7b)
	{
		fputs("IL_Print IL_Hello World\0\r\n", write);//IL表示
		fputs("IR_Print IR_Hello World\0\r\n", write);//IR表示
	}

	fclose(write);
	fclose(read);

	// CLR 内存加载部分 构建MethodDesc模型
	struct MethodDesc
	{
		char m_pszDebugMethodName[10];
		char m_pszDebugClassName[10];
		char m_pszDebugMethodSignature[10];
		char m_pDebugMethodTable[10];
	};
	struct MethodDesc p_MethodDesc;
	FILE* readCLR = fopen("D:\\Roslyn.h", "r");
	fgets(str, 100, read);
	if (str[0] == 0x30)
	{
		strncpy(p_MethodDesc.m_pszDebugClassName, str + 32, 11);
	}
	fgets(str, 100, read);
	fgets(str, 100, read);
	fgets(str, 100, read);
	if (str[0] == 0x69)
	{
		strncpy(p_MethodDesc.m_pszDebugMethodName, str + 0xd, 4);
	}
	strncpy(p_MethodDesc.m_pDebugMethodTable, "MethodTable", 10);
	strncpy(p_MethodDesc.m_pszDebugMethodSignature, "MethodSignature", 10);
	fclose(readCLR);

	//JIT 部分 编译成机器码
	char* addr = (char*)malloc(100);
	strcpy(addr, "hello world");
	free(addr);
	getchar();
	return 1;
}