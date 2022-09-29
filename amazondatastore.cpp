#include "amazondatastore.h"
#include "util.h"

amazondatastore::amazondatastore(){
	products = std:: map<std::string,std::set<Product*>>();
	users = std:: map<std::string,User*>();
	carts = std:: map<std::string,std::queue<Product*>>();
	inventory = std:: set<Product*>();
}

void amazondatastore::addProduct(Product* p){
	std::set<std::string> words=p->keywords();
	std::set<std::string>::iterator it;
	for(it=words.begin();it!=words.end();it++){
		if(products.find(*it)==products.end()){
			products[*it]=std::set<Product*>();
		}
		products[*it].insert(p);
	}
	inventory.insert(p);
}

void amazondatastore::addUser(User* u){
users[u->getName()]=u;
carts[u->getName()]=std::queue <Product*>();
}

std::vector<Product*> amazondatastore::search(std::vector<std::string>& terms, int type){
	std::set<Product*> result;
if(type==0){
	if(products.find(terms[0])==products.end()){
		return std::vector<Product*>();
	}
result=products[terms[0]];
for(int i=1;i<(int)terms.size();i++){
		if(products.find(terms[i])==products.end()){
		return std::vector<Product*>();
		}
	result=setIntersection(result,products[terms[i]]);
	}
}
else{
	for(int i=0;i<(int)terms.size();i++){
		if(products.find(terms[i])==products.end()){
		continue;
		}
	result=setUnion(result,products[terms[i]]);
	}
}
return std::vector<Product*>(result.begin(),result.end());
}


void amazondatastore::dump(std::ostream& ofile){
ofile<<"<products>"<<std::endl;
std::set<Product*>::iterator it1;
std:: map<std::string,User*>::iterator it2;
for(it1=inventory.begin();it1!=inventory.end();it1++){
	(*it1)->dump(ofile);
}
ofile<<"</products>"<<std::endl;
ofile<<"<users>"<<std::endl;
for(it2=users.begin();it2!=users.end();it2++){
	it2->second->dump(ofile);
}
ofile<<"</users>"<<std::endl;
}

bool amazondatastore::addToCart(std::string user,Product* item){
if(users.find(user)!=users.end()){
	if(carts.find(user)==carts.end()){
		carts[user]=std::queue<Product*>();
	}
	carts[user].push(item);
} 
else{
return false;
}
return true;
}

bool amazondatastore::viewCart(std::string user){
	if(users.find(user)!=users.end()){
		if(carts.find(user)!=carts.end()){
			std::queue<Product*> views=carts.at(user);
			for(int i=0;i<(int)carts.at(user).size();i++){
				std::cout<<i+1<<": "<< views.front()->displayString()<<std::endl;
				views.pop();
			}
		}
	return true;
	}
	return false;
}

bool amazondatastore::buyCart(std::string user){

if(users.find(user)!=users.end()){
		User* u = users.at(user);
		if(carts.find(user)!=carts.end()){
			std::queue<Product*> cart=carts.at(user);
			std::queue<Product*> remaining=std::queue<Product*>();
			for(int i=0;i<(int)cart.size();i++){
				if(cart.front()->getQty()>0 && cart.front()->getPrice()< u->getBalance()){
					cart.front()->subtractQty(1);
					u->deductAmount(cart.front()->getPrice());
				}
				else{
					remaining.push(cart.front());
				}
				cart.pop();
			}
			carts[user]=remaining;
		}
	return true;
	}
	return false;
}