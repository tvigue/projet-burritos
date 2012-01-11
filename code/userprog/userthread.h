#ifdef CHANGED

#ifndef USERTHREAD_H
#define USERTHREAD_H

#define STACK_PAGE_NUMBER 3
	

	extern int do_UserThreadCreate(int f, int arg);
	extern void do_UserThreadExit();
	extern void initUserThread();
	extern void do_WaitUserThread();
	extern void do_UserThreadJoin(int n);


#endif
#endif //CHANGED
