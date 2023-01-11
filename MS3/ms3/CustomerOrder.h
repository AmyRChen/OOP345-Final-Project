// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include "Utilities.h"
#include "Station.h"

namespace sdds {
	struct Item 
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		
		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder {
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};	//Array of pointers -> Double Layer!!! Dynamic!!
		//Class variable
		static size_t m_widthField;

	public:
		CustomerOrder() {};
		CustomerOrder(const std::string& src);
		//Rule of five
		CustomerOrder(const CustomerOrder& src);
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src) noexcept;
		CustomerOrder& operator=(CustomerOrder&& src) noexcept;
		~CustomerOrder();
		//
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}

#endif // !SDDS_CUSTOMERORDER_H

