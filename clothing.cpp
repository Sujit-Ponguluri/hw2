#include "clothing.h"
#include "util.h"

	Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
		const std::string size, const std::string brand) : 
    Product(category,name,price,qty), 
		size_(size),
		brand_(brand)
		 {
			
		}
		Clothing::~Clothing(){

		}
		std::set<std::string>Clothing::keywords() const{
			std::set<std::string> strings;
			std::set<std::string> rand;
			rand=parseStringToWords(name_);
			strings=setUnion(strings,rand);
			std::set<std::string> rand2;
			rand2=parseStringToWords(size_);
			strings=setUnion(strings,rand2);
			std::set<std::string> rand3;
			rand3=parseStringToWords(brand_);
			strings= setUnion(strings,rand3);
			std::set<std::string>::iterator it;
			for (it=strings.begin();it!=strings.end();it++){
				std::cout<<*it<<std::endl;
			}
			return strings;
		}

			std::string Clothing::displayString() const{
			std::string string="";
			string+=name_+"\n";
			string+="Size: " + size_+" Brand: "+brand_+"\n";
			string+=std::to_string(price_);
			string+=" ";
			string+=std::to_string(qty_)+" left.";
			return string;
		}

		void Clothing::dump(std::ostream& os) const{
			os<<category_<<std::endl;
			os<<name_<<std::endl;
			os<<price_<<std::endl;
			os<<qty_<<std::endl;
			os<<size_<<std::endl;
			os<<brand_<<std::endl;
		}

		