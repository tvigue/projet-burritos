#ifdef CHANGED

#ifndef USERTHREAD_H
#define USERTHREAD_H

#define STACK_PAGE_NUMBER 3
	

	extern int do_UserThreadCreate(int f, int arg);
	extern void do_UserThreadExit();
	extern void do_UserThreadWait();
	extern void do_UserThreadJoin(int n);
	extern void do_ForkExec(int n);
	extern void initUserProcessus();
	extern void do_UserProcessusExit();
	extern void do_UserProcessusWait();


#endif
#endif //CHANGED
