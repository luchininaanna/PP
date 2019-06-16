#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include "BankClient.h"

using namespace std;

enum SynchronousVariant {
	CriticalSection,
	Mutex
};

class CBank
{
public:
	CBank(int variant);

	CBankClient* CreateClient();

	map <int, int> clientBalance;

	void SetClientBalance(int idClient, int balance);
	void UpdateClientBalance(CBankClient& client, int value);

	int GetTotalBalance();
	int GetClientBalance(int idClient);

	vector<CBankClient>TotalClients();
	SynchronousVariant GetPrimitive();

private:
	std::vector<CBankClient> m_clients;
	int m_totalBalance;

	void SetTotalBalance(int value);
	void SomeLongOperations();

	void EnableSynchronous();
	void DisableSynchronous();

	mutex mutexUpdateBalance;
	CRITICAL_SECTION csUpdateBalance;

	SynchronousVariant m_variant;
};