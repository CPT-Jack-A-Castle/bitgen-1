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




printHeader("Test 1 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hash ksjdfhksjdhfkjsdhfkjsdhfkjsdhfkjsdhfkjshdfkjshdfkjshdfkjshdfjksdhfjshdfsdhfsdhfshdfsdfsjjjjjjjjdfhsjdfhkjsdhfksjdhfkjsdhfksjdhfkjsdhfkjsdhfkjsdhfjdshfsjdfjsdhfjsdhfjsdfsdfsdfsdfksdjfhsdkfjhsdkjfhsdkjfhskdjhfskdjfhskdjfhkjhsdfsdfshhhtttkjhdskjfhjjh")
if retval1 != 0:
	print "test 1 error"
	sys.exit()

if not os.path.isfile("electrum_bch_ec15VafBEt3kYshr8QFUV7R197ZeGxz8tFC9rC6j6382z8ThK4Jc3RMC7Lay1_private.txt"):
	print "test 1 file error"
	sys.exit()


printHeader("Test 2 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hash KJSKDJKJkjkdjksdjfksdjfksjdfksjdfksjdfkjsdkfjskdfjskdjfksdjfksdjfksdjfksdjfskdjfskdjfskdjfksdjfksjdfksdjfdsfkkidufsidufisadaisdaisduaisudaisudiasudisaduiiasdiasduaisudaisudadsdasdasdasiduaisduaisduaisuduuusususuususudausduuudsfsdfsdfsdfsdfsdffww words 15 name \"My fifteen word mnemonic\"")
if retval1 != 0:
	print "test 2 error"
	sys.exit()

if not os.path.isfile("electrum_bch_o4riHsX182nnwtPBJ86V9KLyGGk4ADSLKcRn33bohBqKW81H37X459tkuGv9s_share.txt"):
	print "test 2 file error"
	sys.exit()


printHeader("Test 3 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum mnemonic \"abstract stone illness repeat more siege nerve inherit mass aunt immune bronze review portion execute opera capital iron fossil visual slot vacuum child practice\"")
if retval1 != 0:
	print "test 3 error"
	sys.exit()
	
if not os.path.isfile("electrum_bch_uuErrreiXEzZcg4ooudgQzZEMrpfVkhmDGQVYXpLvmdBAp7X3XFu71Vu6pLsd_private.ps"):
	print "test 3 file error"
	sys.exit()




printHeader("Test 4 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum mnemonic \"scatter junk horn muscle advance health bamboo more issue correct yard caution\" name \"This is a test\"")
if retval1 != 0:
	print "test 4 error"
	sys.exit()

if not os.path.isfile("electrum_bch_HLUrbyviEgQJoJLyEcNpU1sQ7SHs27h5KjKy3Xup848jyS5ndhSL6BMzrtuZE_private.txt"):
	print "test 4 file error"
	sys.exit()






printHeader("Test 5 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hex 1231239912382193123982938939482938492384AAABF1232138999201232211")
if retval1 != 0:
	print "test 5 error"
	sys.exit()

if not os.path.isfile("electrum_bch_NGwdGr8tH2G7JgcpG2whhbeYhddd4sof4PyYePtD7wqnUzEuviYmndZqHsfU3_private.txt"):
	print "test 5 file error"
	sys.exit()







printHeader("Test 6 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hex 919199191919191992929292992939394 words 12")
if retval1 != 0:
	print "test 6 error"
	sys.exit()

if not os.path.isfile("electrum_bch_BRY69ZqVc3AnwgPDyaL7TMcPWoyixJvkYCRhr6dbGue19RmKf13QsrhacRJ5T_private.txt"):
	print "test 6 file error"
	sys.exit()




printHeader("Test 7 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum dice 6363663636362661661616161616166161616161616166161616216626262626262626262626262626262626626262666666")
if retval1 != 0:
	print "test 7 error"
	sys.exit()

if not os.path.isfile("electrum_bch_LMM9GHPtvwNhB9Y8RfUtFLq7MH9MQS7jb2t6cC1U7skkbosd8uVUYg21suCfm_private.txt"):
	print "test 7 file error"
	sys.exit()




