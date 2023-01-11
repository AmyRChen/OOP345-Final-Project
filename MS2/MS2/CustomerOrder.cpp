// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include "CustomerOrder.h"
using namespace std;

namespace sdds {
   size_t CustomerOrder::m_widthField{};

   CustomerOrder::CustomerOrder(const std::string& src){
      Utilities temp{};
      size_t pos{};
      bool more{ true };
      vector <string> tempItem{};
      m_name = temp.extractToken(src, pos, more);
      m_product = temp.extractToken(src, pos, more);
      while (more) { 
         tempItem.push_back(temp.extractToken(src, pos, more));
      }
      m_cntItem = tempItem.size();
      m_lstItem = new Item * [m_cntItem];
      for (auto i = 0u; i < m_cntItem; i++) {
         m_lstItem[i] = new Item(tempItem[i]);
      }

      m_widthField < temp.getFieldWidth() ? m_widthField = temp.getFieldWidth() : m_widthField;
   }

   CustomerOrder::CustomerOrder(const CustomerOrder& src){
      throw string("ERROR: Cannot make copies.");
   }

   CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept{
      *this = std::move(src);
   }

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept{
      if (this != &src) {
         for (auto i = 0u; i < m_cntItem; i++) {
            delete m_lstItem[i];
         }
         delete[] m_lstItem;
         m_lstItem = src.m_lstItem;
         src.m_lstItem = nullptr;
         m_cntItem = src.m_cntItem;
         src.m_cntItem = 0;
         m_name = src.m_name;
         src.m_name = "";
         m_product = src.m_product;
         src.m_product = "";
      }
      return *this;
   }

   CustomerOrder::~CustomerOrder(){
      for (auto i = 0u; i < m_cntItem; i++) {
         delete m_lstItem[i];
      }
      delete[] m_lstItem;
   }

   bool CustomerOrder::isOrderFilled() const{
      bool check{ true };
      for (auto i = 0u; i < m_cntItem; i++) {
         m_lstItem[i]->m_isFilled == true ? check : check = false;
      }
      return check; 
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const{
      bool check{ true };

      for (auto i = 0u; i < m_cntItem; i++) {
         if (m_lstItem[i]->m_itemName == itemName) {
            m_lstItem[i]->m_isFilled == true ? check : check = false;
         }
      }
      return check;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os){
      bool found{ false }; 
      for (auto i = 0u; i < m_cntItem && !found; i++) {
         if (m_lstItem[i]->m_itemName == station.getItemName() && station.getQuantity() >= 1) {
            found = true;
            station.updateQuantity();
            m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
            m_lstItem[i]->m_isFilled = true;
            os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
         }
         else if (m_lstItem[i]->m_itemName == station.getItemName() && station.getQuantity() == 0) {
            found = true;
            os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
         }
      } 
   }

   void CustomerOrder::display(std::ostream& os) const{
      os << m_name << " - " << m_product << endl;
      for (auto i = 0u; i < m_cntItem; i++) {
         os << "[";
         os.fill('0');
         os.width(6);
         os << m_lstItem[i]->m_serialNumber << "] ";
         os.fill(' ');
         os.width(m_widthField);
         os.setf(ios::left);
         os << m_lstItem[i]->m_itemName << "   - ";
         os.unsetf(ios::left);
         if (m_lstItem[i]->m_isFilled) {
            os << "FILLED";
         }
         else {
            os << "TO BE FILLED";
         }
         os << endl;
      }
   }
}