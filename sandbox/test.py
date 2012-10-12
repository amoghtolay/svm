#!/usr/bin/env python

import subprocess

process = subprocess.Popen(['./test.sh'])
error = process.wait();
if error != 0:
	print "There were some errors"
	print "It returned error code ", error