printHeader("Test 8 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum dice 61616166115155151515151551555515515551555151222322 words 12 name \"The dice test\"")
if retval1 != 0:
	print "test 8 error"
	sys.exit()

if not os.path.isfile("electrum_bch_Yac2TE37FZvmJfafb5a8YAnvZXo8qEbbrAqoMsuQNLU21rEvWKyUDitDDwiHh_private.txt"):
	print "test 8 file error"
	sys.exit()




printHeader("Test 9 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum brain myemail@ycer.com \"A small ugly creature will crawl in the dirt where land meets the black sea and the bird flies BAck to the big creature\"")
if retval1 != 0:
	print "test 9 error"
	sys.exit()

if not os.path.isfile("electrum_bch_uQEKryfwxKYewYDkKUbfRqXtU7mpipLS7bwsCwVrPxikVJKRyJPMnxgNjCXrN_private.txt"):
	print "test 9 file error"
	sys.exit()




printHeader("Test 10 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum brain someemail@salting.com \"I you he her his he will he want I do you need she knows it goes I go went gone to you and him and him\" words 15 name \"Brainwallet testphrase\"")
if retval1 != 0:
	print "test 10 error"
	sys.exit()

if not os.path.isfile("electrum_bch_ENayGDw4xfjWPVKcdwCYFyr4GpMdXaRbby4CS3UxoRB6NPk13fW7fd91HTuMb_private.txt"):
	print "test 10 file error"
	sys.exit()






printHeader("Test 11 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum random")
if retval1 != 0:
	print "test 11 error"
	sys.exit()



printHeader("Test 12 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hash uuuuuududududiuiuiudiiiia")
if retval1 == 0:
	print "test 12 error"
	sys.exit()




printHeader("Test 13 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum random 10")
if retval1 == 0:
	print "test 13 error"
	sys.exit()



printHeader("Test 14 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hex 918181181881818188181818888288221 words 12 name \"Hex Test\" nops")
if retval1 != 0:
	print "test 14 error"
	sys.exit()

if not os.path.isfile("electrum_bch_iiKpxLvKgc95zg1BjW8y6EbM298LiezhFYWTWiwPtJM1Xn6j33QU5vMv6bxm9_private.txt"):
	print "test 14 file error"
	sys.exit()




printHeader("Test 15 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hex 929929292929292822982982982982988 words 12 name \"Hex Test 2\" notxt")
if retval1 != 0:
	print "test 15 error"
	sys.exit()

if not os.path.isfile("electrum_bch_KZCAKJS6se8M5rxsqjsnZaNyEZWrsoEXnoDuac9Qu3MceMZTyY5kEcK3QwRY8_share.ps"):
	print "test 15 file error"
	sys.exit()




printHeader("Test 16 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hex 6666666666666666666666666666666666666666666666666 words 18")
if retval1 != 0:
	print "test 16 error"
	sys.exit()

if not os.path.isfile("electrum_bch_Uski3AMejam3qAtXB2t2RwTruv4cSQaTibJGoUsXLcsRhJmLfGFyLe18oiaKK_private.txt"):
	print "test 16 file error"
	sys.exit()




printHeader("Test 17 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum hex CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC words 12")
if retval1 != 0:
	print "test 17 error"
	sys.exit()

if not os.path.isfile("electrum_bch_FCxCFkLCjFnrUcQzSs7779XtAdUr9UDymy6Hjzrd2K8nxabGgeNndfFeAzEPf_private.ps"):
	print "test 17 file error"
	sys.exit()




printHeader("Test 18 bitgen-bch electrum")
retval1 = os.system("../bitgen-bch electrum dice 55555555555555555555555555555555555555555555555555 words 12")
if retval1 != 0:
	print "test 18 error"
	sys.exit()

if not os.path.isfile("electrum_bch_egd7MuT7Sg6UzdeY2NjU2kkZxj18wYiBUWL3Cf5yW1EszQTrdrvuFzxJCeoSr_private.txt"):
	print "test 18 file error"
	sys.exit()




print ""
print ""
print ""
print "Cleaning up"
os.system("rm *.trans *.script *.txt *.sig *.ps")

print ""
print ""
print ""
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++ All tests passed OK +++++++++++++++++++++++++++"
print "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"

sys.exit(123)

