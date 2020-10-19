#!/bin/bash

WORKER_COUNT=8
DIR=$(dirname "${BASH_SOURCE[0]}")
cd $DIR

# low-quality parallelized workers
seq $WORKER_COUNT | parallel -j $WORKER_COUNT python2 ./worker.py '{}'

