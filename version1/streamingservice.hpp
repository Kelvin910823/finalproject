/**
 * streamingservice.hpp
 * Defines the data types and Service for price streams.
 *
 * @author Breman Thuraisingham
 */
#ifndef STREAMING_SERVICE_HPP
#define STREAMING_SERVICE_HPP

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>     
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>


#include "soa.hpp"
#include "marketdataservice.hpp"
#include "products.hpp"
#include "pricingservice.hpp"


using namespace std::chrono;

using namespace std;  

/**
 * A price stream order with price and quantity (visible and hidden)
 */
class PriceStreamOrder
{

public:

  // ctor for an order
  PriceStreamOrder(double _price, long _visibleQuantity, long _hiddenQuantity, PricingSide _side);
  PriceStreamOrder(){};

  // The side on this order
  PricingSide GetSide() const;

  // Get the price on this order
  double GetPrice() const;

  // Get the visible quantity on this order
  long GetVisibleQuantity() const;

  // Get the hidden quantity on this order
  long GetHiddenQuantity() const;

private:
  double price;
  long visibleQuantity;
  long hiddenQuantity;
  PricingSide side;

};

/**
 * Price Stream with a two-way market.
 * Type T is the product type.
 */
template<typename T>
class PriceStream
{

public:

  // ctor
  PriceStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder);

  PriceStream(){};

  // Get the product
  const T& GetProduct() const;

  // Get the bid order
  const PriceStreamOrder& GetBidOrder() const;

  // Get the offer order
  const PriceStreamOrder& GetOfferOrder() const;

private:
  T product;
  PriceStreamOrder bidOrder;
  PriceStreamOrder offerOrder;

};


class AlgoStream
{
private:
  PriceStream<Bond> priceStream;
public:
  AlgoStream(PriceStream<Bond> data):priceStream(data){};
  AlgoStream(){};
  
  const Bond& GetProduct() const
  {
    return priceStream.GetProduct();
  }

  const PriceStreamOrder& GetBidOrder() const
  {
    return priceStream.GetBidOrder();
  }

  const PriceStreamOrder& GetOfferOrder() const
  {
    return priceStream.GetOfferOrder();
  }

  PriceStream<Bond>  GetPriceStream() const
  {
    return priceStream;
  }

};




class BondAlgoStreamService
{
private:
  std::map<string, AlgoStream > AlgoStreamMP;
  std::vector< ServiceListener< AlgoStream >* > AlgoStreamListeners;
public:

   virtual AlgoStream& GetData(string key)
   {
    return AlgoStreamMP[key];
   }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(AlgoStream &data)
  {

    if(AlgoStreamListeners.size()!=0)
    {
    //std::cout<<"OnMessage 2"<<std::endl;

  //for(std::vector<ServiceListener< Trade<Bond> >* >::iterator it = TradeListeners.begin();it!=TradeListeners.end();it++)
    for(int i = 0; i<AlgoStreamListeners.size();i++)
    {
    //std::cout<<"OnMessage 3"<<std::endl;
    //(*it)->ProcessAdd(data);
      AlgoStreamListeners[i]->ProcessAdd(data);
      //std::cout<<"listener invoked for market data service"<<std::endl;
    }
  //std::cout<<"OnMessage 4"<<std::endl;
    
    }
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< AlgoStream > *listener)
  {
    AlgoStreamListeners.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener<AlgoStream>* >& GetListeners() const
  {
    return AlgoStreamListeners;
  }

  void AddStream(AlgoStream &data)
  {
     if(AlgoStreamMP.find(data.GetProduct().GetProductId())==AlgoStreamMP.end())
     {
        AlgoStreamMP.insert(std::pair<string, AlgoStream >(data.GetProduct().GetProductId(), data));  
     }
     else
     {
        AlgoStreamMP[data.GetProduct().GetProductId()] = data;
     }
     std::cout<<"finally"<<std::endl;
     OnMessage(data);
  }
};



class BondPricingAlgoStreamServiceListener : public ServiceListener< Price<Bond> >
{
  public:
   
