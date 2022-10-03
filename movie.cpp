#include "movie.h"
#include "util.h"

	Movie::Movie(const std::string category, const std::string name, double price, int qty,
		const std::string genre, const std::string rating) :    
		Product(category,name,price,qty), 
		genre_(genre),
		rating_(rating)
		 {
			
		}
		Movie::~Movie(){

		}
		std::set<std::string> Movie::keywords() const{
		std::set<std::string> strings;
			std::set<std::string> rand;
			rand=parseStringToWords(name_);
			strings=setUnion(strings,rand);
			std::set<std::string> rand2;
			rand2=parseStringToWords(genre_);
			strings=setUnion(strings,rand2);
			strings.insert(rating_);
			return strings;
		}

			std::string Movie::displayString() const{
			std::string string="";
			string+=name_+"\n";
			string+="Genre: " + genre_+" Rating: "+rating_+"\n";
			string+=std::to_string(price_);
			string+=" ";
			string+=std::to_string(qty_)+" left.";
			return string;
		}

		void Movie::dump(std::ostream& os) const{
			os<<category_<<std::endl;
			os<<name_<<std::endl;
			os<<price_<<std::endl;
			os<<qty_<<std::endl;
			os<<genre_<<std::endl;
			os<<rating_<<std::endl;
		}

		