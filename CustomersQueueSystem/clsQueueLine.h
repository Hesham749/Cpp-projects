#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <ctime>
#include <string>
#include"clsDate.h"
using namespace std;

class clsQueueLine
{

	string _Prefix = "";
	int _TotalTickets = 0;
	short _AverageServeTime = 0;

	struct strTicket
	{
		string Number;
		string DateTime;
		int WaitingClients = 0;
		int TimeToWait = 0;
	};

	queue <strTicket> _OriginalQueue;

	strTicket _GetTicket()
	{
		strTicket Ticket;
		Ticket.Number = _Prefix + to_string(_TotalTickets);
		Ticket.DateTime = clsDate::GetSystemDateTimeString();
		Ticket.WaitingClients = WaitingClients();
		Ticket.TimeToWait = _AverageServeTime * WaitingClients();
		return Ticket;
	}

	void _PrintTicketInfo(strTicket& Ticket)
	{
		cout << "\n___________________________________";
		cout << "\n\n\t\t" << Ticket.Number << "\n";
		cout << "\n\t" << Ticket.DateTime;
		cout << "\n\tWaiting Clients = " << Ticket.WaitingClients;
		cout << "\n\t   Serve Time In\n\t    " << Ticket.TimeToWait << " Minutes.\n";
		cout << "\n___________________________________\n";
	}

public:
	clsQueueLine(string Prefix, short AverageServeTime)
		:_Prefix(Prefix), _AverageServeTime(AverageServeTime)
	{}

	void IssueTicket()
	{
		_TotalTickets++;
		strTicket Ticket = _GetTicket();
		_OriginalQueue.push(Ticket);
	}

	int ServedClients()
	{
		return _TotalTickets - _OriginalQueue.size();
	}

	int WaitingClients()
	{
		return _OriginalQueue.size();
	}

	void PrintInfo()
	{
		cout << "\n\n------------------------------------------";
		cout << "\n\t\tQueue Info";
		cout << "\n__________________________________________\n";
		cout << "\nPrefix         = " << _Prefix;
		cout << "\nTotalTickets   = " << _TotalTickets;
		cout << "\nServedClients  = " << ServedClients();
		cout << "\nWaitingClients = " << WaitingClients();
		cout << "\n__________________________________________\n";
	}

	void PrintTicketsLineRTL()
	{
		cout << "\nTickets : ";
		if (_OriginalQueue.empty())
		{
			cout << "\n\n\n\t   ---No Tickets---\n";
			return;
		}
		queue <strTicket> _TempQueue = _OriginalQueue;
		while (!_OriginalQueue.empty())
		{
			cout << _OriginalQueue.front().Number << " <-- ";
			_OriginalQueue.pop();
		}
		_OriginalQueue = _TempQueue;
	}

	void PrintTicketsLineLTR()
	{
		cout << "\nTickets : ";
		if (_OriginalQueue.empty())
		{
			cout << "\n\n\n\t   ---No Tickets---\n";
			return;
		}
		stack <strTicket> _MyStack;
		queue <strTicket> _TempQueue = _OriginalQueue;
		while (!_OriginalQueue.empty())
		{
			_MyStack.push(_OriginalQueue.front());
			_OriginalQueue.pop();
		}
		_OriginalQueue = _TempQueue;
		while (!_MyStack.empty())
		{
			cout << _MyStack.top().Number << " --> ";
			_MyStack.pop();
		}
	}

	void PrintAllTickets()
	{
		cout << "\n\n\n\t   ---Tickets---\n";
		if (_OriginalQueue.empty())
		{
			cout << "\n\n\n\t   ---No Tickets---\n";
			return;
		}
		queue <strTicket> _TempQueue = _OriginalQueue;
		while (!_OriginalQueue.empty())
		{
			_PrintTicketInfo(_OriginalQueue.front());
			_OriginalQueue.pop();
		}
		_OriginalQueue = _TempQueue;
	}

	bool ServeNextClient()
	{
		if (_OriginalQueue.empty())
			return false;
		queue <strTicket> _TempQueue = _OriginalQueue;
		_TempQueue.pop();
		while (!_OriginalQueue.empty())
		{
			_OriginalQueue.pop();
		}
		while (!_TempQueue.empty())
		{
			_TempQueue.front().WaitingClients--;
			_TempQueue.front().TimeToWait -= _AverageServeTime;
			_OriginalQueue.push(_TempQueue.front());
			_TempQueue.pop();
		}
		return true;
	}
};

