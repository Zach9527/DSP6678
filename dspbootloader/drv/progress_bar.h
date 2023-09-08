/*
 * progress_bar.h
 * 
 *  文件描述:
 *  创建时间: 2014-6-19
 *  修改历史:
 * Author: YangJun
 */



#ifndef PROGRESS_BAR_H_
#define PROGRESS_BAR_H_

typedef struct BAR{
	unsigned int flag;
	unsigned int last_count;
	unsigned int now_count;
}HANDLE_BAR;

HANDLE_BAR* creat_progress_bar(void);
HANDLE_BAR* progress_bar(HANDLE_BAR* handle_bar, unsigned int count, unsigned int totle);
HANDLE_BAR* stop_progress_bar(HANDLE_BAR* handle_bar);
void destory_progress_bar(HANDLE_BAR* handle_bar);

#endif /* PROGRESS_BAR_H_ */