    BondPricingAlgoStreamServiceListener(BondAlgoStreamService* AlgoStreamService_):AlgoStreamService(AlgoStreamService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(Price<Bond> &data)
  {
    string productId = data.GetProduct().GetProductId();
    double midPrice = data.GetMid();
    double spreadPrice = data.GetBidOfferSpread();
    
    PricingSide pside1 = BID;
    PricingSide pside2 = OFFER;
    

    double bidPrice = midPrice - spreadPrice*0.5;
    double offerPrice = midPrice + spreadPrice * 0.5;


    int factor1, factor2;
    srand (time(NULL));
    factor1 = rand() % 10 + 1;
    factor2 = rand() % 10  + 1;
    long visibleQuant = factor1 * 10000000;
    long hiddenQuant = factor2 * 10000000;

    PriceStreamOrder bidOrder(bidPrice,visibleQuant,hiddenQuant,pside1);
    PriceStreamOrder offerOrder(offerPrice, visibleQuant, hiddenQuant,pside2);


        if(productId == "2Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2019,Oct,31);
          Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);

          PriceStream<Bond> obj = PriceStream<Bond>(bond2Y,bidOrder, offerOrder);
          AlgoStream algoStreamObj(obj);
          AlgoStreamService->AddStream(algoStreamObj);
        }
        else if(productId == "3Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
          PriceStream<Bond> obj = PriceStream<Bond>(bond3Y,bidOrder, offerOrder);
          AlgoStream algoStreamObj(obj);
          AlgoStreamService->AddStream(algoStreamObj);
        }

        else if(productId == "5Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);
          PriceStream<Bond> obj = PriceStream<Bond>(bond5Y,bidOrder, offerOrder);
          AlgoStream algoStreamObj(obj);
          AlgoStreamService->AddStream(algoStreamObj);
        }
        else if(productId == "7Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          PriceStream<Bond> obj = PriceStream<Bond>(bond7Y,bidOrder, offerOrder);
          AlgoStream algoStreamObj(obj);
          AlgoStreamService->AddStream(algoStreamObj);
          
        }
        else if(productId == "10Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);
          PriceStream<Bond> obj = PriceStream<Bond>(bond10Y,bidOrder, offerOrder);
          AlgoStream algoStreamObj(obj);
          AlgoStreamService->AddStream(algoStreamObj);

        }
        else if(productId == "30Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);
          PriceStream<Bond> obj = PriceStream<Bond>(bond30Y,bidOrder, offerOrder);
          AlgoStream algoStreamObj(obj);
          AlgoStreamService->AddStream(algoStreamObj);
          
        }
  
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(Price<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(Price<Bond> &data)
  {

  }

  private:

  BondAlgoStreamService* AlgoStreamService;

};






/**
 * Streaming service to publish two-way prices.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class StreamingService : public Service<string,PriceStream <T> >
{

public:

  // Publish two-way prices
   virtual void PublishPrice( PriceStream<T>& priceStream) = 0;

};




class BondStreamingService : public StreamingService <Bond>
{
private:
  std::map<string, PriceStream<Bond> > BondStreamMP;
  std::vector< ServiceListener<PriceStream<Bond> >*> BondStreamListeners;
public:

  // Get data on our service given a key
  virtual PriceStream<Bond>& GetData(string key)
  {
    return BondStreamMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(PriceStream<Bond> &data)
  {

    if(BondStreamListeners.size()!=0)
    {
    for(int i = 0; i<BondStreamListeners.size();i++)
    {

      BondStreamListeners[i]->ProcessAdd(data);
      
    }
    }

  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< PriceStream<Bond> > *listener)
  {
    BondStreamListeners.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< PriceStream<Bond> >* >& GetListeners() const
  {
    return BondStreamListeners;
  }

  void PublishPrice( PriceStream<Bond>& priceStream)
  {
      if(BondStreamMP.find(priceStream.GetProduct().GetProductId())==BondStreamMP.end())
     {
        BondStreamMP.insert(std::pair<string, PriceStream<Bond> >(priceStream.GetProduct().GetProductId(), priceStream));  
     }
     else
     {
        BondStreamMP[priceStream.GetProduct().GetProductId()] = priceStream;
     }
     OnMessage(priceStream);
     std::cout<<"price transferred!!!"<<std::endl;
  }

};

class BondAlgoStreamStreamServiceListener : public ServiceListener < AlgoStream >
{
  public:
   
    BondAlgoStreamStreamServiceListener(BondStreamingService* BondStreamService_):BondStreamService(BondStreamService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(AlgoStream &data)

  {
    auto product = data.GetProduct();
    auto bidOrder = data.GetBidOrder();
    auto offerOrder = data.GetOfferOrder();

    PriceStream<Bond> obj=PriceStream<Bond>(product,bidOrder,offerOrder);
    BondStreamService->PublishPrice(obj);
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(AlgoStream &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(AlgoStream &data)
  {

  }

  private:

  BondStreamingService* BondStreamService;


};


class GUIServiceConnector : public Connector < Price<Bond> >
{
public:
  GUIServiceConnector(){};

  virtual void Publish(Price<Bond>& price)
  {
    
    ofstream myfile;
    myfile.open ("gui.txt",fstream::app);
    std::string productId = price.GetProduct().GetProductId();
    double midPrice = price.GetMid();
    double bidofferSpread = price.GetBidOfferSpread();

    double bid = midPrice - 0.5*bidofferSpread;
    double offer = midPrice + 0.5*bidofferSpread;

    std::ostringstream strs1;
    strs1 << bid;
    std::string str1 = strs1.str();

    std::ostringstream strs2;
    strs2 << offer;
    std::string str2 = strs2.str();

    milliseconds ms = duration_cast< milliseconds >(
    system_clock::now().time_since_epoch());

   // std::cout<< ms<<std::endl;

    std::string quote = productId + ","+ str1 +","+str2+","+std::to_string(ms.count())+"\n";
    myfile<<quote;
    myfile.close();

  }
};



class GUIService
{
private:
  std::map<string, Price<Bond> > GUIServiceMP;
  GUIServiceConnector publishCon;
  std::vector< ServiceListener<Price<Bond> >*> GUIListener;
public:

    GUIService(GUIServiceConnector publishCon_):publishCon(publishCon_)
    {
        GUIServiceMP = std::map<string, Price<Bond> >();
        GUIListener = std::vector< ServiceListener<Price<Bond> >*>();
    }


  // Get data on our service given a key
  virtual Price<Bond>& GetData(string key)
  {
      return GUIServiceMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(Price<Bond> &data) 
  {
     if(GUIListener.size()!=0)
    {
    for(int i = 0; i<GUIListener.size();i++)
    {

      GUIListener[i]->ProcessAdd(data);
      
    }
    }

  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener<Price<Bond> > *listener)
  {
    GUIListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener<Price<Bond> >* >& GetListeners() const
  {
    return GUIListener;
  }

  void AddPrice(Price<Bond> data)
  {
    if(GUIServiceMP.find(data.GetProduct().GetProductId())==GUIServiceMP.end())
     {
        GUIServiceMP.insert(std::pair<string, Price<Bond> >(data.GetProduct().GetProductId(), data));  
     }
     else
     {
        GUIServiceMP[data.GetProduct().GetProductId()] = data;
     }
    // std::cout<<"finally"<<std::endl;
     publishCon.Publish(data);
     OnMessage(data); 
  }

};


class BondPricingGUIServiceListener : public ServiceListener < Price<Bond> >
{
  public:
   
    BondPricingGUIServiceListener(GUIService* BondGUIService_):BondGUIService(BondGUIService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(Price<Bond> &data)

  {
    BondGUIService->AddPrice(data);
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(Price<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(Price<Bond> &data)
  {

  }

  private:

  GUIService* BondGUIService;


};


PriceStreamOrder::PriceStreamOrder(double _price, long _visibleQuantity, long _hiddenQuantity, PricingSide _side)
{
  price = _price;
  visibleQuantity = _visibleQuantity;
  hiddenQuantity = _hiddenQuantity;
  side = _side;
}

double PriceStreamOrder::GetPrice() const
{
  return price;
}

long PriceStreamOrder::GetVisibleQuantity() const
{
  return visibleQuantity;
}

long PriceStreamOrder::GetHiddenQuantity() const
{
  return hiddenQuantity;
}

template<typename T>
PriceStream<T>::PriceStream(const T &_product, const PriceStreamOrder &_bidOrder, const PriceStreamOrder &_offerOrder) :
  product(_product), bidOrder(_bidOrder), offerOrder(_offerOrder)
{
}

template<typename T>
const T& PriceStream<T>::GetProduct() const
{
  return product;
}

template<typename T>
const PriceStreamOrder& PriceStream<T>::GetBidOrder() const
{
  return bidOrder;
}

template<typename T>
const PriceStreamOrder& PriceStream<T>::GetOfferOrder() const
{
  return offerOrder;
}

#endif
