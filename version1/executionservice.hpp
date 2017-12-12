/**
 * executionservice.hpp
 * Defines the data types and Service for executions.
 *
 * @author Breman Thuraisingham
 */
#ifndef EXECUTION_SERVICE_HPP
#define EXECUTION_SERVICE_HPP

#include <string>
#include <sys/time.h>
#include <functional>
#include <chrono>
#include <iostream>
#include <chrono>
#include <ctime>
#include <ratio>
#include <sstream>
#include <cstdlib>
#include "soa.hpp"
#include "marketdataservice.hpp"
#include "tradebookingservice.hpp"







using namespace std;
using namespace std::chrono;


int roll(int min, int max)
{
   // x is in [0,1[
   double x = rand()/static_cast<double>(RAND_MAX+1); 

   // [0,1[ * (max - min) + min is in [min,max[
   int that = min + static_cast<int>( x * (max - min) );

   return that;
}



enum OrderType { FOK, IOC, MARKET, LIMIT, STOP };

enum Market { BROKERTEC, ESPEED, CME };

/**
 * An execution order that can be placed on an exchange.
 * Type T is the product type.
 */
template<typename T>
class ExecutionOrder
{

public:

  // ctor for an order
  ExecutionOrder(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, double _visibleQuantity, double _hiddenQuantity, string _parentOrderId, bool _isChildOrder);

  ExecutionOrder(){};
  // Get the product
  const T& GetProduct() const;

  // Get the order ID
  const string& GetOrderId() const;

  // Get the order type on this order
  OrderType GetOrderType() const;

  // Get the price on this order
  double GetPrice() const;

  // Get the visible quantity on this order
  long GetVisibleQuantity() const;

  // Get the hidden quantity
  long GetHiddenQuantity() const;

  // Get the parent order ID
  const string& GetParentOrderId() const;

  // Is child order?
  bool IsChildOrder() const;

private:
  T product;
  PricingSide side;
  string orderId;
  OrderType orderType;
  double price;
  double visibleQuantity;
  double hiddenQuantity;
  string parentOrderId;
  bool isChildOrder;

};


template<typename T>
class AlgoExecution
{
private:
  ExecutionOrder<T> executionOrder;
public:
    AlgoExecution(ExecutionOrder<T> _executionOrder):executionOrder(_executionOrder){};

    const T& GetProduct() const
    {
      return executionOrder.GetProduct();
    }

    // Get the order ID
    const string& GetOrderId() const
    {
      return executionOrder.GetOrderId();
    }

    // Get the order type on this order
    OrderType GetOrderType() const
    {
      return executionOrder.GetOrderType();
    }

    // Get the price on this order(
      double GetPrice() const
    {
      return executionOrder.GetPrice();
    }
  
    // Get the visible quantity on this order
    long GetVisibleQuantity() const
    {
      return executionOrder.GetVisibleQuantity();
    }
  
    // Get the hidden quantity
    long GetHiddenQuantity() const
    {
      return executionOrder.GetHiddenQuantity();
    }


    // Get the parent order ID
    const string& GetParentOrderId() const
    {
      return executionOrder.GetParentOrderId();
    }

    // Is child order?
    bool IsChildOrder() const
    {
      return executionOrder.IsChildOrder();
    }

    ExecutionOrder<T> GetExecutionOrder()
    {
      return executionOrder;
    }

};


