import os

for i in range(1, 1001):
    with open("{:03d}_test.txt".format(i), 'w') as f:
        f.write(i * "XXXXXXXX\n")
