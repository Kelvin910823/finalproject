

import random


file = open("price.txt","w")

##print "\n".join(["{0:03}".format(i) for i in range(0,10)])
	
for count in range(0,1000000):
	
	bid = random.randint(99,100)
	multiple = random.randint(2,4)
	spread = float(multiple * float(1./256))
	offer = float(bid + spread)

	while offer > 101 :
		multiple = random.randint(2,4)
		spread = float(multiple *float( 1./256))
		offer = float(bid + spread)

 	mid = float(( bid + offer )/ 2)
 	
	file.write( "2Y" +","+ "912828F62"+","+str(mid)+","+str(spread) +"\n")

for count in range(0,1000000):
	
	bid = random.randint(99,100)
	multiple = random.randint(2,4)
	spread = float(multiple * float(1./256))
	offer = float(bid + spread)

	while offer > 101 :
		multiple = random.randint(2,4)
		spread = float(multiple *float( 1./256))
		offer = float(bid + spread)

 	mid = float(( bid + offer )/ 2)

	file.write( "3Y" +","+ "9128283G3"+","+str(mid)+","+str(spread) +"\n")

for count in range(0,1000000):
	
	bid = random.randint(99,100)
	multiple = random.randint(2,4)
	spread = float(multiple * float(1./256))
	offer = float(bid + spread)

	while offer > 101 :
		multiple = random.randint(2,4)
		spread = float(multiple *float( 1./256))
		offer = float(bid + spread)

 	mid = float(( bid + offer )/ 2)


	file.write( "5Y" +","+ "9128283C2"+","+str(mid)+","+str(spread) +"\n")

for count in range(0,1000000):

	bid = random.randint(99,100)
	multiple = random.randint(2,4)
	spread = float(multiple * float(1./256))
	offer = float(bid + spread)

	while offer > 101 :
		multiple = random.randint(2,4)
		spread = float(multiple *float( 1./256))
		offer = float(bid + spread)

 	mid = float(( bid + offer )/ 2)

	file.write( "7Y" +","+ "9128283D0"+","+str(mid)+","+str(spread) +"\n")

for count in range(0,1000000):
	
	bid = random.randint(99,100)
	multiple = random.randint(2,4)
	spread = float(multiple * float(1./256))
	offer = float(bid + spread)

	while offer > 101 :
		multiple = random.randint(2,4)
		spread = float(multiple *float( 1./256))
		offer = float(bid + spread)

 	mid = float(( bid + offer )/ 2)


	file.write( "10Y" +","+ "9128283F5"+","+str(mid)+","+str(spread) +"\n")

for count in range(0,1000000):
	
	bid = random.randint(99,100)
	multiple = random.randint(2,4)
	spread = float(multiple * float(1./256))
	offer = float(bid + spread)

	while offer > 101 :
		multiple = random.randint(2,4)
		spread = float(multiple *float( 1./256))
		offer = float(bid + spread)

 	mid = float(( bid + offer )/ 2)

 	file.write( "30Y" +","+ "912810RZ3"+","+str(mid)+","+str(spread) +"\n")


file.close()

