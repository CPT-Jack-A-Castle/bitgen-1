#!/usr/bin/python

import os
import sys
import os.path

def printHeader(str) :
   "Prints header text"
   print "===================== " + str + " ====================="
   return

if not os.path.isfile("../bitgen-bch"):
	print "Error, application binary does not exist"
	sys.exit()




#============ Start of tests ============

printHeader("Test 1 bitgen-bch info")
retval1 = os.system("../bitgen-bch info Kyaogh9vZXqRkVr8yyyqQuTTataBGzv4GMY7g5nK9kTsEzu9nQHK > out.txt")
if retval1 != 0:
	print "test 1 error"
	sys.exit()


with open("out.txt") as f:
	content2 = f.read()  
	#print content2
	if "qrcq75cn7w9wtrwcztmzsz726cy4vza5cchnymk983" not in content2: 
		print "test 1 file error"
		sys.exit()



printHeader("Test 2 bitgen-bch info")
retval1 = os.system("../bitgen-bch info L4HLDQ4ReQkGYY8GrZ3yUHk4uEojJPjQ2azCWdbb5X5sfv3pnU1G > out2.txt")
if retval1 != 0:
	print "test 2 error"
	sys.exit()


with open("out2.txt") as f:
	content2 = f.read()  
	if "qpvckzzf9r2fkuzr5ccn4r3472z8ehgcpusa6zjsew" not in content2: 
		print "test 2 file error"
		sys.exit()


printHeader("Test 3 bitgen-bch info")
retval1 = os.system("../bitgen-bch info KwokcmFgZWAMf2UtmD8QSizupVwnpTDYJK2wni1PFsdWTsaQz2dL > out3.txt")
if retval1 != 0:
	print "test 3 error"
	sys.exit()


with open("out3.txt") as f:
	content2 = f.read()  
	if "qqum3eyuqmvfyjefsyf62g6pr9e72rrpgu2s3gl33h" not in content2: 
		print "test 3 file error"
		sys.exit()



printHeader("Test 4 bitgen-bch info")
retval1 = os.system("../bitgen-bch info 16b5WjNodVADXHeKDds2isVr7wX4yuHrFY > out4.txt")
if retval1 != 0:
	print "test 4 error"
	sys.exit()


with open("out4.txt") as f:
	content2 = f.read()  
	if "qq754zw7yn6jgvveszndxm08ygh9yue0jvd7lerczt" not in content2: 
		print "test 4 file error"
		sys.exit()


printHeader("Test 5 bitgen-bch info")
retval1 = os.system("../bitgen-bch info 16cLvaUdpwkiApbwRbWKUJVSW5PJ5B1ks > out5.txt")
if retval1 != 0:
	print "test 5 error"
	sys.exit()


with open("out5.txt") as f:
	content2 = f.read()  
	if "qqqsl9298sf36lfnacn2pcdmvh0xvaqf55d5rj2tvw" not in content2: 
		print "test 5 file error"
		sys.exit()


printHeader("Test 6 bitgen-bch info")
retval1 = os.system("../bitgen-bch info 3P14159f73E4gFr7JterCCQh9QjiTjiZrG > out6.txt")
if retval1 != 0:
	print "test 6 error"
	sys.exit()


with open("out6.txt") as f:
	content2 = f.read()  
	if "pr5u8hgvq74vwctea0rk5mrc6nt8cmqkpg6fa7u8sd" not in content2: 
		print "test 6 file error"
		sys.exit()



printHeader("Test 7 bitgen-bch info")
retval1 = os.system("../bitgen-bch info pr5u8hgvq74vwctea0rk5mrc6nt8cmqkpg6fa7u8sd > out7.txt")
if retval1 != 0:
	print "test 7 error"
	sys.exit()


with open("out7.txt") as f:
	content2 = f.read()  
	if "3P14159f73E4gFr7JterCCQh9QjiTjiZrG" not in content2: 
		print "test 7 file error"
		sys.exit()


printHeader("Test 8 bitgen-bch info")
retval1 = os.system("../bitgen-bch info qryyksu8hxnwrllx59vrrzjev8958mquesg9hlgvc8 > out8.txt")
if retval1 != 0:
	print "test 8 error"
	sys.exit()

with open("out8.txt") as f:
	content2 = f.read()  
	if "qryyksu8hxnwrllx59vrrzjev8958mquesg9hlgvc8" not in content2: 
		print "test 8 file error"
		sys.exit()


printHeader("Test 9 bitgen-bch info")
retval1 = os.system("../bitgen-bch info L4HLDQ4ReQkGYY8GrZ3yUHk4uEojJPjQ2azCWdbb5X5sfv3pnU1G > out9.txt")
if retval1 != 0:
	print "test 9 error"
	sys.exit()

with open("out9.txt") as f:
	content2 = f.read()  
	if "qpvckzzf9r2fkuzr5ccn4r3472z8ehgcpusa6zjsew" not in content2: 
		print "test 9 file error"
		sys.exit()





printHeader("Test 10 bitgen-bch info")
retval1 = os.system("../bitgen-bch info 31nwvkZwyPdgzjBJZXfDmSWsC4ZLKpYyUw > out10.txt")
if retval1 != 0:
	print "test 10 error"
	sys.exit()

with open("out10.txt") as f:
	content2 = f.read()  
	if "pqq3728yw0y47sqn6l2na30mcw6zm78dzq5ucqzc37" not in content2: 
		print "test 10 file error"
		sys.exit()


printHeader("Test 11 bitgen-bch info")
retval1 = os.system("../bitgen-bch info bitcoincash:ppm2qsznhks23z7629mms6s4cwef74vcwvn0h829pq > out11.txt")
if retval1 != 0:
	print "test 11 error"
	sys.exit()

with open("out11.txt") as f:
	content2 = f.read()  
	if "0876A04053BDA0A88BDA5177B86A15C3B29F5598739BEE751420" not in content2: 
		print "test 11 file error"
		sys.exit()


print ""
print ""
print ""
print "Cleaning up"
os.system("rm *.trans *.script *.txt *.sig")

print ""
print ""
print ""
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++ All tests passed OK +++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"


sys.exit(123)
