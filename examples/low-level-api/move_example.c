/*******************************************************************************
 * Copyright (C) 2023 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "dml/dml.h"
#include "examples_utils.h"

#define BUFFER_SIZE 1024 // 1 KB

/*
* This example demonstrates how to create and run a mem_move operation
*/

int main(int argc, char **argv)
{
    dml_path_t execution_path = DML_PATH_SW;

    // Get path from input argument
    int parse_ret = parse_execution_path(argc, argv, &execution_path);
    if (parse_ret != 0) {
        return 1;
    }

    printf("Starting memory move job example.\n");
    printf("Moving region of size 1KB.\n");

    dml_job_t *dml_job_ptr = NULL;
    uint32_t size = 0u;

    uint8_t source      [BUFFER_SIZE];
    uint8_t destination [BUFFER_SIZE];

    for(int i = 0; i < BUFFER_SIZE; i++){
        source[i] = i % 256;
    }

    dml_status_t status = dml_get_job_size(execution_path, &size);
    if (DML_STATUS_OK != status) {
        printf("An error (%u) occured during getting job size.\n", status);
        return 1;
    }

    dml_job_ptr = (dml_job_t *)malloc(size);

    status = dml_init_job(execution_path, dml_job_ptr);
    if (DML_STATUS_OK != status) {
        printf("An error (%u) occured during job initialization.\n", status);
        free(dml_job_ptr);
        return 1;
    }
    
    dml_job_ptr->operation              = DML_OP_MEM_MOVE;
    dml_job_ptr->source_first_ptr       = source;
    dml_job_ptr->destination_first_ptr  = destination;
    dml_job_ptr->source_length          = BUFFER_SIZE;

    status = dml_execute_job(dml_job_ptr, DML_WAIT_MODE_BUSY_POLL);
    if (DML_STATUS_OK != status) {
        printf("An error (%u) occured during job execution.\n", status);
        dml_finalize_job(dml_job_ptr);
        free(dml_job_ptr);
        return 1;
    }

    for(int i = 0; i < BUFFER_SIZE; i++){
        if(destination[i] != source[i]){
            printf("Error: Operation result is incorrect.\n");
            dml_finalize_job(dml_job_ptr);
            free(dml_job_ptr);
            return 1;
        }
    }

    status = dml_finalize_job(dml_job_ptr);
    if (DML_STATUS_OK != status) {
        printf("An error (%u) occured during job finalization.\n", status);
        free(dml_job_ptr);
        return 1;
    }
    free(dml_job_ptr);

    printf("Job Completed Successfully.\n");
    return 0;
}
