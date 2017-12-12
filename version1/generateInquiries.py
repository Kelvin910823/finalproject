import random

file = open("inquiries.txt","w")

##print "\n".join(["{0:03}".format(i) for i in range(0,10)])
	
for count in range(0,10):
	
	price = 0000
	InquiryId = "912828F62"+str(count)

	quantity = random.randint(1000000,3000000)
	

	siderand = random.randint(0,1)
	if siderand == 0:
		side = "BUY"
	else:
		side = "SELL"
	
	file.write( InquiryId +","+ "2Y"+","+side+","+str(quantity)+","+str(price)+","+"RECEIVED"+"\n")

file.close()
