/**
 * inquiryservice.hpp
 * Defines the data types and Service for customer inquiries.
 *
 * @author Breman Thuraisingham
 */
#ifndef INQUIRY_SERVICE_HPP
#define INQUIRY_SERVICE_HPP


#include "tradebookingservice.hpp"
#include <memory>



class BondInquiryServiceConnector;

// Various inqyury states
enum InquiryState { RECEIVED, QUOTED, DONE, REJECTED, CUSTOMER_REJECTED };

/**
 * Inquiry object modeling a customer inquiry from a client.
 * Type T is the product type.
 */
template<typename T>
class Inquiry
{

public:

  // ctor for an inquiry
  Inquiry(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state);

  Inquiry(){};

  // Get the inquiry ID
  const string& GetInquiryId() const;

  // Get the product
  const T& GetProduct() const;

  // Get the side on the inquiry
  Side GetSide() const;

  // Get the quantity that the client is inquiring for
  long GetQuantity() const;

  // Get the price that we have responded back with
  double GetPrice() const;

  // Get the current state on the inquiry
  InquiryState GetState() const;

  void SetPrice(double _price)
  {
    price = _price;
  }

  void SetState( InquiryState _state)
  {
    state = _state;
  }

private:
  string inquiryId;
  T product;
  Side side;
  long quantity;
  double price;
  InquiryState state;

};

/**
 * Service for customer inquirry objects.
 * Keyed on inquiry identifier (NOTE: this is NOT a product identifier since each inquiry must be unique).
 * Type T is the product type.
 */
template<typename T>
class InquiryService : public Service<string,Inquiry <T> >
{

public:

  // Send a quote back to the client
  virtual void SendQuote(const string &inquiryId, double price) = 0;

  // Reject an inquiry from the client
  virtual void RejectInquiry(const string &inquiryId) = 0;

};


class BondInquiryService : public InquiryService<Bond>
{
private:
  std::map<string, Inquiry<Bond> > BondInquiryMP;
  std::vector<ServiceListener< Inquiry<Bond> >* >  InquiryListener;
  BondInquiryServiceConnector* publishCon;

public:

  BondInquiryService(BondInquiryServiceConnector* publishCon_):publishCon(publishCon_)
  {
    BondInquiryMP = std::map<string, Inquiry<Bond> >();
    InquiryListener = std::vector<ServiceListener< Inquiry<Bond> >* >();
    //publishCon = (BondInquiryServiceConnector*)std::malloc(sizeof(BondInquiryServiceConnector*));
  }
  /*
  void SetConnector(BondInquiryServiceConnector* Con_)
  {
    publishCon = Con_;
  }*/
  // Send a quote back to the client
  void SendQuote(const string &inquiryId, double price)
  {
    BondInquiryMP[inquiryId].SetPrice(price);
  }

  // Reject an inquiry from the client
  void RejectInquiry(const string &inquiryId)
  {
    InquiryState InqState = REJECTED;
    BondInquiryMP[inquiryId].SetState(InqState);
  }


  void UpdateState(const string &inquiryId,InquiryState state )
  {
    BondInquiryMP[inquiryId].SetState(state);
  }

  // Get data on our service given a key
  virtual Inquiry<Bond>& GetData(string key)
  {
      return BondInquiryMP[key];
  }

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(Inquiry<Bond> &data)
  {
    AddInquiry(data);
     if(InquiryListener.size()!=0)
    {
    for(int i = 0; i<InquiryListener.size();i++)
    {
      InquiryListener[i]->ProcessAdd(data);
    }
    }

    InquiryState state2 = QUOTED;
    string inquiryId = data.GetInquiryId();
    UpdateState(inquiryId, state2);
    Inquiry<Bond> query =GetData(inquiryId); 
    
    publishCon->Publish(query);
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener< Inquiry<Bond> > *listener)
  {
      InquiryListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< Inquiry<Bond> >* >& GetListeners() const
  {
    return InquiryListener;
  }

  void AddInquiry(Inquiry<Bond> inquiry)
  {
    BondInquiryMP.insert(pair< string,Inquiry<Bond> >( inquiry.GetInquiryId(), inquiry ) );
  }
};


class BondInquiryServiceConnector : Connector < Inquiry<Bond> >
{
private:
  BondInquiryService* inquiryService;
public:

  BondInquiryServiceConnector(){}
  
  void SetInquiryService(BondInquiryService* inquiryService_)
  {
    inquiryService = inquiryService_;
  }
  
  virtual void Publish(Inquiry<Bond> &data)
  {
    ofstream myfile;
    myfile.open ("inquiries_done.txt",fstream::app);
    std::string inquiryId = data.GetInquiryId();

    std::string productId = data.GetProduct().GetProductId();
    Side pside = data.GetSide();

    string PricingSide;
    
    Side side1 = BUY;
    Side side2 = SELL;
    if(pside == side1)
    {
      PricingSide = "BUY";
    }
    else
    {
      PricingSide = "SELL";
    }
    long quant = data.GetQuantity();
    std::string quantity = std::to_string(quant);
    double quote = data.GetPrice();
    
    std::ostringstream strs1;
    strs1 << quote;
    std::string price = strs1.str();

    std::string state = "DONE";

    std::string inquiry = inquiryId + ","+ productId +","+PricingSide+","+ quantity+","+price +","+state+"\n";
    myfile<<inquiry;
    myfile.close();


  }

