#include "stdafx.h"
#include <string> 

#include "Bank.h"
#include "BankClient.h"

using namespace std;


int clientsAmount = 2;
int variant = 0;
int currClientsBalance = 0;

void GetErrorInfo() {
	cout << "This is not right form of command." << endl;
	cout << "Use this pattern: <pp2.exe 3> <clients number> then (0 or 1)" << endl;
	cout << "SynchronousPrimitiveOption: CriticalSection = 0, Mutex = 1" << endl;
}

int main(int argc, char *argv[])
{

	if (argc == 3) {
		clientsAmount = atoi(argv[1]);
		variant = atoi(argv[2]);

		bool errorVariant = (variant != 0) || (variant != 1);

		if ((clientsAmount <= 0) || errorVariant) {
			GetErrorInfo();
		}
	}
	else {
		GetErrorInfo();
	}

	CBank* bank = new CBank(variant);

	for (size_t i = 0; i < clientsAmount; i++) {
		CBankClient* client1 = bank->CreateClient();
	}

	// TODO: WaitForMultipleObjects
	string operand;
	while (cin >> operand)
	{
		if ((operand == "exit") || (operand == "quit")) {
			break;
		}
	}

	for (CBankClient client : bank->TotalClients()) {
		auto clientBalance = bank->GetClientBalance(client.GetId());

		currClientsBalance += clientBalance;
	}

	cout << "Clients balance: " << currClientsBalance << endl;
	cout << "Bank balance: " << bank->GetTotalBalance() << endl;

    return 0;
}