#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "../include/routes.hpp"
#include "../include/WebServer.hpp"
#include "../include/WebRequest.hpp"
#include "../include/WebResponse.hpp"
#include "../include/TinyParser.hpp"

using namespace std;

string default_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/default.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployment_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/deployment.html");
	
	parser.inject("id", request.getParam("id"));
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string server_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/server.html");
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string stop_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/stop.html");
	
	// Arrêt du serveur
	WebServer::getInstance()->stop();
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string restart_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/restart.html");
	
	// Restart du serveur
	WebServer::getInstance()->restart();
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string deployments_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/deployments.html");
	
	ostringstream oss;
	
	oss << "<table>";
	oss << "<tr><th>#</th><th>Lien d'accès</th><th>Etat</th></tr>";
	oss << "<tr><td>1</td><td><a href=\"deployment?id=1\">Deploiement #1</a></td><td style=\"color: green;\">Actif</td></tr>";
	oss << "</table>";
	
	parser.inject("list", oss.str());
	
	WebResponse response(200, parser.render());
	return response.getRawData();
}

string notfound_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/error404.html");
	
	WebResponse response(404, parser.render());
	return response.getRawData();
}

string internalerror_route(WebRequest& request)
{
	TinyParser parser(WEBSERVER_ROOT + "/error500.html");
	
	WebResponse response(500, parser.render());
	return response.getRawData();
}

std::string ressource_route(WebRequest& request)
{
	// Test de ressource
	// Ouverture du fichier de template
	ifstream file(string(WEBSERVER_ROOT + request.getTarget()).c_str(), ifstream::in); 

	if(file)
	{      
		// copier l'intégralité du fichier dans le buffer
		stringstream buffer;
		buffer << file.rdbuf();
		file.close();  // on ferme le fichier
		
		return buffer.str();
	}
	else  
	{
		cerr << "(server) Erreur, impossible d'ouvrir le fichier " << request.getTarget() << "... " << endl;
		cout << "(server) Le client a demandé une page qui n'existe pas. (TARGET=" << request.getTarget() << ")" << endl;
		// Redirection vers page d'erreur
		return notfound_route(request);
	}
}
