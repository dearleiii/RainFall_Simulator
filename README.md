# rainFall
Performance optimization and parallelism  


Check Script - Usage: ./check.py [dimension] [validation file] [output file]

Test 4x4 Input & Output (./rainfall [P] 10 0.25 4 sample_4x4.in)

Test 16x16 Input & Output (./rainfall [P] 20 0.5 16 sample_16x16.in)

Test 32x32 Input & Output (./rainfall [P] 20 0.5 32 sample_32x32.in)

Test 128x128 Input & Output (./rainfall [P] 30 0.25 128 sample_128x128.in)

Test 512x512 Input & Output (./rainfall [P] 30 0.75 512 sample_512x512.in)

Test 2048x2048 Input & Output (./rainfall [P] 35 0.5 2048 sample_2048x2048.in)

Measurement Input 4096x4096 Input & Output (note they are gzip'ed) 

Use the following program arguments: ./rainfall [P] 50 0.5 4096 measurement_4096x4096.in
