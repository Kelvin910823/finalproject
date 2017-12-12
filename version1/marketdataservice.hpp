/**
 * marketdataservice.hpp
 * Defines the data types and Service for order book market data.
 *
 * @author Breman Thuraisingham
 */
#ifndef MARKET_DATA_SERVICE_HPP
#define MARKET_DATA_SERVICE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>

#include "soa.hpp"
#include "products.hpp"

using namespace std;

// Side for market data
enum PricingSide { BID, OFFER };

/**
 * A market data order with price, quantity, and side.
 */
class Order
{

public:

  // ctor for an order
  Order(double _price, long _quantity, PricingSide _side);

  // Get the price on the order
  double GetPrice() const;

  // Get the quantity on the order
  long GetQuantity() const;

  // Get the side on the order
  PricingSide GetSide() const;

private:
  double price;
  long quantity;
  PricingSide side;

};


Order::Order(double _price, long _quantity, PricingSide _side)
{
  price = _price;
  quantity = _quantity;
  side = _side;
}

double Order::GetPrice() const
{
  return price;
}
 
long Order::GetQuantity() const
{
  return quantity;
}
 
PricingSide Order::GetSide() const
{
  return side;
}




/**
 * Class representing a bid and offer order
 */
class BidOffer
{

public:

  // ctor for bid/offer
  BidOffer(const Order &_bidOrder, const Order &_offerOrder);

  // Get the bid order
  const Order& GetBidOrder() const;

  // Get the offer order
  const Order& GetOfferOrder() const;

private:
  Order bidOrder;
  Order offerOrder;

};




BidOffer::BidOffer(const Order &_bidOrder, const Order &_offerOrder) :
  bidOrder(_bidOrder), offerOrder(_offerOrder)
{
}

const Order& BidOffer::GetBidOrder() const
{
  return bidOrder;
}

const Order& BidOffer::GetOfferOrder() const
{
  return offerOrder;
}



/**
 * Order book with a bid and offer stack.
 * Type T is the product type.
 */
template<typename T>
class OrderBook
{

public:

  // ctor for the order book
  OrderBook(const T &_product, const vector<Order> &_bidStack, const vector<Order> &_offerStack);
  OrderBook(){};

  // Get the product
  const T& GetProduct() const;

  // Get the bid stack
  const vector<Order>& GetBidStack() const;

  // Get the offer stack
  const vector<Order>& GetOfferStack() const;

private:
  T product;
  vector<Order> bidStack;
  vector<Order> offerStack;

};




template<typename T>
OrderBook<T>::OrderBook(const T &_product, const vector<Order> &_bidStack, const vector<Order> &_offerStack) :
  product(_product), bidStack(_bidStack), offerStack(_offerStack)
{
}

template<typename T>
const T& OrderBook<T>::GetProduct() const
{
  return product;
}

template<typename T>
const vector<Order>& OrderBook<T>::GetBidStack() const
{
  return bidStack;
}

template<typename T>
const vector<Order>& OrderBook<T>::GetOfferStack() const
{
  return offerStack;
}



/**
 * Market Data Service which distributes market data
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class MarketDataService : public Service<string,OrderBook <T> >
{

public:

  // Get the best bid/offer order
 // virtual const BidOffer& GetBestBidOffer(const string &productId) = 0;

  // Aggregate the order book
  virtual const OrderBook<T>& AggregateDepth(const string &productId) = 0;

};


class BondMarketDataService : public MarketDataService < Bond >
{

public:

  virtual OrderBook<Bond>& GetData(string key)
  {
    return MarketDataMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(OrderBook<Bond> &data)
  {
    
    UpdateMD(data);



    if(MarketDataListeners.size()!=0)
    {
    //std::cout<<"OnMessage 2"<<std::endl;

  //for(std::vector<ServiceListener< Trade<Bond> >* >::iterator it = TradeListeners.begin();it!=TradeListeners.end();it++)
    for(int i = 0; i<MarketDataListeners.size();i++)
    {
    //std::cout<<"OnMessage 3"<<std::endl;
    //(*it)->ProcessAdd(data);
      MarketDataListeners[i]->ProcessAdd(data);
      std::cout<<"listener invoked for market data service"<<std::endl;
    }
  //std::cout<<"OnMessage 4"<<std::endl;
    
    }
  }


  void UpdateMD(OrderBook<Bond> &data)
  {

    string productId = data.GetProduct().GetProductId();

    if(MarketDataMP.find(productId)== MarketDataMP.end())
    {  

      MarketDataMP.insert(std::pair<string,OrderBook<Bond> >(productId, data));
    }
    else
    {
      MarketDataMP[productId] = data;
    }
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< OrderBook<Bond> > *listener)
  {
    MarketDataListeners.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< OrderBook<Bond> >* >& GetListeners() const
  {
    return MarketDataListeners;
  }

/*

  // Get the best bid/offer order
  virtual const BidOffer& GetBestBidOffer(const string &productId)
  {
      OrderBook<Bond> currentOrder = MarketDataMP[productId];
      vector<Order> bidStack = MarketDataMP[productId].GetBidStack();
      vector<Order> offerStack = MarketDataMP[productId].GetOfferStack();
      int idx=0;
      double spread = offerStack[0].GetPrice() - bidStack[0].GetPrice();

      for(int i = 0; i< bidStack.size(); i++)
      {
        double res = offerStack[i].GetPrice() - bidStack[i].GetPrice();
        if(res <= spread)
        {
          spread = res;
          idx = i;
        }
      }


      const BidOffer bestBidOffer(bidStack[idx],offerStack[idx]);
      return bestBidOffer;



  }
  */

  // Aggregate the order book
  virtual const OrderBook<Bond>& AggregateDepth(const string &productId)
  {

    return MarketDataMP[productId];

  }

