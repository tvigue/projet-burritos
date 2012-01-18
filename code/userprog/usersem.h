#ifdef CHANGED

#ifndef USERSEM_H
#define USERSEM_H

	extern int do_UserSemCreate(int n);
	extern int do_UserSemPost(int id);
	extern int do_UserSemWait(int id);
	void initUserSem();
	void delUserSem();

#endif
#endif //CHANGED
