// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: 2022/11/05
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Station.h"

using namespace std;
namespace sdds {
   //Class variable initialize
   unsigned Station::m_widthField{};
   unsigned Station::id_generator{};

   Station::Station(const std::string& rec){
      Utilities temp{};
      size_t pos{};  //Pass in and change corresponding
      bool more{true};  //Pass in and change corresponding
      m_itemName = temp.extractToken(rec, pos, more);
      m_serialNum = stoi(temp.extractToken(rec, pos, more));
      m_inStockNum = stoi(temp.extractToken(rec, pos, more));

      m_widthField = max((int)m_widthField, (int)temp.getFieldWidth());
      m_desc = temp.extractToken(rec, pos, more);

      m_id = id_generator += 1;
   }

   const std::string& Station::getItemName() const{
      return m_itemName;
   }

   size_t Station::getNextSerialNumber(){
      return m_serialNum++;
   }

   size_t Station::getQuantity() const{
      return m_inStockNum;
   }

   void Station::updateQuantity(){
      if (m_inStockNum) { m_inStockNum--; }
   }

   void Station::display(std::ostream& os, bool full) const{
      os.width(3);
      os.fill('0');
      os << m_id << " | ";
      os.fill(' ');

      os.setf(ios::left);
      os.width(m_widthField);
      os << m_itemName << "  | ";
      os.unsetf(ios::left);

      os.fill('0');
      os.width(6);
      os << m_serialNum << " | ";
      os.fill(' ');

      if (full) {
         os.width(4);
         os << m_inStockNum << " | ";
         os << m_desc;
      }
      os << endl;
   }



}