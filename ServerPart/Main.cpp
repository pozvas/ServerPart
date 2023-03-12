#include "ConnectionListener.h"

PatientRepository ConnectionListener::_repository;
ConnectionListener* ConnectionListener::_server = nullptr;
std::vector<std::pair<std::pair<std::string, std::string>, SOCKET>> ConnectionListener::_accountsBase;
int ConnectionListener::_connectionsCounter = 0;
SOCKET ConnectionListener::_connections[100];


int main() {
	ConnectionListener* server = ConnectionListener::GetServer(); 
}


