		#include "clothing.h"

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
			keywords = setUnion(keywords, brand);
			keywords.insert(size_); //should not have any gaps to parse
			
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
			std::string productInfo = getName() + " " + brand_ + " " + size_ + " " + std::to_string(getPrice()) + " " + std::to_string(getQty());
			return productInfo;
		}
		
    /**
     * Outputs the product info in the database format
     */
    void Clothing::dump(std::ostream& os) const
		{
			os << category_  << "/n" << getName() << "/n" << std::to_string(getPrice()) << "/n" << std::to_string(getQty()) << "/n" << size_ << "n/" << brand_;
		}