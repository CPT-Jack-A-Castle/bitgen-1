#!/usr/bin/python

import os
import sys
import os.path

def printHeader(str) :
   "Prints header text"
   print "===================== " + str + " ====================="
   return

if not os.path.isfile("../bitgen-vtc"):
	print "Error, application binary does not exist"
	sys.exit()

retvalRemovexor = os.system("../bitgen-vtc removexor")
if retvalRemovexor == 0:
	print "Error, test can not be performed with static xor configured"
	sys.exit()



#============ Start of tests ============

retval1 = os.system("../bitgen-vtc setnextnum 5")
if retval1 != 0:
	print "test init error"
	sys.exit()


printHeader("Test 1 bitgen-vtc otpgen 2")
retval1 = os.system("../bitgen-vtc otpgen 2 hash hasdjasdhajshdajshdasdiusduaisudausdiuasyduasyduasydiasuydaisydiasydiausydiauysdiausydiuasydiuasydiausydiuasyduiasydiuasydiauydiausydiausydiuasydiuasydiuasydiuasydiususususuususudaydiuasyd")
if retval1 != 0:
	print "test 1 error"
	sys.exit()


if not os.path.isfile("vtc_address_5_private_pad1.txt"):
	print "test 1 file error"
	sys.exit()

if not os.path.isfile("vtc_address_5_private_pad2.txt"):
	print "test 1 file error"
	sys.exit()


if not os.path.isfile("vtc_address_5_pad_share.txt"):
	print "test 1 file error"
	sys.exit()

with open("vtc_address_5_private_pad1.txt") as f:
	content1 = f.read()  
	if "DF872B08D5E67C7C447CE20AE566F9FA336F3713AF8B25F9DC80C02864B63387" not in content1: 
		print "test 1 file error for pad 1"
		sys.exit()

with open("vtc_address_5_private_pad2.txt") as f:
	content2 = f.read()  
	if "903F0D4941884F9D82E65DB69A9D0354F588A10EF64455D08526B37BC39C2AD6" not in content2: 
		print "test 1 file error for pad 2"
		sys.exit()


#--------------------------------------------------

printHeader("Test 2 bitgen-vtc otpgen 2 hex")
retval1 = os.system("../bitgen-vtc otpgen 2 hex 1231231239999ABCEEEFFE1289371298371298371298379821731982731982371982739182739182739187238123123123123312123123991231230030312331")
if retval1 != 0:
	print "test 2 error"
	sys.exit()


with open("vtc_address_6_private_pad1.txt") as f:
	content1 = f.read()  
	if "1231231239999ABCEEEFFE128937129837129837129837982173198273198237" not in content1: 
		print "test 2 file error for pad 1"
		sys.exit()


with open("vtc_address_6_private_pad2.txt") as f:
	content1 = f.read()  
	if "1982739182739182739187238123123123123312123123991231230030312331" not in content1: 
		print "test 2 file error for pad 2"
		sys.exit()


#--------------------------------------------------

printHeader("Test 3 bitgen-vtc otpgen 2 hex")
retval1 = os.system("../bitgen-vtc otp 1231231239999ABCEEEFFE128937129837129837129837982173198273198237 1982739182739182739187238123123123123312123123991231230030312331")
if retval1 != 0:
	print "test 3 error"
	sys.exit()


with open("vtc_address_VpYDoT2otKi18qbEoJWgTtqDQRiWRsGHZD_private.txt") as f:
	content1 = f.read()  
	if "WSnDwQUHkYrHKQzU15eMojL5oEvwNVdCtS3PYaHEtvQBR5ic4t5r" not in content1: 
		print "test 3 file error for private"
		sys.exit()


if not os.path.isfile("vtc_address_VpYDoT2otKi18qbEoJWgTtqDQRiWRsGHZD_share.txt"):
	print "test 3 file error"
	sys.exit()



#--------------------------------------------------

printHeader("Test 4 bitgen-vtc otpgen 2 dice")
retval1 = os.system("../bitgen-vtc otpgen 2 dice 12312312312362153625365461546154615461256253615236253625316253612536125361253162536125361253265366262662616161616626352365216351623561235123612531625361253162616161666161661616161231231232131231232131")
if retval1 != 0:
	print "test 4 error"
	sys.exit()


with open("vtc_address_7_private_pad1.txt") as f:
	content1 = f.read()  
	if "35BEB4E5BAC9F82421DD739E42CDC11EDA0613A6C5B464CEAF85568DEDD1EB57" not in content1: 
		print "test 4 file error for pad 1"
		sys.exit()

with open("vtc_address_7_private_pad2.txt") as f:
	content1 = f.read()  
	if "DCD911BE16728E4F98C91508E367815884008495F5B2F345C0EECD2DF5F1AD64" not in content1: 
		print "test 4 file error for pad 2"
		sys.exit()



#--------------------------------------------------

printHeader("Test 5 bitgen-vtc otpgen 2 dice")
retval1 = os.system("../bitgen-vtc otp 35BEB4E5BAC9F82421DD739E42CDC11EDA0613A6C5B464CEAF85568DEDD1EB57 DCD911BE16728E4F98C91508E367815884008495F5B2F345C0EECD2DF5F1AD64")
if retval1 != 0:
	print "test 5 error"
	sys.exit()



