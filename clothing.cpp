		#include "clothing.h"
		#include <iomanip>

		Clothing::Clothing(const std::string category, const std::string name, const std::string size, const std::string brand,  double price, int qty) : 
		Product(category, name, price, qty),
		size_(size),
		brand_(brand)
		{
		}
		/**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> Clothing::keywords() const
		{
			std::set<std::string> keywords = parseStringToWords(getName());
			std::set<std::string> brand = parseStringToWords(brand_);
			for(std::set<std::string>::iterator it = brand.begin(); it != brand.end(); ++it)
			{
				keywords.insert(*it);
			}
			// keywords = setUnion(keywords, brand);			
			return keywords;
		}

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
		{
			return false;
		}

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string Clothing::displayString() const
		{
			std::stringstream price_buffer;
			price_buffer << std::fixed << std::setprecision(2) << getPrice();

			std::string productInfo = getName() + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + price_buffer.str() + " " + std::to_string(getQty()) + " left.";
			return productInfo;
		}
		
    /**
     * Outputs the product info in the database format
     */
    void Clothing::dump(std::ostream& os) const
		{
			os << "clothing"  << std::endl << getName() <<std::endl;
			os <<std::fixed << std::setprecision(2) << getPrice() << std::endl;
			os << std::to_string(getQty()) << std::endl << size_ << std::endl << brand_ << std::endl;
		}

		std::string Clothing::getCategory() const
		{
			return "clothing";
		}
