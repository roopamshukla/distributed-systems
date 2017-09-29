#include"rpc/rpc.h"
#include"eligibility.h"
#include"stdlib.h"
#include"math.h"

square_out *squareproc_1_svc(square_in *inp,struct svc_req *rqstp)
{
     static square_out out;
     int i=0;
     while(inp->arg1[i] != '\0')
     {
     out.res1[i]= inp->arg1[i];
     i++;
    }
    if(inp->arg2<60)
    {
    strcpy(out.res2,"Status : Not Eligible");
    }else{
    strcpy(out.res2,"Status : Eligible");
    }
     return(&out);
}
