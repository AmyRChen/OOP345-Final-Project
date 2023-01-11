// Name: PingJu, Chen
// Seneca Student ID: 151043205
// Seneca email: pchen72@myseneca.ca
// Date of completion: TBA
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "LineManager.h"

using namespace std;

namespace sdds {
   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
      std::fstream fileIn(file);
      std::vector<Workstation*> nextStationPtr{};
      try {
         while (!fileIn.eof()) {
            std::string record{};
            Utilities temp{};
            size_t pos{};
            bool more{ true };

            std::string ws{}, nextWs{};

            getline(fileIn, record);   //SHOULD READ A WHOLE LINE
            ws = temp.extractToken(record, pos, more);
            nextWs = temp.extractToken(record, pos, more);

            Workstation* tempStation{};
            tempStation = *(find_if(stations.begin(), stations.end(), [=](Workstation* st) {return st->getItemName() == ws; }));
            m_activeLine.push_back(tempStation);

            if (nextWs.length()) {  //mextWs.length() == 0 -> lest station.
               tempStation = *(find_if(stations.begin(), stations.end(), [=](Workstation* st) {return st->getItemName() == nextWs; }));
               m_activeLine.back()->setNextStation(tempStation);
               nextStationPtr.push_back(tempStation);
            }
         }
         fileIn.close();

         //Find the first one.
         for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* st) {
            if (find(nextStationPtr.begin(), nextStationPtr.end(), st) == nextStationPtr.end()) {
               m_firstStation = st;
            }
            });

         m_cntCustomerOrder = g_pending.size();
      }catch (...) {
         throw std::string("ERROR: Something went wrong in LineManager constructor.");
      }
   }

   void LineManager::reorderStations(){
      vector<Workstation* > temp;
      temp.push_back(m_firstStation);
      for (auto i = 0u; i < m_activeLine.size() - 1; i++) { //Already got first one
         temp.push_back(temp[i]->getNextStation());
      }

      m_activeLine.clear();
      m_activeLine = temp;
   }

   bool LineManager::run(std::ostream& os){
      static size_t itCnt{};
      os << "Line Manager Iteration: " << ++itCnt << endl;

      if (!g_pending.empty()) {
         *m_firstStation += std::move(g_pending.front());
         g_pending.pop_front();
      }

      for (auto i = 0u; i < m_activeLine.size(); i++) {
         m_activeLine[i]->fill(os);
      }

      for (auto i = 0u; i < m_activeLine.size(); i++) {
         m_activeLine[i]->attemptToMoveOrder();
      }

      return (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder ? true : false;
   }

   void LineManager::display(std::ostream& os) const{
      for (auto i = 0u; i < m_activeLine.size(); i++) {
         m_activeLine[i]->display(os);
      }
   }
}