private:

  map<string,OrderBook<Bond> > MarketDataMP;
  std::vector< ServiceListener< OrderBook<Bond> >* > MarketDataListeners;

};




class BondMarketDataServiceConnector : public Connector < OrderBook <Bond> >
{
private:
  BondMarketDataService bondMDService;

public:
  BondMarketDataServiceConnector( BondMarketDataService& _myline):bondMDService(_myline){}; 
  virtual void Publish(OrderBook<Bond>& data){};

  void Subscribe()
  {
    string line;
    std::ifstream file("marketdata_backup.txt");

    while(getline(file,line))
  {
    
    if(!line.empty())
    {
      std::stringstream linestream(line);

      std::string product;
      std::string stack;
      std::string productID;

      std::string bid1;
      std::string offer1;
      std::string quant1;

      std::string bid2;
      std::string offer2;
      std::string quant2;

      std::string bid3;
      std::string offer3;
      std::string quant3;

      std::string bid4;
      std::string offer4;
      std::string quant4;

      std::string bid5;
      std::string offer5;
      std::string quant5;

      std::getline(linestream,product,',');
      std::getline(linestream,stack,',');
      std::getline(linestream,productID,',');

      std::getline(linestream,bid1,',');
      std::getline(linestream,offer1,',');
      std::getline(linestream,quant1,',');
      
      std::getline(linestream,bid2,',');
      std::getline(linestream,offer2,',');
      std::getline(linestream,quant2,',');
      
      std::getline(linestream,bid3,',');
      std::getline(linestream,offer3,',');
      std::getline(linestream,quant3,',');
      
      std::getline(linestream,bid4,',');
      std::getline(linestream,offer4,',');
      std::getline(linestream,quant4,',');
      
      std::getline(linestream,bid5,',');
      std::getline(linestream,offer5,',');
      std::getline(linestream,quant5,',');
      
      long quantity1 = atol(quant1.c_str());
      long quantity2 = atol(quant2.c_str());
      long quantity3 = atol(quant3.c_str());
      long quantity4 = atol(quant4.c_str());
      long quantity5 = atol(quant5.c_str());

      double bid_1 = stod(bid1);
      double offer_1 = stod(offer1);
      double bid_2 = stod(bid2);
      double offer_2 = stod(offer2);
      double bid_3 = stod(bid3);
      double offer_3 = stod(offer3);
      double bid_4 = stod(bid4);
      double offer_4 = stod(offer4);
      double bid_5 = stod(bid5);
      double offer_5 = stod(offer5);

     

      PricingSide pSide1 = BID;
      PricingSide pSide2 = OFFER;


      Order bidOrder1(bid_1,quantity1,pSide1);
      Order offerOrder1(offer_1,quantity1,pSide2);


      Order bidOrder2(bid_2,quantity2,pSide1);
      Order offerOrder2(offer_2,quantity2,pSide2);

      Order bidOrder3(bid_3,quantity3,pSide1);
      Order offerOrder3(offer_3,quantity3,pSide2);

      Order bidOrder4(bid_4,quantity4,pSide1);
      Order offerOrder4(offer_4,quantity4,pSide2);

      Order bidOrder5(bid_5,quantity5,pSide1);
      Order offerOrder5(offer_5,quantity5,pSide2);

      const vector<Order> bidStack = {bidOrder1,bidOrder2,bidOrder3,bidOrder4,bidOrder5 };

      const vector<Order> offerStack = {offerOrder1,offerOrder2,offerOrder3,offerOrder4,offerOrder5};

    if(!product.empty())
    {
        if(product == "2Y")
      {

            BondIdType idType = CUSIP;
            date maturityDate(2019,Oct,31);
            const Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);
                


            OrderBook<Bond> obj1 = OrderBook<Bond>(bond2Y,bidStack,offerStack);

            bondMDService.OnMessage(obj1);
            std::cout<<"updated"<<std::endl;
      }
      else if (product == "3Y")
      {

            BondIdType idType = CUSIP;
            date maturityDate(2020,Nov,15);
            const Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
            
            OrderBook<Bond> obj1 = OrderBook<Bond>(bond3Y,bidStack,offerStack);

            bondMDService.OnMessage(obj1);


      }
      else if (product == "5Y")
      {
            BondIdType idType = CUSIP;
            date maturityDate(2022,Oct,31);
            const Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

            OrderBook<Bond> obj1 = OrderBook<Bond>(bond5Y,bidStack,offerStack);

            bondMDService.OnMessage(obj1);

      }
      else if (product == "7Y")
      {
            BondIdType idType = CUSIP;
            date maturityDate(2024,Oct,31);
            const Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);

            OrderBook<Bond> obj1 = OrderBook<Bond>(bond7Y,bidStack,offerStack);

            bondMDService.OnMessage(obj1);

      }
      else if (product == "10Y")
      {

            BondIdType idType = CUSIP;
            date maturityDate(2027,Nov,15);
            const Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

            OrderBook<Bond> obj1 = OrderBook<Bond>(bond10Y,bidStack,offerStack);

            bondMDService.OnMessage(obj1);

      }
      else if (product == "30Y")
      {

            BondIdType idType = CUSIP;
            date maturityDate(2047,Nov,15);
            const Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);

            OrderBook<Bond> obj1 = OrderBook<Bond>(bond30Y,bidStack,offerStack);

            bondMDService.OnMessage(obj1);

      }
    }
      
  }
    
}
}


};

















#endif
