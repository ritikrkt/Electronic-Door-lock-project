#ifndef DOOR_LOCK_H
#define DOOR_LOCK_H

#define LOCKED 0
#define UNLOCKED 1
#define SECURITY_LOCKOUT 2

int check_password(char password[]);
int change_password(void);
void load_password(void);
void save_password(void);

void unlock_door(void);
void lock_door(void);
void security_lockout(void);
int get_door_state(void);

#endif