  void Subscribe()
  {
    string line;
    std::ifstream file("inquiries.txt");

    while(getline(file,line))
  {
    
        std::stringstream linestream(line);

        std::string inquiryId;
        std::string productId;
        std::string side;
        std::string quant;
        std::string price;
        std::string state;

        std::getline(linestream,inquiryId,',');
        std::getline(linestream,productId,',');
        std::getline(linestream,side,',');
        std::getline(linestream,quant,',');
        std::getline(linestream,price,',');
        std::getline(linestream,state,',');

        Side pside;

        if(side == "BUY")
        {
          pside = BUY;
        }
        else
        {
          pside = SELL;
        }

        InquiryState pstate;

        if(state == "RECEIVED")
        {
          pstate = RECEIVED;
        }
        else if(state == "QUOTED")
        {
          pstate = QUOTED;
        }
        else if(state == "DONE")
        {
          pstate = DONE;
        }
        else if(state == "REJECTED")
        {
          pstate = REJECTED;
        }
        else if(state == "CUSTOMER_REJECTED")
        {
          pstate = CUSTOMER_REJECTED;
        }


        long quantity = atol(quant.c_str());
        double quote = stod(price);

        if(!inquiryId.empty())
        {
          if(productId == "2Y")
          {
            BondIdType idType = CUSIP;
            date maturityDate(2019,Oct,31);
            Bond bond2Y("2Y", idType,"T", 0.015, maturityDate);

            Inquiry<Bond> obj = Inquiry<Bond>(inquiryId,bond2Y,pside,quantity,quote,pstate);
            inquiryService->OnMessage(obj);
          }
          else if(productId == "3Y")
          {
            BondIdType idType = CUSIP;
            date maturityDate(2020,Nov,15);
            Bond bond3Y("3Y", idType, "T", 0.0175, maturityDate);

            Inquiry<Bond> obj = Inquiry<Bond>(inquiryId,bond3Y,pside,quantity,quote,pstate);
            inquiryService->OnMessage(obj);

          }
          else if (productId == "5Y")
          {
            BondIdType idType = CUSIP;
            date maturityDate(2022,Oct,31);
            Bond bond5Y("5Y", idType, "T", 0.02, maturityDate);

            Inquiry<Bond> obj = Inquiry<Bond>(inquiryId,bond5Y,pside,quantity,quote,pstate);
            inquiryService->OnMessage(obj);
          }
          else if(productId == "7Y")
          {
            BondIdType idType = CUSIP;
            date maturityDate(2024,Oct,31);
            Bond bond7Y("7Y", idType, "T", 0.0225, maturityDate);

            Inquiry<Bond> obj = Inquiry<Bond>(inquiryId,bond7Y,pside,quantity,quote,pstate);
            inquiryService->OnMessage(obj);

          }
          else if(productId == "10Y")
          {
            BondIdType idType = CUSIP;
            date maturityDate(2027,Nov,15);
            Bond bond10Y("10Y", idType, "T", 0.0225, maturityDate);

            Inquiry<Bond> obj = Inquiry<Bond>(inquiryId,bond10Y,pside,quantity,quote,pstate);
            inquiryService->OnMessage(obj);

          }
          else if(productId == "30Y")
          {
            BondIdType idType = CUSIP;
            date maturityDate(2047,Nov,15);
            Bond bond30Y("30Y", idType, "T", 0.0275, maturityDate);

            Inquiry<Bond> obj = Inquiry<Bond>(inquiryId,bond30Y,pside,quantity,quote,pstate);
            inquiryService->OnMessage(obj);
          }
         }
      } 
    }
};


class BondInquiryServiceListener : public ServiceListener<Inquiry<Bond> >
{

private:

  BondInquiryService* InquiryService;

public:

  BondInquiryServiceListener(BondInquiryService* InquiryService_):InquiryService(InquiryService_){};

  // Listener callback to process an add event to the Service
  virtual void ProcessAdd(Inquiry<Bond> &data)
  {
      InquiryState state1 = RECEIVED;
      double price = 100;
      string inquiryId = data.GetInquiryId();
      if(data.GetState() == state1)
      {
        InquiryService->SendQuote(inquiryId,100);  
      }
      std::cout<<"quote sent"<<std::endl;
      
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(Inquiry<Bond> &data)
  {

  }
  

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(Inquiry<Bond> &data)
  {

  }
};








template<typename T>
Inquiry<T>::Inquiry(string _inquiryId, const T &_product, Side _side, long _quantity, double _price, InquiryState _state) :
  product(_product)
{
  inquiryId = _inquiryId;
  side = _side;
  quantity = _quantity;
  price = _price;
  state = _state;
}

template<typename T>
const string& Inquiry<T>::GetInquiryId() const
{
  return inquiryId;
}

template<typename T>
const T& Inquiry<T>::GetProduct() const
{
  return product;
}

template<typename T>
Side Inquiry<T>::GetSide() const
{
  return side;
}

template<typename T>
long Inquiry<T>::GetQuantity() const
{
  return quantity;
}

template<typename T>
double Inquiry<T>::GetPrice() const
{
  return price;
}

template<typename T>
InquiryState Inquiry<T>::GetState() const
{
  return state;
}

#endif