with open("vtc_address_VoVYTGksd5gcE6BuSDPtcJ176GwezinFqK_private.txt") as f:
	content1 = f.read()  
	if "WaDBsiWjKDEJuvo5YAGU2WcdLdr8W2T1S25vvZG3PRK2RwKjYvpY" not in content1: 
		print "test 5 file error for private"
		sys.exit()


if not os.path.isfile("vtc_address_VoVYTGksd5gcE6BuSDPtcJ176GwezinFqK_share.ps"):
	print "test 5 file error"
	sys.exit()


#--------------------------------------------------

printHeader("Test 6 bitgen-vtc otpgen 2 dice")
retval1 = os.system("../bitgen-vtc otpgen 3 hash hfsdhfhhfhfhfhhfsdjdsfhkjKJhKJHKJHKJHkjhkjhKJHKJHkjhkjhKJHKJHkjhkjhkJHKJhkjhkjhkjhskjdfhsdjkfsdjkfjsdfjksjkdfkjsdfkjsdfsdfdyfysdfusdfysidufysifdsifsoo")
if retval1 != 0:
	print "test 6 error"
	sys.exit()


with open("vtc_address_8_private_pad1.txt") as f:
	content1 = f.read()  
	if "C44CE66839D8F5CE2BBFCC3A70257C94106FF4152806CADCF49CC38C989FCD9D" not in content1: 
		print "test 6 file error for pad 1"
		sys.exit()

with open("vtc_address_8_private_pad2.txt") as f:
	content1 = f.read()  
	if "3FA02A27A59366906263B07E79391DC8F963D8373B94A4D6A7634923B7866023" not in content1: 
		print "test 6 file error for pad 2"
		sys.exit()

with open("vtc_address_8_private_pad3.txt") as f:
	content1 = f.read()  
	if "5A005FAD73D71923638C90C115E113E87574F31177EB23ED79E90D411182A6F0" not in content1: 
		print "test 6 file error for pad 3"
		sys.exit()


if not os.path.isfile("vtc_address_8_pad_share.txt"):
	print "test 6 file error"
	sys.exit()


#--------------------------------------------------

printHeader("Test 7 bitgen-vtc otpgen 2 dice")
retval1 = os.system("../bitgen-vtc otp C44CE66839D8F5CE2BBFCC3A70257C94106FF4152806CADCF49CC38C989FCD9D 3FA02A27A59366906263B07E79391DC8F963D8373B94A4D6A7634923B7866023 5A005FAD73D71923638C90C115E113E87574F31177EB23ED79E90D411182A6F0")
if retval1 != 0:
	print "test 7 error"
	sys.exit()

with open("vtc_address_Veg3sc6cuqnnaGPmaqkQSP5ZSiKXAmPdf5_private.txt") as f:
	content1 = f.read()  
	if "WXpEpaUwa3Ua2ehtSCSbj6NQX9QT2aLqrDat42Kyg5Vv6LETtFaq" not in content1: 
		print "test 7 file error for private"
		sys.exit()


if not os.path.isfile("vtc_address_Veg3sc6cuqnnaGPmaqkQSP5ZSiKXAmPdf5_share.txt"):
	print "test 7 file error"
	sys.exit()

#------------------------------------------------------

printHeader("Test 8 bitgen-vtc otp")
retval1 = os.system("../bitgen-vtc otp 1000000000000000000000000000000000000000000000000000000000000000 0100000000000000000000000000000000000000000000000000000000000000 0010000000000000000000000000000000000000000000000000000000000000")
if retval1 != 0:
	print "test 8 error"
	sys.exit()

with open("vtc_address_Vieb1mRHnuPYz5UXjwUrKNF66zbSuyVpda_private.txt") as f:
	content1 = f.read()  
	if "WSxeUpAV8hGGxxwqmvSNHbcQN6EpZofR5xw5pBdKwkM19fpK3o4A" not in content1: 
		print "test 8 file error for private"
		sys.exit()


if not os.path.isfile("vtc_address_Vieb1mRHnuPYz5UXjwUrKNF66zbSuyVpda_share.txt"):
	print "test 8 file error"
	sys.exit()

#------------------------------------------------------

printHeader("Test 9 bitgen-vtc otp")
retval1 = os.system("../bitgen-vtc otp 1111111111111111111111111111111111111111111111111111111111111111 2222222222222222222222222222222222222222222222222222222222222222 4444444444444444444444444444444444444444444444444444444444444444")
if retval1 != 0:
	print "test 9 error"
	sys.exit()

with open("vtc_address_Vb6iwoYQ6MuKTXZikKi9NAp72YqgqgYz8S_private.txt") as f:
	content1 = f.read()  
	if "WWPhyj1W44gHuHWVK3jQ4eftF15FWsVCfvKfYg7DcBTmhCPoEKum" not in content1: 
		print "test 9 file error for private"
		sys.exit()


if not os.path.isfile("vtc_address_Vb6iwoYQ6MuKTXZikKi9NAp72YqgqgYz8S_share.txt"):
	print "test 9 file error"
	sys.exit()


print ""
print ""
print ""
print "Cleaning up"
os.system("rm *.txt *.ps")

print ""
print ""
print ""
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++ All tests passed OK +++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"


sys.exit(123)
