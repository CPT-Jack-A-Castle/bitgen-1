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


print "Copying files"
os.system("cp testfiles/bch_8CF0BD490F2CF39959FCEF72411BDF52E8791A4779F0B96279BF3C9651295CDF.trans .")
os.system("cp testfiles/bch_97971462B124020B63FF2BFA5A9A1B4BE901AD6F6AFF7703E7E0B3E73AC93665.trans .")


printHeader("Test 1 bitgen-bch runtrans")
retval1 = os.system("../bitgen-bch runtrans testfiles/bch_8CF0BD490F2CF39959FCEF72411BDF52E8791A4779F0B96279BF3C9651295CDF.trans")
if retval1 != 0:
	print "test 1 error"
	sys.exit()


os.system("cp testfiles/bch_6401CA84B4CC30820DC29F74A5EDD7FEEEFBCD5EBBB1DEDA18526AA97197807C.trans .")
os.system("cp testfiles/bch_BD41BF8AF5189613EDF489DB2620202BC64E337FDEB8661DF2D90F26B3A868D8.trans .")
os.system("cp testfiles/bch_EA65A0EB6EF7A4E775DFBCE7226C884DDD023E23E2F9101656764CDE0435AC6E.trans .")


printHeader("Test 2 bitgen-bch runtrans")
retval1 = os.system("../bitgen-bch runtrans bch_EA65A0EB6EF7A4E775DFBCE7226C884DDD023E23E2F9101656764CDE0435AC6E.trans")
if retval1 != 0:
	print "test 1 error"
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

