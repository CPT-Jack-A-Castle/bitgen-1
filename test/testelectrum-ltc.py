#!/usr/bin/python

import os
import sys
import os.path

def printHeader(str) :
   "Prints header text"
   print "===================== " + str + " ====================="
   return

if not os.path.isfile("../bitgen-ltc"):
	print "Error, application binary does not exist"
	sys.exit()



#============ Start of tests ============




printHeader("Test 1 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hash ydyssdfsdfkkdfsksdfsdfkasdjasdjaskdjaskdjaskjdjjjJJKJKJKJKJKJKJKJKJKJKJKJKJKJKJKJKJjjjjjjjjjjjjjjjjddjjdjdjdjdjkfsjfdkjsdfjsdkfjskdfjskdjfskdjfsdfjskdfjjjsdjfskdjfksdjfsjdfksdjfksjdfkjdididsfisdfsdfsdfsdfsdfsdfsdfsdfsdfsdffsdfsdfsdfsdfsdfsdfsdfsdf")
if retval1 != 0:
	print "test 1 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_NdvKQwHE6xGzj4vjM4EfpAhCDcEbGq3zksmdgGSYf6UebKxeK1rfB5rEH6AoS_private.txt"):
	print "test 1 file error"
	sys.exit()


printHeader("Test 2 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hash Qsdfsdfsdfkjhdskfjhsdkfjhskjdfhskdjhfksjdhfksjdhfksjhdfskjdfhskjdhfkjsdhfksjdhfkjshdfkjsdhjjsdjfsjdfhskjdfhksjdhfkjsdhfksdjhfkjsdhfkjsdfsdufsdufusdfsdfsdfsddfsdfskjdfhskjdhfskjhdjdjjdjdddkdkfjsdfkjsdfkjsdfkjsdfsdhfhhhfhsdfsdsdkfjhsdfjhsdkfjhjkqq words 15 name \"My fifteen word mnemonic\"")
if retval1 != 0:
	print "test 2 error"
	sys.exit()


if not os.path.isfile("electrum_ltc_qhG2tkGA1tsFzkhUjKgzLY2m9D9vwUUdykQYrUYiURWfQZgwS959733pzQ11B_share.txt"):
	print "test 2 file error"
	sys.exit()


printHeader("Test 3 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum mnemonic \"absorb elevator virtual bronze lens rebuild sphere gain tray alter crouch fly rely uphold above loop logic nuclear empty very frequent reunion daring material\"")
if retval1 != 0:
	print "test 3 error"
	sys.exit()


if not os.path.isfile("electrum_ltc_GZx5F9Kco36LmHxTcnTJbvJDW8h8ZWqr1YUm8MSX3fwYApcda8LS6KGUGEvzr_private.ps"):
	print "test 3 file error"
	sys.exit()




printHeader("Test 4 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum mnemonic \"mobile coconut rough doll beach habit taxi canal frame talk remember elegant mixture isolate pig\" name \"This is a test seed\"")
if retval1 != 0:
	print "test 4 error"
	sys.exit()


if not os.path.isfile("electrum_ltc_KezKFy7ofr2UnejNXJDZHoMTV5TuiRJhnjmD4cfnPBTgHBnh2K8dyCMuNLRHJ_private.txt"):
	print "test 4 file error"
	sys.exit()






printHeader("Test 5 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hex 1239812738828183123773783728123712837999ABBBCFFFEFFEFFEF12312289")
if retval1 != 0:
	print "test 5 error"
	sys.exit()


if not os.path.isfile("electrum_ltc_cq1NSuh3RQNjxeo1gvb62Pz4cqLxo4pDCX4jjCKfvVQZNQcJFMru9kVjir2gE_private.txt"):
	print "test 5 file error"
	sys.exit()







printHeader("Test 6 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hex 234392423948923849238498777477773 words 12")
if retval1 != 0:
	print "test 6 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_oG3wiaHbfeu5zFi2DUSm4eGJH8bo8azSZmcUZpsFiX4iLr2bmatMKL5dsXZCw_private.txt"):
	print "test 6 file error"
	sys.exit()




