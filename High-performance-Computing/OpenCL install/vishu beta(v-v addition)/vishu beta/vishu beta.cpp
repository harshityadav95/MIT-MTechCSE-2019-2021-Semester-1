// testCL.cpp : A COMPLETE PROGRAM FOR VECTOR-VECTOR ADDITION

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <CL/cl.h>
#include<time.h>

#define MAX_SOURCE_SIZE (0x100000)

int main(void) {
    // Create the two input vectors
    int i;
	clock_t start, end;

 	start = clock();
    const int LIST_SIZE = 102400;
    int *A = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *B = (int*)malloc(sizeof(int)*LIST_SIZE);

    //Initialize the input vectors
    for(i = 0; i < LIST_SIZE; i++)
    {
        A[i] = i;
        B[i] = LIST_SIZE - i;
    }

    // Load the kernel source code into the array source_str
    FILE *fp;
    char *source_str;
    size_t source_size;

    fp = fopen("vectorCLKernel.cl", "r"); 


    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
		getchar();
        exit(1);
    }
    source_str = (char*)malloc(MAX_SOURCE_SIZE);
    source_size = fread( source_str, 1, MAX_SOURCE_SIZE, fp);
    fclose( fp );

    // Get platform and device information
    cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
	
	
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	cl_platform_info info;
	ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_ALL, 1,&device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, CL_QUEUE_PROFILING_ENABLE, &ret);

    // Create memory buffers on the device for each vector
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,LIST_SIZE * sizeof(int), NULL, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,LIST_SIZE * sizeof(int), NULL, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(int), A, 0, NULL, NULL);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(int), B, 0, NULL, NULL);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1,(const char**)&source_str, (const size_t *)&source_size, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vector_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&c_mem_obj);

    // Execute the OpenCL kernel on the list
    size_t global_item_size = LIST_SIZE; // Process the entire lists
    size_t local_item_size = 64; // Process in groups of 64
	
	
	// Read the memory buffer C on the device to the local variable C

	int *C = (int*)malloc(sizeof(int)*LIST_SIZE);
	
	cl_event event;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL,&global_item_size, &local_item_size, 0, NULL, &event);
	ret = clFinish(command_queue);
	cl_ulong time_start, time_end;
	double total_time;
	
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_START, sizeof(time_start), &time_start, NULL);
	 			
	clGetEventProfilingInfo(event, CL_PROFILING_COMMAND_END, sizeof(time_end), &time_end, NULL);
	total_time = double (time_end - time_start);

    
	ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0,LIST_SIZE * sizeof(int), C, 0, NULL, NULL);
	    
   // Display the result to the screen
    for(i = 0; i < LIST_SIZE; i++)
        printf("%d + %d = %d\n", A[i], B[i], C[i]);
	
    // Clean up
    ret = clFlush(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    free(A);
    free(B);
    free(C);
	end = clock();
    
	printf("\n\n Time taken to execute the KERNEL in milliseconds = %0.3f msec\n\n", total_time/1000);
	printf( "\nTime taken to execute the whole program in seconds: %0.3f Seconds\n", (end-start)/(double)CLOCKS_PER_SEC );
	printf("Done");
	getchar();

	return 0;
}

