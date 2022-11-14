#include "mydatastore.h"
#include "util.h"

	MyDataStore::~MyDataStore()
	{
			//CLEAR MEMORY
			//products
			for(std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it)
			{
				delete *it;
			}

			//users
			for(unsigned int i=0; i < users_list.size(); i++)
			{
				User* x = users_list[i];
				delete x;
			}
	}

	/**
  * Adds a product to the data store
  */
    void MyDataStore::addProduct(Product* p) 
		{
				products.insert(p); //used for memory cleanup
				
				//get correct keywords for specific product category
				std::set<std::string> keywords = p->keywords();

				for(std::set<std::string, Product*>::iterator it = keywords.begin(); it != keywords.end(); ++it)
				{
					if(productKeys.find(*it) != productKeys.end()) //if keyword not in the map
					{
						productKeys[*it].insert(p);
					}
					else
					{
						std::set<Product*> prodsWithKey; //create set of products
						prodsWithKey.insert(p); //add product to set
						productKeys.insert({*it, prodsWithKey}); //add set to map

					}
				}
		}

    /**
     * Adds a user to the data store
     */
    void MyDataStore::addUser(User* u)
		{
			if(u == nullptr)
			{
				return;
			}

			std::string user_name = u->getName();
			//store user name into a common case in the map. Makes username input case insensitive.
			user_name = convToLower(user_name);	

			if(userCarts.find(user_name) != userCarts.end()) //user already stored
			{
				return;
			}
			else
			{
				users_list.push_back(u); //used for memory cleanup
				users.insert({user_name, u});

				std::vector<Product*> cartItems;
				userCarts.insert({user_name, cartItems});
			}
		}

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
		{
			std::set<Product*> foundProducts = productKeys[terms[0]]; //can't do intersection properly with empty set

			//check for each keyword presented in the map. If in map, perform correct set operations.
			for(unsigned int i=0; i < terms.size(); i++)
			{
				if(productKeys.find(terms[i]) != productKeys.end())
				{
					if(type == 0)
					{
						foundProducts = setIntersection(foundProducts, productKeys[terms[i]]);
					}
					else if (type == 1)
					{
						foundProducts = setUnion(foundProducts, productKeys[terms[i]]);
					}
				}
			}

			std::vector<Product*> foundProds;

			//store set of foundProducts into vector because need to return vector
			for(std::set<Product*>::iterator it = foundProducts.begin(); it != foundProducts.end(); ++it)
			{
				foundProds.push_back(*it);
			}
      return foundProds;
		}

		void MyDataStore::addCart(std::string username, std::vector<Product*> hits, int hit_result_index)
		{	
			//check if given a username and if hits given by search
			if(username.empty() || (unsigned int) hit_result_index > hits.size() || hit_result_index <= 0)
			{
				std::cout << "Invalid Request" <<std::endl;
				return;
			}

			username = convToLower(username);
			
			if(userCarts.find(username) != userCarts.end()) //user in map
			{
				userCarts.find(username)->second.push_back(hits[hit_result_index - 1]);
			}
			else
			{
				std::cout << "Invalid Request" << std::endl;
			}
		}

		void MyDataStore::viewCart(std::string username)
		{
			std::vector<Product*> user_cart;
			username = convToLower(username);  //process username to how it is stored in map
			int count = 1;

			if(userCarts.find(username) != userCarts.end()) //user in map
			{
				user_cart = userCarts.find(username)->second;
				for(std::vector<Product*>::iterator it = user_cart.begin(); it != user_cart.end(); it++)
				{
					if(*it == NULL)
					{
						std::cout << "product pointer is null" << std::endl;
						continue;
					}
					//list eech item in cart
					//std::cout << count << ".) " << (*it)->getName() << std::endl;
					std::cout << "Item " << count << std::endl;
					std::cout << (*it)->displayString() << std::endl << std::endl;
					count += 1;
				}
			}
			else
			{
				std::cout << "Invalid Username" << std::endl;
			}
		}


		void MyDataStore::buyCart(std::string username)
		{
			//process username to how it is stored in map
			username = convToLower(username);
			User* user;
			std::vector<Product*> user_cart;

			if(userCarts.find(username) != userCarts.end()) //user in map
			{
				user = users.find(username)->second;

				std::vector<Product*>::iterator it = userCarts.find(username)->second.begin();
				while(it != userCarts.find(username)->second.end())
				{
					if(*it == NULL)
					{
						std::cout << "product pointer is null" << std::endl;
						++it;
						continue;
					}

					if(user->getBalance() >= (*it)->getPrice() && (*it)->getQty() > 0) // can afford product and item in stock
					{
							user->deductAmount((*it)->getPrice());
							(*it)->subtractQty(1);
							//delete element in vector and update the iterator to next item, vector changes so need to act accordingly
							it = userCarts.find(username)->second.erase(it);
					}
					else
					{
						++it;
					}
				}
			}
			else
			{
				std::cout << "Invalid Username" << std::endl;
			}
		}
		
    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(std::ostream& ofile)
		{
			//PRINT TO FILE
			ofile << "<products>" << std::endl;
			for(std::set<Product*>::iterator it = products.begin(); it != products.end(); ++it)
			{
				//call dump of each product to print all category specific members
				(*it)->dump(ofile);
			}
			ofile << "</products>\n";

			ofile << "<users>\n";
			for(std::vector<User*>::iterator it = users_list.begin(); it != users_list.end(); ++it)
			{
				//call dump of each user to print all user members
				(*it)->dump(ofile);
			}
			ofile << "</users>\n";
		}