// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H
#include <string>
#include <deque>
#include "CustomerOrder.h"

extern std::deque<sdds::CustomerOrder> g_pending;
extern std::deque<sdds::CustomerOrder> g_completed;
extern std::deque<sdds::CustomerOrder> g_incomplete;

namespace sdds {

   class Workstation : public Station {
      std::deque<CustomerOrder> m_orders{};
      Workstation* m_pNextStation{};

   public:
      //Rule of six
      Workstation(const Workstation& src) = delete;
      Workstation& operator=(const Workstation& src) = delete;
      Workstation(const Workstation&& src) = delete;
      Workstation& operator=(Workstation&& src) = delete;
      ~Workstation(){};

      //Member Functions
      Workstation(const std::string& rec) : Station(rec){};
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station = nullptr);
      Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder&& newOrder);
   };
}
#endif // !SDDS_WORKSTATION_H

