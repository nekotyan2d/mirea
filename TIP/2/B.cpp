#include <iostream>

using namespace std;

void SendBK(const string& id, const string& message) {
    cout << "Send '" << message << "' to BK user " << id << endl;
}

void SendTelegraph(const string& login, const string& message) {
    cout << "Send '" << message << "' to Telegraph user " << login << endl;
}

class NotifierBase {
    public:
        virtual void notify(const string& message) {
            cout << message << endl;
        }; 
};

class BKNotifier : public NotifierBase {
    string id;

    public:
        BKNotifier(string id) : id(id) {};
        void notify(const string& message) {
            SendBK(id, message);
        }
};

class TelegraphNotifier : public NotifierBase {
    string login;

    public:
        TelegraphNotifier(string login) : login(login) {}
        void notify(const string& message) {
            SendTelegraph(login, message);
        }
};