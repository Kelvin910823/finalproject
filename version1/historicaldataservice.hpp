/**
 * historicaldataservice.hpp
 * historicaldataservice.hpp
 *
 * @author Breman Thuraisingham
 * Defines the data types and Service for historical data.
 *
 * @author Breman Thuraisingham
 */
#ifndef HISTORICAL_DATA_SERVICE_HPP
#define HISTORICAL_DATA_SERVICE_HPP

#include <string>
#include <iostream>
#include <ofstream>

/**
 * Service for processing and persisting historical data to a persistent store.
 * Keyed on some persistent key.
 * Type T is the data type to persist.
 */
template<typename T>
class HistoricalDataService : Service<string,T>
{

public:

  // Persist data to a store
  void PersistData(string persistKey, const T& data) = 0;

};




//position service
class BondHistoricalDataPositionService : public HistoricalDataService < Position<Bond> >
{
private:
	std::map<string, Position<Bond> > HistoricalPositionMP; 
	BondHistoricalDataPositionConnector* publishCon; 
	std::vector< ServiceListener< Position<Bond> >* > HistoricalPositionListener;
public:


	// Get data on our service given a key
  virtual Position<Bond>& GetData(string key)
  {
  	return HistoricalPositionMP[key];
  } 

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(Position<Bond> &data)
  {
  	publishCon->Publish(data);
  	if(HistoricalPositionListener.size()!=0)
  		{
  			for(int i = 0; i<HistoricalPositionListener.size();i++)
  			{
    			HistoricalPositionListener[i]->ProcessAdd(data);
  			}
  		}	
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener<Position<Bond>> *listener)
  {
  		HistoricalPositionListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< Position<Bond> >* >& GetListeners() const
  {
  	return HistoricalPositionListener;
  }

  void PersistData(string persistKey, const Position<Bond>& data)
  {
  	HistoricalPosition[persistKey] = data;
  }

};

class BondHistoricalDataPositionConnector : public Connector < Position<Bond> >
{
	 

public:

