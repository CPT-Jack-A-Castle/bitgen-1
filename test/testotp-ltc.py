#!/usr/bin/python

import os
import sys
import os.path

def printHeader(str) :
   "Prints header text"
   print "===================== " + str + " ====================="
   return

if not os.path.isfile("../bitgen-btc"):
	print "Error, application binary does not exist"
	sys.exit()

retvalRemovexor = os.system("../bitgen-ltc removexor")
if retvalRemovexor == 0:
	print "Error, test can not be performed with static xor configured"
	sys.exit()



#============ Start of tests ============

retval1 = os.system("../bitgen-ltc setnextnum 17")
if retval1 != 0:
	print "test init error"
	sys.exit()



printHeader("Test 1 bitgen-ltc otpgen 2")
retval1 = os.system("../bitgen-ltc otpgen 2 hash hasdjasdhajshdajshdasdiusduaisudausdiuasyduasyduasydiasuydaisydiasydiausydiauysdiausydiuasydiuasydiausydiuasyduiasydiuasydiauydiausydiausydiuasydiuasydiuasydiuasydiususususuususudaydiuasyd")
if retval1 != 0:
	print "test 1 error"
	sys.exit()


if not os.path.isfile("ltc_address_17_private_pad1.txt"):
	print "test 1 file error"
	sys.exit()

if not os.path.isfile("ltc_address_17_private_pad2.txt"):
	print "test 1 file error"
	sys.exit()


if not os.path.isfile("ltc_address_17_pad_share.txt"):
	print "test 1 file error"
	sys.exit()

with open("ltc_address_17_private_pad1.txt") as f:
	content1 = f.read()  
	#print content1
	if "DF872B08D5E67C7C447CE20AE566F9FA336F3713AF8B25F9DC80C02864B63387" not in content1: 
		print "test 1 file error for pad 1"
		sys.exit()

with open("ltc_address_17_private_pad2.txt") as f:
	content2 = f.read()  
	#print content2
	if "903F0D4941884F9D82E65DB69A9D0354F588A10EF64455D08526B37BC39C2AD6" not in content2: 
		print "test 1 file error for pad 2"
		sys.exit()



#---------------------------------------------------------------------

printHeader("Test 2 bitgen-ltc otpgen 2")
retval1 = os.system("../bitgen-ltc otpgen 2 dice 12312312312312363636351515361253612536125361532612536125361253126351635612531635165361253165321653162536152361253621536125362512312531523512351253521351253152356262626612316236126312636213612631263125")
if retval1 != 0:
	print "test 2 error"
	sys.exit()


if not os.path.isfile("ltc_address_18_pad_share.txt"):
	print "test 2 file error"
	sys.exit()

with open("ltc_address_18_private_pad1.txt") as f:
	content1 = f.read()  
	#print content1
	if "35BEB4DC9076B81B9E31D02890BE30434BE89521D46570B9FF74EF46D2C0903D" not in content1: 
		print "test 2 file error for pad 1"
		sys.exit()

with open("ltc_address_18_private_pad2.txt") as f:
	content2 = f.read()  
	#print content2
	if "A44C877D1F4E41D559B4E98074DF7CF76571CF17D11741D5DAF192A3302DC76A" not in content2: 
		print "test 2 file error for pad 2"
		sys.exit()

#---------------------------------------------------------------------

printHeader("Test 3 bitgen-ltc otpgen 2")
retval1 = os.system("../bitgen-ltc otpgen 2 hex 1293871293871239871238901203123ABCDEFABBABABABCBCBF12312313212038123091823091823091823092183091283092183091823091283091823091811")
if retval1 != 0:
	print "test 3 error"
	sys.exit()


if not os.path.isfile("ltc_address_19_pad_share.txt"):
	print "test 3 file error"
	sys.exit()

with open("ltc_address_19_private_pad1.txt") as f:
	content1 = f.read()  
	if "1293871293871239871238901203123ABCDEFABBABABABCBCBF1231231321203" not in content1: 
		print "test 3 file error for pad 1"
		sys.exit()

with open("ltc_address_19_private_pad2.txt") as f:
	content2 = f.read()  
	if "8123091823091823091823092183091283092183091823091283091823091811" not in content2: 
		print "test 3 file error for pad 2"
		sys.exit()



#---------------------------------------------------------------------

printHeader("Test 4 bitgen-ltc otpgen 3")
retval1 = os.system("../bitgen-ltc otpgen 3 hash aksjdhaskjdhaksjhdakjshdkjashdkasjdhkajsdhaskjdhaskjdhkjadshfkjshdfkjshdfkjhsdjkfhsdkjfhskjdfhskjdhfskdjhfjdsakhfsdfsufudsudfudifuaisudisudisudisduiuisudiasudaisudasoiudaoisufsoiufsoudfihhfhhhfhfhhfsdkjfskdjfhskdjfhskjdfhskdjhfskjdhfksjdhfkjdshfkjsdhfkjsdhfksjdhfkjh")
if retval1 != 0:
	print "test 4 error"
	sys.exit()


if not os.path.isfile("ltc_address_20_pad_share.txt"):
	print "test 4 file error"
	sys.exit()

with open("ltc_address_20_private_pad1.txt") as f:
	content1 = f.read()  
	if "DA0C691DB117736393FC0B54CC3A4E9DE92812FA121C0291643BE94A7BF6AB0E" not in content1: 
		print "test 4 file error for pad 1"
		sys.exit()

with open("ltc_address_20_private_pad2.txt") as f:
	content2 = f.read()  
	if "5B4CFB396CA544386A1BE17C0FDD89C38D17A08DFF7EE16A0DF0D3CAA9319CF3" not in content2: 
		print "test 4 file error for pad 2"
		sys.exit()

with open("ltc_address_20_private_pad3.txt") as f:
	content3 = f.read()  
	if "63A3A6FED5DB3973B11A4B1EE90AF3D0A2BB3D0A2D65503F7E54EE6D603E6D9A" not in content3: 
		print "test 4 file error for pad 3"
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
