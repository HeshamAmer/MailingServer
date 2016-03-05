#include <cpprest/http_listener.h>
#include <cpprest/json.h>
//#pragma comment(lib, "cpprest110_1_1")
#include "CSmtp.h"
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
#include "retrieveAlert.h"

#define TRACE(msg)            wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"



void send_mail(string Receipent, string text){

	bool bError = false;

	try
	{
		CSmtp mail;

#define test_gmail_tls

#if defined(test_gmail_tls)
		mail.SetSMTPServer("smtp.gmail.com", 587);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_gmail_ssl)
		mail.SetSMTPServer("smtp.gmail.com", 465);
		mail.SetSecurityType(USE_SSL);
#elif defined(test_hotmail_TLS)
		mail.SetSMTPServer("smtp.live.com", 25);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_aol_tls)
		mail.SetSMTPServer("smtp.aol.com", 587);
		mail.SetSecurityType(USE_TLS);
#elif defined(test_yahoo_ssl)
		mail.SetSMTPServer("plus.smtp.mail.yahoo.com", 465);
		mail.SetSecurityType(USE_SSL);
#endif

		mail.SetLogin("YOUR_LOGIN");
		mail.SetPassword("YOUR_PASSWORD");
		mail.SetSenderName("Gedy");
		mail.SetSenderMail("user@domain.com");
		mail.SetReplyTo("user@domain.com");
		mail.SetSubject("Alarm notification from client");
		mail.AddRecipient(Receipent.c_str());

		mail.SetXPriority(XPRIORITY_HIGH);
		mail.SetXMailer("The Bat! (v3.02) Professional");
		mail.AddMsgLine("Hello,");
		mail.AddMsgLine("");

		mail.AddMsgLine(text.c_str());

		mail.AddMsgLine("");
		mail.AddMsgLine("");
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		mail.AddMsgLine("Custom WMI");

		mail.Send();
	}
	catch (ECSmtp e)
	{
		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		bError = true;
	}
	if (!bError)
		std::cout << "Mail was send successfully.\n";
	return;
}


map<utility::string_t, utility::string_t> dictionary;

/* handlers implementation */


void handle_get(http_request request)
{
   TRACE(L"\nhandle GET\n");
   
   cout << "Recieved request\n" << request.body() <<endl;
   //Insert values from the request body into the below function
   string res=getAlertType("user", "password", 20, 20, 200);
   
	send_mail("GedyHD@gmail.com", "Hello you "+res);
   
   
   http_response response;
   request.reply(response);
}
int main()
{
   http_listener listener(L"http://localhost:8080");

   listener.support(methods::GET, handle_get);
   //getAlertType();
   try
   {
      listener.open()
         .then([&listener](){
		  
		  TRACE(L"\nstarting to listen\n");
		  
		  //printf("%s\n",listener.uri());
	  }
		  )
         .wait();

      while (true);
   }
   catch (exception const & e)
   {
      wcout << e.what() << endl;
   }

  
   return 0;
}