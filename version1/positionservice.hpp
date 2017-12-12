/**
 * positionservice.hpp
 * Defines the data types and Service for positions.
 *
 * @author Breman Thuraisingham
 */
#ifndef POSITION_SERVICE_HPP
#define POSITION_SERVICE_HPP

#include <string>
#include <map>
#include "soa.hpp"
#include "tradebookingservice.hpp"

using namespace std;

/**
 * Position class in a particular book.
 * Type T is the product type.
 */
template<typename T>
class Position
{

public:

  // ctor for a position
  Position(const T &_product);
  Position(){};

  // Get the product
  const T& GetProduct() const;

  // Get the position quantity
  long GetPosition(string &book);

  // Get the aggregate position
  long GetAggregatePosition();


  void UpdatePosition(string &book, long quant)
  {
    if(positions.find(book)== positions.end())
    {
      positions[book] = quant;
    }
    else
    {
      positions[book] += quant;
    }
  }

private:
  T product;  //2Y , 3Y , 5Y ...
  map<string,long> positions;  //<book, quant>

};


template<typename T>
Position<T>::Position(const T &_product) :
  product(_product)
{
  positions = map<string,long>();
}

template<typename T>
const T& Position<T>::GetProduct() const
{
  return product;
}

template<typename T>
long Position<T>::GetPosition(string &book)
{
  return positions[book];
}

template<typename T>
long Position<T>::GetAggregatePosition()
{
  // No-op implementation - should be filled out for implementations
  long res = 0;
  for(std::map<string,long>::iterator it = positions.begin();it!=positions.end();it++)
  {
      res += it->second;
  }

  return res;
}







/**
 * Position Service to manage positions across multiple books and secruties.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class PositionService : public Service<string,Position <T> >
{

public:
  // Add a trade to the service
  virtual void AddTrade(const Trade<T> &trade) = 0;

};


class BondPositionService : public PositionService<Bond>
{


private:
  std::map<string, Position<Bond> > PositionMP;    
  std::vector< ServiceListener<Position<Bond> >* > TradeListeners;

  //std::vector<ServiceListener< Position<Bond> >* > TradeListeners;

public:
  BondPositionService()
  {
    PositionMP = std::map<string, Position<Bond> >();// <2Y, Position<Bond2Y> >
    TradeListeners = std::vector< ServiceListener<Position<Bond> >* >();
  };

  // Get data on our service given a key
  virtual Position<Bond>& GetData(string key)
  {
    return PositionMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(Position<Bond> &data)
  {
    if(TradeListeners.size()!=0)
    {
    //std::cout<<"OnMessage 2"<<std::endl;

  //for(std::vector<ServiceListener< Trade<Bond> >* >::iterator it = TradeListeners.begin();it!=TradeListeners.end();it++)
      for(int i = 0; i<TradeListeners.size();i++)
    {
    //std::cout<<"OnMessage 3"<<std::endl;
    //(*it)->ProcessAdd(data);
      TradeListeners[i]->ProcessAdd(data);
    }
  //std::cout<<"OnMessage 4"<<std::endl;
    
    }
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< Position<Bond> > *listener)
  {
    TradeListeners.push_back(listener);
  }

  // Get all listeners on the Service.
  const std::vector<ServiceListener< Position<Bond> >* >& GetListeners() const
  {
    return TradeListeners;
  }

  virtual void AddTrade(const Trade<Bond>& trade)
  {
    string productID = trade.GetProduct().GetProductId();
    string book = trade.GetBook();
    long quant = trade.GetQuantity();
    Side pside = trade.GetSide();
    long price = trade.GetPrice();

    switch(pside)
    {
      case BUY: quant = quant; break;
      case SELL: quant = -quant; break;
    }

    //std::cout<<"Add Trade Initial"<<std::endl;
   if(PositionMP.find(productID)== PositionMP.end())
    {
      
      if(productID == "2Y")
      {
        //std::cout<<"Begining Add"<<std::endl;
          BondIdType idType = CUSIP;
          date maturityDate(2019,Oct,31);
          const Bond bond2Y("2Y", idType, "T", 0.015, maturityDate);

          //std::cout<<"position 1"<<std::endl;
          
          Position<Bond> obj1 = Position<Bond>(bond2Y);
          //std::cout<<"position 2"<<std::endl;
          obj1.UpdatePosition(book,quant);
          //std::cout<<"position 3"<<std::endl;
         
          //PositionMP[productID] = obj1;
          OnMessage(obj1);
          
          PositionMP.insert(std::pair<string,Position<Bond> >(productID, obj1));

          //std::cout<<"add first"<<std::endl;

      }
      else if(productID == "3Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          const Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
          
          Position<Bond> obj1 = Position<Bond>(bond3Y);
          obj1.UpdatePosition(book,quant);
          OnMessage(obj1);
          //PositionMP[productID] = obj1;
          PositionMP.insert(std::pair<string,Position<Bond> >(productID, obj1));

      }
      else if(productID == "5Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          const Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

          Position<Bond> obj1 = Position<Bond>(bond5Y);
          obj1.UpdatePosition(book,quant);
          
          OnMessage(obj1);
          //PositionMP[productID] = obj1;
          PositionMP.insert(std::pair<string,Position<Bond> >(productID, obj1));

      }
      else if(productID == "7Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          const Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          Position<Bond> obj1 = Position<Bond>(bond7Y);
          obj1.UpdatePosition(book,quant);
          
          OnMessage(obj1);
          //PositionMP[productID] = obj1;
          PositionMP.insert(std::pair<string,Position<Bond> >(productID, obj1));

      }
      else if(productID == "10Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          const Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

          
          Position<Bond> obj1 = Position<Bond>(bond10Y);
          obj1.UpdatePosition(book,quant);
          
          OnMessage(obj1);
          //PositionMP[productID] = obj1;
          PositionMP.insert(std::pair<string,Position<Bond> >(productID, obj1));

      }
      else if(productID == "30Y")
      {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          const Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate); 
          
          Position<Bond> obj1 = Position<Bond>(bond30Y);
          obj1.UpdatePosition(book,quant);
          
          OnMessage(obj1);
          //PositionMP[productID] = obj1;
          PositionMP.insert(std::pair<string,Position<Bond> >(productID, obj1));

      }
    }
    else
    {
      PositionMP[productID].UpdatePosition(book , quant);

      OnMessage(PositionMP[productID]);
      //std::cout<<"I am Finnally!!!!"<<std::endl;
    }

  } 
};





class BondBookingPositionServiceListener : public ServiceListener< Trade<Bond> >
{
  public:
   
    BondBookingPositionServiceListener(BondPositionService* bondPositionService_):positionService(bondPositionService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(Trade<Bond> &data)
  {
    //std::cout<<"Listern 1"<<std::endl;
    positionService->AddTrade(data);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(Trade<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(Trade<Bond> &data)
  {

  }

  private:

  BondPositionService* positionService;

};


#endif
