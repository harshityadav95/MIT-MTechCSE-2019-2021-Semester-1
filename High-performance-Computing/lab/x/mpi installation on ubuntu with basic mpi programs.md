# Installing and Basic Programs on MPI C


### Installing MPI on Ubuntu

Run the following command on `terminal`
```
sudo apt update
sudo apt install mpich
```

#### Compiling the MPI Program

```
mpicc -o hello_world_c hello_world.c
```
#### Executing MPI Programs

```
mpiexec -np 4 ./hello_world_c
```
> -np : Number of Processes


### Basic MPI Programs


>#### Basic MPI Function

>*`MPI_Init(&argc,&argv)` : Initialize MPI part of the program. `Compulsory for all MPI programs`.

>*`MPI_Comm_rank(MPI_COMM_WORLD,&rank)` : Returns the rank (process id) of that processes.

>*`MPI_Comm_size(MPI_COMM_WORLD,&size)`: Returns the total number of processes.

>*`MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Status *status)`:Recieves data from specified rank.

>*`MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm)` : Sends data to the specified rank.

>*`MPI_Scatter(void *send_data,int send_count,MPI_Datatype send_datatype,void *recv_data,int recv_count,MPI_Datatype recv_datatype,int root,MPI_Comm communicator)` : Scatters data from a specified rank accross all the processes.

>*`MPI_Gather(void *send_data,int send_count,MPI_Datatype send_datatype,void *recv_data,int recv_count,MPI_Datatype recv_datatype,int root, MPI_Comm communicator)` : Gathers data from all process to the specified process.

>*`MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype,MPI_Op op, int root, MPI_Comm comm)` :Reduces the specified a array by a specific operation accross all processes.


#### References
* [http://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/](http://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/)
* https://github.com/nowke/hpc_lab/tree/master/10_mpi_routines
* [![Introduction to MPI Programming, part 1, by Hristo Iliev](http://img.youtube.com/vi/LBgx_S5ougk/0.jpg)](https://www.youtube.com/watch?v=LBgx_S5ougk "Introduction to MPI Programming, part 1, by Hristo Iliev") 