	 virtual void Publish(Position<Bond> &data)
	 {
	 		ofstream myfile;
    		myfile.open ("positions.txt",fstream::app);

    		std::string product = data.GetProduct().GetProductId();

    		std::string book1 = "TRSY1";
    		std::string book2 = "TRSY2";
    		std::string book3 = "TRSY3";

    		long pos1 = data.GetPosition(book1);
    		long pos2 = data.GetPosition(book2);
    		long pos3 = data.GetPosition(book3);
    		long aggPos = data.GetAggregatePosition();

    		std::string quant1 = std::to_string(pos1);
    		std::string quant2 = std::to_string(pos2);
			std::string quant3 = std::to_string(pos3);
			std::string total = std::to_string(aggPos);
			std::string output = product + "," + book1 +","+quant1 +book2 +","+quant2 +book3 +","+quant3 +","+"Aggregate"+","+ total+"\n";
			myfile<< output;
			myfile.close();

 	 }
};

class BondPositionHistoricalDataServiceListener : public ServiceListener< Position<Bond> >
{
	 BondPositionHistoricalDataServiceListener(BondHistoricalDataPositionService* bondHistoricalPositionService_):HistoricalpositionService(bondHistoricalPositionService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(Position<Bond> &data)
  {
    //std::cout<<"Listern 1"<<std::endl;
    HistoricalpositionService->OnMessage(data);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(Position<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(Position<Bond> &data)
  {

  }

  private:

  BondHistoricalDataPositionService* HistoricalpositionService;
};







//risk service historical


class BondHistoricalDataRiskService : public HistoricalDataService < PV01<Bond> >
{
private:
	std::map<string, PV01<Bond> > HistoricalRiskMP; 
	BondHistoricalDataRiskConnector* publishCon; 
	std::vector< ServiceListener< PV01<Bond> >* > HistoricalRiskListener;
public:

	// Get data on our service given a key
  virtual PV01<Bond>& GetData(string key)
  {
  	return HistoricalRiskMP[key];
  } 

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(PV01<Bond> &data)
  {
  	publishCon->Publish(data);
  	if(HistoricalRiskListener.size()!=0)
  		{
  			for(int i = 0; i<HistoricalRiskListener.size();i++)
  			{
    			HistoricalRiskListener[i]->ProcessAdd(data);
  			}
  		}	
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener<PV01<Bond> > *listener)
  {
  		HistoricalRiskListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< PV01<Bond> >* >& GetListeners() const
  {
  	return HistoricalRiskListener;
  }

  void PersistData(string persistKey, const PV01<Bond>& data)
  {
  	HistoricalRiskMP[persistKey] = data;
  }

};

class BondHistoricalDataRiskConnector : public Connector < PV01<Bond> >
{
	 

public:

	 virtual void Publish(PV01<Bond> &data)
	 {
	 		ofstream myfile;
    		myfile.open ("risk.txt",fstream::app);

    		std::string product = data.GetProduct().GetProductId();

    		double risk = data.GetPV01();
    		long quant = data.GetQuantity();
    		
    		std::ostringstream strs;
			strs << risk;
			std::string riskquant = strs.str();
			std::string quantity = std::to_string(quant);

			std::string output = product + "," + riskquant + ","+quantity+"\n";
			myfile<< output;
			myfile.close();

 	 }
};

class BondRiskHistoricalDataServiceListener : public ServiceListener< PV01<Bond> >
{
	 BondRiskHistoricalDataServiceListener(BondHistoricalDataRiskService* bondHistoricalRiskService_):HistoricalriskService(bondHistoricalRiskService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(PV01<Bond> &data)
  {
    //std::cout<<"Listern 1"<<std::endl;
    HistoricalriskService->OnMessage(data);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(PV01<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(PV01<Bond> &data)
  {

  }

  private:

  BondHistoricalDataRiskService* HistoricalriskService;
};


//bond execution service historical data

class BondHistoricalDataExecutionService : public HistoricalDataService < ExecutionOrder<Bond> >
{
private:
	std::map<string, ExecutionOrder<Bond> > HistoricalExecutionMP; 
	BondHistoricalDataExecutionConnector* publishCon; 
	std::vector< ServiceListener< ExecutionOrder<Bond> >* > HistoricalExecutionListener;
public:

	// Get data on our service given a key
  virtual ExecutionOrder<Bond>& GetData(string key)
  {
  	return HistoricalExecutionMP[key];
  } 

  // The callback that a Connector should invoke for any new or updated data
  virtual void OnMessage(ExecutionOrder<Bond> &data)
  {
  	publishCon->Publish(data);
  	if(HistoricalExecutionListener.size()!=0)
  		{
  			for(int i = 0; i<HistoricalExecutionListener.size();i++)
  			{
    			HistoricalExecutionListener[i]->ProcessAdd(data);
  			}
  		}	
  }

  // Add a listener to the Service for callbacks on add, remove, and update events
  // for data to the Service.
  virtual void AddListener(ServiceListener<ExecutionOrder<Bond> > *listener)
  {
  		HistoricalExecutionListener.push_back(listener);
  }

  // Get all listeners on the Service.
  virtual const vector< ServiceListener< ExecutionOrder<Bond> >* >& GetListeners() const
  {
  	return HistoricalExecutionListener;
  }

  void PersistData(string persistKey, const ExecutionOrder<Bond>& data)
  {
  	HistoricalRiskMP[persistKey] = data;
  }

};

class BondHistoricalDataExecutionConnector : public Connector < ExecutionOrder<Bond> >
{
	 

public:

	 virtual void Publish(ExecutionOrder<Bond> &data)
	 {
	 		ofstream myfile;
    		myfile.open ("execution.txt",fstream::app);


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

    		std::string product = data.GetProduct().GetProductId();

    		double risk = data.GetPV01();
    		long quant = data.GetQuantity();
    		
    		std::ostringstream strs;
			strs << risk;
			std::string riskquant = strs.str();
			std::string quantity = std::to_string(quant);

			std::string output = product + "," + riskquant + ","+quantity+"\n";
			myfile<< output;
			myfile.close();

 	 }
};

class BondRiskHistoricalDataServiceListener : public ServiceListener< ExecutionOrder<Bond> >
{
	 BondRiskHistoricalDataServiceListener(BondHistoricalDataRiskService* bondHistoricalRiskService_):HistoricalriskService(bondHistoricalRiskService_){};
    
    // Listener callback to process an add event to the Service
  virtual void ProcessAdd(ExecutionOrder<Bond> &data)
  {
    //std::cout<<"Listern 1"<<std::endl;
    HistoricalriskService->OnMessage(data);
    //std::cout<<"Listern 2"<<std::endl;
  }

  // Listener callback to process a remove event to the Service
  virtual void ProcessRemove(ExecutionOrder<Bond> &data)
  {

  }

  // Listener callback to process an update event to the Service
  virtual void ProcessUpdate(ExecutionOrder<Bond> &data)
  {

  }

  private:

  BondHistoricalDataRiskService* HistoricalriskService;
};






#endif
