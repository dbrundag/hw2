#include "datastore.h"
#include <iostream>
class AmazonStore : public DataStore{
public:
    // virtual ~DataStore() { }

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override 
		{
				std::cout << "override addProduct" << std::endl;
		}

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override
		{
			std::cout << "override addUser" << std::endl;
		}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type)
		{
			std::cout << "override search" << std::endl;
			return NULL;
		}

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile)
		{
			std::cout << "override dump" << std::endl;
		}


};