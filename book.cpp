		#include "book.h"
		#include "util.h"

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
			keywords = setUnion(keywords, author);
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
			std::string productInfo = getName() + " " + author_ + " " + ISBN_ + " " + std::to_string(getPrice()) + " " + std::to_string(getQty());
			return productInfo;
		}
		
    /**
     * Outputs the product info in the database format
     */
    void Book::dump(std::ostream& os) const
		{
			os << category_  << "/n" << getName() << "/n" << std::to_string(getPrice()) << "/n" << std::to_string(getQty()) << "/n" << ISBN_ << "n/" << author_;
		}