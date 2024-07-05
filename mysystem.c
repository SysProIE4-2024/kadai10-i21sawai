/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース
char *execpath="/bin/sh";
// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  int pid=0;
   if(command==NULL){
    return 1;
  }
  if((pid=fork())<0){
    return -1;
  }
  if(pid != 0){
    while (wait(&status)!=pid);
  } else {
    execl(execpath,"sh", "-c" ,command ,NULL);
    perror(execpath);
    exit (127);
  }
  return status;
}

/* 実行例
% ls -l                
total 616
-rw-r--r--  1 takuya  staff     143  7  4 09:43 Makefile
-rw-r--r--  1 takuya  staff    2795  7  4 09:43 README.md
-rw-r--r--  1 takuya  staff  238232  7  4 09:43 README.pdf
-rwxr-xr-x  1 takuya  staff   50392  7  4 14:24 mysysmain
-rw-r--r--  1 takuya  staff     925  7  4 09:43 mysysmain.c
-rw-r--r--  1 takuya  staff     673  7  4 14:30 mysystem.c
-rw-r--r--  1 takuya  staff      90  7  4 09:43 mysystem.h

./mysysmain "ls -l"
% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 takuya  staff     143  7  4 09:43 Makefile
-rw-r--r--  1 takuya  staff    2795  7  4 09:43 README.md
-rw-r--r--  1 takuya  staff  238232  7  4 09:43 README.pdf
-rwxr-xr-x  1 takuya  staff   50392  7  4 14:24 mysysmain
-rw-r--r--  1 takuya  staff     925  7  4 09:43 mysysmain.c
-rw-r--r--  1 takuya  staff    1109  7  4 14:34 mysystem.c
-rw-r--r--  1 takuya  staff      90  7  4 09:43 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 takuya  staff     143  7  4 09:43 Makefile
-rw-r--r--  1 takuya  staff    2795  7  4 09:43 README.md
-rw-r--r--  1 takuya  staff  238232  7  4 09:43 README.pdf
-rwxr-xr-x  1 takuya  staff   50392  7  4 14:24 mysysmain
-rw-r--r--  1 takuya  staff     925  7  4 09:43 mysysmain.c
-rw-r--r--  1 takuya  staff    1109  7  4 14:34 mysystem.c
-rw-r--r--  1 takuya  staff      90  7  4 09:43 mysystem.h
retval = 00000000

 % ./mysysmain        
使い方 : ./mysysmain コマンド文字列

*/
