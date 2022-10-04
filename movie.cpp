#include "movie.h"
#include <iomanip>

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
			for(std::set<std::string>::iterator it = genre.begin(); it != genre.end(); ++it)
			{
				keywords.insert(*it);
			}
			// keywords = setUnion(keywords, genre);			
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
			std::string productInfo = getName() + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(getPrice()) + " " + std::to_string(getQty()) + " left.";
			return productInfo;
		}
		
    /**
     * Outputs the product info in the database format
     */
    void Movie::dump(std::ostream& os) const
		{
			os << "movie"  << std::endl << getName() << std::endl;
			os << std::fixed << std::setprecision(2) << getPrice() << std::endl;
			os << std::to_string(getQty()) << std::endl << genre_ << std::endl << rating_ << std::endl;
		}

		std::string Movie::getCategory() const
		{
			return "movie";
		}