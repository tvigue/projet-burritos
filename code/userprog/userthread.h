#ifdef CHANGED

#ifndef USERTHREAD_H
#define USERTHREAD_H

#define STACK_PAGE_NUMBER 3
	

	extern int do_UserThreadCreate(int f, int arg);
	extern void do_UserThreadExit();
	extern void initUserThread();
	extern void do_WaitUserThread();

typedef struct argument
{
	void func(void *arg);
	char * args;
}argument;
#endif
#endif //CHANGED
