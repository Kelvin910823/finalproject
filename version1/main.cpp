

#include "soa.hpp"
#include "products.hpp"


#include "positionservice.hpp"
#include "tradebookingservice.hpp"
#include "marketdataservice.hpp"
#include "executionservice.hpp"



#include "pricingservice.hpp"
#include "streamingservice.hpp"
#include "inquiryservice.hpp"
//#include "riskservice.hpp"

/*
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
*/




int main()
{

	
	BondTradeBookingService bookingService;
	
	//bookingService.print();
	BondPositionService positionService;
	//BondRiskService riskService;
	
	//BondPositionRiskServiceListener myListener9(&riskService);
	
	//positionService.AddListener(&myListener9);
	BondBookingPositionServiceListener myListener(&positionService);
	
	
	

	bookingService.AddListener(&myListener);

	
	BondTradeBookingServiceConnector BookingServiceCon(bookingService);
	BookingServiceCon.Subscribe();
	

	BondMarketDataService marketdataService;
	
	BondAlgoExecutionService AlgoExecutionService;
	BondMarketDataAlgoExecutionServiceListener myListener2(&AlgoExecutionService);
	marketdataService.AddListener(&myListener2);
	
	BondExecutionService executionService;
	BondAlgoExecutionExecutionServiceListener myListener3(&executionService);
	AlgoExecutionService.AddListener(&myListener3);

	BondExecutionTradeBookingServiceListener myListener4(&bookingService);
	executionService.AddListener(&myListener4);

	BondMarketDataServiceConnector marketdataServiceCon(marketdataService);
	marketdataServiceCon.Subscribe();

	BondPricingService pricingService;
	BondAlgoStreamService AlgoStreamService;

	BondStreamingService BondstreamService;
	BondAlgoStreamStreamServiceListener myListener6(&BondstreamService);
	AlgoStreamService.AddListener(&myListener6);

	BondPricingAlgoStreamServiceListener myListener5(&AlgoStreamService);
	pricingService.AddListener(&myListener5);


	GUIServiceConnector publishCon;
	GUIService bondGUIService(publishCon);
	BondPricingGUIServiceListener myListener7(&bondGUIService);
	pricingService.AddListener(&myListener7);

	BondPricingServiceConnector PricingServiceCon(pricingService);
	PricingServiceCon.Subscribe();


	
	 //inquiryService;
	BondInquiryServiceConnector inquiryServiceCon;
	//BondInquiryServiceConnector inquiryServiceCon2;

	//inquiryService.SetConnector(&inquiryServiceCon);
	
	BondInquiryService inquiryService(&inquiryServiceCon);
	inquiryServiceCon.SetInquiryService(&inquiryService);

	BondInquiryServiceListener myListener8(&inquiryService);
	inquiryService.AddListener(&myListener8);
	inquiryServiceCon.Subscribe();

	////auto inquiryService_ptr = std::make_shared(inquiryService);

	






/*
	std::string s = "123.32";
	double num = stod(s);
	std::cout<< s <<std::endl;
*/

	//std::cout<<"Book: "<<BookingServiceCon.GetBook("912828F62000")<<std::endl;


	//std::cout<<"TradeId: "<<bookingService.GetData("912828F62000").GetTradeId();
	//std::cout<<"Trade ID" << obj.GetTradeId()<<std::endl;
	//std::cout<<"Book "<<obj.GetBook()<<std::endl;

	return 0;


}