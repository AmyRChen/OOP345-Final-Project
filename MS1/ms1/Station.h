// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>
#include "Utilities.h"

namespace sdds {
   class Station {
      int m_id{};
      std::string m_itemName{};
      std::string m_desc{};
      size_t m_serialNum{};
      size_t m_inStockNum{};
      //Class variables
      static unsigned m_widthField;
      static unsigned id_generator;
   public:
      //one-arrgument constructor
      Station(const std::string& rec);
      const std::string& getItemName() const;
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };
}
#endif // !SDDS_STATION_H

