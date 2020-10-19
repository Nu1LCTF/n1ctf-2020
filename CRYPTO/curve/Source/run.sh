#!/bin/bash

cd `dirname ${BASH_SOURCE[0]}`
exec stdbuf -i0 -o0 -e0 sage ./chall.sage
