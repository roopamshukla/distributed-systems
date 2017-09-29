#include"errno.h"
#include"rpc/rpc.h"
#include"eligibility.h"
#include"stdio.h"
#include"stdlib.h"
#include"math.h"

int main(int argc,char **argv)
{
     CLIENT *cl;
 square_in in;
 square_out *outp;
 if(argc!=4)
     {
           printf("\n\n error:insufficient arguments!!!");
           exit(-1);
     }

 cl=clnt_create(argv[1],SQUARE_PROG,SQUARE_VERS,"tcp");
 strcpy(in.arg1, argv[2]);
 in.arg2 = atoi(argv[3]);

     if(cl==NULL)
     {
           printf("\nerror:%s",strerror(errno));
           exit(-1);
     }

     if((outp=squareproc_1(&in,cl))==NULL)
     {
           printf("\nerror :%s",clnt_sperror(cl,argv[1]));
           exit(-1);
     }

     printf("User Name : %s\n", outp->res1);
     printf("%s\n",outp->res2);
     exit(0);
}
