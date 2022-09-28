#include "movie.h"

Movie::Movie(const std::string category, const std::string name, const std::string genre, const std::string rating,  double price, int qty) : 
		Product(category, name, price, qty),
		genre_(genre),
		rating_(rating)
		{
		}
		/**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> Movie::keywords() const
		{
			std::set<std::string> keywords = parseStringToWords(getName());
			std::set<std::string> genre = parseStringToWords(genre_);
			keywords = setUnion(keywords, genre);
			keywords.insert(rating_); //should not have any gaps to parse
			
			return keywords;
		}

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool Movie::isMatch(std::vector<std::string>& searchTerms) const
		{
			return false;
		}

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string Movie::displayString() const
		{
			std::string productInfo = getName() + " " + genre_ + " " + rating_ + " " + std::to_string(getPrice()) + " " + std::to_string(getQty());
			return productInfo;
		}
		
    /**
     * Outputs the product info in the database format
     */
    void Movie::dump(std::ostream& os) const
		{
			os << category_  << "/n" << getName() << "/n" << std::to_string(getPrice()) << "/n" << std::to_string(getQty()) << "/n" << genre_ << "n/" << rating_;
		}