printHeader("Test 7 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum dice 6123561253612531625362662626263612635123625365355355535352662626262626623616232312312365213615236125")
if retval1 != 0:
	print "test 7 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_9sU8vXnHPRWPXab5HC6yWvN1wtQSGjbUsVu56TPbadA3AcqWDnHaj9tMnfyBg_private.txt"):
	print "test 7 file error"
	sys.exit()




printHeader("Test 8 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum dice 61523612536125361523662666262626626262626626266666 words 12 name \"Another dice test\"")
if retval1 != 0:
	print "test 8 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_X9nCGFhUGjESXARW8vqE5oMqyGLxMfZL72BnxuT7TTipJ2vQB71HkFfpxWhBD_private.txt"):
	print "test 8 file error"
	sys.exit()




printHeader("Test 9 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum brain myemail@testing.com \"The road is long to the next stop and I go there now with my feet on and on and on we go to the moon and the sun and the stars and the rainbow\"")
if retval1 != 0:
	print "test 9 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_rf8Av3HpatEVu8D8CstYGnmG6MHTYonYXXKsGjsGFN2YS1WhhyEX4iH6TGePQ_private.txt"):
	print "test 9 file error"
	sys.exit()




printHeader("Test 10 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum brain myemail@salting.com \"Go on go quick to the left right front bottom up up up and then down down down on and on we go go google home\" words 15 name \"My brainwallet testphrase\"")
if retval1 != 0:
	print "test 10 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_ogXkQrnFor5KWzoEoG8N3upshkswsMvg4dzWGQefNwRzWFSqY2NYdY4siSEwu_private.txt"):
	print "test 10 file error"
	sys.exit()






printHeader("Test 11 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum random")
if retval1 != 0:
	print "test 11 error"
	sys.exit()



printHeader("Test 12 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hash uuuuuududududiuiuiudiiiia")
if retval1 == 0:
	print "test 12 error"
	sys.exit()




printHeader("Test 13 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum random 10")
if retval1 == 0:
	print "test 13 error"
	sys.exit()



printHeader("Test 14 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hex 32423434FFFF123123123123981239828 words 12 name \"Hex Test\" nops")
if retval1 != 0:
	print "test 14 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_pK1jkYzaLbj8zbZqAZBvCpSbZYK38WHpd4jBoE1DrU3YVe5ZddbHYxjw54Ntk_private.txt"):
	print "test 14 file error"
	sys.exit()




printHeader("Test 15 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hex 111234324123123FCA123123123123222 words 12 name \"Hex Test 2\" notxt")
if retval1 != 0:
	print "test 15 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_n2uzGprsmn3iXHuK7ZbUCmFz1An4DVha3SKLLs8dow5M1WLTbuiVTG5sTFMYt_share.ps"):
	print "test 15 file error"
	sys.exit()




printHeader("Test 16 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hex 1111111111111111111111111111111111111111111111111 words 18")
if retval1 != 0:
	print "test 16 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_NVWWH5t3giKcXepGmBDuQ5frVSemrKgVjVthiEUYm9XoZzUtwnxkSG8eBuvPi_private.txt"):
	print "test 16 file error"
	sys.exit()




printHeader("Test 17 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum hex EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE words 12")
if retval1 != 0:
	print "test 17 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_zk1THc5p9gBaoHMXKNEhFdSvKH6PvTPvE8WnUwuRrCoswV7QaJTKerwVdtGdD_private.ps"):
	print "test 17 file error"
	sys.exit()




printHeader("Test 18 bitgen-ltc electrum")
retval1 = os.system("../bitgen-ltc electrum dice 33333333333333333333333333333333333333333333333333 words 12")
if retval1 != 0:
	print "test 18 error"
	sys.exit()

if not os.path.isfile("electrum_ltc_VY31EGAZX4HV4GZwae2HyMVpdwT1N9HZTsYwdNxgTEN4p6oMq9MrMGNb94ACs_private.txt"):
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

