// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Workstation.h"

using namespace std;

std::deque<sdds::CustomerOrder> g_pending;
std::deque<sdds::CustomerOrder> g_completed;
std::deque<sdds::CustomerOrder> g_incomplete;

namespace sdds {
   void Workstation::fill(std::ostream& os){
      if (!m_orders.empty()) {
         m_orders.front().fillItem(*this, os);
      }
   }

   bool Workstation::attemptToMoveOrder(){
      bool movedCheck{ false };
      if (!m_orders.empty()) {
         if (m_orders.front().isItemFilled(getItemName()) || !getQuantity()) {
            if (m_pNextStation) {
               m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
            }
            else {
               m_orders.front().isOrderFilled() ?
                  g_completed.push_back(std::move(m_orders.front())) : g_incomplete.push_back(std::move(m_orders.front()));
            }

            m_orders.pop_front();
            movedCheck = true;
         }
      }
      
      return movedCheck;
   }

   void Workstation::setNextStation(Workstation* station){
      m_pNextStation = station;
   }

   Workstation* Workstation::getNextStation() const{
      return m_pNextStation;
   }

   void Workstation::display(std::ostream& os) const{
      if (m_pNextStation) {
         os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
      }
      else {
         os << getItemName() << " --> End of Line" << endl;
      }
   }

   Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
      m_orders.push_back(std::move(newOrder));
      return *this;
   }
}