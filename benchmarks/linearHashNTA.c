#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <lladd/transactional.h>
#include <unistd.h>


int main(int argc, char** argv) {

  assert(argc == 3);

  int xact_count = atoi(argv[1]);
  int count = atoi(argv[2]);
  int k;

  /*  unlink("storefile.txt");
  unlink("logfile.txt");
  unlink("blob0_file.txt");
  unlink("blob1_file.txt"); */
  
  Tinit();
   int xid = Tbegin();
   
   recordid hash = ThashCreate(xid, sizeof(int), sizeof(int));
   //recordid hash = ThashCreate(xid, VARIABLE_LENGTH, VARIABLE_LENGTH);

   Tcommit(xid);
   
   int i = 0;
   
   for(k = 0; k < xact_count; k++) {
     
     xid = Tbegin();
     
     for(;i < count *(k+1) ; i++) {
       
       ThashInsert(xid, hash, (byte*)&i, sizeof(int), (byte*)&i, sizeof(int));
       
     }
     
     Tcommit(xid);
     
   }

   Tdeinit();

}