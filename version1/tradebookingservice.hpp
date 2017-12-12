/**
 * tradebookingservice.hpp
 * Defines the data types and Service for trade booking.
 *
 * @author Breman Thuraisingham
 */
#ifndef TRADE_BOOKING_SERVICE_HPP
#define TRADE_BOOKING_SERVICE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>

#include "soa.hpp"
#include "products.hpp"



// Trade sides
enum Side { BUY, SELL };

/**
 * Trade object with a price, side, and quantity on a particular book.
 * Type T is the product type.
 */
template<typename T>
class Trade
{

public:
  // ctor for a trade
  Trade(const T &_product, string _tradeId, double price_, string _book, long _quantity, Side _side);

  Trade(){};
  // Get the product
  const T& GetProduct() const;

  // Get the trade ID
  const string& GetTradeId() const;

  // Get the book
  const string& GetBook() const;

  // Get the quantity
  long GetQuantity() const;

  // Get the side
  Side GetSide() const;

  double GetPrice() const;
private:
  T product;
  string tradeId;
  string book;
  long quantity;
  Side side; 
  double price;

};



template<typename T>
Trade<T>::Trade(const T &_product, string _tradeId, double price_, string _book, long _quantity, Side _side) :
  product(_product)
{
  tradeId = _tradeId;
  book = _book;
  quantity = _quantity;
  side = _side;
  price = price_;
}

template<typename T>
const T& Trade<T>::GetProduct() const
{
  return product;
}

template<typename T>
const string& Trade<T>::GetTradeId() const
{
  return tradeId;
}

template<typename T>
const string& Trade<T>::GetBook() const
{
  return book;
}

template<typename T>
long Trade<T>::GetQuantity() const
{
  return quantity;
}

template<typename T>
Side Trade<T>::GetSide() const
{
  return side;
}


template<typename T>
double Trade<T>::GetPrice() const
{
  return price;
}










/**
 * Trade Booking Service to book trades to a particular book.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class TradeBookingService : public Service<string,Trade <T> >
{

public:

  // Book the trade
  virtual void BookTrade( Trade<T> &trade) = 0;

};
/*
template<typename T>
void TradeBookingService<T>::BookTrade(const Trade<T> &trade)
{
}*/


class BondTradeBookingService : public TradeBookingService<Bond>
{
  public:

  BondTradeBookingService();

  // Get data on our service given a key-tradeID
  virtual Trade<Bond>& GetData(string key);

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(Trade<Bond> &data);

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< Trade<Bond> >* listener);

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< Trade<Bond> >* >& GetListeners() const;

  // Book the trade
  virtual void BookTrade(Trade<Bond> &trade); 

  //void print(){std::cout<<"hello"<<std::endl;};
  
  private:
    
  std::map<string,Trade<Bond> > TradeMP;
    
  //std::vector<ServiceListener<Trade<Bond> >* >TradeListeners;

  std::vector< ServiceListener<Trade<Bond> >* >TradeListeners;

};



BondTradeBookingService::BondTradeBookingService()
{
  
  TradeMP = map<string,Trade<Bond> >();
 
  TradeListeners = vector< ServiceListener< Trade<Bond> >* >();
  
}


Trade<Bond>& BondTradeBookingService::GetData(string key)
{
  if(TradeMP.find(key)!=TradeMP.end())
  {
    return TradeMP[key];
  }
  //std::cout<<key<<std::endl;
}

void BondTradeBookingService::OnMessage(Trade<Bond> &data)
{
  BookTrade(data);

  if(TradeListeners.size()!=0)
  {
  for(int i = 0; i<TradeListeners.size();i++)
  {
    TradeListeners[i]->ProcessAdd(data);
  }
  }
  
}

void BondTradeBookingService::AddListener(ServiceListener<Trade<Bond> > *listener)
{
    TradeListeners.push_back(listener);
}

  // Get all listeners on the Service.
