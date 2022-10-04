#include "datastore.h"
#include <iostream>
#include <map>
#include <list>

class MyDataStore : public DataStore{
public:

    ~MyDataStore() override;

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

		void addCart(std::string username, std::vector<Product*> hits,  int hit_result_index);
		void viewCart(std::string username);
		void buyCart(std::string username);
private:
	std::set<Product*> products;
	std::vector<User*> users_list;
	std::map<std::string, User*> users;
	std::map<std::string, std::set<Product*>> productKeys;
	std::map<std::string, std::vector<Product*>> userCarts;
};