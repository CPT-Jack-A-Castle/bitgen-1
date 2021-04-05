#!/usr/bin/python

import os
import sys
import os.path

def printHeader(str) :
   "Prints header text"
   print "===================== " + str + " ====================="
   return

if not os.path.isfile("../bitgen-ppc"):
	print "Error, application binary does not exist"
	sys.exit()

retvalRemovexor = os.system("../bitgen-ppc removexor")
if retvalRemovexor == 0:
	print "Error, test can not be performed with static xor configured"
	sys.exit()



#============ Start of tests ============

retval1 = os.system("../bitgen-ppc setnextnum 29")
if retval1 != 0:
	print "test init error"
	sys.exit()


printHeader("Test 1 bitgen-ppc otpgen 2")
retval1 = os.system("../bitgen-ppc otpgen 2 hash hasdjasdhajshdajshdasdiusduaisudausdiuasyduasyduasydiasuydaisydiasydiausydiauysdiausydiuasydiuasydiausydiuasyduiasydiuasydiauydiausydiausydiuasydiuasydiuasydiuasydiususususuususudaydiuasyd")
if retval1 != 0:
	print "test 1 error"
	sys.exit()


if not os.path.isfile("ppc_address_29_private_pad1.txt"):
	print "test 1 file error"
	sys.exit()

if not os.path.isfile("ppc_address_29_private_pad2.txt"):
	print "test 1 file error"
	sys.exit()


if not os.path.isfile("ppc_address_29_pad_share.txt"):
	print "test 1 file error"
	sys.exit()

with open("ppc_address_29_private_pad1.txt") as f:
	content1 = f.read()  
	if "DF872B08D5E67C7C447CE20AE566F9FA336F3713AF8B25F9DC80C02864B63387" not in content1: 
		print "test 1 file error for pad 1"
		sys.exit()

with open("ppc_address_29_private_pad2.txt") as f:
	content2 = f.read()  
	if "903F0D4941884F9D82E65DB69A9D0354F588A10EF64455D08526B37BC39C2AD6" not in content2: 
		print "test 1 file error for pad 2"
		sys.exit()


#--------------------------------------------------

printHeader("Test 2 bitgen-ppc otpgen 2 hex")
retval1 = os.system("../bitgen-ppc otpgen 2 hex 1231231239999ABCEEEFFE1289371298371298371298379821731982731982371982739182739182739187238123123123123312123123991231230030312331")
if retval1 != 0:
	print "test 2 error"
	sys.exit()


with open("ppc_address_30_private_pad1.txt") as f:
	content1 = f.read()  
	if "1231231239999ABCEEEFFE128937129837129837129837982173198273198237" not in content1: 
		print "test 2 file error for pad 1"
		sys.exit()


with open("ppc_address_30_private_pad2.txt") as f:
	content1 = f.read()  
	if "1982739182739182739187238123123123123312123123991231230030312331" not in content1: 
		print "test 2 file error for pad 2"
		sys.exit()


#--------------------------------------------------

printHeader("Test 3 bitgen-ppc otpgen 2 hex")
retval1 = os.system("../bitgen-ppc otp 1231231239999ABCEEEFFE128937129837129837129837982173198273198237 1982739182739182739187238123123123123312123123991231230030312331")
if retval1 != 0:
	print "test 3 error"
	sys.exit()


with open("ppc_address_PP8a3iGCXSHz3uMrQbBahtUdLMbQzKqeDT_private.txt") as f:
	content1 = f.read()  
	if "U5W8nphtx6C5j8nB9sL54wpHpHiW1oHaHN5JbJjj3GLnunZNe6Mz" not in content1: 
		print "test 3 file error for private"
		sys.exit()


if not os.path.isfile("ppc_address_PP8a3iGCXSHz3uMrQbBahtUdLMbQzKqeDT_share.txt"):
	print "test 3 file error"
	sys.exit()



#--------------------------------------------------

printHeader("Test 4 bitgen-ppc otpgen 2 dice")
retval1 = os.system("../bitgen-ppc otpgen 2 dice 12312312312362153625365461546154615461256253615236253625316253612536125361253162536125361253265366262662616161616626352365216351623561235123612531625361253162616161666161661616161231231232131231232131")
if retval1 != 0:
	print "test 4 error"
	sys.exit()


with open("ppc_address_31_private_pad1.txt") as f:
	content1 = f.read()  
	if "35BEB4E5BAC9F82421DD739E42CDC11EDA0613A6C5B464CEAF85568DEDD1EB57" not in content1: 
		print "test 4 file error for pad 1"
		sys.exit()

with open("ppc_address_31_private_pad2.txt") as f:
	content1 = f.read()  
	if "DCD911BE16728E4F98C91508E367815884008495F5B2F345C0EECD2DF5F1AD64" not in content1: 
		print "test 4 file error for pad 2"
		sys.exit()



#--------------------------------------------------

printHeader("Test 5 bitgen-ppc otpgen 2 dice")
retval1 = os.system("../bitgen-ppc otp 35BEB4E5BAC9F82421DD739E42CDC11EDA0613A6C5B464CEAF85568DEDD1EB57 DCD911BE16728E4F98C91508E367815884008495F5B2F345C0EECD2DF5F1AD64")
if retval1 != 0:
	print "test 5 error"
	sys.exit()



