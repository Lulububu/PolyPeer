#include <string>
#ifdef WIN32 /* si vous êtes sous Windows */
	#define sleep(t) Sleep(t)
#endif


#include <ConnectionManager.hpp>

ConnectionManager::ConnectionManager(int port)
{
	bool bind = false;
	while(!bind)
	{
		try
		{
			serverSocket = new ServerSocket(port);
			bind = true;
		}catch(BindException)
		{
			cout << "impossible de lier le port d'écoute numéro :" << port << endl;
			cout << "tentative de reconnexion dans 5 secondes" << endl;
			sleep(5);
		}
	}


}

ConnectionManager::~ConnectionManager()
{
	stop();
}

void ConnectionManager::addConnection(std::string name, Socket* socket)
{

	Connection* tmp = new Connection(socket);
	tmp->throwUpdatePacket();
	listConnections[name] = tmp;
	tmp->start();
}

Connection* ConnectionManager::getConnection(std::string name)
{
	return listConnections[name];
}

void* runFct(void* connectionManager)
{
	ConnectionManager* connectionManagerTmp = (ConnectionManager*)connectionManager;
	connectionManagerTmp->run = true;
	Socket* sockTmp;
	while(connectionManagerTmp->run)
	{
		cout << "en attente "<<endl;
		sockTmp = connectionManagerTmp->serverSocket->accept();
		cout << "connexion "<<endl;
		connectionManagerTmp->addConnection(sockTmp->getIpAdress(), sockTmp);

	}
	return NULL;

}


void ConnectionManager::start()
{
	pthread_create(&thread, NULL, runFct, this);

}

void ConnectionManager::stop()
{
	run = false;

	std::map<std::string, Connection*>::const_iterator itr;
	for(itr = listConnections.begin(); itr!=listConnections.end(); ++itr)
	{
		delete itr->second;
	}

	serverSocket->close();
}

void ConnectionManager::sendTo(std::string dest, Packet packet)
{
	Connection* connection = listConnections[dest];
	if(connection != NULL)
	{
		connection->getSocket()->send(packet.serialize());
	}else
	{
		cout << "l'adresse ip est inconnu dans le ConnectionManager" << endl;
	}
}

void ConnectionManager::wait()
{
	pthread_join(thread, NULL);
}

void ConnectionManager::removeConnection(std::string ip)
{
	Connection* connec = listConnections[ip];
	if(connec != NULL)
	{
		connec->stop();
		listConnections.erase(ip);
	}
}
