#include "datastore.h"
#include <map>
#include <queue>
class amazondatastore: public DataStore{
public:
amazondatastore();
bool addToCart(std::string user,Product* item);
bool viewCart(std::string user);
bool buyCart(std::string user);
void addProduct(Product* p);
void addUser(User* u);
std::vector<Product*> search(std::vector<std::string>& terms, int type);
void dump(std::ostream& ofile);
private:
std:: map<std::string,std::set<Product*>> products;
std:: map<std::string,User*> users;
std:: map<std::string,std::queue<Product*>> carts;
std:: set<Product*> inventory;
};