/**
 * pricingservice.hpp
 * Defines the data types and Service for internal prices.
 *
 * @author Breman Thuraisingham
 */
#ifndef PRICING_SERVICE_HPP
#define PRICING_SERVICE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
#include <chrono>
#include <thread>
#include "soa.hpp"
#include "products.hpp"

using namespace std;
/**
 * A price object consisting of mid and bid/offer spread.
 * Type T is the product type.
 */
template<typename T>
class Price
{

public:

  // ctor for a price
  Price(const T& _product, double _mid, double _bidOfferSpread);
  
  Price(){};

  // Get the product
  const T& GetProduct() const;

  // Get the mid price
  double GetMid() const;

  // Get the bid/offer spread around the mid
  double GetBidOfferSpread() const;

private:
  T product;
  double mid;
  double bidOfferSpread;

};

/**
 * Pricing Service managing mid prices and bid/offers.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PricingService : public Service<string,Price <T> >
{
};

template<typename T>
Price<T>::Price(const T &_product, double _mid, double _bidOfferSpread) :
  product(_product)
{
  mid = _mid;
  bidOfferSpread = _bidOfferSpread;
}

template<typename T>
const T& Price<T>::GetProduct() const
{
  return product;
}

template<typename T>
double Price<T>::GetMid() const
{
  return mid;
}

template<typename T>
double Price<T>::GetBidOfferSpread() const
{
  return bidOfferSpread;
}





class BondPricingService : public PricingService <Bond>
{

  std::map<string, Price<Bond> > BondPriceMP;  //<2Y, Price<Bond> >
  std::vector< ServiceListener< Price<Bond> >* > BondPriceListener;

public:
  BondPricingService()
  {
    BondPriceMP = std::map<string, Price<Bond> >();
    BondPriceListener =std::vector< ServiceListener< Price<Bond> >* > ();
  }

  // Get data on our service given a key
  virtual Price<Bond>& GetData(string key)
  {
     if(BondPriceMP.find(key)!=BondPriceMP.end())
    {
      return BondPriceMP[key];
    }
       // return BondPriceMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(Price<Bond> &data)
  {

    BondPriceMP.insert(std::pair<string,Price<Bond> >(data.GetProduct().GetProductId(), data));

    if(BondPriceListener.size()!=0)
    {
    for(int i = 0; i<BondPriceListener.size();i++)
    {

      BondPriceListener[i]->ProcessAdd(data);
      std::cout<<"data send to AlgoStremingService"<<std::endl;
    }

    
    }



  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< Price<Bond> > *listener)
  {
    BondPriceListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< Price<Bond> >* >& GetListeners() const
  {
    return BondPriceListener;
  }
};


class BondPricingServiceConnector : public Connector < Price <Bond> >
{
private:
  BondPricingService bondPriceService;

public:
  BondPricingServiceConnector( BondPricingService& _myline):bondPriceService(_myline){}; 
  
  virtual void Publish(Price<Bond>& data){};

  void Subscribe()
  {
    string line;
    std::ifstream file("price.txt");

    while(getline(file,line))
  {
    

    
    std::this_thread::sleep_for(chrono::seconds(1));
   


    if(!line.empty())
    {
      std::stringstream linestream(line);

      std::string product;
      std::string cusip;
      std::string mid;
      std::string spread;

      
      std::getline(linestream,product,',');
      std::getline(linestream,cusip,',');

      std::getline(linestream,mid,',');
      std::getline(linestream,spread,',');

      double midPrice = stod(mid);
      double bidofferspread = stod(spread);

      
      
    if(!product.empty())
    {
                if(product == "2Y")
              {

                    BondIdType idType = CUSIP;
                    date maturityDate(2019,Oct,31);
                     const Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);
                        
                    Price<Bond> obj1 = Price<Bond>(bond2Y,midPrice,bidofferspread);
                    bondPriceService.OnMessage(obj1);
                    //std::cout<<"updated"<<std::endl;
                    std::cout<<"Price imported"<<std::endl;
              }
              else if (product == "3Y")
              {

                    BondIdType idType = CUSIP;
                    date maturityDate(2020,Nov,15);
                    const Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
                    
                    Price<Bond> obj1 = Price<Bond>(bond3Y,midPrice,bidofferspread);
                    bondPriceService.OnMessage(obj1);

              }
              else if (product == "5Y")
              {
                    BondIdType idType = CUSIP;
                    date maturityDate(2022,Oct,31);
                    const Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

                    Price<Bond> obj1 = Price<Bond>(bond5Y,midPrice,bidofferspread);
                    bondPriceService.OnMessage(obj1);
              }
              else if (product == "7Y")
              {
                    BondIdType idType = CUSIP;
                    date maturityDate(2024,Oct,31);
                    const Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);

                    Price<Bond> obj1 = Price<Bond>(bond7Y,midPrice,bidofferspread);
                    bondPriceService.OnMessage(obj1);
              }
              else if (product == "10Y")
              {

                    BondIdType idType = CUSIP;
                    date maturityDate(2027,Nov,15);
                    const Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

                    Price<Bond> obj1 = Price<Bond>(bond10Y,midPrice,bidofferspread);
                    bondPriceService.OnMessage(obj1);

              }
              else if (product == "30Y")
              {

                    BondIdType idType = CUSIP;
                    date maturityDate(2047,Nov,15);
                    const Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);

                    Price<Bond> obj1 = Price<Bond>(bond30Y,midPrice,bidofferspread);
                    bondPriceService.OnMessage(obj1);
              }
    }
      
    }
    
 }

 }

};































#endif