class BondAlgoExecutionService
{
private:
  std::map<string, AlgoExecution<Bond> > AlgoExecutionMP;
  vector< ServiceListener< AlgoExecution<Bond> >* > BondAlgoExecutionServiceListener;
 
public:
  BondAlgoExecutionService ()
  {
    AlgoExecutionMP = std::map<string,AlgoExecution<Bond> >();
  };


  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< AlgoExecution<Bond> > *listener)
  {
      BondAlgoExecutionServiceListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< AlgoExecution<Bond> >* >& GetListeners() const
  {
      return BondAlgoExecutionServiceListener;
  }

  std::vector< AlgoExecution<Bond> > GetBestExecution(OrderBook<Bond> orderBook)
  {

      std::vector< AlgoExecution<Bond> > res;

      Bond product = orderBook.GetProduct();
      vector<Order> bidStack = orderBook.GetBidStack();
      vector<Order> offerStack = orderBook.GetOfferStack();
      int bestIdx;

      for(int i = 0; i<bidStack.size();i++)
      {
        if(offerStack[i].GetPrice()-bidStack[i].GetPrice() == 0.00390625)
        {
          bestIdx = i;
          break;
        }
      }

      long quant = bidStack[bestIdx].GetQuantity();
      double buyPrice = bidStack[bestIdx].GetPrice();
      double sellPrice = offerStack[bestIdx].GetPrice();

      string productType = product.GetProductId();

      PricingSide side1 = BID;
      PricingSide side2 = OFFER;
      OrderType orderType = LIMIT;
      double visibleQuantity = quant;
      double hiddenQuantity = 0;
      
      bool isChildOrder = false;

      if(productType == "2Y")
      {
        
        BondIdType idType = CUSIP;
        date maturityDate(2019,Oct,31);
        Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);
            
        
        high_resolution_clock::time_point now = high_resolution_clock::now();
        std::time_t now_c = std::chrono::high_resolution_clock::to_time_t(now);
        char ch[64];
        strftime(ch, sizeof(ch), "%Y-%m-%d %H-%M-%S", localtime(&now_c)); //年-月-日 时-分-秒
    
        auto key1 = hash<string>{}(ch);
        std::stringstream ss1;
        ss1  << key1;
        std::string OrderId1 = ss1.str();
        std::string cusip = "912828F62";
    
        string buyparentOrderId = cusip+OrderId1;
        ExecutionOrder<Bond> obj1 = ExecutionOrder<Bond>(bond2Y,side1,buyparentOrderId,orderType,buyPrice,quant,0,buyparentOrderId,isChildOrder);

        //str2 = datetime.datetime.now().strftime("%Y-%T");
        high_resolution_clock::time_point now2 = high_resolution_clock::now();
        std::time_t now_c2 = std::chrono::high_resolution_clock::to_time_t(now2);
        char ch2[64];
        strftime(ch2, sizeof(ch2), "%Y-%m-%d %H-%M-%S", localtime(&now_c2)); //年-月-日 时-分-秒
    
        auto key2 = hash<string>{}(ch2);
        std::stringstream ss2;
        ss2  << key2;
        std::string OrderId2 = ss2.str();
        string sellparentOrderId = "912828F62"+OrderId2;
        ExecutionOrder<Bond> obj2 = ExecutionOrder<Bond>(bond2Y,side2,sellparentOrderId,orderType,sellPrice,-quant,0,sellparentOrderId,isChildOrder);  
       
        res.push_back(obj1);
        res.push_back(obj2);
        return res; 
      }
     /* else if(productType == "3Y")
      {
        
        BondIdType idType = CUSIP;
        date maturityDate(2020,Nov,15);
        Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);
            
        

       // str1 = datetime.datetime.now().strftime("%Y-%T");
        auto key1 = hash(str1);
        std::stringstream ss1;
        ss1  << key1;
        std::string OrderId1 = ss1.str();
        
        string buyparentOrderId = "9128283G3"+OrderId1;

        ExecutionOrder<Bond> obj1 = ExecutionOrder<Bond>(bond3Y,side1,buyparentOrderId,orderType,buyPrice,quant,0,buyparentOrderId,isChildOrder);

        //str2 = datetime.datetime.now().strftime("%Y-%T");
        auto key2 = hash(str2);
        std::stringstream ss1;
        ss1  << key2;
        std::string OrderId2 = ss2.str();
        string sellparentOrderId = "9128283G3"+OrderId2;
        ExecutionOrder<Bond> obj2 = ExecutionOrder<Bond>(bond3Y,side2,sellparentOrderId,orderType,sellPrice,quant,0,sellparentOrderId,isChildOrder);  
        res.push_back(obj1);
        res.push_back(obj2);
        return res; 
      }
       else if(productType == "5Y")
      {
        
        BondIdType idType = CUSIP;
        date maturityDate(2022,Oct,31);
        Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);
            
       // str1 = datetime.datetime.now().strftime("%Y-%T");
        auto key1 = hash(str1);
        std::stringstream ss1;
        ss1  << key1;
        std::string OrderId1 = ss1.str();
        
        string buyparentOrderId = "9128283C2"+OrderId1;
        ExecutionOrder<Bond> obj1 = ExecutionOrder<Bond>(bond5Y,side1,buyparentOrderId,orderType,buyPrice,quant,0,buyparentOrderId,isChildOrder);

        //str2 = datetime.datetime.now().strftime("%Y-%T");
        auto key2 = hash(str2);
        std::stringstream ss1;
        ss1  << key2;
        std::string OrderId2 = ss2.str();
        string sellparentOrderId = "9128283C2"+OrderId2;
        ExecutionOrder<Bond> obj2 = ExecutionOrder<Bond>(bond5Y,side2,sellparentOrderId,orderType,sellPrice,quant,0,sellparentOrderId,isChildOrder);  
        res.push_back(obj1);
        res.push_back(obj2);
        return res; 
      }
       else if(productType == "7Y")
      {
        
        BondIdType idType = CUSIP;
        date maturityDate(2024,Oct,31);
        Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
            
        //str1 = datetime.datetime.now().strftime("%Y-%T");
        auto key1 = hash(str1);
        std::stringstream ss1;
        ss1  << key1;
        std::string OrderId1 = ss1.str();
        
        string buyparentOrderId = "9128283D0"+OrderId1;
        ExecutionOrder<Bond> obj1 = ExecutionOrder<Bond>(bond7Y,side1,buyparentOrderId,orderType,buyPrice,quant,0,buyparentOrderId,isChildOrder);

        //str2 = datetime.datetime.now().strftime("%Y-%T");
        auto key2 = hash(str2);
        std::stringstream ss1;
        ss1  << key2;
        std::string OrderId2 = ss2.str();
        string sellparentOrderId = "9128283D0"+OrderId2;
        ExecutionOrder<Bond> obj2 = ExecutionOrder<Bond>(bond7Y,side2,sellparentOrderId,orderType,sellPrice,quant,0,sellparentOrderId,isChildOrder);  
        res.push_back(obj1);
        res.push_back(obj2);
        return res; 
      }
       else if(productType == "10Y")
      {
        
       BondIdType idType = CUSIP;
       date maturityDate(2027,Nov,15);
       Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);
            
        //str1 = datetime.datetime.now().strftime("%Y-%T");
        auto key1 = hash(str1);
        std::stringstream ss1;
        ss1  << key1;
        std::string OrderId1 = ss1.str();
        
        string buyparentOrderId = "9128283F5"+OrderId1;
        ExecutionOrder<Bond> obj1 = ExecutionOrder<Bond>(bond10Y,side1,buyparentOrderId,orderType,buyPrice,quant,0,buyparentOrderId,isChildOrder);

       // str2 = datetime.datetime.now().strftime("%Y-%T");
        auto key2 = hash(str2);
        std::stringstream ss1;
        ss1  << key2;
        std::string OrderId2 = ss2.str();
        string sellparentOrderId = "9128283F5"+OrderId2;
        ExecutionOrder<Bond> obj2 = ExecutionOrder<Bond>(bond10Y,side2,sellparentOrderId,orderType,sellPrice,quant,0,sellparentOrderId,isChildOrder);  
        res.push_back(obj1);
        res.push_back(obj2);
        return res; 
      }
       else if(productType == "30Y")
      {
        
        BondIdType idType = CUSIP;
        date maturityDate(2047,Nov,15);
        Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);
            
        //str1 = datetime.datetime.now().strftime("%Y-%T");
        auto key1 = hash(str1);
        std::stringstream ss1;
        ss1  << key1;
        std::string OrderId1 = ss1.str();
        
        string buyparentOrderId = "912810RZ3"+OrderId1;
        ExecutionOrder<Bond> obj1 = ExecutionOrder<Bond>(bond30Y,side1,buyparentOrderId,orderType,buyPrice,quant,0,buyparentOrderId,isChildOrder);

        //str2 = datetime.datetime.now().strftime("%Y-%T");
        auto key2 = hash(str2);
        std::stringstream ss1;
        ss1  << key2;
        std::string OrderId2 = ss2.str();
        string sellparentOrderId = "912810RZ3"+OrderId2;
        ExecutionOrder<Bond> obj2 = ExecutionOrder<Bond>(bond30Y,side2,sellparentOrderId,orderType,sellPrice,quant,0,sellparentOrderId,isChildOrder);  
        res.push_back(obj1);
        res.push_back(obj2);
        return res; 
      }*/
  }

  void AddExecutionOrder( OrderBook<Bond>& data )
  {
    std::vector< AlgoExecution<Bond> > bestOrder = GetBestExecution(data);
    AlgoExecutionMP.insert(std::pair<string,AlgoExecution<Bond> >(bestOrder[0].GetOrderId(), bestOrder[0]));
    AlgoExecutionMP.insert(std::pair<string,AlgoExecution<Bond> >(bestOrder[1].GetOrderId(), bestOrder[1]));
    
    std::cout<<bestOrder[0].GetOrderId()<<std::endl;
    std::cout<<bestOrder[1].GetOrderId()<<std::endl;
    OnMessage(data);
    std::cout<<"trade executed"<<std::endl;

  }


  void OnMessage(OrderBook<Bond> orderBook)
  {
    //to be developed
    
    std::vector< AlgoExecution<Bond> > bestOrder = GetBestExecution(orderBook);
    AlgoExecutionMP.insert(std::pair<string,AlgoExecution<Bond> >(bestOrder[0].GetOrderId(), bestOrder[0]));
    AlgoExecutionMP.insert(std::pair<string,AlgoExecution<Bond> >(bestOrder[1].GetOrderId(), bestOrder[1]));
    if(BondAlgoExecutionServiceListener.size()!=0)
    {
    for(int i = 0; i<BondAlgoExecutionServiceListener.size();i++)
    {
    
      BondAlgoExecutionServiceListener[i]->ProcessAdd(bestOrder[0]);
      BondAlgoExecutionServiceListener[i]->ProcessAdd(bestOrder[1]);
      
    }
    }
  }

};


