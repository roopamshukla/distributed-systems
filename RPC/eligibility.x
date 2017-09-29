struct square_in
{
/*input arg*/
char arg1[100];
    int arg2;
};

struct square_out
{
/*op result*/
char res1[100];
    char res2[100];
};

program SQUARE_PROG
{
version SQUARE_VERS
{
square_out SQUAREPROC(square_in)=1; /*proc no=1*/
}=1; /*version no*/
}=0x31230000;/*prog no*/
