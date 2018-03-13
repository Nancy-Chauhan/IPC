# IPC-
INTER PROCESS COMMUNICATION BETWEEN REQ.CLIENT SERVER & PROCESSOR 

SERVER

Server like main part of ipc project because that maintain both services requesting  from sender & processing from processor.
In this project we use 3 processor but count of clients and processors are unlimited depends upon the application.
Server connected with the clients and processors via single-single pipe .
The pipe is created by server using pipe system call.
For making connection between clients and processor we pass the FD,s from server using 
        excel command. 
two types of FD – read FD and write FD.
READ FD use for read the data & WRITE FD is used for write the data.

REQUESTING CLIENTS

Requesting clients means users which are sending the request to server for process the data.
There have three clients-
Addition
Subtraction
Multiplication
Every  client send 2 variable and a single operator (+) to server for process the data.
Variables having some value which are processed by processors to client through server.

PROCESSORS

According to the project there have three processors which process the data which send from client to server.
Sever send the client requested data according to operator value to the processor.
Means there have following type processors:
Addition purpose processor(+)
Subtraction purpose processor(-)
Multiplication purpose processor(*)

