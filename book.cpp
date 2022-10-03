#include "book.h"
#include "util.h"

	Book::Book(const std::string category, const std::string name, double price, int qty,
		const std::string author, const std::string isbn) :   
		Product(category,name,price,qty), 
		author_(author),
		isbn_(isbn)
		 {
		}
		Book::~Book(){

		}
		std::set<std::string> Book::keywords() const{
			std::set<std::string> strings;
			std::set<std::string> rand;
			rand=parseStringToWords(name_);
			strings=setUnion(strings,rand);
			std::set<std::string> rand2;
			rand2=parseStringToWords(author_);
			strings=setUnion(strings,rand2);
			strings.insert(isbn_);
			return strings;
		}

			std::string Book::displayString() const{
			std::string string="";
			string+=name_+"\n";
			string+="Author: " + author_+" ISBN: "+isbn_ +"\n";
			string+=std::to_string(price_);
			string+=" ";
			string+=std::to_string(qty_)+" left.";
			return string;
		}

		void Book::dump(std::ostream& os) const{
			Product::dump(os);
			os<<isbn_<<std::endl;
			os<<author_<<std::endl;
		}

		