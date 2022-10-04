		#include "book.h"
		#include <iomanip>

		Book::Book(const std::string category, const std::string name, const std::string author, const std::string ISBN,  double price, int qty) : 
		Product(category, name, price, qty),
		author_(author),
		ISBN_(ISBN)
		{
		}
		/**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> Book::keywords() const
		{
			std::set<std::string> keywords = parseStringToWords(getName());
			std::set<std::string> author = parseStringToWords(author_);
			for(std::set<std::string>::iterator it = author.begin(); it != author.end(); ++it)
			{
				keywords.insert(*it);
			}
			// keywords = setUnion(keywords, author);
			keywords.insert(ISBN_); //should not have any gaps to parse
			
			return keywords;
		}

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool Book::isMatch(std::vector<std::string>& searchTerms) const
		{
			return false;
		}

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string Book::displayString() const
		{
			std::string productInfo = getName() + "\n" + "Author: " + author_ + " ISBN: " + ISBN_ + "\n" + std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.";
			return productInfo;
		}
		
    /**
     * Outputs the product info in the database format
     */
    void Book::dump(std::ostream& os) const
		{
			os << "book"  << std::endl << getName() << std::endl;
			os << std::fixed << std::setprecision(2) << getPrice() << std::endl;
			os << std::to_string(getQty()) << std::endl << ISBN_ << std::endl << author_ << std::endl;
			// os << "cow" << std::endl;
			// os << "book" << std::endl << getName() << std::endl << std::to_string(getPrice()) << std::endl << std::to_string(getQty()) << std::endl;
		}

		std::string Book::getCategory() const
		{
			return "book";
		}