class BondMarketDataAlgoExecutionServiceListener : public ServiceListener< OrderBook <Bond> >
{
    private:
      BondAlgoExecutionService* AlgoExecutionService;
    public:
      BondMarketDataAlgoExecutionServiceListener(BondAlgoExecutionService* AlgoExecutionService_):AlgoExecutionService(AlgoExecutionService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(OrderBook<Bond> &data)
  {
    //std::cout<<"Listern 1"<<std::endl;
    AlgoExecutionService->AddExecutionOrder(data);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(OrderBook<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(OrderBook<Bond> &data)
  {

  }
};








/**
 * Service for executing orders on an exchange.
 * Keyed on product identifier.
 * Type T is the product type.
 */
template<typename T>
class ExecutionService : public Service<string,ExecutionOrder <T> >
{

public:

  // Execute an order on a market
  virtual void ExecuteOrder( ExecutionOrder<T>& order, Market market) = 0;

};
//GetOrderId


class BondExecutionService : public ExecutionService< Bond >
{
  private:
  map<string,ExecutionOrder<Bond> > ExecutionOrderMP;
  map<string,Trade<Bond> > ExecutionTradeMP;
  vector< ServiceListener< ExecutionOrder<Bond> >* > BondExecutionServiceListener;

  public:

  // Get data on our service given a key
  virtual ExecutionOrder<Bond>& GetData(string key)
  {
    return ExecutionOrderMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(ExecutionOrder<Bond> &data)
  {
    //to be developed
    if(BondExecutionServiceListener.size()!=0)
    {
    //std::cout<<"OnMessage 2"<<std::endl;

  //for(std::vector<ServiceListener< Trade<Bond> >* >::iterator it = TradeListeners.begin();it!=TradeListeners.end();it++)
    for(int i = 0; i<BondExecutionServiceListener.size();i++)
    {
    //std::cout<<"OnMessage 3"<<std::endl;
    //(*it)->ProcessAdd(data);
      BondExecutionServiceListener[i]->ProcessAdd(data);
      //std::cout<<"listener invoked for market data service"<<std::endl;
    }
  //std::cout<<"OnMessage 4"<<std::endl;
    
    }
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< ExecutionOrder<Bond> > *listener)
  {
      BondExecutionServiceListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< ExecutionOrder<Bond> >* >& GetListeners() const
  {
      return BondExecutionServiceListener;
  }

  void ExecuteOrder( ExecutionOrder<Bond>& order, Market market)
  {
      Bond product = order.GetProduct();
      string tradeId = order.GetOrderId();
      double tradePrice = order.GetPrice();
      long quant = order.GetVisibleQuantity();
      string productId = product.GetProductId();

      int bookNum = roll(1,3);
      string book;

      if(bookNum == 1)
      {
        book = "TRSY1";
      }
      else if(bookNum == 2)
      {
        book = "TRSY2";
      }
      else if(bookNum == 3)
      {
        book = "TRSY3";
      }


       Side pside;
       if(quant < 0 )
       {
        pside = SELL;
       }
       else

       {
        pside = BUY;
       }

        if(productId == "2Y")
        {
            BondIdType idType = CUSIP;
            date maturityDate(2019,Oct,31);
            Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);
             Trade<Bond> obj1 = Trade<Bond>(bond2Y,tradeId,tradePrice,book,quant,pside);
            ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
            std::cout<<"trade executed!!!"<<std::endl;
            OnMessage(order);


        }
        else if(productId == "3Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);

          const Trade<Bond> obj1 = Trade<Bond>(bond3Y,tradeId,tradePrice,book,quant,pside);
          ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
          OnMessage(order);
        }

        else if(productId == "5Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

           Trade<Bond> obj1 = Trade<Bond>(bond5Y,tradeId,tradePrice,book,quant,pside);
          ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));//myline.push_back(obj1);  
          OnMessage(order);        
        }
        else if(productId == "7Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          
           Trade<Bond> obj1 = Trade<Bond>(bond7Y,tradeId,tradePrice,book,quant,pside);
          ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
          OnMessage(order);
        }
        else if(productId == "10Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

           Trade<Bond> obj1 = Trade<Bond>(bond10Y,tradeId,tradePrice,book,quant,pside);
          ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
          OnMessage(order);
        }
        else if(productId == "30Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);
           Trade<Bond> obj1 = Trade<Bond>(bond30Y,tradeId,tradePrice,book,quant,pside);
          ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
          OnMessage(order);
        }

  }
};


class BondAlgoExecutionExecutionServiceListener : public ServiceListener< AlgoExecution <Bond> >
{
  private:
      BondExecutionService* ExecutionService;
    public:
      BondAlgoExecutionExecutionServiceListener(BondExecutionService* ExecutionService_):ExecutionService(ExecutionService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd( AlgoExecution<Bond> &data)
  {
    Market mkt = CME;
    ExecutionOrder<Bond> executedOrder = data.GetExecutionOrder();
    //std::cout<<"Listern 1"<<std::endl;
    ExecutionService->ExecuteOrder(executedOrder,mkt);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(AlgoExecution<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(AlgoExecution<Bond> &data)
  {

  }
};





class BondExecutionTradeBookingServiceListener : public ServiceListener < ExecutionOrder<Bond> >
{
  private:
      BondTradeBookingService* TradeBookingService;
    public:
      BondExecutionTradeBookingServiceListener(BondTradeBookingService* TradeBookingService_):TradeBookingService(TradeBookingService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd( ExecutionOrder<Bond> &data)
  {

      Bond product = data.GetProduct();
      string tradeId = data.GetOrderId();
      double tradePrice = data.GetPrice();
      long quant = data.GetVisibleQuantity();
      string productId = product.GetProductId();

      int bookNum = roll(1,3);
      string book;

      if(bookNum == 1)
      {
        book = "TRSY1";
      }
      else if(bookNum == 2)
      {
        book = "TRSY2";
      }
      else if(bookNum == 3)
      {
        book = "TRSY3";
      }


       Side pside;
       if(quant < 0 )
       {
        pside = SELL;
       }
       else

       {
        pside = BUY;
       }

        if(productId == "2Y")
        {
            BondIdType idType = CUSIP;
            date maturityDate(2019,Oct,31);
            Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);
             Trade<Bond> obj1 = Trade<Bond>(bond2Y,tradeId,tradePrice,book,quant,pside);
          
          //  ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
            
            TradeBookingService->BookTrade(obj1);
            std::cout<<"trade booked!!!"<<std::endl;


        }
        else if(productId == "3Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2020,Nov,15);
          Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);

           Trade<Bond> obj1 = Trade<Bond>(bond3Y,tradeId,tradePrice,book,quant,pside);
          TradeBookingService->BookTrade(obj1);
          //ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
        }

        else if(productId == "5Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2022,Oct,31);
          Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

           Trade<Bond> obj1 = Trade<Bond>(bond5Y,tradeId,tradePrice,book,quant,pside);
          TradeBookingService->BookTrade(obj1);
          //ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));//myline.push_back(obj1);          
        }
        else if(productId == "7Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2024,Oct,31);
          Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);
          
           Trade<Bond> obj1 = Trade<Bond>(bond7Y,tradeId,tradePrice,book,quant,pside);
           TradeBookingService->BookTrade(obj1);
          //ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
        }
        else if(productId == "10Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2027,Nov,15);
          Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

           Trade<Bond> obj1 = Trade<Bond>(bond10Y,tradeId,tradePrice,book,quant,pside);
           TradeBookingService->BookTrade(obj1);
          //ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
        }
        else if(productId == "30Y")
        {
          BondIdType idType = CUSIP;
          date maturityDate(2047,Nov,15);
          Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);
           Trade<Bond> obj1 = Trade<Bond>(bond30Y,tradeId,tradePrice,book,quant,pside);
           TradeBookingService->BookTrade(obj1);
          //ExecutionTradeMP.insert(std::pair<string,Trade<Bond> >(tradeId, obj1));
        }

  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(ExecutionOrder<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(ExecutionOrder<Bond> &data)
  {

  }
};




template<typename T>
ExecutionOrder<T>::ExecutionOrder(const T &_product, PricingSide _side, string _orderId, OrderType _orderType, double _price, double _visibleQuantity, double _hiddenQuantity, string _parentOrderId, bool _isChildOrder) :
  product(_product)
{
  side = _side;
  orderId = _orderId;
  orderType = _orderType;
  price = _price;
  visibleQuantity = _visibleQuantity;
  hiddenQuantity = _hiddenQuantity;
  parentOrderId = _parentOrderId;
  isChildOrder = _isChildOrder;
}

template<typename T>
const T& ExecutionOrder<T>::GetProduct() const
{
  return product;
}

template<typename T>
const string& ExecutionOrder<T>::GetOrderId() const
{
  return orderId;
}

template<typename T>
OrderType ExecutionOrder<T>::GetOrderType() const
{
  return orderType;
}

template<typename T>
double ExecutionOrder<T>::GetPrice() const
{
  return price;
}

template<typename T>
long ExecutionOrder<T>::GetVisibleQuantity() const
{
  return visibleQuantity;
}

template<typename T>
long ExecutionOrder<T>::GetHiddenQuantity() const
{
  return hiddenQuantity;
}

template<typename T>
const string& ExecutionOrder<T>::GetParentOrderId() const
{
  return parentOrderId;
}

template<typename T>
bool ExecutionOrder<T>::IsChildOrder() const
{
  return isChildOrder;
}

#endif
