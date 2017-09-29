**********ONLY FOR LINUX AND UNIX*************

1) compile using :

rpcgen -C eligibility.x && cc -c client.c -o client.o && cc -c eligibility_clnt.c -o eligibility_clnt.o && cc -c eligibility_xdr.c -o eligibility.xdr.o && cc -o client client.o eligibility_clnt.o eligibility.xdr.o && cc -c client.c server.c eligibility_xdr.c && cc -c server.c -o server.o && cc -c eligibility_svc.c -o eligibility_svc.o && cc -o server server.o eligibility_svc.o eligibility_xdr.o

2) run server :

./server &

3) run client :

./client localhost "User Name" "Marks"

Note 1 : if error comes

Cannot register service: RPC: Unable to receive; errno = Success
unable to register (SQUARE_PROG, SQUARE_VERS, udp)

Install 'portmap' using

sudo apt install portmap

then run 'rpcinfo'

now run server and client

Note 2 : rpcinfo needs to be run everytime before running server and client


