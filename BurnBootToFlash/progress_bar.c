/*
 * progress_bar.c
 * 
 *  文件描述:
 *  创建时间: 2014-6-19
 *  修改历史:
 * Author: YangJun
 */
#include <stdio.h>
#include <stdlib.h>
#include "progress_bar.h"
HANDLE_BAR* creat_progress_bar(void)
{
	HANDLE_BAR *handle_bar = (HANDLE_BAR*)malloc(sizeof(HANDLE_BAR));

	(*handle_bar).flag = 0;
	(*handle_bar).last_count = 0;
	(*handle_bar).now_count = 0;

	printf("\n  0 %%  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>100%%\n");

	return handle_bar;
}

HANDLE_BAR* progress_bar(HANDLE_BAR* handle_bar, unsigned int count, unsigned int totle)
{

	if(count > totle)
	{
		return handle_bar;
	}

	if(0 == count)
	{
		printf("waiting");
		fflush(stdout);
	}

	handle_bar ->now_count = count*50/totle;
	if(handle_bar ->last_count == handle_bar ->now_count )
	{
		return handle_bar;
	}

	handle_bar ->last_count = handle_bar ->now_count;
	printf(">");
	fflush(stdout);

	return handle_bar;
}

HANDLE_BAR* stop_progress_bar(HANDLE_BAR* handle_bar)
{
	handle_bar ->flag = 0;
	handle_bar ->last_count = 0;
	handle_bar ->now_count = 0;

	printf("complete\n");

	return handle_bar;
}
void destory_progress_bar(HANDLE_BAR* handle_bar)
{
	free(handle_bar);
	handle_bar = NULL;
}

