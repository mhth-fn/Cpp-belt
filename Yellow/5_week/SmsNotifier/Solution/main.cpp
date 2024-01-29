#include <iostream>
#include <string>

using namespace std;


void SendSms(const string& number, const string& message) {
  cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
  cout << "Send '" << message << "' to e-mail "  << email << endl;
}

class INotifier{
public:
	virtual void Notify(const string& message) const = 0;
};

class SmsNotifier : public INotifier{
public:
	 SmsNotifier(const string& number)
		 : number_(number){}

	 void Notify(const string& message) const override{
		 SendSms(number_, message);
	 }
private:
	 const string number_;
};

class EmailNotifier : public INotifier{
public:
	EmailNotifier(const string& email)
		: email_(email){}

	void Notify(const string& message) const override{
		SendEmail(email_, message);
	}

private:
	const string email_;
};

void Notify(INotifier& notifier, const string& message) {
  notifier.Notify(message);
}