const vector< ServiceListener<Trade<Bond> >* >& BondTradeBookingService::GetListeners() const
{
    return TradeListeners;
}

// Book the trade
void BondTradeBookingService::BookTrade( Trade<Bond> &trade)
{
  TradeMP.insert(pair< string,Trade<Bond> >( trade.GetTradeId(), trade ) );
} 
  

class BondTradeBookingServiceConnector: public Connector < Trade<Bond> >
{
public:

  BondTradeBookingServiceConnector( BondTradeBookingService& _myline):BondTradeBooking(_myline){}; 
  virtual void Publish(Trade<Bond>& data){};




  void Subscribe()
  {
    string line;
    std::ifstream file("trades.txt");

    while(getline(file,line))
  {
    
    std::stringstream linestream(line);

    std::string product;
    std::string tradeID;
    std::string price;
    std::string book;
    std::string quantity;
    std::string side;

    std::getline(linestream,product,',');
    std::getline(linestream,tradeID,',');
    std::getline(linestream,price,',');
    std::getline(linestream,book,',');
    std::getline(linestream,quantity,',');
    std::getline(linestream,side,',');
   
    
   // std::cout<<"here initial "<<side<<std::endl;



    if(!product.empty())
    {

       long quant = atol(quantity.c_str());

          Side pside;
          if(side == "BUY")
          {
            pside = BUY;
          }
          else
          {
            pside = SELL;
          }          
          std::string delimiter = "-";
          std::string token1 = price.substr(0,price.find(delimiter));
          std::string token2 = price.substr(price.find(delimiter)+1,(price.length()-1));
          
          double tradedPrice;
          if(token1.size() ==2)
          {
            tradedPrice = double(token1[0]-'0')*10 + double(token1[1]-'0');          
          }
          else if(token1.size() == 3)
          {
            tradedPrice = double(token1[0]-'0')*100 + double(token1[1]-'0')*10 + double(token1[2]-'0'); 
          }
          
          double xy = (double)(token2[0]-'0')*10+(double)(token2[1]-'0');   //std::string z = token2[2];
          double z = (double)(token2[2]-'0');

          tradedPrice = tradedPrice + xy / 32 + z/256;
  
        if(product == "2Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2019,Oct,31);
          Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);
          
          Trade<Bond> obj1 = Trade<Bond>(bond2Y,tradeID,tradedPrice,book,quant,pside);
          
          std::cout<<"here 1"<<std::endl;

          BondTradeBooking.OnMessage(obj1);

          std::cout<<"here 2"<<std::endl;
          //std::cout<<"product: "<<BondTradeBooking.GetData(tradeID).GetTradeId()<<std::endl;
        }

        else if(product == "3Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);

          Trade<Bond> obj1 = Trade<Bond>(bond3Y,tradeID,tradedPrice,book,quant,pside);
          BondTradeBooking.OnMessage(obj1);
  
        }

        else if(product == "5Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

          Trade<Bond> obj1 = Trade<Bond>(bond5Y,tradeID,tradedPrice,book,quant,pside);
          BondTradeBooking.OnMessage(obj1);
          //myline.push_back(obj1);          
        }
        else if(product == "7Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          
          Trade<Bond> obj1 = Trade<Bond>(bond7Y,tradeID,tradedPrice,book,quant,pside);
          BondTradeBooking.OnMessage(obj1);          
        }
        else if(product == "10Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

          Trade<Bond> obj1 = Trade<Bond>(bond10Y,tradeID,tradedPrice,book,quant,pside);
          BondTradeBooking.OnMessage(obj1);
        }
        else if(product == "30Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);
          
          Trade<Bond> obj1 = Trade<Bond>(bond30Y,tradeID,tradedPrice,book,quant,pside);
          BondTradeBooking.OnMessage(obj1);
        }

    }
  }


  }
private:
  BondTradeBookingService BondTradeBooking;
};





#endif
