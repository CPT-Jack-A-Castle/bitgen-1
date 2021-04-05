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



#============ Start of tests ============




printHeader("Test 1 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hash KJKJHKJHKJHkjhkjhkjhjkhasdasdiiisiiiiiiiiiiiiiiiiiiiiiiisisisiisisiisiiiiisisosdasdasdasdasdasdasdOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUOIUIUOIUOIUIIIIIIIIIuoiuoiuoiuoiuoiuoiuoiuoiuoiusoidfusoidfusoidfusoidfusdoifuudsfusdfusdufsdufsudfusdfu")
if retval1 != 0:
	print "test 1 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_TzGSxMkm2ff3B1KtRim1qSUPWZ4WWModvasf5zXMMSdpVa8u2FNE9fphG1VRo_private.txt"):
	print "test 1 file error"
	sys.exit()


printHeader("Test 2 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hash sdfsddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddfsdfffffffffffffffffffffffffffffffffffffffffffffffffffsdfsdfffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffsdfsdfsdfsdfsdfsdfsdfdd words 15 name \"My mnemonic\"")
if retval1 != 0:
	print "test 2 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_ytFKFP5S3akkJu5DyLSoCeApDjnrrGsYRRXMPudDCNbCGeFD7D7Y5HzXvAHi5_share.txt"):
	print "test 2 file error"
	sys.exit()


printHeader("Test 3 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum mnemonic \"absent tomorrow tooth grape day awkward fish ability multiply meadow deputy nominee expose strong large hazard dawn unit sunset update book know truth mention\"")
if retval1 != 0:
	print "test 3 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_VgF1cRjZg4i4BrpKh4FaGa295Ax3CaPntexXfbCkxUdCF4q9pcJ5LvUjtCnf2_private.ps"):
	print "test 3 file error"
	sys.exit()




printHeader("Test 4 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum mnemonic \"scatter junk horn muscle advance health bamboo more issue correct yard caution\" name \"This is a test\"")
if retval1 != 0:
	print "test 4 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_HLUrbyviEgQJoJLyEcNpU1sQ7SHs27h5KjKy3Xup848jyS5ndhSL6BMzrtuZE_private.txt"):
	print "test 4 file error"
	sys.exit()






printHeader("Test 5 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hex 12313123231231231233161616161616161616FFFFAFAFFAFAFAFFFFAFAFFFFF")
if retval1 != 0:
	print "test 5 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_ADX8hv348QCaHMRmt2BsjHXbtbQzK8Sfaepkvu24oJ3jhCwr9JnR6pTt7waaH_private.txt"):
	print "test 5 file error"
	sys.exit()







printHeader("Test 6 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hex 921319238912839283182399992999992 words 12")
if retval1 != 0:
	print "test 6 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_NYtGHdR9s4E74XXTGxvtGU5WyANxKoPFcTzw6z48zFcvUb3JsLS15ZnmkmhWp_private.txt"):
	print "test 6 file error"
	sys.exit()




printHeader("Test 7 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum dice 6132612361236126316236123612631263666262626262636126321636123612631623612361236126316236123612362622")
if retval1 != 0:
	print "test 7 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_DEayfmy3bkPvmtaVkZ73Rg78xsUnHAUacvbfEKeEwtXMt131D2CPMxutPifqc_private.txt"):
	print "test 7 file error"
	sys.exit()




printHeader("Test 8 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum dice 12312312312312312312312312312312312333312312322111 words 12 name \"A dice test\"")
if retval1 != 0:
	print "test 8 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_NjixDnYHMxQ3RPL3Vgiip6ZKHUaBF1kMmUuWD3gVzjqi5XLW7SezLwUm9HzZA_private.txt"):
	print "test 8 file error"
	sys.exit()




printHeader("Test 9 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum brain errian@recale.com \"My little story of a random star in the solar system far far away in the clouds of the sun and the moon and the void empty cold sPace\"")
if retval1 != 0:
	print "test 9 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_KnPTJxSpFa7FadruZxXopQGsgwHGpwUsTbZQWzaT6on9DDwc38o21ZAA5b8rs_private.txt"):
	print "test 9 file error"
	sys.exit()




printHeader("Test 10 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum brain someemail@salting.com \"Yoobee doo dee daba dee doo dido dadi dadda di di da doli do da doti dota didde dadde datt doning danong diddidatt\" words 15 name \"Little testphrase\"")
if retval1 != 0:
	print "test 10 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_Y4ui5YkbTu3tWir5kFAX3fTn5ptcZxtMfsJv3jRcnA55nGs8yQ3AUuhZoiE1o_private.txt"):
	print "test 10 file error"
	sys.exit()






printHeader("Test 11 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum random")
if retval1 != 0:
	print "test 11 error"
	sys.exit()



printHeader("Test 12 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hash afasfasasdasdasdasdnnnndd")
if retval1 == 0:
	print "test 12 error"
	sys.exit()




printHeader("Test 13 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum random 10")
if retval1 == 0:
	print "test 13 error"
	sys.exit()



printHeader("Test 14 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hex 021931203891230981230982130921832 words 12 name \"a hex Test\" nops")
if retval1 != 0:
	print "test 14 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_Sx9GbymknhMXdL35vdvyM1b8Kw9LMqbqx37KqgSf56TPP4Gpu2PskVobnm8CQ_private.txt"):
	print "test 14 file error"
	sys.exit()




printHeader("Test 15 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hex 929929292929292822982982982982988 words 12 name \"Hex Test 2\" notxt")
if retval1 != 0:
	print "test 15 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_KZCAKJS6se8M5rxsqjsnZaNyEZWrsoEXnoDuac9Qu3MceMZTyY5kEcK3QwRY8_share.ps"):
	print "test 15 file error"
	sys.exit()




printHeader("Test 16 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hex 1212121212121212121212121212121212121212121212121 words 18")
if retval1 != 0:
	print "test 16 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_KELpZ8XBHVQkFLgAmqervSWsj5PdQbauRehq6JFey1HaeJfP4vYH1BoCzWmvr_private.txt"):
	print "test 16 file error"
	sys.exit()




printHeader("Test 17 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum hex DDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD words 12")
if retval1 != 0:
	print "test 17 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_cBotkeNkbsmeUsViWyWSKxchCaBwhScwHLzBbZBprMqad588VrVet7wGCboZ4_private.ps"):
	print "test 17 file error"
	sys.exit()




printHeader("Test 18 bitgen-vtc electrum")
retval1 = os.system("../bitgen-vtc electrum dice 44444444444444444444444444444444444444444444444444 words 12")
if retval1 != 0:
	print "test 18 error"
	sys.exit()

if not os.path.isfile("electrum_vtc_zeUt7QS6gL6KMxD1t5D1q557FpdTtoibc89uy6YEssF2e9LxVBGmYi3oQhBzW_private.txt"):
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

