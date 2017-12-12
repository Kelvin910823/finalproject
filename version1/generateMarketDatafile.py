import random



multiple = [1,2,3,4,3,2]



file = open("marketdata.txt","w")

##print "\n".join(["{0:03}".format(i) for i in range(0,10)])
i = 0
	
for count in range(0,1000000):
	
	#first staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "2Y" +","+"first"+","+ "912828F62"+","+str(bid)+","+str(offer) +","+str(notional)+",")	

	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "2Y" +","+"first"+","+ "912828F62"+","+str(bid)+","+str(offer) +","+str(notional)+",")

	#second staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write(str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#third staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fourth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write(str(bid)+","+str(offer) +","+str(notional)+",")

	#fifth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")



for count in range(0,1000000):

	#first staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "3Y" +","+"first"+","+ "9128283G3"+","+str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "3Y" +","+"first"+","+ "9128283G3"+","+str(bid)+","+str(offer) +","+str(notional)+",")

	#second staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#third staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fourth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fifth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")



for count in range(0,1000000):

	#first staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "5Y" +","+"first"+","+ "9128283C2"+","+str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "5Y" +","+"first"+","+ "9128283C2"+","+str(bid)+","+str(offer) +","+str(notional)+",")

	#second staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#third staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fourth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fifth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")




for count in range(0,1000000):

	#first staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "7Y" +","+"first"+","+ "9128283D0"+","+str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "7Y" +","+"first"+","+ "9128283D0"+","+str(bid)+","+str(offer) +","+str(notional)+",")

	#second staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#third staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fourth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fifth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")




for count in range(0,1000000):

	#first staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "10Y" +","+"first"+","+ "9128283F5"+","+str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "10Y" +","+"first"+","+ "9128283F5"+","+str(bid)+","+str(offer) +","+str(notional)+",")

	#second staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#third staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fourth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fifth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")


for count in range(0,1000000):

	#first staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "30Y" +","+"first"+","+ "912810RZ3"+","+str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 10000000
		file.write( "30Y" +","+"first"+","+ "912810RZ3"+","+str(bid)+","+str(offer) +","+str(notional)+",")

	#second staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 20000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#third staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 30000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fourth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 40000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+",")

	#fifth staock	
	bid = random.randint(99,100)
	if i <= 5 :
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")
	else:
		i = 0
		spread = multiple[i]*float(1./256)
		i = i+1
		offer = float(bid + spread)

		while offer > 101 :
			bid = random.randint(99,100)
			offer = bid + spread
		notional = 50000000
		file.write( str(bid)+","+str(offer) +","+str(notional)+"\n")






file.close()