with open("ppc_address_PN5thXzGGCGb99xX3W4nrHeX2CpZfpTaAm_private.txt") as f:
	content1 = f.read()  
	if "UCw6j8kLWka7KeangwxBHj6qMgdh9L7Npx7qyHiXXmFdve7veZaZ" not in content1: 
		print "test 5 file error for private"
		sys.exit()


if not os.path.isfile("ppc_address_PN5thXzGGCGb99xX3W4nrHeX2CpZfpTaAm_share.ps"):
	print "test 5 file error"
	sys.exit()


#--------------------------------------------------

printHeader("Test 6 bitgen-ppc otpgen 2 dice")
retval1 = os.system("../bitgen-ppc otpgen 3 hash hfsdhfhhfhfhfhhfsdjdsfhkjKJhKJHKJHKJHkjhkjhKJHKJHkjhkjhKJHKJHkjhkjhkJHKJhkjhkjhkjhskjdfhsdjkfsdjkfjsdfjksjkdfkjsdfkjsdfsdfdyfysdfusdfysidufysifdsifsoo")
if retval1 != 0:
	print "test 6 error"
	sys.exit()


with open("ppc_address_32_private_pad1.txt") as f:
	content1 = f.read()  
	if "C44CE66839D8F5CE2BBFCC3A70257C94106FF4152806CADCF49CC38C989FCD9D" not in content1: 
		print "test 6 file error for pad 1"
		sys.exit()

with open("ppc_address_32_private_pad2.txt") as f:
	content1 = f.read()  
	if "3FA02A27A59366906263B07E79391DC8F963D8373B94A4D6A7634923B7866023" not in content1: 
		print "test 6 file error for pad 2"
		sys.exit()

with open("ppc_address_32_private_pad3.txt") as f:
	content1 = f.read()  
	if "5A005FAD73D71923638C90C115E113E87574F31177EB23ED79E90D411182A6F0" not in content1: 
		print "test 6 file error for pad 3"
		sys.exit()


if not os.path.isfile("ppc_address_32_pad_share.txt"):
	print "test 6 file error"
	sys.exit()


#--------------------------------------------------

printHeader("Test 7 bitgen-ppc otpgen 2 dice")
retval1 = os.system("../bitgen-ppc otp C44CE66839D8F5CE2BBFCC3A70257C94106FF4152806CADCF49CC38C989FCD9D 3FA02A27A59366906263B07E79391DC8F963D8373B94A4D6A7634923B7866023 5A005FAD73D71923638C90C115E113E87574F31177EB23ED79E90D411182A6F0")
if retval1 != 0:
	print "test 7 error"
	sys.exit()

with open("ppc_address_PDGQ7sL1YxNmVLAPC8RJgNiyNeCRpxuUHb_private.txt") as f:
	content1 = f.read()  
	if "UAY9fziYmapNSNVbaz8JzJrcYCC1ft1DF9co6knTpRSXb332giXe" not in content1: 
		print "test 7 file error for private"
		sys.exit()


if not os.path.isfile("ppc_address_PDGQ7sL1YxNmVLAPC8RJgNiyNeCRpxuUHb_share.txt"):
	print "test 7 file error"
	sys.exit()

#------------------------------------------------------

printHeader("Test 8 bitgen-ppc otp")
retval1 = os.system("../bitgen-ppc otp 1000000000000000000000000000000000000000000000000000000000000000 0100000000000000000000000000000000000000000000000000000000000000 0010000000000000000000000000000000000000000000000000000000000000")
if retval1 != 0:
	print "test 8 error"
	sys.exit()

with open("ppc_address_PHEwG2egS1yXu9F9ME9kZMtW2vUMWS3mwD_private.txt") as f:
	content1 = f.read()  
	if "U5gZLEQ6LEc5NgjYvi85Yp6cP92PD7KnUtxzrv5p66HceNeARuif" not in content1: 
		print "test 8 file error for private"
		sys.exit()


if not os.path.isfile("ppc_address_PHEwG2egS1yXu9F9ME9kZMtW2vUMWS3mwD_share.txt"):
	print "test 8 file error"
	sys.exit()

#------------------------------------------------------

printHeader("Test 9 bitgen-ppc otp")
retval1 = os.system("../bitgen-ppc otp 1111111111111111111111111111111111111111111111111111111111111111 2222222222222222222222222222222222222222222222222222222222222222 4444444444444444444444444444444444444444444444444444444444444444")
if retval1 != 0:
	print "test 9 error"
	sys.exit()

with open("ppc_address_P9h5C4mnjUVJNbLLMcP3cATWxUibMwyRHW_private.txt") as f:
	content1 = f.read()  
	if "U97cq9F7Fc26K1JCTqR7KsA6G3rpAB9a4rMabQZhkXQPBuE19MWN" not in content1: 
		print "test 9 file error for private"
		sys.exit()


if not os.path.isfile("ppc_address_P9h5C4mnjUVJNbLLMcP3cATWxUibMwyRHW_share.txt"):
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
