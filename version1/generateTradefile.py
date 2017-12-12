import random

file = open("trades.txt","w")

##print "\n".join(["{0:03}".format(i) for i in range(0,10)])
	
for count in range(0,10):
	xy = random.randint(0,31)
	z = random.randint(0,7)
	price = random.randint(99,100)
	tradeprice = str(price)+"-"+str("{0:02}".format(xy))+str(z)
	bookrand = random.randint(0,2)
	if bookrand == 0:
		book = "TRSY1"
	elif bookrand == 1:
		book = "TRSY2"
	elif bookrand == 2:
		book = "TRSY3"
	quantity = random.randint(1000000,3000000)
	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	file.write( "2Y" +","+ "912828F62"+str("{0:03}".format(count))+","+str(tradeprice)+","+book+","+str(quantity)+","+side+"\n")


for count in range(0,10):
	xy = random.randint(0,31)
	z = random.randint(0,7)
	price = random.randint(99,100)
	tradeprice = str(price)+"-"+str("{0:02}".format(xy))+str(z)
	bookrand = random.randint(0,2)
	if bookrand == 0:
		book = "TRSY1"
	elif bookrand == 1:
		book = "TRSY2"
	elif bookrand == 2:
		book = "TRSY3"
	quantity = random.randint(1000000,3000000)
	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	file.write( "3Y" +","+ "9128283G3"+str("{0:03}".format(count))+","+str(tradeprice)+","+book+","+str(quantity)+","+side+"\n")


for count in range(0,10):
	xy = random.randint(0,31)
	z = random.randint(0,7)
	price = random.randint(99,100)
	tradeprice = str(price)+"-"+str("{0:02}".format(xy))+str(z)
	bookrand = random.randint(0,2)
	if bookrand == 0:
		book = "TRSY1"
	elif bookrand == 1:
		book = "TRSY2"
	elif bookrand == 2:
		book = "TRSY3"
	quantity = random.randint(1000000,3000000)
	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	file.write( "5Y" +","+ "9128283C2"+str("{0:03}".format(count))+","+str(tradeprice)+","+book+","+str(quantity)+","+side+"\n")


for count in range(0,10):
	xy = random.randint(0,31)
	z = random.randint(0,7)
	price = random.randint(99,100)
	tradeprice = str(price)+"-"+str("{0:02}".format(xy))+str(z)
	bookrand = random.randint(0,2)
	if bookrand == 0:
		book = "TRSY1"
	elif bookrand == 1:
		book = "TRSY2"
	elif bookrand == 2:
		book = "TRSY3"
	quantity = random.randint(1000000,3000000)
	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	file.write( "7Y" +","+ "9128283D0"+str("{0:03}".format(count))+","+str(tradeprice)+","+book+","+str(quantity)+","+side+"\n")


for count in range(0,10):
	xy = random.randint(0,31)
	z = random.randint(0,7)
	price = random.randint(99,100)
	tradeprice = str(price)+"-"+str("{0:02}".format(xy))+str(z)
	bookrand = random.randint(0,2)
	if bookrand == 0:
		book = "TRSY1"
	elif bookrand == 1:
		book = "TRSY2"
	elif bookrand == 2:
		book = "TRSY3"
	quantity = random.randint(1000000,3000000)
	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	file.write( "10Y" +","+ "9128283F5"+str("{0:03}".format(count))+","+str(tradeprice)+","+book+","+str(quantity)+","+side+"\n")


for count in range(0,10):
	xy = random.randint(0,31)
	z = random.randint(0,7)
	price = random.randint(99,100)
	tradeprice = str(price)+"-"+str("{0:02}".format(xy))+str(z)
	bookrand = random.randint(0,2)
	if bookrand == 0:
		book = "TRSY1"
	elif bookrand == 1:
		book = "TRSY2"
	elif bookrand == 2:
		book = "TRSY3"
	quantity = random.randint(1000000,3000000)
	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	file.write( "30Y" +","+ "912810RZ3"+str("{0:03}".format(count))+","+str(tradeprice)+","+book+","+str(quantity)+","+side+"\n")


file.close()