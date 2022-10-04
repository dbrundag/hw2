#include "product.h"
#include "util.h"

class Movie : public Product {
public:
		Movie(const std::string category, const std::string name, const std::string genre, const std::string rating,  double price, int qty);
    /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const override;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    bool isMatch(std::vector<std::string>& searchTerms) const override;

    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const override;
		
    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const override;

    std::string getCategory() const;
    
protected:
	const std::string genre_;
	const std::string rating_;
};