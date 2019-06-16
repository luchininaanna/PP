#include "Bank.h"

CBank::CBank(int variant)
{
	m_clients = std::vector<CBankClient>();
	m_totalBalance = 0;
	m_variant = SynchronousVariant(variant);
	InitializeCriticalSection(&csUpdateBalance);
}


CBankClient* CBank::CreateClient()
{
	unsigned clientId = unsigned(m_clients.size());
	CBankClient* client = new CBankClient(this, clientId);
	m_clients.push_back(*client);
	return client;
}


int CBank::GetClientBalance(int clientId)
{
	return clientBalance.at(clientId);
}


vector<CBankClient> CBank::TotalClients() {
	return m_clients;
}


void CBank::SetClientBalance(int idClient, int balance) {

	auto currBalance = clientBalance.find(idClient);

	if (currBalance == clientBalance.end()) {
		clientBalance.emplace(idClient, balance);
	}
	else {
		currBalance->second += balance;
	}
}


void CBank::UpdateClientBalance(CBankClient &client, int value)
{
	EnableSynchronous();

	int totalBalance = GetTotalBalance();
	std::cout << "Client " << client.GetId() << " initiates reading total balance. Total = " << totalBalance << "." << std::endl;
	
	SomeLongOperations();
	totalBalance += value;

	SetClientBalance(client.GetId(), value);

	std::cout
		<< "Client " << client.GetId() << " updates his balance with " << value
		<< " and initiates setting total balance to " << totalBalance
		<< ". Must be: " << GetTotalBalance() + value << "." << std::endl;

	// Check correctness of transaction through actual total balance
	if (totalBalance != GetTotalBalance() + value) {
		std::cout << "! ERROR !" << std::endl;
	}

	SetTotalBalance(totalBalance);
	DisableSynchronous();
}


int CBank::GetTotalBalance()
{
	return m_totalBalance;
}


void CBank::SetTotalBalance(int value)
{
	m_totalBalance = value;
}


void CBank::SomeLongOperations()
{
	// TODO
	Sleep(1000);
}


SynchronousVariant CBank::GetPrimitive() {
	return m_variant;
}


void CBank::EnableSynchronous() {
	if (CBank::GetPrimitive() == SynchronousVariant::CriticalSection) {
		EnterCriticalSection(&csUpdateBalance);
	}
	else if (CBank::GetPrimitive() == SynchronousVariant::Mutex) {
		mutexUpdateBalance.lock();
	}
}


void CBank::DisableSynchronous() {
	if (CBank::GetPrimitive() == SynchronousVariant::CriticalSection) {
		LeaveCriticalSection(&csUpdateBalance);
	}
	else if (CBank::GetPrimitive() == SynchronousVariant::Mutex) {
		mutexUpdateBalance.unlock();
	}
}